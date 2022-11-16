#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>
#include <cstdint>
#include <math.h>

void test_branch(
	CPU &cpu,
	const opcode_type opcode,
	const uint8_t flag_to_check,
	const bool set,
	const int8_t offset
) {
	const auto flags = cpu.flags;
	cpu.mem[0xFFFC] = opcode;
	cpu.mem[0xFFFD] = offset;

	uint16_t expected_PC = cpu.PC + 2;
	uint32_t cycles = 2;
	if (!!(cpu.flags & 1 << flag_to_check) == set) {
		++cycles;
		const uint8_t curr_page = cpu.PC >> 8;
		expected_PC += offset;
		const uint8_t new_page = expected_PC >> 8;
		if (curr_page != new_page) { ++cycles; }
	}
	const auto actual_cycles = cpu.execute();
	test_execution(expected_PC, cpu.PC, cycles, actual_cycles);
	test_unchaged_flags(flags, cpu.flags, 0xFF);
}

TEST_CASE("BCC") {
	INIT_TEST
	SECTION("BCC NEGATIVE") { test_branch(cpu, BCC, CPU::C, false, 0xA0); }
	SECTION("BCC POSITIVE") { test_branch(cpu, BCC, CPU::C, false, 10); }
	(void)flags;
}

TEST_CASE("BCS") {
	INIT_TEST
	SECTION("BCS NEGATIVE") { test_branch(cpu, BCS, CPU::C, true, -12); }
	SECTION("BCS POSITIVE") { test_branch(cpu, BCS, CPU::C, true, 80); }
	(void)flags;
}

TEST_CASE("BMI") {
	INIT_TEST
	SECTION("BMI NEGATIVE") { test_branch(cpu, BMI, CPU::N, true, -128); }
	SECTION("BMI POSITIVE") { test_branch(cpu, BMI, CPU::N, true, 127); }
	(void)flags;
}

TEST_CASE("BNE") {
	INIT_TEST
	SECTION("BNE NEGATIVE") { test_branch(cpu, BNE, CPU::Z, false, -1); }
	SECTION("BNE POSITIVE") { test_branch(cpu, BNE, CPU::Z, false, 1); }
	(void)flags;
}

TEST_CASE("BPL") {
	INIT_TEST
	SECTION("BPL NEGATIVE") { test_branch(cpu, BPL, CPU::N, false, -12); }
	SECTION("BPL POSITIVE") { test_branch(cpu, BPL, CPU::N, false, 10); }
	(void)flags;
}

TEST_CASE("BVC") {
	INIT_TEST
	SECTION("BVC NEGATIVE") { test_branch(cpu, BVC, CPU::V, false, -88); }
	SECTION("BVC POSITIVE") { test_branch(cpu, BVC, CPU::V, false, 99); }
	(void)flags;
}

TEST_CASE("BVS") {
	INIT_TEST
	SECTION("BVS NEGATIVE") { test_branch(cpu, BVS, CPU::V, true, -123); }
	SECTION("BVS POSITIVE") { test_branch(cpu, BVS, CPU::V, true, 22); }
	(void)flags;
}
