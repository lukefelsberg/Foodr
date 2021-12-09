#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;



struct Business
{
	//string business_id;
	string name;
	string address;
	string city;
	string state;
	string postal_code;
	float latitude;
	float longitude;
	string stars;
	//string review_count;
	//bool isOpen;
	string attributes;
	string categories;
	string hours;


	//written to include only necessary attributes- name, city/state, lat/long, stars, attributes, catergories
	//passing by reference to save memory; values won't be changed
	Business(string& _name, string _address, string& _city, string& _state, string& postalCode, float& _lat, float& _long, string& _stars, string& _attributes, string& _categories, string _hours)
	{
		name = _name;
		address = _address;
		city = _city;
		state = _state;
		latitude = _lat;
		longitude = _long;
		stars = _stars;
		attributes = _attributes;
		categories = _categories;
		hours = _hours;
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
	float getLat()
	{
		return latitude;
	}
	float getLong()
	{
		return longitude;
	}
	string getStars()
	{
		return stars;
	}
	string getAttributes()
	{
		return attributes;
	}
	string getCategories()
	{
		return categories;
	}
	string getHours()
	{
		return hours;
	}
};



int main()
{
	//method for reading file inspired by COP3503 labs

	ifstream YelpDataset("output_delimited.csv");
	ofstream outFile("output_delimited_new.csv");

	string lineFromFile;
	getline(YelpDataset, lineFromFile);

	//restuarant data members
	string name;
	string address;
	string city;
	string state;
	string postalCode;
	string tempLatitude;
	float latitude;
	string tempLongitude;
	float longitude;
	string stars;
	string attributes; //simply save whole thing as string, use substr method to see if specific tag is present (example below)
	string categories; //^
	string hours;

	vector<Business> businesses;

	int count = 0;
	int countNew = 0;

	//set<string> set1;

	while(getline(YelpDataset, lineFromFile))
	{
		istringstream stream(lineFromFile);

		getline(stream, name, '|');
		getline(stream, address, '|');
		getline(stream, city, '|');
		getline(stream, state, '|');
		getline(stream, postalCode, '|');
		getline(stream, tempLatitude, '|');
		latitude = stof(tempLatitude);
		getline(stream, tempLongitude, '|');
		longitude = stof(tempLongitude);
		getline(stream, stars, '|');
		getline(stream, attributes, '|');
		getline(stream, categories, '|');
		getline(stream, hours); //last item


		Business business(name, address, city, state, postalCode, latitude, longitude, stars, attributes, categories, hours);


		businesses.push_back(business); //for testing purposes
		auto check = businesses[count].getCategories();


		//to filter out non-restaurant data
		if ((check.find("Spas") == std::string::npos) && (check.find("Education") == std::string::npos) && (check.find("Pets") == std::string::npos) && (check.find("Automotive") == std::string::npos) && (check.find("Bank") == std::string::npos) && (check.find("Fitness") == std::string::npos) && (check.find("Thrift") == std::string::npos) && (check.find("Electronics") == std::string::npos) && (check.find("Tobacco") == std::string::npos) && (check.find("Medical") == std::string::npos) && (check.find("Real Estate") == std::string::npos))
		{
			outFile << lineFromFile << endl;
			countNew++;
		}


		count++;
	}

	cout << count << " " << countNew << endl;
	//resulted in a 160,000 -> 104,000 change in data sets

	return 0;

}