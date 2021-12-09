#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Business
{
    string name;
    string address;
    string city;
    string state;
    string postalCode;
    string stars;
    string categories;

    //written to include only necessary attributes- name, city/state, lat/long, stars, attributes, catergories
    //passing by reference to save memory; values won't be changed
public:
    Business(string& _name, string& _address, string& _city, string& _state, string& _postalCode, string& _stars, string& _categories)
    {
        name = _name;
        address = _address;
        city = _city;
        state = _state;
        postalCode = _postalCode;
        stars = _stars;
        categories = _categories;
    }

    string getName()
    {
        return name;
    }
    string getAddress()
    {
        return address;
    }
    string getCity()
    {
        return city;
    }
    string getState()
    {
        return state;
    }
    string getStars()
    {
        return stars;
    }
    string getCategories()
    {
        return categories;
    }
    void Print()
    {
        cout << "Name: " << name << endl;
        cout << "Address: " << address << ", " << city << ", " << state << endl;
    }
};