#include "cpu.hpp"
#include "memory.hpp"

#include <spdlog/spdlog.h>

int main() {
	spdlog::set_level(spdlog::level::trace);
	spdlog::info("Hello world");
}
