#ifndef UTIL_H
#define UTIL_H
#include "../src/cpu.hpp"

#include <cinttypes>
#include <string>

std::string hex_to_string(const uint32_t);

void test_unchaged_flags(flag_t, flag_t, flag_t);

void test_execution(uint8_t, uint8_t, uint32_t, uint32_t);

void test_ZNC_flags(bool, bool, bool, flag_t, flag_t);

void test_ZN_flags(flag_t, flag_t, uint8_t);

#endif
