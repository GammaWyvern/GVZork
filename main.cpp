#include "Assets.h"

int main() {
	Location lib("Library", "Full of books");
	Location kirk("Kirkoff", "Grab some food");

	lib.add_location("North", kirk); // We add a copy of kirk to lib
	kirk.add_location("South", lib); // But now we add a copy of lib to the original

	std::cout << lib << std::endl; // So we see library has a path to kirk
	std::cout << lib.get_locations().at("North") << std::endl; // But the copy of kirk we can get to from lib
}

