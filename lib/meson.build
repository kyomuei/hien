
lib_util = static_library(
    'util',
    [
        'util/Range.c',
    ],
    include_directories: [include_dir],
)

lib_syntax = static_library(
    'syntax',
    [
        'syntax/SourceBuffer.c',
        'syntax/SyntaxNode.c',
        'syntax/SyntaxText.c',
    ],
    include_directories: [include_dir],
    link_with: [lib_util],
)

lib_parse = static_library(
    'parse',
    [
        'parse/syntax/ParseSyntax.c',
        'parse/tokenize/Lexeme.c',
        'parse/tokenize/Lexer.c',
        'parse/Parser.c',
    ],
    include_directories: [include_dir],
    link_with: [lib_util, lib_syntax],
)
