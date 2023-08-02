#pragma once
#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include<vector>
#include<iterator>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

class AdjacencyList{
private:
    unordered_map<string, unordered_map<string,float>> graph;
    map<string, float> keys;

public:
    AdjacencyList(){};
    int V(){return graph.size();}//Returns number of vertices
//    int E(); //Returns number of edges
    void insertEdge(string from, string to);
    bool isEdge(string from, string to);
//    vector<int> getAdjacent(int vertex);
    void printGraph();
//    void PageRank(int n);
    void insertRanks();
    void printMatrix(vector<vector<float>> matrix, vector<string> keys);
    vector<float> powerIterations(int n);
    void printResults();
    float sumPR();
    map<string, float> Keys();
};


//Log(n)
void AdjacencyList::insertEdge(string from, string to)
{
    //Simply push the edge into the map, handles duplicates for us O(logn) since ordered map is an RB Tree
    //Initialize the page rank to 0
    graph[from][to] = 0;
    //If to doesn't already exist in the map add it mapping to an empty vector
    if (graph.find(to)==graph.end())
        graph[to] = {};
}

//Prints in basically random order O(V+E)
void AdjacencyList::printGraph()
{
    for (auto i : graph)
    {
        cout << i.first << ": ";
        for(auto j : graph[i.first])
            cout << "(" << j.first << " " << j.second << ") ";
        cout << endl;
    }
}

//O(logV + log(outdegree(V)))?? = O(logV)
bool AdjacencyList::isEdge(std::string from, std::string to)
{
    //If from is in the map and to is in the vector belonging to "to"
    if (graph.count(from)>0 && graph[from].count(to) > 0)
        return true;
    return false;
}
//O(V^2*logV)
void AdjacencyList::insertRanks()
{
    //If an edge exists populate it with the to's outdegree O(logV + outdegree(V))
    for(auto iter = graph.begin(); iter != graph.end(); iter++)
    {
        for (auto jiter = graph[iter->first].begin(); jiter != graph[iter->first].end(); jiter++)
        {
            //Is to -> from and edge?
            if (isEdge(iter->first,jiter->first))
            {
                float value = graph.find(iter->first)->second.size();
                if (value > 0)
                    graph[iter->first][jiter->first] = 1/value;
            }
        }
    }
}

//O(p*Elog(V))
vector<float> AdjacencyList::powerIterations(int n)
{
    //O(V^2logV)
    vector<float> results_matrix(V(), 0);
    vector<float> power_matrix(V(), 1/float(V()));
    unordered_map<string, unordered_map<string,float>> powerGraph = graph;
    int counter = 0;
    //Do the power iterations n-1 times O(p*ElogV)
    if (n > 1)
    {
        //For each power iteration
        for (int p = 0; p < n-1; p++)
        {
            //Iterating through the map of maps O(Elog(V)
            for (auto iter = powerGraph.begin(); iter != powerGraph.end(); iter++)
            {
                //Counter to keep track of which element in the unordered map im on
                //Goes through every key/value pair in each from map
                for (auto jiter = powerGraph[iter->first].begin(); jiter != powerGraph[iter->first].end(); jiter++)
                {
                    //log(V)
                    float value = powerGraph.find(iter->first)->second.size();
                    if (value > 0)
                        jiter->second = 1/value;
                    //Multiply each value by the associated power matrix value
                    jiter->second = jiter->second * power_matrix[counter];
                }
                //Use this loop to also reset the results matrix for the next iteration

                results_matrix[counter] = 0;
                counter ++;
            }
            //Sums accross rows
            //Iterating through the map of maps
            counter = 0;
            //O(Elog(outdegree(V))
            for (auto iter = powerGraph.begin(); iter != powerGraph.end(); iter++)
            {
                //Look to see if the to value exists in every from, if it does add it to the results matrix
                for (auto jiter = powerGraph.begin(); jiter != powerGraph.end(); jiter++)
                {
                    //if the from that wer're searching for exists as a value in a to map add it to the from's results matrix spot
                    if(powerGraph[jiter->first].count(iter->first) > 0)
                        results_matrix[counter] += powerGraph[jiter->first][iter->first];

                }
                keys[iter->first] = results_matrix[counter];
                counter++;
            }
            power_matrix = results_matrix;
            counter = 0;
        }
        return results_matrix;
        //Condition for 0 power iterations
    } else
    {
        for(auto iter = powerGraph.begin(); iter != powerGraph.end(); iter++)
        {
            keys[iter->first] = power_matrix[0];
        }
        return power_matrix;
    }
}

//O(V)
void AdjacencyList::printResults()
{
    int counter = 0;
    for (auto iter = keys.begin(); iter != keys.end(); iter++)
    {
        cout << iter->first << " " << setprecision(2) <<  fixed << iter->second;
        cout << endl;
        counter ++;
    }
}

float AdjacencyList::sumPR()
{
    float result = 0;
    for(auto iter = keys.begin(); iter != keys.end(); iter++)
    {
        result += iter->second;
    }
    return result;
}

map<string, float> AdjacencyList::Keys()
{
    return keys;
}