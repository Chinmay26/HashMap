/*
 * functionality_tests.cpp
 *
 *  Created on: Sep 11, 2017
 *  Author: chinmay naik
 */

#include<iostream>
#include<cassert>
#include<unordered_set>
#include "../tests/HashMap.h"
using namespace std;

struct MyHashCompute {
	size_t operator()(const string &key, const int  &hashSize=1000) const
	{
		return std::hash<std::string>() (key) % hashSize;
	}
};

int main(){

	// Test basic initialization
	cout << endl << "Test 1: Basic Initialization";
	MyHashMap<std::string,int,MyHashCompute> h(5);
	assert(sizeof(h));
	cout << " : Pass" << endl;

	// Validate HashMap Set, Get , Delete operations
	cout << endl << "Test 2: Basic Hash Map operations";
	//size_t S = 20;
	MyHashMap<std::string,int,MyHashCompute> hmap(5);
	bool res = false;
	int val;
	// HashMap SET operations
	res =  hmap.set("coursera",2012);
	assert(res == true);
	res = hmap.set("airware",2011);
	assert(res == true);
	res = hmap.set("drawbridge",2014);
	assert(res == true);
	res = hmap.set("stripe",2010);
	assert(res == true);
	// Insert Same key
	res = hmap.set("stripe",2010);
	assert(res == false);

	// HashMap GET operations
	val = hmap.get("coursera");
	assert(val == 2012);
	try{
		//Invalid key
		val = hmap.get("flipboard");
	}
	catch (const std::invalid_argument& e){
		//do nothing
		;
	}
	// HashMap DELETE operations
	val = hmap.delete_key("stripe");
	assert(val == 2010);
	try{
		//Invalid key
		val = hmap.delete_key("stripe");
	}
	catch (const std::invalid_argument& e){
		//do nothing
		;
	}
	cout << " : Pass" << endl;

	// Test Hash Table allocation when size is exceeded
	cout << endl <<  "Test 3: Hash size exceeded" ;
	MyHashMap<std::string,int,MyHashCompute> cmap(5);
	bool ret = false;
	ret =  cmap.set("coursera",2012);
	assert(ret == true);
	ret = cmap.set("airware",2011);
	assert(ret == true);
	ret = cmap.set("drawbridge",2014);
	assert(ret == true);
	ret = cmap.set("stripe",2010);
	assert(ret == true);
	ret = cmap.set("uber",2010);
	assert(ret == true);
	// Inserting 6th element in a hash of size 5
	ret = cmap.set("doordash",2010);
	assert(ret == false);
	cout << " : Pass" << endl;


	//Evaluate the correctness of Hash Collisions
	cout << endl << "Test 4: Hash Collision: Linear probing evaluation";
	MyHashMap<std::string,int,MyHashCompute> lmap(5);
	bool r = false;
	r = lmap.set("stripe",2011);
	assert(r == true);
	r = lmap.set("drawbridge",2014);
	assert(r == true);
	size_t s1 = lmap.get_hashed_value("stripe");
	size_t s2 = lmap.get_hashed_value("drawbridge");
	// the hash value generated for keys are the same
	assert(s1 == s2);
	// the key values should be adjacent
	int s3 = lmap.get_array_index("stripe");
	int s4 = lmap.get_array_index("drawbridge");
	assert(abs(s3 - s4) == 1);
	cout << " : Pass" << endl;

	// Evaluate the correctness of the load factor
	cout << endl << "Test 5: Load Factor evaluation";
	MyHashMap<std::string,int,MyHashCompute> zmap(5);
	bool rt = false;
	rt = zmap.set("uber",2011);
	assert(rt == true);
	float f = zmap.load();
	assert( f == float(0.2));
	rt = zmap.set("doordash",2014);
	assert(rt == true);
	f = zmap.load();
	assert( f == float(0.4));
	val = zmap.delete_key("uber");
	assert(val == 2011);
	f = zmap.load();
	assert( f == float(0.2));
	cout << " : Pass" << endl;

	// Validate delete flags : Refer http://www.cs.rmit.edu.au/online/blackboard/chapter/05/documents/contribute/chapter/05/linear-probing.html
	cout << endl << "Test 6: Hash table pollution testing ";
	MyHashMap<std::string,int,MyHashCompute> dmap(5);
	bool rd = false;
	rd = dmap.set("airware",2011);
	assert(rd == true);
	rd = dmap.set("drawbridge",2014);
	assert(rd == true);
	rd = dmap.set("doordash",2014);
	assert(rd == true);
	rd = dmap.set("stripe",2010);
	assert(rd == true);
	val = dmap.delete_key("doordash");
	assert(val == 2014);
	val = dmap.get("stripe");
	assert(val == 2010);
	val = dmap.delete_key("drawbridge");
	assert(val == 2014);
	val = dmap.get("stripe");
	assert(val == 2010);
	val = dmap.delete_key("airware");
	assert(val == 2011);
	val = dmap.get("stripe");
	assert(val == 2010);
	rd = dmap.set("drawbridge",2014);
	assert(rd == true);
	val = dmap.get("stripe");
	assert(val == 2010);
	cout << " : Pass" << endl;


	// Generate random key values and checking the performance of the hashmap
	cout << endl << "Test 7: Performance Testing Results : ";
	size_t P = 1000000;
	// Generate random strings of length 10
	static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	string sample(10,' ');
	int collison_count = 0;
	unordered_set<int> hset;

	MyHashMap<std::string,int,MyHashCompute> pmap(P);
	for(size_t i=0; i < P/2; i++){
		for (size_t i = 0; i < 10; i++) {
			sample[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		size_t h = pmap.get_hashed_value(sample);
		//cout << sample << " " << h << endl;
		if (hset.find(h) != hset.end()) collison_count += 1;
		else hset.insert(h);
	}
	cout << "Detected " << collison_count << " collisions from total " << P/2 << " elements";
	// Results hover around ~20% collision rate
	return 0;


}

