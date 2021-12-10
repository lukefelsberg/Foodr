#include "Graph.h"
using namespace std;

void ReadDataFromCSVFile(string filename, vector<Business*>& businesses);
int main()
{
    string filename = "output_delimited_new.csv";
    vector<Business*> businesses;
    set<string> states;
    //method for reading file inspired by COP3503 labs
    ReadDataFromCSVFile(filename, businesses);

    //create a graph
    Graph* graph = new Graph(businesses);
    //graph->PrintStates();
    //graph->PrintAdjacent();
    //graph->PrintCategories();
    //graph->bfsState("CO");
    //graph->bfs();
    //graph->dfs();

    //Command Line Interface
    string input;
    cout << "Welcome to Foodr! A program designed to help you find a restaurant based on your preferences." << endl;
    while (true)
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Search for a similar restaurant in a specific state" << endl;
        cout << "2. Search for a similar restaurant located anywhere" << endl;
        cout << "3. Look at all the states available" << endl;
        cout << "4. Look at all the categories" << endl;
        cout << "5. Exit" << endl;
        getline(cin, input);
        
        set<string> categories;
        set<string> allCategories = graph->getAllCategories();
        if (input == "1")
        {
            cout << "What state would you like to search?" << endl;
            string state = "";
            getline(cin, state);
            set<string> states = graph->getStates();
            if (states.find(state) == states.end())
            {
                cout << "This state is unavaible.\n" << endl;
            }
            else
            {
                cout << "Please enter all the categories you are looking for." << endl;
                cout << "Once you are finished, type \"Exit\"" << endl;
                categories.clear();
                categories.insert("Restaurants");
                while(input != "Exit")
                {
                    getline(cin, input);
                    categories.insert(input);
                }
                cout << "BFS Search" << endl;
                graph->findMostSimilarBusinessBFS(categories, state);
                cout << endl;
                cout << "DFS Search" << endl;
                graph->findMostSimilarBusinessDFS(categories, state);
                cout << endl;
            }
        }
        else if (input == "2")
        {
            cout << "You have chosen to not search a specific state." << endl;
            cout << "Please enter all the categories you are looking for." << endl;
            cout << "Once you are finished, type \"Exit\"" << endl;
            categories.clear();
            categories.insert("Restaurants");
            while (input != "Exit")
            {
                getline(cin, input);
                categories.insert(input);
            }
            cout << "BFS Search" << endl;
            graph->findMostSimilarBusinessBFS(categories);
            cout << endl;
            cout << "DFS Search" << endl;
            graph->findMostSimilarBusinessDFS(categories);
            cout << endl;
        }
        else if (input == "3")
        {
            graph->PrintStates();
        }
        else if (input == "4")
        {
            graph->PrintCategories();
        }
        else if (input == "5")
        {
            cout << "Goodbye, have a nice day!" << endl;
            break;
        }
        else
        {
            cout << "Invalid input.\n" << endl;
        }
    }

    return 0;
}

void ReadDataFromCSVFile(string filename, vector<Business*>& businesses)
{
    ifstream YelpDataset(filename);

    string lineFromFile;
    getline(YelpDataset, lineFromFile);

    //restuarant data members
    string name;
    string address;
    string city;
    string state;
    string postalCode;
    string stars; 
    string categories;

    while (getline(YelpDataset, lineFromFile))
    {
        istringstream stream(lineFromFile);
        getline(stream, name, '|');
        getline(stream, address, '|');
        getline(stream, city, '|');
        getline(stream, state, '|');
        getline(stream, postalCode, '|');
        getline(stream, stars, '|');
        getline(stream, categories); //last item

        businesses.push_back(new Business(name, address, city, state, postalCode, stars, categories)); //for testing purposes
    }
}