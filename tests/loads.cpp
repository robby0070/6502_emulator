#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("LDA IMMEDIATE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;
	constexpr auto value = 0xDE;

	test_immediate(cpu, mem, LDA_IMMEDIATE, cpu.A, value, value, 2);
	test_ZN_flags(cpu.A, flags, cpu.flags);
}

TEST_CASE("LDA ZERO PAGE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;
	test_zero_page(cpu, mem, LDA_ZERO_PAGE, cpu.A, 0xAF, 0xAF, 3);
	test_zero_page_X(cpu, mem, LDA_ZERO_PAGE_X, cpu.A, 0xDE, 0xDE, 4);
	test_ZN_flags(cpu.A, flags, cpu.flags);
}

TEST_CASE("LDA ABSOLUTE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);

	test_absolute(cpu, mem, LDA_ABSOLUTE, cpu.A, 0xFF, 0xFF, 4);
	test_absolute_X(cpu, mem, LDA_ABSOLUTE_X, cpu.A, 0x01, 0x01, 4, true);
	test_absolute_Y(cpu, mem, LDA_ABSOLUTE_Y, cpu.A, 0x04, 0x04, 4, true);
}

TEST_CASE("LDA INDIRECT", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);

	test_indirect_X(cpu, mem, LDA_INDIRECT_X, cpu.A, 0x07, 0x07, 6);
	test_indirect_Y(cpu, mem, LDA_INDIRECT_Y, cpu.A, 0x84, 0x84, 5);
}

TEST_CASE("LDX IMMEDIATE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_immediate(cpu, mem, LDX_IMMEDIATE, cpu.X, 0xEE, 0xEE, 2);
}

TEST_CASE("LDX ZERO PAGE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_zero_page(cpu, mem, LDX_ZERO_PAGE, cpu.X, 0x44, 0x44, 3);
	test_zero_page_Y(cpu, mem, LDX_ZERO_PAGE_Y, cpu.X, 0x64, 0x64, 4);
}

TEST_CASE("LDX ABSOLUTE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_absolute(cpu, mem, LDX_ABSOLUTE, cpu.X, 0x12, 0x12, 4);
	test_absolute_Y(cpu, mem, LDX_ABSOLUTE_Y, cpu.X, 0x18, 0x18, 4, true);
}

TEST_CASE("LDY IMMEDIATE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_immediate(cpu, mem, LDY_IMMEDIATE, cpu.Y, 0x99, 0x99, 2);
}

TEST_CASE("LDY ZERO PAGE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_zero_page(cpu, mem, LDY_ZERO_PAGE, cpu.Y, 0x73, 0x73, 3);
	test_zero_page_X(cpu, mem, LDY_ZERO_PAGE_X, cpu.Y, 0xEE, 0xEE, 4);
}

TEST_CASE("LDY ABSOLUTE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_absolute(cpu, mem, LDY_ABSOLUTE, cpu.Y, 0xAF, 0xAF, 4);
	test_absolute_X(cpu, mem, LDY_ABSOLUTE_X, cpu.Y, 0xFF, 0xFF, 4, true);
}
// TEST_CASE("JSR", "[CPU]") {
// 	cpu.reset(0xFF00);
// 	mem[0xFF00] = JSR;
// 	mem[0xFF01] = 0x34;
// 	mem[0xFF02] = 0x12;
// 	CPU cpu_copy = cpu;

// 	const auto actual_cycles = cpu.execute(6);

// 	REQUIRE(actual_cycles == 6);
// 	REQUIRE(cpu.SP == cpu_copy.SP - 2);
// 	REQUIRE(cpu.PC == 0x1234);
// }