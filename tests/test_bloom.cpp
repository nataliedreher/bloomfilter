// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Bloom.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_Bloom : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_Bloom::total_grade = 0;
double test_Bloom::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_Bloom, InitTable){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100, 4);
  ASSERT_TRUE(fltr);
  add_points_to_grade(1);
  ASSERT_EQ(fltr->size, 100);
  add_points_to_grade(1);
  //ASSERT_TRUE(fltr->table);
  //add_points_to_grade(1);
  ASSERT_EQ(fltr->hashes, 4);
  add_points_to_grade(1);
  ASSERT_EQ(fltr->elements, 0);
  add_points_to_grade(1);
  for (unsigned int i=0; i < fltr->size; i++) {
    ASSERT_FALSE(fltr->table[i]);
    add_points_to_grade(0.1);
  }
}

TEST_F(test_Bloom, Hash){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100, 4);
  vector<int> test_hash_values = mybloom.Hash("banana",fltr);
  vector<int> hash_values; 
  hash_values.push_back(28);
  hash_values.push_back(94);
  hash_values.push_back(74);
  hash_values.push_back(18);
  ASSERT_EQ(test_hash_values.size(), 4);
  add_points_to_grade(1);
  //ASSERT_TRUE(fltr->table);
  //add_points_to_grade(1);
  ASSERT_EQ(fltr->elements, 0);
  add_points_to_grade(1);
  for (unsigned int i=0; i < 4; i++) {
    ASSERT_EQ(test_hash_values[i],hash_values[i]);
    add_points_to_grade(0.5);
  }
}


TEST_F(test_Bloom, AddToBloom){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100, 4);
  mybloom.AddToBloom(fltr,"banana");
  vector<int> hash_values; 
  ASSERT_EQ(fltr->elements, 0);
  add_points_to_grade(1);
  for (unsigned int i=0; i < 4; i++) {
    if (i != 28 || i != 94 || i != 74 || i != 18) {
		ASSERT_FALSE(fltr->table[i]);
    	add_points_to_grade(0.1);
	} else {
		ASSERT_TRUE(fltr->table[i]);
    	add_points_to_grade(0.5);
	}
  }
}