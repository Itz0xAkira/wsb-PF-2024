#include <gtest/gtest.h>
#include "password_cracker.hpp"

class PasswordCrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for all tests
    }
};

TEST_F(PasswordCrackerTest, ShortPassword) {
    PasswordCracker cracker("abcdefghijklmnopqrstuvwxyz", 4);
    std::string targetPassword = "test";
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    std::string crackedPassword = cracker.crackPassword(verifier);
    EXPECT_EQ(crackedPassword, targetPassword);
}

TEST_F(PasswordCrackerTest, MixedCasePassword) {
    PasswordCracker cracker("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 6);
    std::string targetPassword = "TeSt";
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    std::string crackedPassword = cracker.crackPassword(verifier);
    EXPECT_EQ(crackedPassword, targetPassword);
}

TEST_F(PasswordCrackerTest, AlphanumericPassword) {
    PasswordCracker cracker("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 6);
    std::string targetPassword = "Abc123";
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    std::string crackedPassword = cracker.crackPassword(verifier);
    EXPECT_EQ(crackedPassword, targetPassword);
}

TEST_F(PasswordCrackerTest, PasswordNotFound) {
    PasswordCracker cracker("abcdefghijklmnopqrstuvwxyz", 3);
    std::string targetPassword = "test";  // Longer than max length
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    std::string crackedPassword = cracker.crackPassword(verifier);
    EXPECT_TRUE(crackedPassword.empty());
}

TEST_F(PasswordCrackerTest, ParallelProcessing) {
    PasswordCracker cracker("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 6, true);
    std::string targetPassword = "Xyz789";
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    std::string crackedPassword = cracker.crackPassword(verifier);
    EXPECT_EQ(crackedPassword, targetPassword);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
