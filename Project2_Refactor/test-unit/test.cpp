//#include "../AdjacencyList.h"
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//
///*
//	To check output (At the maze_escape directory):
//		g++ -std=c++14 -Werror -Wuninitialized -o test test-unit/test.cpp && ./test
//*/
//
//
//TEST_CASE("Function: Test 1", "[given]")
//{
//
//    AdjacencyList myGraph;
//    myGraph.insertEdge("google.com", "gmail.com");
//    myGraph.insertEdge("google.com", "maps.com");
//    myGraph.insertEdge("facebook.com", "ufl.edu");
//    myGraph.insertEdge("ufl.edu", "google.com");
//    myGraph.insertEdge("ufl.edu", "gmail.com");
//    myGraph.insertEdge("maps.com", "facebook.com");
//    myGraph.insertEdge("gmail.com", "maps.com");
//
//
//    myGraph.powerIterations(3);
//    myGraph.printResults();
//    float result = myGraph.sumPR();
//
//	REQUIRE(result==1);
//}
//
//TEST_CASE("Function: Test 2", "[given]")
//{
//
//    AdjacencyList myGraph;
//    myGraph.insertEdge("google.com", "gmail.com");
//    myGraph.insertEdge("google.com", "maps.com");
//    myGraph.insertEdge("facebook.com", "ufl.edu");
//    myGraph.insertEdge("ufl.edu", "google.com");
//    myGraph.insertEdge("ufl.edu", "gmail.com");
//    myGraph.insertEdge("maps.com", "facebook.com");
//    myGraph.insertEdge("gmail.com", "maps.com");
//    myGraph.insertEdge("youtube.com", "maps.com");
//    myGraph.insertEdge("facebook.com", "maps.com");
//    myGraph.insertEdge("yahoo.com", "maps.com");
//    myGraph.insertEdge("robot.com", "maps.com");
//
//
//
//    myGraph.powerIterations(1);
//    myGraph.printResults();
//    float result = myGraph.sumPR();
//
//    REQUIRE(result==1);
//}
//
//TEST_CASE("Function: Test 3", "[given]")
//{
//
//    AdjacencyList myGraph;
//    myGraph.insertEdge("google.com", "gmail.com");
//    myGraph.insertEdge("google.com", "maps.com");
//    myGraph.insertEdge("facebook.com", "ufl.edu");
//    myGraph.insertEdge("ufl.edu", "google.com");
//    myGraph.insertEdge("ufl.edu", "gmail.com");
//    myGraph.insertEdge("maps.com", "facebook.com");
//    myGraph.insertEdge("gmail.com", "maps.com");
//    myGraph.insertEdge("ufl.edu", "maps.com");
//    myGraph.insertEdge("facebook.com", "maps.com");
//    myGraph.insertEdge("yahoo.com", "maps.com");
//    myGraph.insertEdge("robot.com", "maps.com");
//
//
//
//    myGraph.powerIterations(100);
//
//    float result = myGraph.sumPR();
//    REQUIRE(result==1.0f);
//}
//
//TEST_CASE("Function: Test 4", "[given]")
//{
//
//    AdjacencyList myGraph;
//    myGraph.insertEdge("google.com", "gmail.com");
//    myGraph.insertEdge("facebook.com", "maps.com");
//    myGraph.insertEdge("school.com", "food.com");
//    myGraph.insertEdge("pin.com", "pen.com");
//    myGraph.insertEdge("sleep.com", "pillow.com");
//
//
//
//
//    myGraph.powerIterations(10);
//    myGraph.printResults();
//    float result = myGraph.sumPR();
//    REQUIRE(result==0);
//}
//
//TEST_CASE("Function: Test 5", "[given]")
//{
//
//    AdjacencyList myGraph;
//    myGraph.insertEdge("google.com", "gmail.com");
//    myGraph.insertEdge("gmail.com", "school.com");
//    myGraph.insertEdge("school.com", "gmail.com");
//    myGraph.insertEdge("google.com", "google.com");
//    myGraph.insertEdge("school.com", "google.com");
//
//
//
//
//
//    myGraph.powerIterations(10000);
//    myGraph.printResults();
//    float result = myGraph.sumPR();
//    REQUIRE(result==1);
//}