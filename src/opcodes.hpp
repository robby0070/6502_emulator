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

	STA_ZERO_PAGE = 0x85,
	STA_ZERO_PAGE_X = 0x95,
	STA_ABSOLUTE = 0x8D,
	STA_ABSOLUTE_X = 0x9D,
	STA_ABSOLUTE_Y = 0x99,
	STA_INDIRECT_X = 0x81,
	STA_INDIRECT_Y = 0x91,

	STX_ZERO_PAGE = 0x86,
	STX_ZERO_PAGE_Y = 0x96,
	STX_ABSOLUTE = 0x8E,

	STY_ZERO_PAGE = 0x84,
	STY_ZERO_PAGE_X = 0x94,
	STY_ABSOLUTE = 0x8C,

	// register transfers
	TAX = 0xAA,
	TAY = 0xA8,
	TXA = 0x8A,
	TYA = 0x98,

	// stack operations
	TSX = 0xBA,
	TXS = 0x9A,
	PHA = 0x48,
	PHP = 0x08,
	PLA = 0x68,
	PLP = 0x28,

	// logical
	AND_IMMEDIATE = 0x29,
	AND_ZERO_PAGE = 0x25,
	AND_ZERO_PAGE_X = 0x35,
	AND_ABSOLUTE = 0x2D,
	AND_ABSOLUTE_X = 0x3D,
	AND_ABSOLUTE_Y = 0x39,
	AND_INDIRECT_X = 0x21,
	AND_INDIRECT_Y = 0x31,

	EOR_IMMEDIATE = 0x49,
	EOR_ZERO_PAGE = 0x45,
	EOR_ZERO_PAGE_X = 0x55,
	EOR_ABSOLUTE = 0x4D,
	EOR_ABSOLUTE_X = 0x5D,
	EOR_ABSOLUTE_Y = 0x59,
	EOR_INDIRECT_X = 0x41,
	EOR_INDIRECT_Y = 0x51,

	ORA_IMMEDIATE = 0x09,
	ORA_ZERO_PAGE = 0x05,
	ORA_ZERO_PAGE_X = 0x15,
	ORA_ABSOLUTE = 0x0D,
	ORA_ABSOLUTE_X = 0x1D,
	ORA_ABSOLUTE_Y = 0x19,
	ORA_INDIRECT_X = 0x01,
	ORA_INDIRECT_Y = 0x11,
	BIT_ZERO_PAGE = 0x24,
	BIT_ABSOLUTE = 0x2C,

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
	CLC = 0x18,
	CLD = 0xD8,
	CLI = 0x58,
	CLV = 0xB8,
	SEC = 0x38,
	SED = 0xF8,
	SEI = 0x78,

	// system functions
	NOP = 0xEA,
	RTI = 0X40,

};
#endif
