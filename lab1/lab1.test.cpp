#include <gtest/gtest.h>
#include "lab1.cpp" 


TEST(GuessingGameTest, SimulatedGuesses) {
    GuessingGame game;
    game.setTargetNumber(50); 

    testing::internal::CaptureStdout(); 
    game.simulateGuess(30); 
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Value is too small!\n");

    testing::internal::CaptureStdout();
    game.simulateGuess(70); 
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Value is too big!\n");

    testing::internal::CaptureStdout();
    game.simulateGuess(50); 
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Correct! You guessed the number.\n");
}


TEST(CalculatorTest, BasicOperations) {
    Calculator<double> calc;

    EXPECT_DOUBLE_EQ(calc.add(5.0, 3.0), 8.0);
    EXPECT_DOUBLE_EQ(calc.subtract(10.0, 4.0), 6.0);
    EXPECT_DOUBLE_EQ(calc.multiply(3.0, 7.0), 21.0);

    EXPECT_THROW(calc.divide(10.0, 0.0), std::runtime_error); 
}


TEST(EvenOddCheckerTest, CheckEvenOdd) {
    EvenOddChecker checker;

    testing::internal::CaptureStdout();
    checker.check(4); 
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "4 is even.\n");

    testing::internal::CaptureStdout();
    checker.check(7); 
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "7 is odd.\n");
}


TEST(ChangeCalculatorTest, CalculateChange) {
    ChangeCalculator changeCalc;

    testing::internal::CaptureStdout();
    changeCalc.calculateChange(85, 100);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Total change: 15") != std::string::npos);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}