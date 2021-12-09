#pragma once
#include "Business.h"
using namespace std;

class Graph {
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
            while (getline(stream, temp, ','))
            {
                if (temp.at(0) == ' ')
                    temp = temp.substr(1, temp.length() - 1);
                this->categories.insert(temp);
            }
        }
    };

    vector<Vertex*> adjList;
    set<string> states;

public:
    Graph(vector<Business*>& businesses);
    void Print();

    void bfs();
    void bfsState(string state);
    void dfs();
    void dfsState(string state);
};