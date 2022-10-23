#ifndef UTIL_H
#define UTIL_H
#include "../src/cpu.hpp"

#include <cinttypes>

void test_unchaged_flags(flag_type, flag_type, flag_type);

void test_execution(uint8_t,
	 uint8_t,
	 uint32_t,
	 uint32_t);

void test_ZNC_flags(bool,
	 bool,
	 bool,
	 flag_type,
	 flag_type);

void test_ZN_flags(flag_type, flag_type, uint8_t);

#endif
