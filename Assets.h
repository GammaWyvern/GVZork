#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

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
		Location(std::string name, std::string desc);
		std::map<std::string, Location> get_locations();
		void add_location(std::string direction, Location location);
		void add_npc(NPC npc);
		std::vector<NPC> get_npcs();
		void add_item(Item item);
		void set_visited();
		bool get_visited();
		friend std::ostream & operator << (std::ostream &out, const Location *location);
	private:
		std::string name;
		std::string desc;
		bool visited;
		std::map<std::string, Location> neighbors;
		std::vector<NPC> npcs;
		std::vector<Item> items;
};

class Game {
	public:

	private:
		//Command = alias for function -> void (std::vector<std::string>)
		//map<std::string, Command>
		std::vector<Item> playerItems;
		int playerWeight;
		std::vector<Location> locations;
		Location playerLocation;
		int elfHunger;
		bool gameInProgress;
};

