#include "doctest.h"

#include "Vector.h"
#include "BadCon.h"
struct testCpy {
	bool flags[125];
	bool *careFlag;
};

TEST_CASE("Character Vector")
{
	Vector<char> testVector;
	testVector.push_back('a');
	testVector.push_back('b');
	testVector.push_back('c');
	CHECK(testVector[0] == 'a');
	CHECK(testVector.pop_back() == 'c');
}

TEST_CASE("Double Vector")
{
	Vector<double> testVector;
	testVector.push_back(1.4);
	testVector.push_back(8.4);
	testVector.push_back(1.25);
	CHECK(testVector[0] == 1.4);
	CHECK(testVector.pop_back() == 1.25);
}

TEST_CASE("BadCon")
{
	Vector<BadCon> testVector;
	BadCon testObject = BadCon(125);
	testVector.push_back(testObject);
	REQUIRE(testVector[0] == testObject);
	testVector.resize(6);
}

TEST_CASE("Copy Memory")
{
	Vector<testCpy> testVector;
	testCpy testObject;
	testObject.flags[1] = true;
	testObject.careFlag = testObject.flags + 1;
	testVector.push_back(testObject);
	testVector.push_back(testObject); // calling reserve
	REQUIRE(*(testVector[0].careFlag));
}