#include "Graph.h"

Graph::Graph(vector<Business*>& businesses)
{
	//add a vertex to the adjacency list for every business
	for (int i = 0; i < businesses.size(); i++)
	{
		vector<Vertex*> temp;
		Vertex* newVertex = new Vertex(businesses.at(i), temp);
		adjList.push_back(newVertex);

		//insert categories
		allCategories.insert(newVertex->categories.begin(), newVertex->categories.end());
	
		//create an unordered map of states and the businesses in them
		string currState = businesses.at(i)->getState();
		if (states.find(currState) == states.end())
		{
			vector<Vertex*> temp2;
			states.emplace(currState, temp2);
		}
		states[currState].push_back(newVertex);
	}

	for (auto iter = states.begin(); iter != states.end(); iter++)
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			if (iter->second.size() > (2 * i) + 2)
			{
				iter->second.at(i)->adjVertices.push_back(iter->second.at((2 * i) + 2));
				iter->second.at((2 * i) + 2)->adjVertices.push_back(iter->second.at(i));
			}
			if (iter->second.size() > (2 * i) + 1)
			{
				iter->second.at(i)->adjVertices.push_back(iter->second.at((2 * i) + 1));
				iter->second.at((2 * i) + 1)->adjVertices.push_back(iter->second.at(i));
			}
		}
	}
}

set<string> Graph::getStates()
{
	set<string> s;
	for (auto iter = states.begin(); iter != states.end(); iter++)
	{
		s.insert(iter->first);
	}
	return s;
}

set<string> Graph::getAllCategories()
{
	return allCategories;
}

void Graph::PrintStates()
{
	cout << "List of States:" << endl;
	for (auto iter = states.begin(); iter != states.end(); iter++)
	{
		cout << iter->first << endl;
	}
	cout << endl;
}

void Graph::PrintCategories()
{
	cout << "Categories:" << endl;
	for (auto iter = allCategories.begin(); iter != allCategories.end(); iter++)
	{
		cout << *(iter) << endl;
	}
	cout << endl;
}

void Graph::PrintAdjacent() 
{
	cout << "Adjacency List:" << endl;
	for (int i = 0; i < adjList.size(); i++)
	{
		cout << adjList.at(i)->data->getName() << ": " << endl;
		for (Vertex* v : adjList.at(i)->adjVertices)
		{
			cout << v->data->getName() << ", ";
		}
		cout << "\n" << endl;
	}
}

void Graph::bfs()
{
    cout << "BFS: " << endl;
    for (auto st : states)
    {
        bfsState(st.first);
    }
}

void Graph::bfsState(string state)
{
    //method for BFS inspired by Lecture 8b - Graph Traversals and Algorithms
    cout << "BFS of " << state << ":" << endl;
    Vertex* source = states[state].at(0);
    set<Vertex*> visited;
    queue<Vertex*> q;

    visited.insert(source);
    q.push(source);
    int count = 0;
    while (q.empty() == false)
    {
        count++;
        Vertex* front = q.front();
        cout << front->data->getName() << endl;
        q.pop();
        vector<Vertex*> neighbors = front->adjVertices;
        for (Vertex* v : neighbors)
        {
            if (visited.count(v) == 0)
            {
                visited.insert(v);
                q.push(v);
            }
        }
    }
    cout << endl;
}

void Graph::dfs()
{
	cout << "DFS: " << endl;
	for (auto st : states)
	{
		dfsState(st.first);
	}
}

void Graph::dfsState(string state)
{
    //method for DFS inspired by Lecture 8b - Graph Traversals and Algorithms
    Vertex* source = states[state].at(0);
    set<Vertex*> visited;
    stack<Vertex*> s;

    visited.insert(source);
    s.push(source);
	cout << "DFS of " << state << ":" << endl;
    int count = 0;
    while (s.empty() == false)
    {
        count++;
        Vertex* front = s.top();
        cout << front->data->getName() << endl;
        s.pop();
        vector<Vertex*> neighbors = front->adjVertices;
        for (Vertex* v : neighbors)
        {
            if (visited.count(v) == 0)
            {
                visited.insert(v);
                s.push(v);
            }
        }
    }
	cout << endl;
}

//BFS Search
vector<Business*> Graph::findMostSimilarBusiness(set<string>& userCategories)
{
	int highest = 0;
	vector<Business*> similar;
	for (auto st : states)
	{
		Vertex* source = states[st.first].at(0);
		set<Vertex*> visited;
		queue<Vertex*> q;

		visited.insert(source);
		q.push(source);
		int count = 0;
		while (q.empty() == false)
		{
			count++;
			Vertex* front = q.front();
			q.pop();

			int intersection = countIntersection(front->categories, userCategories);
			if (intersection > highest)
			{
				highest = intersection;
				similar.clear();
				similar.push_back(front->data);
			}
			else if (intersection == highest)
			{
				similar.push_back(front->data);
			}
			vector<Vertex*> neighbors = front->adjVertices;
			for (Vertex* v : neighbors)
			{
				if (visited.count(v) == 0)
				{
					visited.insert(v);
					q.push(v);
				}
			}
		}
	}
	if (highest > 1)
	{
		cout << "Most Similar:" << endl;
		for (int i = 0; i < similar.size(); i++)
		{
			similar.at(i)->Print();
		}
		cout << endl;
	}
	else
	{
		cout << "Please select more categories\n" << endl;
		similar.clear();
	}
	return similar;
}

//BFS State Search
vector<Business*> Graph::findMostSimilarBusiness(set<string>& userCategories, string state)
{
	int highest = 0;
	vector<Business*> similar;

	Vertex* source = states[state].at(0);
	set<Vertex*> visited;
	queue<Vertex*> q;

	visited.insert(source);
	q.push(source);
	int count = 0;
	while (q.empty() == false)
	{
		count++;
		Vertex* front = q.front();
		q.pop();

		int intersection = countIntersection(front->categories, userCategories);
		if (intersection > highest)
		{
			highest = intersection;
			similar.clear();
			similar.push_back(front->data);
		}
		else if (intersection == highest)
		{
			similar.push_back(front->data);
		}
		vector<Vertex*> neighbors = front->adjVertices;
		for (Vertex* v : neighbors)
		{
			if (visited.count(v) == 0)
			{
				visited.insert(v);
				q.push(v);
			}
		}
	}
	
	if (highest > 1)
	{
		cout << "Most Similar:" << endl;
		for (int i = 0; i < similar.size(); i++)
		{
			similar.at(i)->Print();
		}
		cout << endl;
	}
	else
	{
		cout << "Please select more categories\n" << endl;
		similar.clear();
	}
	return similar;
}

int Graph::countIntersection(set<string> a, set<string> b)
{
	vector<string> v;
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(v));
	return v.size();
}
