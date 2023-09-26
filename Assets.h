#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

typedef std::function<void(std::vector<std::string>)> command;

namespace GameLogic {
	void get_input(std::vector<std::string> &dest);
}

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
		Game();
		void create_world();
		std::map<std::string, command> setup_commands();
		Location& random_location();
		void play();
		// Commands
		void show_help();
		void talk(std::vector<std::string> tokens);
		void meet(std::vector<std::string> tokens);
		void give(std::vector<std::string> tokens);
		void go(std::vector<std::string> tokens);
		void show_items(std::vector<std::string> tokens);
		void look(std::vector<std::string> tokens);
		void quit(std::vector<std::string> tokens);
		// My own?
		// Could add simple magic, that would be cool????
		// Like make my own simple magic system with mana
		// and spells that you could pick up and/or buy with money?
	private:
		std::map<std::string, command> commands;
		std::vector<Item> player_items;
		int player_weight;
		std::vector<Location> locations;
		Location *player_location;
		int elf_hunger;
		bool game_in_progress;
};

