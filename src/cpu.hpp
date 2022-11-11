#ifndef CPU_H
#define CPU_H

#include "memory.hpp"
#include "opcodes.hpp"

#include <array>
#include <bitset>
#include <cinttypes>
#include <functional>
#include <spdlog/spdlog.h>

using flag_t = uint8_t;
using reg_t = uint8_t;

struct CPU {
	enum FLAGS : unsigned short {
		C,
		Z,
		I,
		D,
		B,
		V,
		N,
		FLAGS_LENGHT,
	};

	enum FLAG_MASKS : unsigned short {
		C_M = 1U << C,
		Z_M = 1U << Z,
		I_M = 1U << I,
		D_M = 1U << D,
		B_M = 1U << B,
		V_M = 1U << V,
		N_M = 1U << N,
	};
	Memory &mem;

	CPU(Memory &mem): mem { mem } { reset(); }

	reg_t A {}, X {}, Y {};
	uint16_t PC {};
	uint8_t SP {};

	flag_t flags {};

	constexpr void reset(const uint16_t start_address = 0xFFFC) {
		PC = start_address;
		SP = 0xFF;
		flags = 0x00;
		A = X = Y = 0;
	}

	constexpr uint32_t execute(const uint32_t cycles = 1) {
		m_cycles = 0;
		while (m_cycles < cycles) { call(fetch_byte()); }
		return m_cycles;
	}

   private:
	using opcode_functions_array = std::array<std::function<void(CPU &)>, 0xFF>;
	void call(uint8_t opcode) {
		static const opcode_functions_array opcodes = gen_opcode_functions();
		auto func = opcodes[opcode];
		if (!func) {
			spdlog::critical(
				"function with opcode: {} not implemented", opcode
			);
		}
		func(*this);
	}

	opcode_functions_array gen_opcode_functions();

	constexpr void load_register(reg_t &reg, uint16_t address) {
		reg = read_byte(address);
		set_ZN_flags(reg);
	}

	constexpr void transfer_register(reg_t &reg_to, reg_t reg_from) {
		++m_cycles;
		load_value(reg_to, reg_from);
	}

	constexpr void ora(reg_t &reg, uint16_t address) {
		reg = reg | read_byte(address);
		set_ZN_flags(reg);
	}

	constexpr void bit_test(uint16_t address) {
		const auto mem_val = read_byte(address);
		flags = (flags & ~Z_M) | !!(mem_val & A) << Z;
		flags = (flags & ~V_M & ~N_M) | (mem_val & 0xC0);
	}

	constexpr void lsr(uint16_t address) {
		m_cycles += 2;
		uint8_t &byte = mem[address];
		lsr_byte(byte);
	}

	constexpr void lsr_byte(uint8_t &byte) {
		++m_cycles;
		flags = (flags & ~C_M) | ((byte & 1U) << C);
		byte = byte >> 1U;
		set_ZN_flags(byte);
	}
	constexpr void rol(const uint16_t address) {
		m_cycles += 2;
		rol_byte(mem[address]);
	}

	constexpr void rol_byte(uint8_t &byte) {
		++m_cycles;
		const auto carry = flags & C_M;
		flags = (flags & ~C_M) | (!!(byte & (1 << 7)) << C);
		byte = (byte << 1U) | carry;
		set_ZN_flags(byte);
	}

	constexpr void ror(const uint16_t address) {
		m_cycles += 2;
		ror_byte(mem[address]);
	}

	constexpr void ror_byte(uint8_t &byte) {
		++m_cycles;
		const auto carry = flags & C_M;
		flags = (flags & ~C_M) | ((byte & 1U) << C);
		byte = (byte >> 1U) | carry << 7;
		set_ZN_flags(byte);
	}

	constexpr void sbc(const uint16_t address) { sbc_byte(read_byte(address)); }

	constexpr void sbc_byte(const uint8_t byte) {
		const uint16_t res = A - byte - !(flags & C_M);
		A = static_cast<uint8_t>(res);
		const uint8_t overflow = !!(res & 0x0100);
		flags = (flags & ~C_M) | (overflow << C);
		set_ZN_flags(A);
	};

	constexpr uint8_t addr_zero_page() { return fetch_byte(); }

	constexpr uint8_t addr_zero_page_X() {
		++m_cycles;
		return fetch_byte() + X;
	}

	constexpr uint8_t addr_zero_page_Y() {
		++m_cycles;
		return fetch_byte() + Y;
	}

	constexpr uint16_t addr_absolute() { return fetch_word(); }

	constexpr uint16_t addr_absolute_X(bool check_page_cross = true) {
		auto word = fetch_word();
		auto word_X = word + X;
		if (check_page_cross) add_cycle_if_page_crossed(word, word_X);
		else
			++m_cycles;
		return word_X;
	}

	constexpr uint16_t addr_absolute_Y(bool check_page_cross = true) {
		const auto word = fetch_word();
		auto word_Y = word + Y;
		if (check_page_cross) add_cycle_if_page_crossed(word, word_Y);
		else
			++m_cycles;
		return word_Y;
	}

	constexpr uint16_t addr_indirect_X() {
		return read_word(addr_zero_page_X());
	}
	constexpr uint16_t addr_indirect_Y(bool check_page_cross = true) {
		const auto word = read_word(addr_zero_page());
		auto word_Y = word + Y;
		if (check_page_cross) add_cycle_if_page_crossed(word, word_Y);
		else
			++m_cycles;
		return word_Y;
	}

	constexpr uint16_t fetch_word() { return fetch_byte() | fetch_byte() << 8; }

	constexpr uint16_t read_word(uint16_t address) {
		return read_byte(address) | read_byte(address + 1) << 8;
	}

	constexpr void write_word(uint16_t value, uint16_t address) {
		write_byte(value & 0xFF, address);
		write_byte(value >> 8, address + 1);
	}

	constexpr uint8_t fetch_byte() {
		++m_cycles;
		return mem[PC++];
	}

	constexpr uint8_t read_byte(uint16_t address) {
		++m_cycles;
		return mem[address];
	}

	constexpr void write_byte(uint8_t value, uint16_t address) {
		++m_cycles;
		mem[address] = value;
	}

	constexpr void push_byte(uint8_t value) {
		++m_cycles;
		write_byte(value, SP-- | 0x0100);
	}

	constexpr uint8_t pull_byte() {
		++m_cycles;
		const uint16_t address = ++SP | 0x0100;
		return read_byte(address);
	}

	/*		HELPERS			*/

	constexpr void load_value(reg_t &reg, uint8_t value) {
		reg = value;
		set_ZN_flags(reg);
	}

	constexpr void set_ZN_flags(reg_t reg) {
		flags = (flags & ~Z_M) | (!reg << Z);
		flags = (flags & ~N_M) | (!!(reg & (1U << 7)) << N);
	}

	constexpr void
	add_cycle_if_page_crossed(uint16_t old_word, uint16_t new_word) {
		if ((old_word ^ new_word) >> 8) ++m_cycles;
	}

	/*		PRIVATE VARIABLES	*/

	uint32_t m_cycles {};
};

#endif
