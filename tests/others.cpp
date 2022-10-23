#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

// TEST_CASE("NOP", "[OTHER]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	auto flags = cpu.flags;

// 	constexpr uint32_t cycles = 2;
// 	mem[0xFFFC] = NOP;

// 	const auto actual_cycles = cpu.execute();
// 	test_unchaged_flags(flags, cpu.flags, 0xFF);
// 	test_execution(0x00, 0x00, cycles, actual_cycles);
// }

// // FIXME: fix tests
// TEST_CASE("SBC IMMEDIATE", "[SBC]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	cpu.A = 10;
// 	cpu.flags = cpu.flags | CPU::C_M;
// 	test_immediate(cpu, mem, cpu.A, SBC_IMMEDIATE, 12, -2);
// }

// TEST_CASE("SBC ZERO PAGE", "[SBC]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	cpu.A = 127;
// 	cpu.flags = cpu.flags | CPU::C_M;
// 	test_zero_page(cpu, mem, cpu.A, SBC_ZERO_PAGE, -8, -121);
// 	cpu.A = 11;
// 	test_zero_page_X(cpu, mem, cpu.A, SBC_ZERO_PAGE_X, 5, 6);
// }

// TEST_CASE("SBC ABSOLUTE", "[SBC]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	cpu.A = 127;
// 	cpu.flags = cpu.flags | CPU::C_M;
// 	test_absolute(cpu, mem, cpu.A, SBC_ABSOLUTE, -8, -121);
// 	cpu.A = 11;
// 	test_absolute_X(cpu, mem, cpu.A, SBC_ABSOLUTE_X, 5, 6);
// 	cpu.A = 29;
// 	test_absolute_Y(cpu, mem, cpu.A, SBC_ABSOLUTE_Y, 35, -6);
// }

// TEST_CASE("SBC INDIRECT", "[SBC]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	cpu.A = 20;
// 	cpu.flags = cpu.flags | CPU::C_M;
// 	test_indirect_X(cpu, mem, cpu.A, SBC_INDIRECT_X, -10, 30);
// 	cpu.A = 29;
// 	test_indirect_Y(cpu, mem, cpu.A, SBC_INDIRECT_Y, 3, 26);
// }

// TEST_CASE("SEC", "[OTHER]") {
// 	Memory mem {};
// 	CPU cpu { mem };
// 	const auto flags = cpu.flags;

// 	mem[0xFFFC] = SEC;
// 	const cpu.execute():

// 	test_unchaged_flags(flags, cpu.flags, ~CPU::C_M);
// }