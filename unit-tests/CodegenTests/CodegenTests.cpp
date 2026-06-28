#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

extern "C" {

#include "hien/codegen/codegen.h"
#include "hien/parse/Parser.h"
#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/SyntaxText.h"

}

class CodegenTests : public testing::Test {
protected:

    std::string tempDir;

    void SetUp() override {
        tempDir = testing::TempDir() + "hientemp";
        std::filesystem::create_directory(tempDir);
    }

    void TearDown() override {
        std::filesystem::remove_all(tempDir);
    }
};

void assertExecAsmCode(SyntaxNode_t *root, std::string dir, std::string file_name, int expected, char const *file, int line);

TEST_F(CodegenTests, testEmptySource) {
    SyntaxNode_t *source = Parser_parse(SyntaxText_empty());
    assertExecAsmCode(source, tempDir, "testEmptySource", 0, __FILE__, __LINE__);
}

TEST_F(CodegenTests, testCodegen) {
    SyntaxNode_t *source = Parser_parse(SyntaxText_fromLiteral("42"));
    assertExecAsmCode(source, tempDir, "testCodegen", 42, __FILE__, __LINE__);
}

void assertExecAsmCode(SyntaxNode_t *root, std::string tempDir, std::string file_name, int expected, char const *file, int line) {
    std::string asm_file_path = tempDir + "/" + file_name + ".s";

    FILE *asm_file = std::fopen(asm_file_path.c_str(), "w");
    codegen(root, asm_file);
    fclose(asm_file);

    std::string exec_file_path = tempDir + "/" + file_name;
    std::string compile_command = "cc -o " + exec_file_path + " " + asm_file_path;
    int compile_result = std::system(compile_command.c_str());
    if (0 != WEXITSTATUS(compile_result)) {
        std::system(("cat " + asm_file_path).c_str());
        ADD_FAILURE_AT(file, line) << "compile failed. file: " << file_name << '\n';
        return;
    }

    int exec_result = std::system(exec_file_path.c_str());
    if (expected != WEXITSTATUS(exec_result)) {
        std::system(("cat " + asm_file_path).c_str());
        ADD_FAILURE_AT(file, line)
            << "Expected " << expected << " but got " << WEXITSTATUS(exec_result) << '\n';
            return;
    }
}
