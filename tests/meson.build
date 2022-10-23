src = files(
	'catch_main.cpp',
	'bitwise.cpp',
	'load_in_register.cpp',
	'loads.cpp',
	'others.cpp',
	'stack.cpp',
	'util.cpp',
)

tests = executable('tests', [src, sources],  dependencies : [catch2, spdlog, fmt]) 
test('tests', tests)