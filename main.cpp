#include "Assets.h"
#include <iostream>

int main(int argc, char* argv[]) {
	/*
	Item banana("Banana", "It's a fruit", 30.0f, 0.2f);
	NPC keag("Keagen", "One annoying ass dude");
	*/

	Location lib("Library", "A relaxing place full of books.");
	Location kirk("Kirkoff", "Enjoy the food and atmosphere!");

	lib.add_location("North", kirk);

	kirk.set_visited();
	std::cout << lib;
}

