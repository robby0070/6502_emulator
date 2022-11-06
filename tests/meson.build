test_src = files(
	'catch_main.cpp',
	'load_in_register.cpp',
	'util.cpp',

	'jumps_calls.cpp',
	'loads_stores.cpp',
	'logical.cpp',
	'shifts.cpp',
	'stack.cpp',
	'system.cpp',
)

tests = executable('tests', [test_src, lib_6502],  dependencies : [catch2, spdlog, fmt]) 
test('tests', tests)