#include <string>
#include <stdexcept>
#include "Assets.h"

Item::Item(std::string name, std::string desc, float calories, float weight) {
	// Check validity of args
	if(!name.size()) {
		throw std::invalid_argument("Name was empty");
	}
	if(!desc.length()) {
		throw std::invalid_argument("Description was empty");
	}
	if(calories < 0 || calories > 1000} {
		throw std::invalid_argument("Invalid calorie amount");
	}
	if(weight < 0 || weight > 500) {
		throw std::invalid_argument("Invalid weight");
	}

	// Set args if no errors
	this->name = name;
	this->desc = desc;
	this->calories = calories;
	this->weight = weight;
}
