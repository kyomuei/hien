#include "hien/syntax/Keyword.h"
#include "hien/syntax/SyntaxText.h"
#include <assert.h>
#include <stdlib.h>

struct Keyword_KeyValue_t {
    char const *text;
    Keyword_t keyword;
};

static struct Keyword_KeyValue_t keywords[] = {
    { .text = "return", .keyword = KEYWORD_RETURN },
};

static Keyword_t _Keyword_lookup(SyntaxText_t text, struct Keyword_KeyValue_t *keywords, int keywordCount) {
    assert(keywords != NULL && keywordCount > 0);

    for (int i = 0; i < keywordCount; i += 1) {
        if (SyntaxText_equals(text, SyntaxText_fromLiteral(keywords[i].text))) {
            return keywords[i].keyword;
        }
    }
    return MAX_KEYWORD;
}

Keyword_t Keyword_lookup(SyntaxText_t text) {
    int keywordCount = sizeof(keywords) / sizeof(keywords[0]);
    return _Keyword_lookup(text, keywords, keywordCount);
}
