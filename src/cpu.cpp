#include "cpu.hpp"

CPU::opcode_functions_array CPU::gen_opcode_functions() {
	opcode_functions_array opcodes;

	//		LDA
	opcodes[LDA_IMMEDIATE] = [](CPU &cpu) {
		cpu.load_value(cpu.A, cpu.fetch_byte());
	};

	opcodes[LDA_ZERO_PAGE] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_zero_page());
	};
	opcodes[LDA_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_zero_page_X());
	};

	opcodes[LDA_ABSOLUTE] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_absolute());
	};
	opcodes[LDA_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_absolute_X());
	};
	opcodes[LDA_ABSOLUTE_Y] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_absolute_Y());
	};

	opcodes[LDA_INDIRECT_X] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_indirect_X());
	};
	opcodes[LDA_INDIRECT_Y] = [](CPU &cpu) {
		cpu.load_register(cpu.A, cpu.addr_indirect_Y());
	};

	//		LDX
	opcodes[LDX_IMMEDIATE] = [](CPU &cpu) {
		cpu.load_value(cpu.X, cpu.fetch_byte());
	};
	opcodes[LDX_ZERO_PAGE] = [](CPU &cpu) {
		cpu.load_register(cpu.X, cpu.addr_zero_page());
	};
	opcodes[LDX_ZERO_PAGE_Y] = [](CPU &cpu) {
		cpu.load_register(cpu.X, cpu.addr_zero_page_Y());
	};
	opcodes[LDX_ABSOLUTE] = [](CPU &cpu) {
		cpu.load_register(cpu.X, cpu.addr_absolute());
	};
	opcodes[LDX_ABSOLUTE_Y] = [](CPU &cpu) {
		cpu.load_register(cpu.X, cpu.addr_absolute_Y());
	};

	//		LDY
	opcodes[LDY_IMMEDIATE] = [](CPU &cpu) {
		cpu.load_value(cpu.Y, cpu.fetch_byte());
	};
	opcodes[LDY_ZERO_PAGE] = [](CPU &cpu) {
		cpu.load_register(cpu.Y, cpu.addr_zero_page());
	};
	opcodes[LDY_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.load_register(cpu.Y, cpu.addr_zero_page_X());
	};
	opcodes[LDY_ABSOLUTE] = [](CPU &cpu) {
		cpu.load_register(cpu.Y, cpu.addr_absolute());
	};
	opcodes[LDY_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.load_register(cpu.Y, cpu.addr_absolute_X());
	};

	// STA
	opcodes[STA_ZERO_PAGE] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_zero_page());
	};
	opcodes[STA_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_zero_page_Y());
	};
	opcodes[STA_ABSOLUTE] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_absolute());
	};
	opcodes[STA_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_zero_page_Y());
	};
	opcodes[STA_ABSOLUTE] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_absolute());
	};
	opcodes[STA_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_absolute_X(false));
	};
	opcodes[STA_ABSOLUTE_Y] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_absolute_Y(false));
	};
	opcodes[STA_INDIRECT_X] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_indirect_X());
	};
	opcodes[STA_INDIRECT_Y] = [](CPU &cpu) {
		cpu.write_byte(cpu.A, cpu.addr_indirect_Y(false));
	};
	// STX
	opcodes[STX_ZERO_PAGE] = [](CPU &cpu) {
		cpu.write_byte(cpu.X, cpu.addr_zero_page());
	};
	opcodes[STX_ZERO_PAGE_Y] = [](CPU &cpu) {
		cpu.write_byte(cpu.X, cpu.addr_zero_page_Y());
	};
	opcodes[STX_ABSOLUTE] = [](CPU &cpu) {
		cpu.write_byte(cpu.X, cpu.addr_absolute());
	};
	// STY
	opcodes[STY_ZERO_PAGE] = [](CPU &cpu) {
		cpu.write_byte(cpu.Y, cpu.addr_zero_page());
	};
	opcodes[STY_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.write_byte(cpu.Y, cpu.addr_zero_page_Y());
	};
	opcodes[STY_ABSOLUTE] = [](CPU &cpu) {
		cpu.write_byte(cpu.Y, cpu.addr_absolute());
	};

	opcodes[TAX] = [](CPU &cpu) { cpu.transfer_register(cpu.X, cpu.A); };
	opcodes[TAY] = [](CPU &cpu) { cpu.transfer_register(cpu.Y, cpu.A); };
	opcodes[TXA] = [](CPU &cpu) { cpu.transfer_register(cpu.A, cpu.X); };
	opcodes[TYA] = [](CPU &cpu) { cpu.transfer_register(cpu.A, cpu.Y); };

	//		LSR
	opcodes[LSR] = [](CPU &cpu) { cpu.lsr_byte(cpu.A); };

	opcodes[LSR_ZERO_PAGE] = [](CPU &cpu) { cpu.lsr(cpu.addr_zero_page()); };
	opcodes[LSR_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.lsr(cpu.addr_zero_page_X());
	};

	opcodes[LSR_ABSOLUTE] = [](CPU &cpu) { cpu.lsr(cpu.addr_absolute()); };
	opcodes[LSR_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.lsr(cpu.addr_absolute_X(false));
	};

	//		NOP
	opcodes[NOP] = [](CPU &cpu) { ++cpu.m_cycles; };

	//		ORA
	opcodes[ORA_IMMEDIATE] = [](CPU &cpu) {
		cpu.A = cpu.A | cpu.fetch_byte();
		cpu.set_ZN_flags(cpu.A);
	};

	opcodes[ORA_ZERO_PAGE] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_zero_page());
	};
	opcodes[ORA_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_zero_page_X());
	};

	opcodes[ORA_ABSOLUTE] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_absolute());
	};
	opcodes[ORA_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_absolute_X());
	};
	opcodes[ORA_ABSOLUTE_Y] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_absolute_Y());
	};

	opcodes[ORA_INDIRECT_X] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_indirect_X());
	};
	opcodes[ORA_INDIRECT_Y] = [](CPU &cpu) {
		cpu.ora(cpu.A, cpu.addr_indirect_Y());
	};

	//		PHA
	opcodes[PHA] = [](CPU &cpu) { cpu.push_byte(cpu.A); };

	//		PHP
	opcodes[PHP] = [](CPU &cpu) { cpu.push_byte(cpu.flags); };

	// 		PL
	opcodes[PLA] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.A = cpu.pull_byte();
		cpu.set_ZN_flags(cpu.A);
	};
	opcodes[PLP] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.flags = cpu.pull_byte();
	};

	//		ROL
	opcodes[ROL] = [](CPU &cpu) { cpu.rol_byte(cpu.A); };

	opcodes[ROL_ZERO_PAGE] = [](CPU &cpu) { cpu.rol(cpu.addr_zero_page()); };
	opcodes[ROL_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.rol(cpu.addr_zero_page_X());
	};

	opcodes[ROL_ABSOLUTE] = [](CPU &cpu) { cpu.rol(cpu.addr_absolute()); };
	opcodes[ROL_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.rol(cpu.addr_absolute_X(false));
	};

	//		ROR
	opcodes[ROR] = [](CPU &cpu) { cpu.ror_byte(cpu.A); };

	opcodes[ROR_ZERO_PAGE] = [](CPU &cpu) { cpu.ror(cpu.addr_zero_page()); };
	opcodes[ROR_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.ror(cpu.addr_zero_page_X());
	};

	opcodes[ROR_ABSOLUTE] = [](CPU &cpu) { cpu.ror(cpu.addr_absolute()); };
	opcodes[ROR_ABSOLUTE_X] = [](CPU &cpu) {
		cpu.ror(cpu.addr_absolute_X(false));
	};

	//		RTI
	opcodes[RTI] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.flags = cpu.pull_byte();
		cpu.PC = cpu.pull_byte();
	};

	//		RTS
	opcodes[RTS] = [](CPU &cpu) {
		cpu.m_cycles += 3;
		cpu.PC = cpu.pull_byte() - 1;
	};

	//		SBC
	opcodes[SBC_IMMEDIATE] = [](CPU &cpu) { cpu.sbc_byte(cpu.fetch_byte()); };

	opcodes[SBC_ZERO_PAGE] = [](CPU &cpu) { cpu.sbc(cpu.addr_zero_page()); };
	opcodes[SBC_ZERO_PAGE_X] = [](CPU &cpu) {
		cpu.sbc(cpu.addr_zero_page_X());
	};

	opcodes[SBC_ABSOLUTE] = [](CPU &cpu) { cpu.sbc(cpu.addr_absolute()); };
	opcodes[SBC_ABSOLUTE_X] = [](CPU &cpu) { cpu.sbc(cpu.addr_absolute_X()); };
	opcodes[SBC_ABSOLUTE_Y] = [](CPU &cpu) { cpu.sbc(cpu.addr_absolute_Y()); };

	opcodes[SBC_INDIRECT_X] = [](CPU &cpu) { cpu.sbc(cpu.addr_indirect_X()); };
	opcodes[SBC_INDIRECT_Y] = [](CPU &cpu) { cpu.sbc(cpu.addr_indirect_Y()); };

	// SEC
	opcodes[SEC] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.flags = cpu.flags | C_M;
	};

	// SED
	opcodes[SBC_INDIRECT_X] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.flags = cpu.flags | D_M;
	};

	// SEI
	opcodes[SBC_INDIRECT_X] = [](CPU &cpu) {
		++cpu.m_cycles;
		cpu.flags = cpu.flags | I_M;
	};
	//		JSR
	// opcodes[JSR] = [](CPU &cpu) {
	// 	++cpu.m_cycles;
	// 	--cpu.SP;
	// 	cpu.write_word(cpu.PC - 1, cpu.SP);
	// 	--cpu.SP;
	// 	cpu.PC = cpu.fetch_word();
	// };

	return opcodes;
}