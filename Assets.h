#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

//This is the real man's way to do C++
#include <memory>

class Item;
class NPC;
class Location;
class Game;

typedef std::function<void(Game*, std::vector<std::string>)> command;

class Item {
	public:
		Item(std::string name, std::string desc, int calories, float weight);
		std::string get_name();
		float get_weight();
		friend std::ostream& operator<<(std::ostream& out, const Item& item);
	private:
		std::string name;
		std::string desc;
		int calories;
		float weight;
};

class NPC {
	public:
		NPC(std::string name, std::string desc);
		std::string get_name() const;
		std::string get_desc() const;
		std::string get_message();
		void add_message(std::string message);
		bool get_has_gift();
		void take_gift();
		friend std::ostream& operator<<(std::ostream& out, const NPC& npc);
	private:
		std::string name;
		std::string desc;
		int message_num;
		std::vector<std::string> messages;
		bool has_gift;
};

class Location {
	public:
		Location(std::string name, std::string desc);
		void add_item(Item item);
		void add_npc(NPC npc);
		void add_location(std::string direction, std::shared_ptr<Location> location);
		void set_visited();
		std::vector<Item>& get_items();
		std::vector<NPC>& get_npcs();
		std::map<std::string, Location*>& get_locations();
		bool get_visited();
		friend std::ostream& operator<<(std::ostream& out, const Location& location);
	private:
		std::string name;
		std::string desc;
		bool visited;
		std::vector<NPC> npcs;
		std::vector<Item> items;
		std::map<std::string, Location*> neighbors;
};

class Game {
	public:
		Game();
		void create_world();
		std::map<std::string, command> setup_commands();
		Location* random_location();
		void play();
		std::string get_input(std::vector<std::string>& tokens);
		// Commands
		void print_help(std::vector<std::string> tokens);
		void talk(std::vector<std::string> tokens);
		void meet(std::vector<std::string> tokens);
		void take(std::vector<std::string> tokens);
		void give(std::vector<std::string> tokens);
		void go(std::vector<std::string> tokens);
		void show_items(std::vector<std::string> tokens);
		void look(std::vector<std::string> tokens);
		void quit(std::vector<std::string> tokens);
		// Own commands
		void smile(std::vector<std::string> tokens);
		void drop(std::vector<std::string> tokens);
	private:
		Item get_random_gift();
		std::map<std::string, command> commands;
		std::vector<Item> player_inventory;
		float player_weight;
		std::vector<std::shared_ptr<Location> > locations;
		Location* player_location;
		int elf_hunger;
		bool game_in_progress;
};

