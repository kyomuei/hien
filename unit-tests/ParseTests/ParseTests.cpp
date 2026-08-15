#include <gtest/gtest.h>

extern "C" {

#include "hien/parse/Parser.h"
#include "hien/syntax/SyntaxKind.h"
#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/SyntaxText.h"

}

class ParseTests : public testing::Test {};

void toJson(SyntaxNode_t *node, std::string &result) {
    switch (node->kind) {
    case SYNTAXKIND_SOURCEFILE:
        result.append("{\"kind\":\"SourceFile\",\"children\":[");
        for (int i = 0; i < node->childrenCount; i++) {
            toJson(node->children[i], result);
        }
        result.append("]}");
        break;
    case SYNTAXKIND_EXPR_NUMBER:
        result.append("{\"kind\":\"Number\",\"text\":\"");
        result.append(std::string(SyntaxText_baseAddress(node->text), SyntaxText_count(node->text)));
        result.append("\"}");
        break;
    case SYNTAXKIND_STMT_RETURN:
        result.append("{\"kind\":\"Return\",\"children\":[");
        for (int i = 0; i < node->childrenCount; i++) {
            toJson(node->children[i], result);
        }
        result.append("]}");
    default:
        break;
    }
}

TEST(ParseTests, testEmpty) {
    SyntaxText_t source = SyntaxText_empty();
    SyntaxNode_t *root = Parser_parse(source);

    std::string expected = "{\"kind\":\"SourceFile\",\"children\":[]}";
    std::string actual;
    toJson(root, actual);
    ASSERT_EQ(expected, actual);
}

TEST(ParseTests, testParse) {
    SyntaxText_t source = SyntaxText_fromLiteral("return 1234567890");
    SyntaxNode_t *root = Parser_parse(source);

    std::string expected = "{\"kind\":\"SourceFile\",\"children\":[{\"kind\":\"Return\",\"children\":[{\"kind\":\"Number\",\"text\":\"1234567890\"}]}]}";
    std::string actual;
    toJson(root, actual);
    ASSERT_EQ(expected, actual);
}
