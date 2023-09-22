#pragma once

#include <string>
#include <iostream>

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
	private:
		std::string name;
		std::string desc;
		int messageNum;
		//std::vector messages;


};

class Location {

};

class Game {

};
