/*
	IntUnitTests.cc - contains unit tests for Vector using integers only
*/
#include "doctest.h"
#include "Vector.h"
#include <utility>

TEST_CASE("push_back")
{
	Vector<int> testVector;
	testVector.push_back(3);
	testVector.push_back(4);
	testVector.push_back(5);
	REQUIRE(testVector[0] == 3);
	REQUIRE(testVector[1] == 4);
	REQUIRE(testVector[2] == 5);
}
TEST_CASE("pop functions")
{
	Vector<int> testVector;
	testVector.push_back(1);
	testVector.push_back(2);
	testVector.push_back(3);
	REQUIRE(testVector[1] == 2);
	REQUIRE(testVector.pop_back() == 3);
	REQUIRE(testVector.pop_front() == 1);
	REQUIRE(testVector[0] == 2);
	REQUIRE(testVector.size() == 1);
}

TEST_CASE("reserve space")
{
	Vector<int> testVector;
	testVector.reserve(64);
	REQUIRE(testVector.capacity() == 64);
	testVector.reserve(32);
	REQUIRE(testVector.capacity() == 32);
}

TEST_CASE("resize")
{
	Vector<int> testVector;
	testVector.push_back(1);
	testVector.resize(5);
	REQUIRE(testVector[4] == 0);
	REQUIRE(testVector.size() == 5);
	testVector.resize(3);
	REQUIRE(testVector.size() == 3);
}

TEST_CASE("equals and bracket operator")
{
	Vector<int> testVector;
	testVector.push_back(1);
	testVector[0] = 6;
	int const x = (testVector = 0);
	REQUIRE(testVector[0] == 6);
	REQUIRE(x == 6);
}

TEST_CASE("copy constructor") // this one is trouble
{
	Vector<int> testVector;
	testVector.push_back(125);
	{
		Vector<int> copyVector = testVector;
		REQUIRE(copyVector[0] == 125);
	}
	REQUIRE(testVector[0] == 125);
}

TEST_CASE("assignment operator")
{
	Vector<int> testVector;
	{
		Vector<int> copyVector;
		copyVector.push_back(125);
		testVector = copyVector;
		REQUIRE(testVector[0] == 125);
	}
	REQUIRE(testVector[0] == 125);
}

TEST_CASE("move constructor")
{
	Vector<int> testVector;
	testVector.push_back(125);
	{
		Vector<int> copyVector = std::move(testVector);
		REQUIRE(copyVector[0] == 125);
	}
	REQUIRE(testVector.size() == 0);
}

TEST_CASE("move assignment operator")
{
	Vector<int> testVector;
	{
		Vector<int> copyVector;
		copyVector.push_back(125);
		testVector =  std::move(copyVector);
		REQUIRE(copyVector.size() == 0);
	}
	REQUIRE(testVector[0] == 125);
}
