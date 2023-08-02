//
#include "AdjacencyList.h"
int main() {
    /*Brain Storming
    Need to insert first url as a key if it doesnt already exist in the map (store in set first)
     and add the second to the value vector
    */

    int no_of_lines, power_iterations;
    set<string> tos;
    AdjacencyList myGraph;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;
    for(int i = 0; i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        myGraph.insertEdge(from, to);
    }
    //myGraph.insertRanks();
    //myGraph.printGraph();
    myGraph.powerIterations(power_iterations);
    myGraph.printResults();



    return 0;
}