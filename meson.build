
project(
    'hien-lang',
    ['c', 'cpp'],
    version : '0.1.0',
    license : 'Apache-2.0',
    default_options : [
        'c_std=c17',
        'cpp_std=c++17',
    ],
)

include_dir = include_directories('include')

gtest_dep = dependency('gtest')

subdir('lib')

subdir('tools')

subdir('unit-tests')
