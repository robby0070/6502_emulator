#ifndef MEMORY_H
#define MEMORY_H

#include <algorithm>
#include <array>
#include <cinttypes>
#include <cstdio>
#include <iterator>

using mem_t = std::array<uint8_t, 1024 * 64>;
struct Memory {
	constexpr uint8_t &operator[](uint32_t address) { return data[address]; }

	constexpr void dump(bool compress = true) {
		auto print_byte = [address = 0, compress](const uint8_t byte) mutable {
			if (!compress || byte != 0) printf("%04X\t%X\n", address, byte);
			++address;
		};
		for (const auto byte : data) print_byte(byte);
	}
	constexpr mem_t::iterator begin() noexcept { return data.begin(); }
	constexpr mem_t::const_iterator begin() const noexcept {
		return data.begin();
	}
	constexpr mem_t::const_iterator cbegin() const noexcept {
		return data.cbegin();
	}

   private:
	mem_t data {};
};

#endif
