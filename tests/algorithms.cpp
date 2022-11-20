#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>
#include <cstdint>
#include <sstream>

TEST_CASE("FIBONACCI") {
	// INIT_TEST_ONCE(0x0D, 20);
	Memory mem {};
	CPU cpu { mem };
	constexpr uint8_t expected_value = 0x0D;
	uint8_t prg[] = {
		0x00, 0x00, 0xa2, 0x01, 0x86, 0x00, 0x38, 0xa0, 0x07, 0x98,
		0xe9, 0x03, 0xa8, 0x18, 0xa9, 0x02, 0x85, 0x01, 0xa6, 0x01,
		0x65, 0x00, 0x85, 0x01, 0x86, 0x00, 0x88, 0xd0, 0xf5,
	};
	std::basic_string<uint8_t> str(prg, 29);
	std::basic_stringstream<uint8_t> stream { str };
	auto start_addr = cpu.load_prg(stream);
	cpu.PC = start_addr;
	cpu.execute(999);
	CHECK(hex_to_string(cpu.A) == hex_to_string(expected_value));
}
