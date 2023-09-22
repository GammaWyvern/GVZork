#include "Assets.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Item item("Banana", "It's a fruit", 30.0f, 0.2f);
	std::cout << item << std::endl;

	NPC npc("Keagen", "One annoying ass dude");
	std::cout << npc << std::endl;
}
