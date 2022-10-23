#ifndef MEMORY_H
#define MEMORY_H

#include <algorithm>
#include <cinttypes>
#include <cstdio>

struct Memory {
	constexpr uint8_t &operator[](uint32_t address) { return data[address]; }

	constexpr void dump(bool compress = true) {
		auto print_byte = [address = 0, compress](const uint8_t byte) mutable {
			if (!compress || byte != 0) printf("%04X\t%X\n", address, byte);
			++address;
		};
		for (const auto byte : data) print_byte(byte);
	}

   private:
	std::array<uint8_t, 1024 * 64> data {};
};

#endif