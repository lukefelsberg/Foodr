#pragma once
#include <algorithm>
#include "Business.h"
using namespace std;

class Graph {
public:
    struct Vertex {
        Business* data;
        vector<Vertex*> adjVertices;
        set<string> categories;
        Vertex(Business* data, vector<Vertex*> adjVertices)
        {
            this->data = data;
            this->adjVertices = adjVertices;

            //read the categories
		    istringstream stream(data->getCategories());
		    string temp;
            if (data->getCategories().find("Restaurants") != string::npos)
            {
                while (getline(stream, temp, ','))
                {
                    if (temp.at(0) == ' ')
                        temp = temp.substr(1, temp.length() - 1);
                    this->categories.insert(temp);
                }
            }
        }
    };

    vector<Vertex*> adjList;
    unordered_map<string, vector<Vertex*>> states;
    set<string> allCategories;
	
public:
	Graph(vector<Business*>& businesses);
    set<string> getStates();
    set<string> getAllCategories();
	void PrintStates();
    void PrintCategories();
    void PrintAdjacent();
    void bfs();
    void bfsState(string state);
    void dfs();
    void dfsState(string state);
    vector<Business*> findMostSimilarBusiness(set<string>& userCategories);
    vector<Business*> findMostSimilarBusiness(set<string>& userCategories, string state);
    int countIntersection(set<string> a, set<string> b);
};
