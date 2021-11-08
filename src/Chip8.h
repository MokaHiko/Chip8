#pragma once

#include <cstdint>
#include <random>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32; 
const unsigned int VIDEO_WIDTH = 64;

class Chip8
{
public:
	uint8_t	 registers[16];
	uint8_t	 memory[4096];
	uint16_t index{};
	uint16_t pc{};
	uint16_t stack[STACK_LEVELS]{};
	uint8_t	 sp{};
	uint8_t	 delayTimer{};
	uint8_t	 soundTimer{};
	uint8_t	 keypad[16];
	uint32_t video[64 * 32];
	uint16_t opcode{};

	Chip8();
	~Chip8();

	void LoadROM(char const* filename);

	void Cycle();
private:
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
	
	//Cxkk : Vx = random byte AND kk.
	void OP_Cxkk();

	//Dxyn : display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
	void OP_Dxyn();

	//Ex9E : skip next instruction if key with the value of Vx is pressed
	void OP_Ex9E();

	//ExA1 :  skip next instruction if the key with Vx is not pressed
	void OP_ExA1();

	//Fx07 : set Vx = delay timer value
	void OP_Fx07();

	//Fx0A : wait for a key press, store the value of the key in Vx.
	void OP_Fx0A();

	//Fx15 : set delay timer = Vx
	void OP_Fx15();

	//Fx18 : set sound timer = Vx
	void OP_Fx18();

	//Fx1E : set I = I + Vx
	void OP_Fx1E();

	//Fx29 : set I = location of sprite for digix Vx
	void OP_Fx29();

	//Fx33 :store bcd representation of Vx in memory Locations I, I + 1, and I + 2
	//the interperter takes the decimal value of Vx and places the hundreds digit in memory at location in I, tens in I +1, ones in I + 2
	void OP_Fx33();
	
	//Fx55 : store registers V0 through Vx in memory starting at location I
	void OP_Fx55();

	//Fx65 : read registers V0 through Vx from memory starting at location I
	void OP_Fx65();

	std::default_random_engine randGen;
	//std::uniform_int_distribution<uint8_t> randByte;

	void Table0();
	void Table8();
	void TableE();
	void TableF();
	void OP_NULL();

	typedef void (Chip8::*Chip8Func)();
	Chip8Func table [0xF  + 1]{ &Chip8::OP_NULL };
	Chip8Func table0[0xE  + 1]{ &Chip8::OP_NULL };
	Chip8Func table8[0xE  + 1]{ &Chip8::OP_NULL };
	Chip8Func tableE[0xE  + 1]{ &Chip8::OP_NULL };
	Chip8Func tableF[0x65 + 1]{ &Chip8::OP_NULL };
};

