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
		void add_location(std::string direction, std::shared_ptr<Location> location);
		void set_visited();
		// Getters
		std::vector<Item>& get_items();
		std::vector<NPC>& get_npcs();
		std::map<std::string, Location*>& get_locations();
		bool get_visited();
		// Visited funcs
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
		// TODO shouldn't need destructor, but I'll have to check for memory
		// leaks after. But when Game is destructed at the end of main(),
		// its locations vector should be freed and all shared_ptr should 
		// be deletede automatically, freeing up all memory used
		void create_world();
		std::map<std::string, command> setup_commands();
		std::shared_ptr<Location> random_location();
		void play();
		std::string get_input(std::vector<std::string>& tokens);
		// Commands
		void print_help(std::vector<std::string> tokens);
		void talk(std::vector<std::string> tokens);
		void meet(std::vector<std::string> tokens);
		// TODO add more commands
	private:
		std::map<std::string, command> commands;
		std::vector<Item> player_inventory;
		int player_weight;
		std::vector<std::shared_ptr<Location> > locations;
		std::shared_ptr<Location> player_location;
		int elf_hunger;
		bool game_in_progress;
};

