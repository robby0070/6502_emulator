#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

// TODO: implement BRK

TEST_CASE("NOP") {
	INIT_TEST
	mem[0xFFFC] = NOP;

	const auto actual_cycles = cpu.execute();
	test_execution(0x00, 0x00, 2, actual_cycles);
	test_unchaged_flags(flags, cpu.flags, 0xFF);
}

// TEST_CASE("RTI") {
// 	SECTION("RTI IMPLIED") {
// 		Memory mem {};
// 		CPU cpu { mem };
// 		constexpr uint32_t cycles = 6;
// 		constexpr uint8_t value_flags = 0x11;
// 		constexpr uint8_t value_PC = 0x22;

// 		cpu.A = value_PC;
// 		mem[0xFFFC] = PHA;
// 		cpu.execute();

// 		cpu.A = value_flags;
// 		mem[0xFFFD] = PHA;
// 		cpu.execute();

// 		mem[0xFFFE] = RTI;

// 		const auto actual_cycles = cpu.execute();
// 		REQUIRE(cpu.PC == value_PC);
// 		test_execution(value_flags, cpu.flags, cycles, actual_cycles);
// 	}
// }
