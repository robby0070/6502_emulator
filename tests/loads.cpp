#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("LDA IMMEDIATE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;
	constexpr uint8_t value = 0xDE;

	const auto actual_cycles = test_immediate(cpu, mem, LDA_IMMEDIATE, value);
	test_execution(value, cpu.A, 2, actual_cycles);
	test_ZN_flags(cpu.A, flags, cpu.flags);
}

TEST_CASE("LDA ZERO PAGE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;

	SECTION("ZERO PAGE") {
		const auto actual_cycles =
			test_zero_page(cpu, mem, LDA_ZERO_PAGE, 0xAF);
		test_execution(0xAF, cpu.A, 3, actual_cycles);
		test_ZN_flags(cpu.A, flags, cpu.flags);
	}

	SECTION("ZERO PAGE X") {
		const auto actual_cycles =
			test_zero_page_X(cpu, mem, LDA_ZERO_PAGE_X, 0xDE);

		test_execution(0xDE, cpu.A, 4, actual_cycles);
		test_ZN_flags(cpu.A, flags, cpu.flags);
	}

	SECTION("ZERO PAGE X WRAP") {
		const auto actual_cycles =
			test_zero_page_X(cpu, mem, LDA_ZERO_PAGE_X, 0x09);

		test_execution(0x09, cpu.A, 4, actual_cycles);
		test_ZN_flags(cpu.A, flags, cpu.flags);
	}
}

TEST_CASE("LDA ABSOLUTE", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);

	SECTION("LDA ABSOLUTE") {}
	test_absolute(cpu, mem, cpu.A, LDA_ABSOLUTE, 0xFF, 0xFF);
	test_absolute_X(cpu, mem, cpu.A, LDA_ABSOLUTE_X, 0x01, 0x01);
	test_absolute_Y(cpu, mem, cpu.A, LDA_ABSOLUTE_Y, 0x04, 0x04);
}

TEST_CASE("LDA INDIRECT", "[LDA]") {
	Memory mem {};
	CPU cpu(mem);

	test_indirect_X(cpu, mem, cpu.A, LDA_INDIRECT_X, 0x07, 0x07);
	test_indirect_Y(cpu, mem, cpu.A, LDA_INDIRECT_Y, 0x84, 0x84);
}

TEST_CASE("LDX IMMEDIATE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_immediate(cpu, mem, cpu.X, LDX_IMMEDIATE, 0xEE, 0xEE);
}

TEST_CASE("LDX ZERO PAGE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_zero_page(cpu, mem, cpu.X, LDX_ZERO_PAGE, 0x44, 0x44);
	test_zero_page(cpu, mem, cpu.X, LDX_ZERO_PAGE_Y, 0x64, 0x64);
}

TEST_CASE("LDX ABSOLUTE", "[LDX]") {
	Memory mem {};
	CPU cpu(mem);

	test_absolute(cpu, mem, cpu.X, LDX_ABSOLUTE, 0x12, 0x12);
	test_absolute_Y(cpu, mem, cpu.X, LDX_ABSOLUTE_Y, 0x18, 0x18);
}

TEST_CASE("LDY IMMEDIATE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_immediate(cpu, mem, cpu.Y, LDY_IMMEDIATE, 0x99, 0x99);
}

TEST_CASE("LDY ZERO PAGE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_zero_page(cpu, mem, cpu.Y, LDY_ZERO_PAGE, 0x73, 0x73);
	test_zero_page_X(cpu, mem, cpu.Y, LDY_ZERO_PAGE_X, 0xEE, 0xEE);
}

TEST_CASE("LDY ABSOLUTE", "[LDY]") {
	Memory mem {};
	CPU cpu(mem);

	test_absolute(cpu, mem, cpu.Y, LDY_ABSOLUTE, 0xAF, 0xAF);
	test_absolute_X(cpu, mem, cpu.Y, LDY_ABSOLUTE_X, 0xFF, 0xFF);
}
TEST_CASE("JSR", "[CPU]") {
	cpu.reset(0xFF00);
	mem[0xFF00] = JSR;
	mem[0xFF01] = 0x34;
	mem[0xFF02] = 0x12;
	CPU cpu_copy = cpu;

	const auto actual_cycles = cpu.execute(6);

	REQUIRE(actual_cycles == 6);
	REQUIRE(cpu.SP == cpu_copy.SP - 2);
	REQUIRE(cpu.PC == 0x1234);
}