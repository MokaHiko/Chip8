#pragma once

#include <cstdint>
#include <random>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int STACK_LEVELS = 16;
class Chip8
{
public:
	uint8_t	 registers[16];
	uint8_t	 memory[4096];
	uint16_t index;
	uint16_t pc;
	uint16_t stack[STACK_LEVELS];
	uint8_t	 sp;
	uint8_t	 delayTimer;
	uint8_t	 soundTimer;
	uint8_t	 keypad[16];
	uint32_t video[64 * 32];
	uint16_t opcode{};
	
	std::default_random_engine randGen;
	//std::uniform_int_distribution<uint8_t> randByte;

	Chip8();
	void LoadROM(char const* filename);
	
	//CLS : clear display
	void OP_00E0();

	//RET : return from a subroutine
	void OP_00EE();

	//1nnn JP addr : sets program counter to nnn 
	void OP_1nnn();

	//2nnn - Call Adder: call subroutine at nnn
	void OP_2nnn();

	//3xkk : skip the next instruction if Vx = kk
	void OP_3xkk();

	//4xkk : skip the next instruction if Vx != kk
	void OP_4xkk();

	//5xy0 : skip the next instruction if Vx = Vy
	void OP_5xy0();

	//6xkk : set Vx = kk;
	void OP_6xkk();

	//7xkk : set Vx = Vx + kk
	void OP_7xkk();

	//8xy0 : set Vx = Vy
	void OP_8xy0();

	//8xy1 : set Vx = Vx or Vy
	void OP_8xy1();

	//8xy2 : set Vx = Vx AND Vy
	void OP_8xy2();

	//8xy3 : set Vx = Vx XOR Vy
	void OP_8xy3();

	//8xy4 : set Vx = Vx + Vy, set VF = carry
	void OP_8xy4();

	//8xy5 : set Vx = Vx - Vy, set VF = NOT barrow
	void OP_8xy5();

	//8xy6 : set Vx = Vx SHR 1
	void OP_8xy6();

	//8xy7 : Vx = Vy - Vx , set VF = NOT borrow
	void OP_8xy7();

	//8xyE : set Vx = Vx SHL 1
	void OP_8xyE();

	//9xy0 : skip next instruction if Vx != Vy
	void OP_9xy0();
	
	//Annn : set I = nnn
	void OP_Annn();

	//Bnnn : Jump to location nnn + V0;
	void OP_Bnnn();
};

