#include "Assets.h"
#include <iostream>
#include <vector>
#include <string>

/***************************************
 * Item Functions
 **************************************/

Item::Item(std::string name, std::string desc, int calories, float weight) {
	// TODO add error checking later
	this->name = name;
	this->desc = desc;
	this->calories = calories;
	this->weight = weight;
}

std::ostream& operator<< (std::ostream& out, const Item& item) {
	out << item.name << " (" << item.calories << " calories) - ";
	out << item.weight << " lb - " << item.desc;
	return out;
}



/***************************************
 * NPC Functions
 **************************************/

NPC::NPC(std::string name, std::string desc) {
	this->name = name;
	this->desc = desc;	
}

std::string NPC::get_name() const {
	return this->name;
}

std::string NPC::get_desc() const {
	return this->desc;
}

std::string NPC::get_message() {
	std::string message = this->messages[this->message_num];
	this->message_num = (this->message_num + 1) % this->messages.size();
	return message;
}

std::ostream& operator<< (std::ostream& out, const NPC& npc) {
	out << npc.name;
	return out;
}



/***************************************
 * Location Functions
 **************************************/

Location::Location(std::string name, std::string desc) {
	this->name = name;
	this->desc = desc;
	this->visited = false;
}

void Location::add_item(Item item) {
	this->items.push_back(item);
}

void Location::add_npc(NPC npc) {
	this->npcs.push_back(npc);
}

// Passes reference to location, BUT
void Location::add_location(std::string direction, Location& location) {
	// TODO check this
	// this still copies the data so the reference doesn't matter??
	this->neighbors.insert(std::pair<std::string, Location>(direction, location));
}

void Location::set_visited() {
	this->visited = true;
}

std::vector<Item>& Location::get_item() {
	return this->items;
}

std::vector<NPC>& Location::get_npc() {
	return this->npcs;
}

std::map<std::string, Location>& Location::get_locations() {
	return this->neighbors;
}

bool Location::get_visited() {
	return this->visited;
}

std::ostream& operator<<(std::ostream& out, const Location& location) {
	out << location.name << " - " << location.desc << std::endl; 
	// NPCs
	out << std::endl << "You see the following NPCs:" << std::endl;
	for(NPC npc: location.npcs)
		out << "\t- " << npc << std::endl;
	out << std::endl;
	// Items
	out << "You see the following Items:" << std::endl;
	for(Item item: location.items)
		out << "\t- " << item << std::endl; 
	out << std::endl;
	// Locations
	out << "You can go in the following directions:" << std::endl;
	for(std::pair<std::string, Location> dir: location.neighbors) {
		out << "\t- " << dir.first << " - "; 
		if(dir.second.get_visited()) {
			out << dir.second.name << " (Visited)" << std::endl;
		} else {
			out << "Unknown" << std::endl;
		}
	}

	return out;
}



/***************************************
 * Game Functions
 **************************************/

Game::Game() {
	this->commands = this->setup_commands();
	this->create_world();
	this->player_weight = 0;
	this->elf_hunger = 500;
	this->player_location = this->random_location();
}

std::map<std::string, command> Game::setup_commands() {
	std::map<std::string, command> commands;
	commands["help"] = &Game::print_help;
	commands["talk"] = &Game::talk;
	commands["meet"] = &Game::meet;

	return commands;
}

Location* Game::random_location() {
	return &this->locations[0];
}

void Game::create_world() {
	Location lib("Library", "Full of books");
	Location kirk("Kirkoff", "Grab some food");
	lib.set_visited();
	kirk.set_visited();

	this->locations.push_back(lib);
	this->locations.push_back(kirk);

	lib.add_location("North", kirk); // We add a copy of kirk to lib
	kirk.add_location("South", lib); // But now we add a copy of lib to the original
}

void Game::play() {
	std::vector<std::string> tokens;
	this->commands["help"](this, tokens);
	this->commands["talk"](this, tokens);
	this->commands["meet"](this, tokens);
}

/***************************************
 * Game Commands 
 **************************************/

void Game::print_help(std::vector<std::string> tokens) {
	std::cout << "Ran help" << std::endl;
}

void Game::talk(std::vector<std::string> tokens) {
	std::cout << "Ran talk" << std::endl;
}

void Game::meet(std::vector<std::string> tokens) {
	std::cout << "Ran meet" << std::endl;
}
