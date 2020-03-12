#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <regex>
#include <ctime>


const std::string CURL = "curl";

const std::string PLACES_URL = "https://maps.googleapis.com/maps/api/place/findplacefromtext/json?";

const std::string API_KEY = "AIzaSyDn0JQkcfEOZzjRZMzA1mH3ETU9iN8gA1U";

const std::string KEY = "key=";	

const std::string PHOTOS_URL = "https://maps.googleapis.com/maps/api/place/photo?maxwidth=400";

const std::string REFERENCE = "photoreference=";

const std::string FLAGS = "-L --silent";

std::string INPUT = "input=";

std::string INPUT_TYPE = "inputtype=textquery&fields=photos,formatted_address,name,rating,opening_hours,geometry";


int main (int argv, char** argc) {

	if (argv < 2) {

		std::cout << "USAGE: ./a.out [\"Search term\"] \n";

		return 1;

	}

	std::string input_string = argc[1];

	std::regex space(" ");	

	auto chopped = std::regex_replace (input_string, space, "%20");

	//std::cout << chopped << "\n";

	auto command = CURL + " " + "\"" + PLACES_URL + (INPUT + chopped) + "&" + INPUT_TYPE + "&" + KEY + API_KEY + "\"";

	//std::cout << command << "\n";

	system((command + " | jq-linux64 '.candidates[].photos[].photo_reference' > ref.txt").c_str());

	std::cout << (command + " | jq-linux64 '.candidates[].photos[].photo_reference' > ref.txt").c_str() << "\n";

	std::ifstream files;

	files.open("ref.txt");

	auto new_cmd = CURL + " " + "\"" + PHOTOS_URL + "&" + REFERENCE + "&" + KEY + API_KEY;

	if (!files.is_open()) std::cout << "Error reading file.\n";

	int xx= 0;

	while (!files.eof() || !files.fail()) {

		std::string input;

		files >> input;			

  
		try {

			auto x = input.substr(1, input.length() - 2);

			auto new_cmd = CURL + " " + FLAGS +  " " + "\"" + PHOTOS_URL + "&" + REFERENCE + x + "&" + KEY + API_KEY + "\"";

			time_t now = time(0);

			char* dt = ctime(&now);			
	
	   		// convert now to tm struct for UTC
   			tm *gmtm = gmtime(&now);

   			dt = asctime(gmtm);

			std::string name = std::string("\"") + dt + std::to_string(xx) + ".jpeg\"";

			std::string POP =  (new_cmd + " > " + name);

			const char* p = POP.c_str();

			std::cout << p << "\n";

			system (p);
		
		}

		catch (...) {}

		++xx;

	}	

}

