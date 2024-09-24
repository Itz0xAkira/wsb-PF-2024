#include <gtest/gtest.h>
#include "lab4.cpp" 

// Test for PointTask
TEST(PointTaskTest, InputAndDisplayPoints) {
    PointTask pointTask;

    testing::internal::CaptureStdout();
    pointTask.inputPoints(3);
    pointTask.displayPoints();
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Displaying Points:") != std::string::npos); 
}

// Test for DynamicArrayTask
TEST(DynamicArrayTaskTest, CreateAndDisplayArray) {
    DynamicArrayTask dynamicArray;

    dynamicArray.createArray(3, 4); 

    testing::internal::CaptureStdout();
    dynamicArray.displayArray();
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Dynamically allocated 2D array:") != std::string::npos);
}

// Test for BuildingTask
TEST(BuildingTaskTest, AddAndDisplayBuildingInfo) {
    BuildingTask buildingTask;

    testing::internal::CaptureStdout(); 
    buildingTask.execute();
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Building Address: 123 Example Street") != std::string::npos); 
}

// Test for BuildingTask with multiple residents
TEST(BuildingTaskTest, MultipleResidentsInfo) {
    BuildingTask buildingTask;

    buildingTask.addTestData(); 

    testing::internal::CaptureStdout(); 
    buildingTask.displayBuildingInfo(); 
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Room Number: 101") != std::string::npos); 
}


TEST(PointTaskTest, MemoryManagement) {
    PointTask pointTask;
    
    ASSERT_NO_THROW(pointTask.execute()); 
}


TEST(DynamicArrayTaskTest, MemoryManagement) {
    DynamicArrayTask dynamicArray;
    
    ASSERT_NO_THROW(dynamicArray.execute()); 
}


TEST(BuildingTaskTest, MemoryManagement) {
    BuildingTask buildingTask;
    
    ASSERT_NO_THROW(buildingTask.execute()); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}