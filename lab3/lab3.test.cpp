#include <gtest/gtest.h>
#include "lab3.cpp"

// Test for PeopleStructure
TEST(PeopleStructureTest, InputAndDisplayData) {
    PeopleStructure people;
    
    
    testing::internal::CaptureStdout(); 
    people.inputData(); 
    people.displayData();
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Name:") != std::string::npos); 
}

// Test for BidirectionalList
TEST(BidirectionalListTest, DisplayReverse) {
    BidirectionalList bidirectionalList;

    testing::internal::CaptureStdout(); 
    bidirectionalList.execute(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("10 9 8 7 6 5 4 3 2 1 0") != std::string::npos); 
}

// Test for FamilyTree
TEST(FamilyTreeTest, DisplayFamily) {
    FamilyTree familyTree;

    testing::internal::CaptureStdout(); 
    familyTree.execute(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Child: Child") != std::string::npos); 
    EXPECT_TRUE(output.find("Father: Father") != std::string::npos); 
}

// Test for SortedPersonList
TEST(SortedPersonListTest, AddAndDisplayPersons) {
    SortedPersonList sortedList;

    sortedList.addPerson("Alice", 30);
    sortedList.addPerson("Bob", 25);
    sortedList.addPerson("Charlie", 35);

    testing::internal::CaptureStdout(); 
    sortedList.execute(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Name: Bob, Age: 25") != std::string::npos);
    EXPECT_TRUE(output.find("Name: Alice, Age: 30") != std::string::npos); 
}

// Test for SortedPersonList with more entries
TEST(SortedPersonListTest, MultipleEntries) {
    SortedPersonList sortedList;

    sortedList.addPerson("David", 44);
    sortedList.addPerson("Eve", 27);
    
    testing::internal::CaptureStdout(); 
    sortedList.execute(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Name: Eve, Age: 27") != std::string::npos); 
}

// Test for Bidirectional List with empty initialization
TEST(BidirectionalListTest, EmptyInitialization) {
    BidirectionalList emptyList; 

    testing::internal::CaptureStdout(); 
    emptyList.execute(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Bidirectional list values from end to start: ") != std::string::npos); 
}

// Test for PeopleStructure with specific inputs (mocking input)
TEST(PeopleStructureTest, MockInputData) {
    PeopleStructure people;
    
    people.inputData();

    EXPECT_EQ(people.getPeopleCount(), 3); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}