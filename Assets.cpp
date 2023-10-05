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

	commands["take"] = &Game::take;
	commands["steal"] = &Game::take;
	commands["plunder"] = &Game::take;
	commands["borrow"] = &Game::take;
	commands["grab"] = &Game::take;
	commands["pick"] = &Game::take;

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
	auto lib = std::shared_ptr<Location>(new Location(" The Library",\
		"Full of books and students procrastinating on their\
		 homework."));
	auto kirk = std::shared_ptr<Location>(new Location("Kirkoff",\
		"Grab some food! You can play pool too!"));
	auto alum = std::shared_ptr<Location>(new Location(" The Alumni house",\
		"Fancy events are had here. It is where the Alumni \
are most welcome."));
	auto minimak = std::shared_ptr<Location>(new Location("Mini Mack\
		 Bridge ", "A fun bridge to walk over."));
	auto fieldhouse = std::shared_ptr<Location>(new Location(\
		"Fieldhouse", "Come watch a football game!"));
	auto mak = std::shared_ptr<Location>(new Location("Mackinac Hall"\
		,"Where all of the best classes are"));
	auto rav = std::shared_ptr<Location>(new Location("The Ravines",\
		"Stay on the path or you might fall a very long way."));
	auto lotC = std::shared_ptr<Location>(new Location("Parking Lot C"\
		, "This is not a friendly place between 10:00AM and 3:00PM. \
Be prepared to FIGHT for a parking spot"));

	fieldhouse->add_location("East", alum);
	fieldhouse->add_location("South", lotC);
	alum->add_location("West", fieldhouse);
	alum->add_location("South", lotC);
	alum->add_location("East", rav);
	lotC->add_location("North", fieldhouse);
	lotC->add_location("North", alum);
	lotC->add_location("East", mak);
	lotC->add_location("South", lib);
	mak->add_location("West", lotC);
	mak->add_location("East", rav);
	mak->add_location("South", minimak);
	minimak->add_location("North", mak);
	minimak->add_location("South", kirk);
	kirk->add_location("North", minimak);
	kirk->add_location("West", lib);
	kirk->add_location("East", rav);
	lib->add_location("East", kirk);
	lib->add_location("North", lotC);
	rav->add_location("West", alum);
	rav->add_location("West", mak);
	rav->add_location("West", kirk);

	this->locations.push_back(fieldhouse);
	this->locations.push_back(alum);
	this->locations.push_back(lotC);
	this->locations.push_back(mak);
	this->locations.push_back(minimak);
	this->locations.push_back(kirk);
	this->locations.push_back(lib);
	this->locations.push_back(rav);

	NPC cas("Casandra", "The girl that wants your parking spot.");
	NPC troll("Troll", "He lives under the bridge.");
	NPC toby("Toby", "The campus healer");
	NPC paul("Paul", "A football player.");
	NPC kevin("Kevin", "Cashier for Panda express.");

	cas.add_message("Hey, are you leaving soon?");
	cas.add_message("Can I have your parking spot?");
	cas.add_message("I was actually here first, go find another spot");
	lotC->add_npc(cas);

	troll.add_message("I have a riddle for you.");
	troll.add_message("I forgot my riddle... UGH!!");
	troll.add_message("You can cross, don't let me stop you.");
	minimak->add_npc(troll);

	toby.add_message("I can heal you.");
	toby.add_message("I can get rid of the cold that I know you have");
	toby.add_message("I'm tired... why is everyone sick????");
	mak->add_npc(toby);

	paul.add_message("I can catch a football!");
	paul.add_message("watch me throw this football.");
	paul.add_message("I hurt my shoulder! Someone find Toby");
	fieldhouse->add_npc(paul);

	kevin.add_message("Your total is $12.75.");
	kevin.add_message("I need a pay raise.");
	kevin.add_message("Do you want a spring rolls or crab rangoons?");
	kirk->add_npc(kevin);

	Item cookie("Chocolate chip cookie", "Cookie baked with love by \
your grandma.", 50, 2.3684);
	Item stick("Stick", "It was once attached to a tree, \
now it is not.", 0, 5.346);
	Item rang("Crab Rangoons", "A delicacy from Panda Express.",\
		70, 4.6);
	Item milk("Chocolate Milk", "A cup of chocolate milk", 90, 2.9f);
	Item fball("Football", "The football thrown by Paul", 0, 4.34f);
	Item sandwich("Turkey sandwich", "Turkey, tomato, lettuce, \
cheese, mustard, and a lot of bacon. What more could you ask for?",\
100, 9.994f);
	Item apple("Apple", "A honey crisp apple", 50, 2.635f);
	Item rock("Rock", "A very large rock.", 0, 15.3468f);
	Item cake("Slice of Cake", "The cake is chocolate...\
and very dense", 250, 12.737f);
	Item coke("Can of Coke", "A fresh, cold, can of Coke", 200, 7.57f);
	Item gift("gift", "This is a gift, it is given only to those who\
are kind.", 50, 0.01f);
	
	fieldhouse->add_item(fball);
	alum->add_item(cookie);
	mak->add_item(milk);
	mak->add_item(cake);
	lib->add_item(apple);
	kirk->add_item(rang);
	kirk->add_item(coke);
	lotC->add_item(sandwich);
	minimak->add_item(stick);
	rav->add_item(rock);
}


void Game::play() {
	std::cout << " \t \t Welcome to GVZork \n \
---------------------------------------------------------------\n \n \
THE CAMPUS IS IN TROUBLE!!!\n\
 The only person who can save the campus is the elf.\n\
 The elf lives in the ravines behind campus and he\
is hungry!!! \n There are some items around campus that the \
elf might want to eat.\n Keep in mind: The elf needs 500 calories \
worth of food. \n Also, you are only able to carry 30 pounds worth \
of items at a time. \n \
You must make sure the elf gets his food or else campus will be \
doomed \n \n" << std::endl;

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

void Game::drop(std::vector<std::string> tokens) {
	// TODO implement this
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

