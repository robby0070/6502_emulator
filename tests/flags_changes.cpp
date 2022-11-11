#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("CLC") {
	INIT_TEST

	mem[0xFFFC] = CLC;
	const auto actual_cycles = cpu.execute();

	test_execution(flags & ~CPU::C_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::C_M);
}
TEST_CASE("CLD") {
	INIT_TEST

	mem[0xFFFC] = CLD;
	const auto actual_cycles = cpu.execute();

	test_execution(flags & ~CPU::D_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::D_M);
}

TEST_CASE("CLI") {
	INIT_TEST

	mem[0xFFFC] = CLI;
	const auto actual_cycles = cpu.execute();

	test_execution(flags & ~CPU::I_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::I_M);
}

TEST_CASE("CLV") {
	INIT_TEST

	mem[0xFFFC] = CLV;
	const auto actual_cycles = cpu.execute();

	test_execution(flags & ~CPU::V_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::V_M);
}

TEST_CASE("SEC") {
	INIT_TEST

	mem[0xFFFC] = SEC;
	const auto actual_cycles = cpu.execute();

	test_execution(flags | CPU::C_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::C_M);
}

TEST_CASE("SED") {
	INIT_TEST

	mem[0xFFFC] = SED;
	const auto actual_cycles = cpu.execute();

	test_execution(flags | CPU::D_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::D_M);
}

TEST_CASE("SEI") {
	INIT_TEST

	mem[0xFFFC] = SEI;
	const auto actual_cycles = cpu.execute();

	test_execution(flags | CPU::I_M, cpu.flags, actual_cycles, 2);
	test_unchaged_flags(flags, cpu.flags, ~CPU::I_M);
}