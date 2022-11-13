#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("JMP") {
	SECTION("JMP ABSOLUTE") {
		INIT_TEST
		mem[0xFFFC] = JMP_ABSOLUTE;
		mem[0xFFFD] = 0x99;
		mem[0xFFFE] = 0x66;
		const auto actual_cycles = cpu.execute();
		CHECK(cpu.PC == 0x6699);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
		CHECK(actual_cycles == 3);
	}
	SECTION("JMP INDIRECT") {
		INIT_TEST
		mem[0xFFFC] = JMP_INDIRECT;
		mem[0xFFFD] = 0x99;
		mem[0xFFFE] = 0x66;
		mem[0x6699] = 0xEF;
		mem[0x669A] = 0xBE;
		const auto actual_cycles = cpu.execute();
		CHECK(cpu.PC == 0xBEEF);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
		CHECK(actual_cycles == 5);
	}
}

TEST_CASE("JSR", "[CPU]") {
	SECTION("JSR ABSOLUTE") {
		INIT_TEST

		mem[0xFFFC] = JSR;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		const auto actual_cycles = cpu.execute();
		CHECK(cpu.PC == 0x1234);
		CHECK(
			(mem[0x0100 | cpu.SP + 1] | mem[0x0100 | cpu.SP + 2] << 8) == 0xFFFE
		);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
		CHECK(actual_cycles == 6);
	}
}

TEST_CASE("RTS", "[PULL STACK]") {
	SECTION("RTS IMPLIED") {
		INIT_TEST;

		mem[0xFFFC] = JSR;
		mem[0xFFFD] = 0x70;
		mem[0xFFFE] = 0x77;
		mem[0x7770] = RTS;
		const auto actual_cycles = cpu.execute(7) - 6;
		CHECK(cpu.PC == 0xFFFF);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
		CHECK(actual_cycles);
	}
}