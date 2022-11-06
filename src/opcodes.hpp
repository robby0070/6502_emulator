#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>

using opcode_type = uint8_t;

enum OPCODES : opcode_type {
	// load store operations
	LDA_IMMEDIATE = 0xA9,
	LDA_ZERO_PAGE = 0xA5,
	LDA_ZERO_PAGE_X = 0xB5,
	LDA_ABSOLUTE = 0xAD,
	LDA_ABSOLUTE_X = 0xBD,
	LDA_ABSOLUTE_Y = 0xB9,
	LDA_INDIRECT_X = 0xA1,
	LDA_INDIRECT_Y = 0xB1,

	LDX_IMMEDIATE = 0xA2,
	LDX_ZERO_PAGE = 0xA6,
	LDX_ZERO_PAGE_Y = 0xB6,
	LDX_ABSOLUTE = 0xAE,
	LDX_ABSOLUTE_Y = 0xBE,

	LDY_IMMEDIATE = 0xA0,
	LDY_ZERO_PAGE = 0xA4,
	LDY_ZERO_PAGE_X = 0xB4,
	LDY_ABSOLUTE = 0xAC,
	LDY_ABSOLUTE_X = 0xBC,

	// register transfers

	// stack operations
	PHA = 0x48,
	PHP = 0x08,
	PLA = 0x68,
	PLP = 0x28,

	// logical
	ORA_IMMEDIATE = 0x09,
	ORA_ZERO_PAGE = 0x05,
	ORA_ZERO_PAGE_X = 0x15,
	ORA_ABSOLUTE = 0x0D,
	ORA_ABSOLUTE_X = 0x1D,
	ORA_ABSOLUTE_Y = 0x19,
	ORA_INDIRECT_X = 0x01,
	ORA_INDIRECT_Y = 0x11,

	// arithmetic
	SBC_IMMEDIATE = 0xE9,
	SBC_ZERO_PAGE = 0xE5,
	SBC_ZERO_PAGE_X = 0xF5,
	SBC_ABSOLUTE = 0xED,
	SBC_ABSOLUTE_X = 0xFD,
	SBC_ABSOLUTE_Y = 0xF9,
	SBC_INDIRECT_X = 0xE1,
	SBC_INDIRECT_Y = 0xF1,

	// increments and decrements

	// shifts
	LSR = 0x4A,
	LSR_ZERO_PAGE = 0x46,
	LSR_ZERO_PAGE_X = 0x56,
	LSR_ABSOLUTE = 0x4E,
	LSR_ABSOLUTE_X = 0x5E,

	ROL = 0x2A,
	ROL_ZERO_PAGE = 0x26,
	ROL_ZERO_PAGE_X = 0x36,
	ROL_ABSOLUTE = 0x2E,
	ROL_ABSOLUTE_X = 0x3E,

	ROR = 0x6A,
	ROR_ZERO_PAGE = 0x66,
	ROR_ZERO_PAGE_X = 0x76,
	ROR_ABSOLUTE = 0x6E,
	ROR_ABSOLUTE_X = 0x7E,

	// jumps and calls
	JSR = 0x20,
	RTS = 0x60,

	// branches

	// status flag changes
	SEC = 0x38,
	SED = 0xF8,
	SEI = 0x78,

	// system functions
	NOP = 0xEA,
	RTI = 0X40,

};
#endif
