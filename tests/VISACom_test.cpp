#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/VISACom.hpp"
#include "core/exceptions.hpp"
#include "MockVISABackend.hpp"

using namespace cvisa;
using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::DoAll;
using ::testing::StrEq;
using ::testing::Invoke;

// --- Category: Mocked VISA Tests ---
class VISAComMockedTest : public ::testing::Test {
protected:
    MockVISABackend* mockBackend;
    VISACom* com;

    void SetUp() override {
        mockBackend = new MockVISABackend();
        // com takes ownership of mockBackend
        com = new VISACom(mockBackend, true);
    }

    void TearDown() override {
        delete com;
    }
};

TEST_F(VISAComMockedTest, SuccessfulConnection) {
    const std::string resourceName = "GPIB0::1::INSTR";
    ViSession rmSession = 1;
    ViSession instSession = 2;

    EXPECT_CALL(*mockBackend, visaOpenDefaultRM(_))
        .WillOnce(DoAll(SetArgPointee<0>(rmSession), Return(VI_SUCCESS)));
    
    EXPECT_CALL(*mockBackend, visaOpen(rmSession, StrEq(resourceName), _, _, _))
        .WillOnce(DoAll(SetArgPointee<4>(instSession), Return(VI_SUCCESS)));

    // applyConfiguration calls
    EXPECT_CALL(*mockBackend, visaSetAttribute(_, _, _)).Times(::testing::AtLeast(0));

    com->connect(resourceName);
    EXPECT_TRUE(com->isConnected());
}

TEST_F(VISAComMockedTest, ConnectionFailure) {
    const std::string resourceName = "GPIB0::1::INSTR";

    EXPECT_CALL(*mockBackend, visaOpenDefaultRM(_))
        .WillOnce(Return(VI_ERROR_SYSTEM_ERROR));

    EXPECT_THROW(com->connect(resourceName), ConnectionException);
    EXPECT_FALSE(com->isConnected());
}

TEST_F(VISAComMockedTest, WriteCommand) {
    const std::string command = "*IDN?";
    ViSession instSession = 2;
    
    // Setup connection first
    EXPECT_CALL(*mockBackend, visaOpenDefaultRM(_)).WillOnce(DoAll(SetArgPointee<0>(1), Return(VI_SUCCESS)));
    EXPECT_CALL(*mockBackend, visaOpen(_, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(instSession), Return(VI_SUCCESS)));
    com->connect("DUMMY");

    EXPECT_CALL(*mockBackend, visaWrite(instSession, _, static_cast<ViUInt32>(command.length()), _))
        .WillOnce(Return(VI_SUCCESS));

    EXPECT_NO_THROW(com->write(command));
}

TEST_F(VISAComMockedTest, ReadCommand) {
    ViSession instSession = 2;
    const std::string response = "HEWLETT-PACKARD,6632B,0,A.01.05\n";
    
    // Setup connection
    EXPECT_CALL(*mockBackend, visaOpenDefaultRM(_)).WillOnce(DoAll(SetArgPointee<0>(1), Return(VI_SUCCESS)));
    EXPECT_CALL(*mockBackend, visaOpen(_, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(instSession), Return(VI_SUCCESS)));
    com->connect("DUMMY");

    EXPECT_CALL(*mockBackend, visaRead(instSession, _, _, _))
        .WillOnce([response](ViSession, ViPBuf buf, ViUInt32, ViPUInt32 retCount) {
            std::copy(response.begin(), response.end(), buf);
            *retCount = static_cast<ViUInt32>(response.length());
            return VI_SUCCESS;
        });

    std::string result = com->read();
    EXPECT_EQ(result, response);
}

// --- Category: Lifecycle Tests ---
class VISAComLifecycle : public ::testing::Test {};

TEST_F(VISAComLifecycle, DefaultConstructorState) {
    VISACom com;
    EXPECT_FALSE(com.isConnected());
    EXPECT_EQ(com.getAddress(), "");
    EXPECT_EQ(com.getTimeout(), 0);
}

TEST_F(VISAComLifecycle, MoveConstructorTransfersState) {
    VISACom com;
    com.setAddress("USB0::0x1234::0x5678::MYSERIAL::INSTR");
    com.setTimeout(1500);
    
    VISACom com2(std::move(com));
    EXPECT_EQ(com2.getAddress(), "USB0::0x1234::0x5678::MYSERIAL::INSTR");
    EXPECT_EQ(com2.getTimeout(), 1500);
    EXPECT_EQ(com.getAddress(), ""); 
    EXPECT_FALSE(com.isConnected());
}

TEST_F(VISAComLifecycle, MoveAssignmentTransfersState) {
    VISACom com;
    com.setAddress("TCPIP0::192.168.1.1::INSTR");
    com.setTimeout(2000);

    VISACom com2;
    com2 = std::move(com);
    EXPECT_EQ(com2.getAddress(), "TCPIP0::192.168.1.1::INSTR");
    EXPECT_EQ(com2.getTimeout(), 2000);
    EXPECT_EQ(com.getAddress(), "");
}

// --- Category: Configuration Tests ---
class VISAComConfig : public ::testing::Test {};

TEST_F(VISAComConfig, SetAddressDisconnected) {
    VISACom com;
    const std::string addr = "GPIB0::1::INSTR";
    com.setAddress(addr);
    EXPECT_EQ(com.getAddress(), addr);
    EXPECT_FALSE(com.isConnected());
}

TEST_F(VISAComConfig, SetTimeoutStoresValue) {
    VISACom com;
    com.setTimeout(5000);
    EXPECT_EQ(com.getTimeout(), 5000);
}

TEST_F(VISAComConfig, SetReadTermination) {
    VISACom com;
    com.setReadTermination('\r', true);
    com.setReadTermination('\n', false);
}

TEST_F(VISAComConfig, SetWriteTermination) {
    VISACom com;
    com.setWriteTermination('\r');
}

TEST_F(VISAComConfig, SetVerbose) {
    VISACom com;
    com.setVerbose(LogLevel::DEBUG);
    com.setVerbose(LogLevel::NONE);
}

TEST_F(VISAComConfig, EnableAutoErrorCheck) {
    VISACom com;
    com.enableAutoErrorCheck(true);
    com.enableAutoErrorCheck(false);
}

// --- Category: Connection Tests ---
class VISAComConnection : public ::testing::Test {};

TEST_F(VISAComConnection, ConnectionFailureWithEmptyAddress) {
    VISACom com;
    EXPECT_THROW(com.connect(), ConnectionException);
}

TEST_F(VISAComConnection, ConnectOverloadThrowsWhenEmpty) {
    VISACom com;
    EXPECT_THROW(com.connect(""), ConnectionException);
}

TEST_F(VISAComConnection, SetAddressThrowsWhenConnected) {
    // Note: Mocking needed for full connection tests
}

// --- Category: I/O Error Handling (Disconnected) ---
class VISAComIOErrors : public ::testing::Test {};

TEST_F(VISAComIOErrors, WriteThrowsWhenDisconnected) {
    VISACom com;
    EXPECT_THROW(com.write("*IDN?"), ConnectionException);
}

TEST_F(VISAComIOErrors, WriteBinaryThrowsWhenDisconnected) {
    VISACom com;
    std::vector<uint8_t> data = {0x01, 0x02, 0x03};
    EXPECT_THROW(com.writeBinary(data), ConnectionException);
}

TEST_F(VISAComIOErrors, ReadThrowsWhenDisconnected) {
    VISACom com;
    EXPECT_THROW(com.read(), ConnectionException);
}

TEST_F(VISAComIOErrors, ReadBinaryThrowsWhenDisconnected) {
    VISACom com;
    EXPECT_THROW(com.readBinary(100), ConnectionException);
}

TEST_F(VISAComIOErrors, QueryThrowsWhenDisconnected) {
    VISACom com;
    EXPECT_THROW(com.query("*IDN?"), ConnectionException);
}
