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
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);
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
    ASSERT_FALSE(fltr->bitTable[i]);
    add_points_to_grade(0.1);
  }
}

TEST_F(test_Bloom, InitTableAuto){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100,true);
  ASSERT_TRUE(fltr);
  add_points_to_grade(1);
  ASSERT_EQ(fltr->size, 100);
  add_points_to_grade(1);
  //ASSERT_TRUE(fltr->table);
  //add_points_to_grade(1);
  ASSERT_EQ(fltr->hashes, 7);
  add_points_to_grade(1);
  ASSERT_EQ(fltr->elements, 0);
  add_points_to_grade(1);
  for (unsigned int i=0; i < fltr->size; i++) {
    ASSERT_FALSE(fltr->bitTable[i]);
    add_points_to_grade(0.1);
  }
}

TEST_F(test_Bloom, Hash){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);
  vector<int> test_hash_values = mybloom.Hash("banana",fltr);
  vector<int> hash_values; 
  hash_values.push_back(71);
  hash_values.push_back(5);
  hash_values.push_back(85);
  hash_values.push_back(43);
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
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);
  mybloom.AddToBloom(fltr,"banana"); 
  ASSERT_EQ(fltr->elements, 1);
  add_points_to_grade(1);
  for (unsigned int i=0; i < 4; i++) {
    if (i != 28 || i != 94 || i != 74 || i != 18) {
      ASSERT_FALSE(fltr->bitTable[i]);
      add_points_to_grade(0.1);
    } else {
      ASSERT_TRUE(fltr->bitTable[i]);
      add_points_to_grade(0.5);
    }
  }
}

TEST_F(test_Bloom, BigAddToBloom){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);

  string users_array[20] = {"Ambiteri", "BinderJunky", "ClassyFamous", "Cyberlogy", "EternalComic", "Eyestaffer", "Flirtypwri", "Fozoanog", "InfernoBorg", "Jiggyttom", "Lawnwolfer", "Mitzillst", "Netikaem", "Noamigr", "Phreeksteb", "PrimeSpy", "Rockstonera", "RunFlirty", "Shadesntha", "Twinkle"};
  for (int i = 0; i < 20; i++) {
    mybloom.AddToBloom(fltr,users_array[i]);
  }
  
  ASSERT_EQ(fltr->elements, 20);
  add_points_to_grade(1);
  ASSERT_FALSE(mybloom.IsUsernamePossiblyAvailable(fltr,"ClassyFamous"));
  add_points_to_grade(1);
  ASSERT_FALSE(mybloom.IsUsernamePossiblyAvailable(fltr,"InfernoBorg"));
  add_points_to_grade(1);
  ASSERT_FALSE(mybloom.IsUsernamePossiblyAvailable(fltr,"RunFlirty"));
  add_points_to_grade(1);
  float test_value = .1;
  int count = 0;
  string test_users_array[20] = {"AnimeGoofy", "Annonscregi", "BoaRight", "ChilledStoop", "Cookyloring", "Darklinote", "DiddyTastic", "Greehoptio", "Grommerli", "Helpfulonda", "HiBear", "Informerch", "Listworkem", "Martzing", "MegaVampire", "Mjetwickso", "NameWonderRun", "NightHood", "Scanneme", "SlayrXcaptain"};
  for (unsigned int i=0; i < 20; i++) {
    bool found = true;
    vector<int> hash_values = mybloom.Hash(test_users_array[i], fltr);
    for (int j = 0; j < 4; j++) {
      if (!fltr->bitTable[hash_values[j]]) {
        found = false;
        break;
      }
    }
    if (found)  {
      count++;
    }
  }
  float percent_true = count / 100.000;
  ASSERT_LE(percent_true, test_value);
  add_points_to_grade(2);
}


TEST_F(test_Bloom, AutoAddToBloom){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(200,true);

  string users_array[20] = {"Ambiteri", "BinderJunky", "ClassyFamous", "Cyberlogy", "EternalComic", "Eyestaffer", "Flirtypwri", "Fozoanog", "InfernoBorg", "Jiggyttom", "Lawnwolfer", "Mitzillst", "Netikaem", "Noamigr", "Phreeksteb", "PrimeSpy", "Rockstonera", "RunFlirty", "Shadesntha", "Twinkle"};
  for (int i = 0; i < 20; i++) {
    mybloom.AddToBloom(fltr,users_array[i]);
  }
  
  ASSERT_EQ(fltr->elements, 20);
  add_points_to_grade(1);
  ASSERT_FALSE(mybloom.IsUsernamePossiblyAvailable(fltr,"ClassyFamous"));
  add_points_to_grade(1);

  
  int count = 0;
  string test_users_array[20] = {"AnimeGoofy", "Annonscregi", "BoaRight", "ChilledStoop", "Cookyloring", "Darklinote", "DiddyTastic", "Greehoptio", "Grommerli", "Helpfulonda", "HiBear", "Informerch", "Listworkem", "Martzing", "MegaVampire", "Mjetwickso", "NameWonderRun", "NightHood", "Scanneme", "SlayrXcaptain"};
  for (unsigned int i=0; i < 20; i++) {
    bool found = true;
    vector<int> hash_values = mybloom.Hash(test_users_array[i], fltr);
    int num_hashes = fltr->hashes;
    for (int j = 0; j < num_hashes; j++) {
      if (!fltr->bitTable[hash_values[j]]) {
        found = false;
        break;
      }
    }
    if (found)  {
      count++;
    }
  }
  float test_value = 0.0083;
  float percent_true = count / 100.0000;
  ASSERT_LE(percent_true, test_value);
  add_points_to_grade(2);
}


TEST_F(test_Bloom, IsUsernamePossiblyAvailable){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);
  mybloom.AddToBloom(fltr,"banana");
  
  ASSERT_FALSE(mybloom.IsUsernamePossiblyAvailable(fltr,"banana"));
  add_points_to_grade(1);
  ASSERT_TRUE(mybloom.IsUsernamePossiblyAvailable(fltr,"apple"));
  add_points_to_grade(1);
}



TEST_F(test_Bloom, FalsePositiveChance){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);

  string users_array[20] = {"Ambiteri", "BinderJunky", "ClassyFamous", "Cyberlogy", "EternalComic", "Eyestaffer", "Flirtypwri", "Fozoanog", "InfernoBorg", "Jiggyttom", "Lawnwolfer", "Mitzillst", "Netikaem", "Noamigr", "Phreeksteb", "PrimeSpy", "Rockstonera", "RunFlirty", "Shadesntha", "Twinkle"};
  for (int i = 0; i < 20; i++) {
    mybloom.AddToBloom(fltr,users_array[i]);
  }
  float test_value = .0920;
  ASSERT_LE(mybloom.FalsePositiveChance(fltr),test_value);
  add_points_to_grade(1);
  test_value = .0918;
  ASSERT_GE(mybloom.FalsePositiveChance(fltr),test_value);
  add_points_to_grade(1);

}


TEST_F(test_Bloom, Clear){
  Bloom mybloom;
  shared_ptr<bloom_filter> fltr = mybloom.InitTable(100);
  mybloom.AddToBloom(fltr,"banana");
  vector<int> hash_values; 
  add_points_to_grade(1);
  for (unsigned int i=0; i < 4; i++) {
    if (i != 28 || i != 94 || i != 74 || i != 18) {
      ASSERT_FALSE(fltr->bitTable[i]);
    } else {
      ASSERT_TRUE(fltr->bitTable[i]);
    }
  }
  mybloom.Clear(fltr);
  for (unsigned int i=0; i < 4; i++) {
    ASSERT_FALSE(fltr->bitTable[i]);  
    add_points_to_grade(0.1);
  }
}