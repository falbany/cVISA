#include <gtest/gtest.h>
#include "core/VISACom.hpp"
#include "core/exceptions.hpp"

using namespace cvisa;

class VISAComTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialization before each test
    }
};

TEST_F(VISAComTest, DefaultConstructorState) {
    VISACom com;
    EXPECT_FALSE(com.isConnected());
    EXPECT_EQ(com.getAddress(), "");
}

TEST_F(VISAComTest, SetAddressDisconnected) {
    VISACom com;
    const std::string addr = "GPIB0::1::INSTR";
    com.setAddress(addr);
    EXPECT_EQ(com.getAddress(), addr);
    EXPECT_FALSE(com.isConnected());
}

TEST_F(VISAComTest, SetTimeoutStoresValue) {
    VISACom com;
    com.setTimeout(5000);
    EXPECT_EQ(com.getTimeout(), 5000);
}

TEST_F(VISAComTest, ConnectionFailureWithEmptyAddress) {
    VISACom com;
    EXPECT_THROW(com.connect(), ConnectionException);
}

TEST_F(VISAComTest, MoveConstructorTransfersState) {
    VISACom com;
    com.setAddress("USB0::0x1234::0x5678::MYSERIAL::INSTR");
    com.setTimeout(1500);
    
    VISACom com2(std::move(com));
    EXPECT_EQ(com2.getAddress(), "USB0::0x1234::0x5678::MYSERIAL::INSTR");
    EXPECT_EQ(com2.getTimeout(), 1500);
    EXPECT_EQ(com.getAddress(), ""); // Original should be cleared
}
