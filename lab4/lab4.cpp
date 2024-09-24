#include <iostream>
#include <vector>
#include <string>

// Base class for Lab 4 tasks
class LabTask {
public:
    virtual void execute() = 0;  // Pure virtual method
};

// Derived class for Task 1: Points
class PointTask : public LabTask {
    struct Point {
        int* x;
        int* y;
    };

    std::vector<Point*>* points;  // Pointer to a vector of pointers to Points

public:
    PointTask() {
        points = new std::vector<Point*>;  // Dynamically allocate the vector
    }

    ~PointTask() {
        for (auto& point : *points) {
            delete point->x;
            delete point->y;
            delete point;  // Free each point
        }
        delete points;  // Free the vector
    }

    void inputPoints(int count) {
        for (int i = 0; i < count; ++i) {
            Point* p = new Point;
            p->x = new int;
            p->y = new int;
            std::cout << "Enter coordinates for point " << i + 1 << " (X Y): ";
            std::cin >> *p->x >> *p->y;
            points->push_back(p);
        }
    }

    void displayPoints() {
        std::cout << "Displaying Points:\n";
        for (const auto& point : *points) {
            std::cout << "Point (X: " << *point->x << ", Y: " << *point->y << ")\n";
        }
    }

    void execute() override {
        int* count = new int;
        std::cout << "How many points do you want to create? ";
        std::cin >> *count;

        inputPoints(*count);
        displayPoints();

        delete count;  // Free count
    }
};

// Derived class for Task 2: Dynamically Allocated 2D Array
class DynamicArrayTask : public LabTask {
    int** array;  // Pointer to a dynamically allocated 2D array
    int* rows;
    int* cols;

public:
    DynamicArrayTask() : array(nullptr), rows(new int(0)), cols(new int(0)) {}

    ~DynamicArrayTask() {
        if (array != nullptr) {
            for (int i = 0; i < *rows; ++i) {
                delete[] array[i];  // Free each row
            }
            delete[] array;  // Free the array of pointers
        }
        delete rows;
        delete cols;
    }

    void createArray(int r, int c) {
        *rows = r;
        *cols = c;
        array = new int*[*rows];
        for (int i = 0; i < *rows; ++i) {
            array[i] = new int[*cols];
        }

        // Fill the array with odd numbers
        int value = 1;
        for (int i = 0; i < *rows; ++i) {
            for (int j = 0; j < *cols; ++j) {
                array[i][j] = value;
                value += 2;  // Ensure it's odd
            }
        }
    }

    void displayArray() {
        std::cout << "Dynamically allocated 2D array:\n";
        for (int i = 0; i < *rows; ++i) {
            for (int j = 0; j < *cols; ++j) {
                std::cout << array[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void execute() override {
        std::cout << "Enter the number of rows: ";
        std::cin >> *rows;
        std::cout << "Enter the number of columns: ";
        std::cin >> *cols;

        createArray(*rows, *cols);
        displayArray();
    }
};

// Derived class for Task 3: Buildings and Residents
class BuildingTask : public LabTask {
    struct Resident {
        int* roomNumber;
        int* numberOfResidents;
        double* rent;
    };

    struct Building {
        std::string* address;
        std::vector<Resident*>* residents;
    };

    Building* building;

public:
    BuildingTask() {
        building = new Building;
        building->address = new std::string;
        building->residents = new std::vector<Resident*>;
    }

    ~BuildingTask() {
        delete building->address;
        for (auto& resident : *building->residents) {
            delete resident->roomNumber;
            delete resident->numberOfResidents;
            delete resident->rent;
            delete resident;
        }
        delete building->residents;
        delete building;
    }

    void addTestData() {
        *building->address = "123 Example Street";
        building->residents->push_back(new Resident{new int(101), new int(2), new double(1200.50)});
        building->residents->push_back(new Resident{new int(102), new int(3), new double(1300.00)});
        building->residents->push_back(new Resident{new int(103), new int(1), new double(1100.75)});
    }

    void displayBuildingInfo() {
        std::cout << "Building Address: " << *building->address << "\n";
        std::cout << "Residents Info:\n";
        for (const auto& resident : *building->residents) {
            std::cout << "Room Number: " << *resident->roomNumber
                      << ", Number of Residents: " << *resident->numberOfResidents
                      << ", Rent: $" << *resident->rent << "\n";
        }
    }

    void execute() override {
        addTestData();
        displayBuildingInfo();
    }
};

// Main function
int main() {
    PointTask* pointTask = new PointTask();
    DynamicArrayTask* dynamicArrayTask = new DynamicArrayTask();
    BuildingTask* buildingTask = new BuildingTask();

    std::cout << "Select a task:\n1. Create and display points\n2. Dynamically allocate 2D array\n3. Building and residents info\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            pointTask->execute();
            break;
        case 2:
            dynamicArrayTask->execute();
            break;
        case 3:
            buildingTask->execute();
            break;
        default:
            std::cout << "Invalid selection!\n";
            break;
    }

    delete pointTask;
    delete dynamicArrayTask;
    delete buildingTask;

    return 0;
}
