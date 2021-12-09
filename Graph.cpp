#include "Graph.h"

Graph::Graph(vector<Business*>& businesses)
{
	set<int> visited;
	//add a vertex to the adjacency list for every business
	for (int i = 0; i < businesses.size(); i++)
	{
		vector<Vertex*> temp;
		adjList.push_back(new Vertex(businesses.at(i), temp));
	}

	//build the graph, by attaching adjacent vertices
	for (int i = 0; i < adjList.size(); i++)
	{
		Vertex* current = adjList.at(i);
		vector<Vertex*> tempAdj;
		//keeps track of visited vertices
		visited.insert(i);
		states.insert(current->data->getState()); //keeps track of states

		//visit all the vertices after i
		for (int j = i + 1; j < adjList.size(); j++)
		{
			//if the current vertex is in the same state as another vertex that hasn't been visited,
			//add it to the current vertex's adjacent businesses
			if (current->data->getState() == adjList.at(j)->data->getState() && visited.count(0)==0)
			{
				adjList.at(i)->adjVertices.push_back(adjList.at(j));
				visited.insert(j);
				adjList.at(j)->adjVertices.push_back(current);
			}

			//if the current vertex is attached to 4 or more adjacent businesses at, move to the next vertex
			if (adjList.at(i)->adjVertices.size() >= 4)
				break;
		}
	}
}

void Graph::Print()
{
	for (int i = 0; i < adjList.size(); i++)
	{
		//prints vertices and their adjacent vertices
		//cout << adjList.at(i)->data->getName() << ": " << endl;
		//for (Vertex* v : adjList.at(i)->adjVertices)
		//{
		//	cout << v->data->getName() << ", ";
		//}
		//cout << "\n" << endl;

		//prints categories
		cout << i << ": ";
		for (auto iter = adjList.at(i)->categories.begin(); iter != adjList.at(i)->categories.end(); iter++)
		{
			cout << *iter << ", ";
		}
		cout << endl;
	}

	//prints list of states
	cout << "List of States:" << endl;
	for (auto iter = states.begin(); iter != states.end(); iter++)
	{
		cout << *iter << endl;
	}
}

void Graph::bfs()
{
	for (auto st : states)
	{
		int position;
		for (int i = 0; i < adjList.size(); i++)
		{
			if (adjList[i]->data->getState() == st)
			{
				position = i;
				break;
			}
		}

		//method for BFS inspired by Lecture 8b - Graph Traversals and ALgorithms

		Vertex* source = adjList[position];

		set<Vertex*> visited;
		queue<Vertex*> q;

		visited.insert(source);
		q.push(source);
		cout << "BFS: " << endl;
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
	}
}

void Graph::bfsState(string state)
{
	int position;
	for (int i = 0; i < adjList.size(); i++)
	{
		if (adjList[i]->data->getState() == state)
		{
			position = i;
			break;
		}
	}

	//method for BFS inspired by Lecture 8b - Graph Traversals and ALgorithms

	Vertex* source = adjList[position];

	set<Vertex*> visited;
	queue<Vertex*> q;

	visited.insert(source);
	q.push(source);
	cout << "BFS: " << endl;
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

	



}

void Graph::dfs()
{
	for (auto st : states)
	{
		int position;
		for (int i = 0; i < adjList.size(); i++)
		{
			if (adjList[i]->data->getState() == st)
			{
				position = i;
				break;
			}
		}

		//method for DFS inspired by Lecture 8b - Graph Traversals and ALgorithms

		Vertex* source = adjList[position];

		set<Vertex*> visited;
		stack<Vertex*> s;

		visited.insert(source);
		s.push(source);
		cout << "BFS: " << endl;
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
					q.push(v);
				}

			}
		}
	}
}

void Graph::dfsState(string state)
{
	int position;
	for (int i = 0; i < adjList.size(); i++)
	{
		if (adjList[i]->data->getState() == state)
		{
			position = i;
			break;
		}
	}

	//method for DFS inspired by Lecture 8b - Graph Traversals and ALgorithms

	Vertex* source = adjList[position];

	set<Vertex*> visited;
	stack<Vertex*> s;

	visited.insert(source);
	s.push(source);
	cout << "DFS: " << endl;
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

}