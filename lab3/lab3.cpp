#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Base class
class LabTask {
public:
    virtual void execute() = 0;  // Pure virtual method for derived classes to implement
};

// Task 1: People Structure
class PeopleStructure : public LabTask {
    struct Person {
        std::string name;
        int age;
        std::string city;
    };
    std::vector<Person> people;

public:
    void inputData() {
        for (int i = 0; i < 3; ++i) {
            Person p;
            std::cout << "Enter name for person " << i + 1 << ": ";
            std::cin >> p.name;
            std::cout << "Enter age for " << p.name << ": ";
            std::cin >> p.age;
            std::cout << "Enter city for " << p.name << ": ";
            std::cin >> p.city;
            people.push_back(p);
        }
    }

    void displayData() {
        for (const auto& p : people) {
            std::cout << "Name: " << p.name << ", Age: " << p.age << ", City: " << p.city << std::endl;
        }
    }

    void execute() override {
        inputData();
        displayData();
        std::cout << "Note: We cannot use a union for this task because a union can only hold one of its members at a time, "
                  << "while we need to store multiple fields (name, age, city) simultaneously for each person." << std::endl;
    }
};

// Task 2: Bidirectional List
class BidirectionalList : public LabTask {
    struct Node {
        int value;
        Node* prev;
        Node* next;
        Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    BidirectionalList() : head(nullptr), tail(nullptr) {
        for (int i = 0; i <= 10; ++i) {
            Node* newNode = new Node(i);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }

    void displayReverse() {
        Node* current = tail;
        while (current) {
            std::cout << current->value << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    void execute() override {
        std::cout << "Bidirectional list values from end to start: ";
        displayReverse();
    }

    ~BidirectionalList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Task 3: Family Tree
class FamilyTree : public LabTask {
    struct FamilyMember {
        std::string name;
        FamilyMember* father;
        FamilyMember* mother;
        FamilyMember(const std::string& n) : name(n), father(nullptr), mother(nullptr) {}
    };
    FamilyMember* child;

public:
    FamilyTree() {
        child = new FamilyMember("Child");
        child->father = new FamilyMember("Father");
        child->mother = new FamilyMember("Mother");
    }

    void displayFamily() {
        std::cout << "Child: " << child->name << std::endl;
        std::cout << "Father: " << child->father->name << std::endl;
        std::cout << "Mother: " << child->mother->name << std::endl;
    }

    void execute() override {
        displayFamily();
    }

    ~FamilyTree() {
        delete child->father;
        delete child->mother;
        delete child;
    }
};

// Task 4: Sorted Person List
class SortedPersonList : public LabTask {
    struct Person {
        std::string name;
        int age;
        Person* next;
        Person(const std::string& n, int a) : name(n), age(a), next(nullptr) {}
    };
    Person* head;

public:
    SortedPersonList() : head(nullptr) {}

    void addPerson(const std::string& name, int age) {
        Person* newPerson = new Person(name, age);
        if (!head || head->age > age) {
            newPerson->next = head;
            head = newPerson;
        } else {
            Person* current = head;
            while (current->next && current->next->age <= age) {
                current = current->next;
            }
            newPerson->next = current->next;
            current->next = newPerson;
        }
    }

    void displayList() {
        Person* current = head;
        while (current) {
            std::cout << "Name: " << current->name << ", Age: " << current->age << std::endl;
            current = current->next;
        }
    }

    void execute() override {
        addPerson("Alice", 18);
        addPerson("Bob", 35);
        addPerson("Charlie", 21);
        addPerson("David", 44);
        addPerson("Eve", 27);

        std::cout << "Sorted list of persons:" << std::endl;
        displayList();
    }

    ~SortedPersonList() {
        Person* current = head;
        while (current) {
            Person* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    PeopleStructure task1;
    BidirectionalList task2;
    FamilyTree task3;
    SortedPersonList task4;

    std::cout << "Select a task:\n1. People Structure\n2. Bidirectional List\n3. Family Tree\n4. Sorted Person List\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            task1.execute();
            break;
        case 2:
            task2.execute();
            break;
        case 3:
            task3.execute();
            break;
        case 4:
            task4.execute();
            break;
        default:
            std::cout << "Invalid selection!\n";
            break;
    }

    return 0;
}