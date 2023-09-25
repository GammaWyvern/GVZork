#pragma once

#include <iostream>
#include <string>
#include <vector>

class Item {
	public:
		Item(std::string name, std::string desc, float calories, float weight);
		friend std::ostream & operator << (std::ostream &out, const Item &item); 
	private:
		std::string name; 
		std::string desc; 
		float calories;
		float weight;
};

class NPC {
	public:
		NPC(std::string name, std::string desc);
		friend std::ostream & operator << (std::ostream &out, const NPC &npc);
		std::string getName();
		std::string getDesc();
		std::string getMessage();
	private:
		std::string name;
		std::string desc;
		int messageNum;
		std::vector<std::string> messages;
};

class Location {
	public:

	private:

};

class Game {

};
