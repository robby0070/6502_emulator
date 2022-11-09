#ifndef UTIL_H
#define UTIL_H
#include "../src/cpu.hpp"

#include <cinttypes>
#include <string>

#define INIT_TEST \
	Memory mem {}; \
	CPU cpu(mem); \
	auto flags = cpu.flags;

#define INIT_TEST_ONCE(v, c) \
	Memory mem {}; \
	CPU cpu(mem); \
	auto flags = cpu.flags; \
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
