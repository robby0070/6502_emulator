#include "util.hpp"

#include <bitset>
#include <catch2/catch.hpp>
#include <cstdint>
#include <fmt/format.h>
#include <sstream>

void test_unchaged_flags(
	flag_t old_flags,
	flag_t new_flags,
	flag_t flags_mask
) {
	CHECK((old_flags & flags_mask) == (new_flags & flags_mask));
}

std::string hex_to_string(const uint32_t value) {
	std::stringstream ss;
	ss << fmt::format("{:#010x}", value);
	return ss.str();
}

std::string hex_to_string(const uint16_t value) {
	std::stringstream ss;
	ss << fmt::format("{:#08x}", value);
	return ss.str();
}

std::string hex_to_string(const uint8_t value) {
	std::stringstream ss;
	ss << fmt::format("{:#04x}", value);
	return ss.str();
}

void test_execution(
	uint8_t expected_value,
	uint8_t actual_value,
	uint32_t expected_cycles,
	uint32_t actual_cycles
) {
	// there is no way that i know of to change the default print of catch2,
	// this are the defaults:
	// 		- uint8_t is printed as a char
	//		- uint32_t is printed as a deciman number
	// in this case i really prefer to show hex value so i'm converting them to
	// strings
	CHECK(hex_to_string(actual_value) == hex_to_string(expected_value));
	CHECK(hex_to_string(actual_cycles) == hex_to_string(expected_cycles));
}

void test_execution(
	uint16_t expected_value,
	uint16_t actual_value,
	uint32_t expected_cycles,
	uint32_t actual_cycles
) {
	CHECK(hex_to_string(actual_value) == hex_to_string(expected_value));
	CHECK(hex_to_string(actual_cycles) == hex_to_string(expected_cycles));
}

void test_ZN_flags(
	const uint8_t value,
	const flag_t old_flags,
	const flag_t new_flags
) {
	test_unchaged_flags(old_flags, new_flags, ~(CPU::Z_M | CPU::N_M));
	CHECK(!!value == !(new_flags & CPU::Z_M));
	CHECK(!!(value & 1 << 7) == !!(new_flags & CPU::N_M));
}

void test_ZNC_flags(
	const flag_t old_flags,
	const flag_t new_flags,
	const flag_t value,
	const bool carry
) {
	test_unchaged_flags(
		old_flags, new_flags, ~(CPU::Z_M | CPU::N_M | CPU::C_M)
	);

	CHECK(!!value == !(new_flags & CPU::Z_M));
	CHECK(!!(value & 1 << 7) == !!(new_flags & CPU::N_M));
	CHECK(carry == !!(new_flags & CPU::C_M));
}
