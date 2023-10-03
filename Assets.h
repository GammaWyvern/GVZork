#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

class Item;
class NPC;
class Location;
class Game;

typedef std::function<void(Game*, std::vector<std::string>)> command;

class Item {
	public:
		Item(std::string name, std::string desc, int calories, float weight);
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
		friend std::ostream& operator<<(std::ostream& out, const NPC& npc);
	private:
		std::string name;
		std::string desc;
		int message_num;
		std::vector<std::string> messages;
};

class Location {
	public:
		Location(std::string name, std::string desc);
		void add_item(Item item);
		void add_npc(NPC npc);
		void add_location(std::string direction, Location& location);
		void set_visited();
		// Getters
		std::vector<Item>& get_item();
		std::vector<NPC>& get_npc();
		std::map<std::string, std::reference_wrapper<Location>>& get_locations();
		bool get_visited();
		// Visited funcs
		friend std::ostream& operator<<(std::ostream& out, const Location& location);
	private:
		std::string name;
		std::string desc;
		bool visited;
		std::vector<NPC> npcs;
		std::vector<Item> items;
		std::map<std::string, std::reference_wrapper<Location>> neighbors;
};

class Game {
	public:
		Game();
		void create_world();
		std::map<std::string, command> setup_commands();
		std::reference_wrapper<Location> random_location();
		void play();
		std::string get_input(std::vector<std::string> tokens);
		// Commands
		void print_help(std::vector<std::string> tokens);
		void talk(std::vector<std::string> tokens);
		void meet(std::vector<std::string> tokens);
		// TODO add more commands
	private:
		std::map<std::string, command> commands;
		std::vector<Item> player_inventory;
		int player_weight;
		std::vector<std::reference_wrapper<Location>> locations;
		//Location player_location;
		int elf_hunger;
		bool game_in_progress;
};

