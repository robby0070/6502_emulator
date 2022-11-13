#ifndef UTIL_H
#define UTIL_H
#include "../src/cpu.hpp"

#include <catch2/catch.hpp>
#include <cinttypes>
#include <string>

#define INIT_TEST \
	Memory mem {}; \
	CPU cpu(mem); \
	cpu.A = GENERATE(take(2, random(0, 0xFF))); \
	cpu.X = GENERATE(take(2, random(0, 0xFF))); \
	cpu.Y = GENERATE(take(2, random(0, 0xFF))); \
	cpu.flags = GENERATE(take(2, random(0, 0xFF))); \
	auto flags = cpu.flags;

#define INIT_TEST_ONCE(v, c) \
	INIT_TEST \
	uint8_t value = v; \
	uint32_t cycles = c;

std::string hex_to_string(const uint32_t);

void test_unchaged_flags(flag_t, flag_t, flag_t);

void test_execution(uint8_t, uint8_t, uint32_t, uint32_t);

void test_ZNC_flags(
	const flag_t old_flags,
	const flag_t new_flags,
	const flag_t value,
	const bool carry
);

void test_ZN_flags(uint8_t value, flag_t old_flags, flag_t new_flags);

#endif
