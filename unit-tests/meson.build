
libparse_ut_exe = executable(
    'parse-tests',
    [
        'TestMain.cpp',
        'ParseTests/TokenizeTests.cpp',
    ],
    include_directories: [include_dir],
    link_with: [lib_parse],
    dependencies: [gtest_dep],
)

test('libparse-unit-tests', libparse_ut_exe)
