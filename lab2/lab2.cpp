#include <iostream>
#include <vector>
#include <algorithm>  

// Base class
class LabTask {
public:
    virtual void execute() = 0;  // Pure virtual method for derived classes to implement
};

// Derived class for Task 1: Array Comparison
class ArrayComparer : public LabTask {
    std::vector<int> array1, array2;

public:
    ArrayComparer() {
        // You can initialize the arrays with sample data or let the user input the values
        array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        array2 = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    }

    void findCommonElements() {
        std::cout << "Common elements: ";
        for (int num : array1) {
            if (std::find(array2.begin(), array2.end(), num) != array2.end()) {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    void execute() override {
        findCommonElements();
    }
};


class AscendingArray : public LabTask {
    int array[10][10];

public:
    AscendingArray() {
        int value = 1;
        for (int col = 0; col < 10; ++col) {
            for (int row = 0; row < 10; ++row) {
                array[row][col] = value++;
            }
        }
    }

    void displayArray() {
        for (int row = 0; row < 10; ++row) {
            for (int col = 0; col < 10; ++col) {
                std::cout << array[row][col] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void execute() override {
        displayArray();
    }
};


class CaesarCipher : public LabTask {
    int shift;

public:
    CaesarCipher(int shiftValue = 3) : shift(shiftValue) {}

    std::string encrypt(const std::string& text) {
        std::string result = text;
        for (char& c : result) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';
                c = (c - offset + shift) % 26 + offset;
            }
        }
        return result;
    }

    std::string decrypt(const std::string& text) {
        std::string result = text;
        for (char& c : result) {
            if (isalpha(c)) {
                char offset = isupper(c) ? 'A' : 'a';
                c = (c - offset - shift + 26) % 26 + offset;
            }
        }
        return result;
    }

    void execute() override {
        std::string text = "HelloWorld";
        std::cout << "Original Text: " << text << std::endl;
        
        std::string encrypted = encrypt(text);
        std::cout << "Encrypted Text: " << encrypted << std::endl;

        std::string decrypted = decrypt(encrypted);
        std::cout << "Decrypted Text: " << decrypted << std::endl;
    }
};


class StudentGrades : public LabTask {
    std::vector<std::vector<int>> studentGrades;

public:
    StudentGrades() {
        studentGrades.resize(3, std::vector<int>(5));
    }

    void inputGrades() {
        for (int i = 0; i < 3; ++i) {
            std::cout << "Enter 5 grades for student " << i + 1 << ": ";
            for (int j = 0; j < 5; ++j) {
                std::cin >> studentGrades[i][j];
            }
        }
    }

    int calculateSum(const std::vector<int>& grades) {
        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return sum;
    }

    double calculateAverage(const std::vector<int>& grades) {
        return static_cast<double>(calculateSum(grades)) / grades.size();
    }

    double calculateMedian(std::vector<int> grades) {
        std::sort(grades.begin(), grades.end());
        if (grades.size() % 2 == 0) {
            return (grades[grades.size() / 2 - 1] + grades[grades.size() / 2]) / 2.0;
        } else {
            return grades[grades.size() / 2];
        }
    }

    void displayGrades() {
        for (int i = 0; i < 3; ++i) {
            std::cout << "Student " << i + 1 << " Grades:\n";
            std::cout << "Sum: " << calculateSum(studentGrades[i]) << "\n";
            std::cout << "Average: " << calculateAverage(studentGrades[i]) << "\n";
            std::cout << "Median: " << calculateMedian(studentGrades[i]) << "\n";
            std::cout << std::endl;
        }
    }

    void execute() override {
        inputGrades();
        displayGrades();
    }
};


int main() {
    ArrayComparer arrayComparer;
    AscendingArray ascendingArray;
    CaesarCipher caesarCipher;
    StudentGrades studentGrades;

    std::cout << "Select a task:\n1. Array Comparison\n2. 10x10 Ascending Array\n3. Caesar Cipher\n4. Student Grades\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            arrayComparer.execute();
            break;
        case 2:
            ascendingArray.execute();
            break;
        case 3:
            caesarCipher.execute();
            break;
        case 4:
            studentGrades.execute();
            break;
        default:
            std::cout << "Invalid selection!\n";
            break;
    }

    return 0;
}
