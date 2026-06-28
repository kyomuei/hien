
libparse_ut_exe = executable(
    'parse-tests',
    [
        'TestMain.cpp',
        'ParseTests/ParseTests.cpp',
        'ParseTests/TokenizeTests.cpp',
    ],
    include_directories: [include_dir],
    link_with: [lib_parse],
    dependencies: [gtest_dep],
)

libcodegen_ut_exe = executable(
    'codegen-tests',
    [
        'TestMain.cpp',
        'CodegenTests/CodegenTests.cpp',
    ],
    include_directories: [include_dir],
    link_with: [lib_codegen, lib_parse],
    dependencies: [gtest_dep],
)

test('libparse-unit-tests', libparse_ut_exe)
test('libcodegen-unit-tests', libcodegen_ut_exe)
