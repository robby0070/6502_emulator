#ifndef UTIL_H
#define UTIL_H
#include "../src/cpu.hpp"

#include <cinttypes>
#include <string>

#define INIT_TEST \
	Memory mem {}; \
	CPU cpu(mem); \
	const auto flags = cpu.flags;

#define INIT_TEST_ONCE(v, c) \
	Memory mem {}; \
	CPU cpu(mem); \
	const auto flags = cpu.flags; \
	constexpr uint8_t value = v; \
	constexpr uint32_t cycles = c;

std::string hex_to_string(const uint32_t);

void test_unchaged_flags(flag_t, flag_t, flag_t);

void test_execution(uint8_t, uint8_t, uint32_t, uint32_t);

void test_ZNC_flags(bool, bool, bool, flag_t, flag_t);

void test_ZN_flags(flag_t, flag_t, uint8_t);

#endif
