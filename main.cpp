#include "Assets.h"
#include <iostream>

int main(int argc, char* argv[]) {
	NPC keag("Keagen", "One annoying ass dude");
	keag.add_message("That's what Joe was sayin");
	keag.add_message("Oh, you don't know who Joe is?");
	keag.add_message("JOE MAMA!");

	Location lib("Library", "A relaxing place full of books.");
	Location kirk("Kirkoff", "Enjoy the food and atmosphere!");
	lib.add_location("North", kirk);
	kirk.set_visited();
	lib.add_npc(keag);

	// Some testing
	std::cout << keag.get_message() << '\n';
	std::cout << lib.get_npcs().at(0).get_message() << '\n';
	std::cout << lib;
}

