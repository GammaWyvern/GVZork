#include "Assets.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>

//This is the real man's way to do C++
#include <memory>

/***************************************
 * Item Functions
 **************************************/

Item::Item(std::string name, std::string desc, int calories, float weight) {
	if (name.empty())
		throw std::invalid_argument("Name cannot be blank.");
	
	if (desc.empty())
		throw std::invalid_argument("Description cannot be blank.");

	if (calories < 0 || calories > 1000)
		throw std::invalid_argument("Calories must be between 0 and 1000");

	if (weight < 0 || weight > 500)
		throw std::invalid_argument("Weight must be between 0 and 500");

	this->name = name;
	this->desc = desc;
	this->calories = calories;
	this->weight = weight;
}

std::string Item::get_name() {
	return this->name;
}

float Item::get_weight() {
	return this->weight;
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
	if (name.empty())
		throw std::invalid_argument("Name cannot be blank.");

	if (desc.empty()) 
		throw std::invalid_argument("Description cannot be blank.");

	this->name = name;
	this->desc = desc;	
	this->message_num = 0;
	this->has_gift = true;
}

std::string NPC::get_name() const {
	return this->name;
}

std::string NPC::get_desc() const {
	return this->desc;
}

std::string NPC::get_message() {
	if(!this->messages.size()) {
		return "They have nothing to say";
	}

	std::string message = this->messages[this->message_num];
	this->message_num = (this->message_num + 1) % this->messages.size();
	return message;
}

void NPC::add_message(std::string message) {
	this->messages.push_back(message);
}

bool NPC::get_has_gift() {
	return this->has_gift;
}

void NPC::take_gift() {
	this->has_gift = false;
}

std::ostream& operator<< (std::ostream& out, const NPC& npc) {
	out << npc.name;
	return out;
}



/***************************************
 * Location Functions
 **************************************/

Location::Location(std::string name, std::string desc) {
	if (name.empty())
		throw std::invalid_argument("Description cannot be blank.");

	if (desc.empty())
		throw std::invalid_argument("Description cannot be blank.");

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

void Location::add_location(std::string direction, std::shared_ptr<Location> location) {
	this->neighbors[direction] = location.get();
}

void Location::set_visited() {
	this->visited = true;
}

std::vector<Item>& Location::get_items() {
	return this->items;
}

std::vector<NPC>& Location::get_npcs() {
	return this->npcs;
}

std::map<std::string, Location*>& Location::get_locations() {
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
	for(std::pair<std::string, Location*> dir: location.neighbors) {
		out << "\t- " << dir.first << " - "; 
		if(dir.second->get_visited()) {
			out << dir.second->name << " (Visited)" << std::endl;
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
	this->player_location->set_visited();
}

std::map<std::string, command> Game::setup_commands() {
	std::map<std::string, command> commands;
	commands["?"] = &Game::print_help;
	commands["??"] = &Game::print_help;
	commands["???"] = &Game::print_help;
	commands["help"] = &Game::print_help;
	commands["sos"] = &Game::print_help;

	commands["talk"] = &Game::talk;
	commands["speak"] = &Game::talk;
	commands["chat"] = &Game::talk;
	commands["discuss"] = &Game::talk;

	commands["meet"] = &Game::meet;
	commands["encounter"] = &Game::meet;
	commands["approach"] = &Game::meet;
	commands["connect"] = &Game::meet;

	commands["give"] = &Game::give;
	commands["offer"] = &Game::give;
	commands["extend"] = &Game::give;
	commands["provide"] = &Game::give;
	commands["contribute"] = &Game::give;
	commands["bestow"] = &Game::give;

	commands["go"] = &Game::go;
	commands["leave"] = &Game::go;
	commands["move"] = &Game::go;
	commands["travel"] = &Game::go;
	commands["walk"] = &Game::go;
	commands["proceed"] = &Game::go;
	commands["taverse"] = &Game::go;

	commands["show"] = &Game::show_items;
	commands["items"] = &Game::show_items;
	commands["display"] = &Game::show_items;

	commands["look"] = &Game::look;
	commands["peer"] = &Game::look;
	commands["stare"] = &Game::look;
	commands["peek"] = &Game::look;
	commands["watch"] = &Game::look;
	commands["view"] = &Game::look;
	commands["examine"] = &Game::look;

	commands["quit"] = &Game::quit;
	commands["exit"] = &Game::quit;
	commands["abandon"] = &Game::quit;
	commands["surrender"] = &Game::quit;
	commands["withdraw"] = &Game::quit;

	commands["thanks"] = &Game::smile;
	commands["smile"] = &Game::smile;
	commands["thank"] = &Game::smile;
	commands["cheers"] = &Game::smile;

	commands["drop"] = &Game::drop;
	commands["give"] = &Game::drop;
	commands["release"] = &Game::drop;
	commands["discard"] = &Game::drop;
	commands["dump"] = &Game::drop;
	commands["ditch"] = &Game::drop;
	commands["throw"] = &Game::drop;

	return commands;
}

Location* Game::random_location() {
	int randInt = rand() % this->locations.size();
	return this->locations[randInt].get();
}

void Game::create_world() {
	auto lib = std::shared_ptr<Location>(new Location("Library", "Full of books"));
	auto kirk = std::shared_ptr<Location>(new Location("Kirkoff", "Grab some food"));

	NPC keag("Keagen", "Some dude.");
	keag.add_message("Hey");
	keag.add_message("What's up?");
	kirk->add_npc(keag);

	Item banana("Banana", "It's a fruit", 50, 0.1f);
	kirk->add_item(banana);

	// Connect locations
	lib->add_location("North", kirk); 
	kirk->add_location("South", lib);

	// Push back locations to game vector
	// IF YOU DON'T THEY WILL BE FREED
	this->locations.push_back(lib);
	this->locations.push_back(kirk);
}

void Game::play() {
	std::string command;
	std::vector<std::string> tokens;

	std::cout << *this->player_location << std::endl;
	while(this->game_in_progress) {
		command = this->get_input(tokens);

		if(this->commands.find(command) != this->commands.end()) {
			this->commands[command](this, tokens);
		} else {
			std::cout << "Could not understand command" << std::endl;
		}

	}
}

std::string Game::get_input(std::vector<std::string>& tokens) {
	tokens.clear();
	std::string token;
	std::string command;

	std::cin >> command;
	if(std::cin.peek() == '\n') {
		return command;
	}

	while(std::cin >> token) {
		tokens.push_back(token);
		
		if(std::cin.peek() == '\n') {
			break;
		}
	}

	return command;
}

/***************************************
 * Game Commands 
 **************************************/

void Game::print_help(std::vector<std::string> tokens) {
	// TODO implement
	std::cout << "Implement help()" << std::endl;
}

void Game::talk(std::vector<std::string> tokens) {
	// TODO this will only work for npc's with a single word name currently
	// Go through each NPC
	for(auto npc=this->player_location->get_npcs().begin(); npc != this->player_location->get_npcs().end(); npc++) {
		// Go through each potential target in tokens 
		for(std::string target: tokens) {
			// If match, print message
			if(!npc->get_name().compare(target)) {
				std::cout << npc->get_message() << std::endl;
				return;
			}
		}
	}

	std::cout << "NPC not found" << std::endl;
}

void Game::meet(std::vector<std::string> tokens) {
	// TODO this will only work for npc's with a single word name currently
	// Go through each NPC
	for(auto npc=this->player_location->get_npcs().begin(); npc != this->player_location->get_npcs().end(); npc++) {
		// Go through each potential target in tokens 
		for(std::string target: tokens) {
			// If match, print message
			if(!npc->get_name().compare(target)) {
				std::cout << npc->get_desc() << std::endl;
				return;
			}
		}
	}

	std::cout << "NPC not found" << std::endl;
}

void Game::take(std::vector<std::string> tokens) {
	// Go through each item in location
	std::vector<Item>& items = this->player_location->get_items();
	for(auto item=items.begin(); item != items.end(); item++) {
		// Check each token for target item
		for(std::string target: tokens) {
			if(!item->get_name().compare(target)) {
				if(player_weight + item->get_weight() > 30) {
					std::cout << "You are carrying too much weight!" << std::endl;
					return;
				}

				this->player_inventory.push_back(*item);
				this->player_weight += item->get_weight();
				items.erase(item);
				return;
			}
		}
	}	

	std::cout << "Item not found" << std::endl;
}

void Game::give(std::vector<std::string> tokens) {
	// TODO implement	
}

void Game::go(std::vector<std::string> tokens) {
	// Go through each key/value pair in cur location neighobrs	
	for(std::pair<std::string, Location*> path: this->player_location->get_locations()) {
		// Go through each target 
		for(std::string target: tokens) {
			// If target matches a direction, go there
			if(!path.first.compare(target)) {
				this->player_location = path.second;
				this->player_location->set_visited();
				std::cout << *this->player_location << std::endl;
				return;
			}
		}
	}

	std::cout << "Direction not found" << std::endl;
}

void Game::show_items(std::vector<std::string> tokens) {
	for(Item item: this->player_inventory) {
		std::cout << item << std::endl;	
	}

	std::cout << "Total weight: " << this->player_weight << std::endl;
}

void Game::look(std::vector<std::string> tokens) {
	std::cout << *this->player_location << std::endl;
}

void Game::quit(std::vector<std::string> tokens) {
	std::cout << "You have failed the game" << std::endl;
	this->game_in_progress = false;
}

void Game::smile(std::vector<std::string> tokens) {
	Item gift = this->get_random_gift();

	std::vector<NPC>& npcs = this->player_location->get_npcs();
	for(auto npc = npcs.begin(); npc != npcs.end(); npc++) {
		for(std::string target: tokens) {
			if(!npc->get_name().compare(target) && npc->get_has_gift()) {
				npc->take_gift();
				this->player_inventory.push_back(gift);
				this->player_weight += gift.get_weight();
				return;
			}				
		}
	}
}

/***************************************
 * Game Private Helper Functions 
 **************************************/

Item Game::get_random_gift() {
	// TODO Add more
	std::vector<Item> gifts = {
		Item("Gift1", "A nice present.", 50, 0.5),
		Item("Gift2", "A nice present.", 50, 0.5),
		Item("Gift3", "A nice present.", 50, 0.5)
	};

	int randIndex = rand() % gifts.size();
	return gifts[randIndex];
}

