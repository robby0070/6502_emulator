#include "util.hpp"

#include <bitset>
#include <catch2/catch.hpp>
#include <iostream>

void test_unchaged_flags(
	flag_type old_flags,
	flag_type new_flags,
	flag_type flags_mask
) {
	REQUIRE((old_flags & flags_mask) == (new_flags & flags_mask));
}

void test_execution(
	uint8_t expected_value,
	uint8_t actual_value,
	uint32_t expected_cycles,
	uint32_t actual_cycles
) {
	REQUIRE(actual_value == expected_value);
	REQUIRE(actual_cycles == expected_cycles);
}

void test_ZN_flags(
	const uint8_t value,
	const flag_type old_flags,
	const flag_type new_flags
) {
	test_unchaged_flags(old_flags, new_flags, ~(CPU::Z_M | CPU::N_M));
	REQUIRE(!!value == !(new_flags & CPU::Z_M));
	REQUIRE(!!(value & 1 << 7) == !!(new_flags & CPU::N_M));
}

void test_ZNC_flags(
	const bool zero,
	const bool negative,
	const bool carry,
	const flag_type old_flags,
	const flag_type new_flags
) {
	test_unchaged_flags(
		old_flags, new_flags, ~(CPU::Z_M | CPU::N_M | CPU::C_M)
	);

	REQUIRE(zero == !!(new_flags & CPU::Z_M));
	REQUIRE(negative == !!(new_flags & CPU::N_M));
	REQUIRE(carry == !!(new_flags & CPU::C_M));
}