#include<iostream>
#include "Chip8.h"

int main()
{
	Chip8* chip = new Chip8();
	std::cout << "pc: " << chip->pc << std::endl;
	delete chip;
	return 0;
}