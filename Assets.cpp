#include "Assets.h"
#include <string>
#include <iostream>
#include <stdexcept>



/***************************************
 * Item Functions
 **************************************/

Item::Item(std::string name, std::string desc, float calories, float weight) {
	// Check validity of args
	if(!name.size())
		throw std::invalid_argument("Name was empty");
	if(!desc.size())
		throw std::invalid_argument("Description was empty");
	if(calories < 0 || calories > 1000)
		throw std::invalid_argument("Invalid calorie amount");
	if(weight < 0 || weight > 500)
		throw std::invalid_argument("Invalid weight");

	// Set args if no errors
	this->name = name;
	this->desc = desc;
	this->calories = calories;
	this->weight = weight;
}

std::ostream & operator << (std::ostream &out, const Item &item) {
	out << item.name << " (" << item.calories << ") - "; 
	out << item.weight << " lb - " << item.desc; 
	return out;
}



/***************************************
 * NPC Functions
 **************************************/

NPC::NPC(std::string name, std::string desc) {
	this->name = name;
	this->desc = desc;
	this->message_num = 0;
	// TODO? this->messages = std::vector<std::string>();
}

std::ostream & operator << (std::ostream &out, const NPC &npc) {
	out << npc.name;
	return out;
}

std::string NPC::get_name() {
	return this->name;
}

std::string NPC::get_desc() {
	return this->desc;
}

std::string NPC::get_message() {
	std::string message = this->messages[this->message_num];
	this->message_num = (++this->message_num) % this->messages.size();
	return message;

}

void NPC::add_message(std::string message) {
	this->messages.push_back(message);
}



/***************************************
 * Location Functions
 **************************************/

Location::Location(std::string name, std::string desc) {
	this->name = name;
	this->desc = desc;
	this->visited = false;
	// TODO add neighobrs, npc, and items?
}

std::map<std::string, Location&> Location::get_locations() {
	return this->neighbors;
}

void Location::add_location(std::string direction, Location &location) {
	if(!direction.size()) {
		throw std::invalid_argument("Direction is empty");
	}
		
	bool result = (this->neighbors.insert(std::pair<std::string, Location&>(direction, location))).second;
	if(!result) {
		throw std::invalid_argument("Direction was already used at location"); 
	}
}

void Location::add_npc(NPC &npc) {
	this->npcs.push_back(npc);
}

void Location::add_item(Item &item) {
	this->items.push_back(item);
}

std::vector<NPC> Location::get_npcs() {
	return this->npcs;
}

void Location::set_visited() {
	this->visited = true;
}

bool Location::get_visited() {
	return this->visited;
}

std::ostream & operator << (std::ostream &out, const Location &location) {
	out << location.name << " - " << location.desc << "\n";

	out << "\nYou see the following NPCs:\n";
	for(NPC npc: location.npcs) {
		out << "\t- " << npc << "\n";
	}

	out << "\nYou see the following items:" << "\n";
	for(Item item: location.items) {
		out << "\t- " << item << "\n";
	}

	out << "\nYou can go in the following directions:" << "\n";
	for(std::pair<std::string, Location&> travel: location.neighbors) {
		if(travel.second.get_visited()) {
			out << "\t- " << travel.first << " - " << travel.second.name << " (Visited)\n";
		} else {
			out << "\t- " << travel.first << " - Unknown\n";
		}
	}

	return out;
}



/***************************************
 * Game Functions
 **************************************/

Game::Game() {
	// TODO a LOT
}



/***************************************
 * GameLogic Functions
 **************************************/

void GameLogic::get_input(std::vector<std::string> &dest) {
	dest.clear();
	std::string instruction;
	while(std::cin >> instruction) {
		dest.push_back(instruction);
		if(std::cin.peek() == '\n')
			break;
	}
}


