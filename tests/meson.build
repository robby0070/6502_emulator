test_src = files(
	'catch_main.cpp',
	'load_in_register.cpp',
	'util.cpp',

	'loads_stores.cpp',
	'transfers.cpp',
	'jumps_calls.cpp',
	'logical.cpp',
	'shifts.cpp',
	'stack.cpp',
	'flags_changes.cpp',
	'system.cpp',
    'branches.cpp',
    'arithmetic.cpp',
    'algorithms.cpp',
)

tests = executable('tests', [test_src, lib_6502],  dependencies : [catch2, spdlog, fmt]) 
test('tests', tests)
