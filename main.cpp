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

    //find all Itailian restaurants
    //for (int i = 0; i < businesses.size(); i++)
    //{
    //    //if (businesses[i]->getCategories().find("Italian") != string::npos) //check if specific tag (Italian) is in category
    //    //    cout << businesses[i]->getName() << endl;
    //    businesses.at(i)->Print();
    //}

    //create a graph
    Graph* graph = new Graph(businesses);
    //graph->Print();
    graph->bfsState("FL");

    //Command Line Interface


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