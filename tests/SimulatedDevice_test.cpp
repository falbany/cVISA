#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/core/VISACom.hpp"
#include "../src/core/SimulatedVISABackend.hpp"
#include "../src/core/SimulationConfig.hpp"
#include <memory>
#include <filesystem>

/**
 * @file SimulatedDevice_test.cpp
 * @brief Unit tests for YAML-based simulation backend
 * 
 * Tests the YAML configuration system and simulation backend integration
 * for testing SCPI drivers without real hardware.
 */

namespace fs = std::filesystem;

/**
 * @brief Test fixture for YAML simulation tests
 */
class YamlSimulationTest : public ::testing::Test {
protected:
    std::unique_ptr<cvisa::SimulatedVISABackend> backend;
    std::string configDir;
    
    void SetUp() override {
        backend = std::make_unique<cvisa::SimulatedVISABackend>();
        
        // Find config directory (relative to source)
        configDir = std::string(CMAKE_SOURCE_DIR) + "/src/drivers";
    }
    
    std::string getTestConfigPath(const std::string& filename) {
        return configDir + "/" + filename;
    }
};

/**
 * @test Test YAML config parsing
 */
TEST_F(YamlSimulationTest, ParseAgilent66xxAConfig) {
    // Skip if config file doesn't exist (might not be present in all environments)
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    auto config = cvisa::simulation::loadConfig(configPath);
    
    // Verify basic config structure
    EXPECT_FALSE(config.spec_version.empty());
    EXPECT_FALSE(config.device_name.empty());
    EXPECT_FALSE(config.device_model.empty());
    EXPECT_GT(config.dialogues.size(), 0);
    
    // Verify some expected dialogues exist
    bool hasIdn = false;
    bool hasVOLT = false;
    for (const auto& dialogue : config.dialogues) {
        if (dialogue.query == "*IDN?") hasIdn = true;
        if (dialogue.query == "VOLTage?") hasVOLT = true;
    }
    EXPECT_TRUE(hasIdn);
    EXPECT_TRUE(hasVOLT);
}

/**
 * @test Test TA5000 config parsing
 */
TEST_F(YamlSimulationTest, ParseTA5000Config) {
    std::string configPath = getTestConfigPath("thermalair_ta5000.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    auto config = cvisa::simulation::loadConfig(configPath);
    
    EXPECT_FALSE(config.spec_version.empty());
    EXPECT_FALSE(config.device_name.empty());
    EXPECT_GT(config.dialogues.size(), 0);
    
    // Verify some TA5000-specific dialogues
    bool hasFAN = false;
    bool hasTEMP = false;
    for (const auto& dialogue : config.dialogues) {
        if (dialogue.query == "FAN?") hasFAN = true;
        if (dialogue.query == "TEMP?") hasTEMP = true;
    }
    EXPECT_TRUE(hasFAN);
    EXPECT_TRUE(hasTEMP);
}

/**
 * @test Test device creation from config
 */
TEST_F(YamlSimulationTest, CreateDeviceFromConfig) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    // Load and create device
    auto device = cvisa::simulation::loadDevice(configPath);
    
    // Verify device has dialogues
    EXPECT_GT(device.processQuery("*IDN?").length(), 0);
    EXPECT_GT(device.processQuery("VOLTage?").length(), 0);
}

/**
 * @test Test resource registration with YAML config
 */
TEST_F(YamlSimulationTest, RegisterResourceFromYaml) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    // Register device from config
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    // Verify device is registered
    EXPECT_TRUE(backend->hasResource("GPIB0::5::INSTR"));
    EXPECT_EQ(backend->getDeviceCount(), 1);
}

/**
 * @test Test multiple resources from single config
 */
TEST_F(YamlSimulationTest, RegisterMultipleResourcesFromYaml) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    std::vector<std::string> resources = {
        "GPIB0::5::INSTR",
        "TCPIP0::192.168.1.100::inst0::INSTR",
        "USB0::0x2A8D::0x0001::SN00000001::INSTR"
    };
    
    // Register multiple resources from same config
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        resources
    );
    
    // Verify all resources are registered
    for (const auto& resource : resources) {
        EXPECT_TRUE(backend->hasResource(resource));
    }
    EXPECT_EQ(backend->getDeviceCount(), 1);  // Same device, multiple resources
}

/**
 * @test Test connection to YAML-configured device
 */
TEST_F(YamlSimulationTest, ConnectToYamlDevice) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    cvisa::VISACom com(backend.get(), true);  // true = VISACom takes ownership
    EXPECT_NO_THROW(com.connect("GPIB0::5::INSTR"));
    EXPECT_TRUE(com.isConnected());
    com.disconnect();
}

/**
 * @test Test SCPI query-response with YAML config
 */
TEST_F(YamlSimulationTest, QueryResponseWithYaml) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    cvisa::VISACom com(backend.get(), true);
    com.connect("GPIB0::5::INSTR");
    
    // Test identity query
    std::string idn = com.query("*IDN?");
    EXPECT_THAT(idn, ::testing::HasSubstr("Keysight"));
    EXPECT_THAT(idn, ::testing::HasSubstr("6641A"));
    
    // Test voltage query
    std::string voltage = com.query("VOLTage?");
    EXPECT_THAT(voltage, ::testing::HasSubstr("5"));
    
    // Test output query
    std::string output = com.query("OUTPut?");
    EXPECT_THAT(output, ::testing::HasSubstr("ON"));
    
    com.disconnect();
}

/**
 * @test Test write command (no response) with YAML config
 */
TEST_F(YamlSimulationTest, WriteCommandWithYaml) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    cvisa::VISACom com(backend.get(), true);
    com.connect("GPIB0::5::INSTR");
    
    // These should not throw
    EXPECT_NO_THROW(com.write("VOLTage 10.0"));
    EXPECT_NO_THROW(com.write("CURRent 1.5"));
    EXPECT_NO_THROW(com.write("OUTPut 1"));
    EXPECT_NO_THROW(com.write("*RST"));
    
    com.disconnect();
}

/**
 * @test Test pattern matching in YAML config
 */
TEST_F(YamlSimulationTest, PatternMatchingFromYaml) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    cvisa::VISACom com(backend.get(), true);
    com.connect("GPIB0::5::INSTR");
    
    // Pattern "VOLTage *" should match any voltage set command
    EXPECT_NO_THROW(com.write("VOLTage 5.0"));
    EXPECT_NO_THROW(com.write("VOLTage 10.0"));
    EXPECT_NO_THROW(com.write("VOLTage 15.0"));
    
    com.disconnect();
}

/**
 * @test Test multiple devices from different YAML configs
 */
TEST_F(YamlSimulationTest, MultipleDevicesFromYamlConfigs) {
    std::string agilentConfig = getTestConfigPath("agilent66xxA.yaml");
    std::string taConfig = getTestConfigPath("thermalair_ta5000.yaml");
    
    if (!fs::exists(agilentConfig) || !fs::exists(taConfig)) {
        GTEST_SKIP() << "Config files not found";
    }
    
    // Load two different devices
    auto agilentDevice = cvisa::simulation::loadDevice(agilentConfig);
    auto taDevice = cvisa::simulation::loadDevice(taConfig);
    
    backend->registerDevice("GPIB0::5::INSTR", agilentDevice);
    backend->registerDevice("GPIB0::10::INSTR", taDevice);
    
    cvisa::VISACom com(backend.get(), true);
    
    // Test Agilent device
    com.connect("GPIB0::5::INSTR");
    std::string idn1 = com.query("*IDN?");
    EXPECT_THAT(idn1, ::testing::HasSubstr("Keysight"));
    com.disconnect();
    
    // Test TA5000 device
    com.connect("GPIB0::10::INSTR");
    std::string idn2 = com.query("*IDN?");
    EXPECT_THAT(idn2, ::testing::HasSubstr("Thermal Air"));
    com.disconnect();
}

/**
 * @test Test unknown command returns empty response
 */
TEST_F(YamlSimulationTest, UnknownCommandReturnsEmpty) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    cvisa::simulation::loadAndRegister(
        backend.get(),
        configPath,
        "GPIB0::5::INSTR"
    );
    
    cvisa::VISACom com(backend.get(), true);
    com.connect("GPIB0::5::INSTR");
    
    // Query for something not in the config
    std::string response = com.query("UNKNOWN:COMMAND?");
    EXPECT_EQ(response, "\n");  // Just the newline terminator
    
    com.disconnect();
}

/**
 * @test Test error handling for invalid config
 */
TEST_F(YamlSimulationTest, InvalidConfigFile) {
    std::string invalidPath = "nonexistent/file.yaml";
    
    EXPECT_THROW(
        cvisa::simulation::loadConfig(invalidPath),
        std::runtime_error
    );
}

/**
 * @test Test complete workflow: load, register, connect, verify
 */
TEST_F(YamlSimulationTest, CompleteWorkflow) {
    std::string configPath = getTestConfigPath("agilent66xxA.yaml");
    if (!fs::exists(configPath)) {
        GTEST_SKIP() << "Config file not found: " << configPath;
    }
    
    // Step 1: Load config
    auto config = cvisa::simulation::loadConfig(configPath);
    EXPECT_FALSE(config.dialogues.empty());
    
    // Step 2: Create device from config
    auto device = cvisa::simulation::configToDevice(config);
    EXPECT_GT(device.processQuery("*IDN?").length(), 0);
    
    // Step 3: Register with backend
    backend->registerDevice("GPIB0::5::INSTR", device);
    EXPECT_TRUE(backend->hasResource("GPIB0::5::INSTR"));
    
    // Step 4: Connect and test
    cvisa::VISACom com(backend.get(), true);
    com.connect("GPIB0::5::INSTR");
    
    // Verify multiple commands
    EXPECT_THAT(com.query("*IDN?"), ::testing::HasSubstr("Keysight"));
    EXPECT_THAT(com.query("VOLTage?"), ::testing::HasSubstr("5"));
    EXPECT_EQ(com.query("OUTPut?"), "ON\n");
    
    com.disconnect();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
