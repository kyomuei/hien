
lib_util = static_library(
    'util',
    [
        'util/Range.c',
        'util/RawBuffer.c',
    ],
    include_directories: [include_dir],
)

lib_syntax = static_library(
    'syntax',
    [
        'syntax/SyntaxText.c',
    ],
    include_directories: [include_dir],
    link_with: [lib_util],
)

lib_parse = static_library(
    'parse',
    [
        'parse/tokenize/Lexeme.c',
        'parse/tokenize/Lexer.c',
    ],
    include_directories: [include_dir],
    link_with: [lib_util, lib_syntax],
)
