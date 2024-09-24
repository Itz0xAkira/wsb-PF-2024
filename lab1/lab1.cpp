#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <ctime>


class LabTask {
public:
    virtual void execute() = 0;  // Pure virtual method to be overridden by derived classes
};


class GuessingGame : public LabTask {
    int targetNumber;

public:
    GuessingGame() {
        srand(time(0));  
        targetNumber = rand() % 100 + 1;  
    }

    void setTargetNumber(int number) {
        targetNumber = number;  
    }

    void simulateGuess(int guess) {
        if (guess < targetNumber) {
            std::cout << "Value is too small!\n";
        } else if (guess > targetNumber) {
            std::cout << "Value is too big!\n";
        } else {
            std::cout << "Correct! You guessed the number.\n";
        }
    }

    void execute() override {
        int guess;
        std::cout << "Guess a number between 1 and 100: ";
        while (true) {
            std::cin >> guess;
            if (guess < targetNumber) {
                std::cout << "Value is too small!\n";
            } else if (guess > targetNumber) {
                std::cout << "Value is too big!\n";
            } else {
                std::cout << "Correct! You guessed the number.\n";
                break;
            }
        }
    }
};


template <typename T>
class Calculator : public LabTask {
    std::vector<std::string> history;

public:
    T add(T num1, T num2) {
        T result = num1 + num2;
        history.push_back("Added: " + std::to_string(num1) + " + " + std::to_string(num2) + " = " + std::to_string(result));
        return result;
    }

    T subtract(T num1, T num2) {
        T result = num1 - num2;
        history.push_back("Subtracted: " + std::to_string(num1) + " - " + std::to_string(num2) + " = " + std::to_string(result));
        return result;
    }

    T multiply(T num1, T num2) {
        T result = num1 * num2;
        history.push_back("Multiplied: " + std::to_string(num1) + " * " + std::to_string(num2) + " = " + std::to_string(result));
        return result;
    }

    T divide(T num1, T num2) {
        if (num2 == 0) {
            throw std::runtime_error("Cannot divide by zero!");
        }
        T result = num1 / num2;
        history.push_back("Divided: " + std::to_string(num1) + " / " + std::to_string(num2) + " = " + std::to_string(result));
        return result;
    }

    void showHistory() {
        std::cout << "Operation History:\n";
        for (const auto& entry : history) {
            std::cout << entry << std::endl;
        }
    }

    void execute() override {
        T num1, num2;
        int choice;
        char cont;

        do {
            std::cout << "Enter first number: ";
            std::cin >> num1;

            std::cout << "Enter second number: ";
            std::cin >> num2;

            std::cout << "Choose an operation:\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n";
            std::cin >> choice;

            try {
                switch (choice) {
                    case 1:
                        std::cout << "Result: " << add(num1, num2) << std::endl;
                        break;
                    case 2:
                        std::cout << "Result: " << subtract(num1, num2) << std::endl;
                        break;
                    case 3:
                        std::cout << "Result: " << multiply(num1, num2) << std::endl;
                        break;
                    case 4:
                        std::cout << "Result: " << divide(num1, num2) << std::endl;
                        break;
                    default:
                        std::cout << "Invalid operation!\n";
                }
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            std::cout << "Do you want to perform another operation? (y/n): ";
            std::cin >> cont;

        } while (cont == 'y');

        showHistory();
    }
};


class EvenOddChecker : public LabTask {
public:
    void check(int number) {
        if (number % 2 == 0) {
            std::cout << number << " is even.\n";
        } else {
            std::cout << number << " is odd.\n";
        }
    }

    void execute() override {
        int number;
        std::cout << "Enter a number to check if it's even or odd: ";
        std::cin >> number;
        check(number);
    }
};

class ChangeCalculator : public LabTask {
public:
    void calculateChange(int payable, int given) {
        int change = given - payable;
        if (change < 0) {
            std::cout << "Not enough money provided.\n";
            return;
        }

        std::vector<int> denominations = {100, 50, 20, 10, 5, 1};
        std::vector<int> result(denominations.size(), 0);

        std::cout << "Total change: " << change << "\n";
        for (size_t i = 0; i < denominations.size(); ++i) {
            result[i] = change / denominations[i];
            change %= denominations[i];
        }

        for (size_t i = 0; i < denominations.size(); ++i) {
            std::cout << denominations[i] << ": " << result[i] << "\n";
        }
    }

    void execute() override {
        int payable, given;
        std::cout << "Enter the amount to pay: ";
        std::cin >> payable;

        std::cout << "Enter the amount given: ";
        std::cin >> given;

        calculateChange(payable, given);
    }
};


int main() {
    GuessingGame guessingGame;
    Calculator<double> calculator;
    EvenOddChecker evenOddChecker;
    ChangeCalculator changeCalculator;

    char EventChoice;
    do
    {
        int choice;
        std::cout << "Select a task:\n1. Guessing Game\n2. Calculator\n3. Even or Odd Checker\n4. Change Calculator\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            guessingGame.execute();
            break;
        case 2:
            calculator.execute();
            break;
        case 3:
            evenOddChecker.execute();
            break;
        case 4:
            changeCalculator.execute();
            break;
        default:
            std::cout << "Invalid selection!\n";
            break;
        }
    
        std::cout << "Do you want to choose a different Program? (y/n): ";
        std::cin >> EventChoice;
    } while (EventChoice == 'y');
    
    return 0;
}

