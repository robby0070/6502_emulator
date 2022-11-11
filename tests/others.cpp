#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>



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
