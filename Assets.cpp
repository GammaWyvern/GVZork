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
	this->messageNum = 0;
	//this->messages = std::vector<>();
}

std::ostream & operator << (std::ostream &out, const NPC &npc) {
	out << npc.name;
	return out;
}

std::string NPC::getName() {
	return this->name;
}

std::string NPC::getDesc() {
	return this->desc;
}
