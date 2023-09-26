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
		std::string get_name();
		std::string get_desc();
		std::string get_message();
		void add_message(std::string message);
	private:
		std::string name;
		std::string desc;
		int message_num;
		std::vector<std::string> messages;
};

class Location {
	public:
		Location(std::string name, std::string desc);
		friend std::ostream & operator << (std::ostream &out, const Location &location);
		void add_location(std::string direction, Location &location);
		void add_npc(NPC &npc);
		void add_item(Item &item);
		std::map<std::string, Location&> get_locations();
		std::vector<NPC> get_npcs();
		bool get_visited();
		void set_visited();
	private:
		std::string name;
		std::string desc;
		std::map<std::string, Location&> neighbors;
		std::vector<NPC> npcs;
		std::vector<Item> items;
		bool visited;
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

