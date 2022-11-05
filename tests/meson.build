test_src = files(
	'catch_main.cpp',
	'load_in_register.cpp',
	'util.cpp',

	# 'bitwise.cpp',
	'loads.cpp',
	# 'others.cpp',
	# 'stack.cpp',
)

tests = executable('tests', [test_src, lib_6502],  dependencies : [catch2, spdlog, fmt]) 
test('tests', tests)