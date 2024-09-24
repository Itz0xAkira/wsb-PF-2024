#include <gtest/gtest.h>
#include "lab2.cpp" 

// Test for ArrayComparer
TEST(ArrayComparerTest, FindCommonElements) {
    ArrayComparer comparer;
    
    testing::internal::CaptureStdout();
    comparer.execute(); 
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Common elements: 5 6 7 8 9 10") != std::string::npos);
}

// Test for AscendingArray
TEST(AscendingArrayTest, DisplayArray) {
    AscendingArray ascendingArray;

    testing::internal::CaptureStdout(); 
    ascendingArray.execute(); 
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("1\t2\t3\t4\t5\t6\t7\t8\t9\t10") != std::string::npos);
}


TEST(CaesarCipherTest, EncryptDecrypt) {
    CaesarCipher cipher(3); 

    std::string original = "HelloWorld";
    std::string encrypted = cipher.encrypt(original);
    std::string decrypted = cipher.decrypt(encrypted);

    EXPECT_EQ(encrypted, "KhoorZruog"); 
    EXPECT_EQ(decrypted, original); 
}

// Test for StudentGrades
TEST(StudentGradesTest, CalculateGrades) {
    StudentGrades grades;

    
    grades.inputGrades(); 

    testing::internal::CaptureStdout(); 
    grades.execute(); 

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Sum:") != std::string::npos); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}