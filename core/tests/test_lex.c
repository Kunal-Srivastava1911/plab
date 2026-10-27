/* Lexer unit tests: token kinds, sigma transitions, header names, digraphs, pp-numbers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plab.h"

static int failures;

static void check(const char *src, const char *expect) {
    uint32_t n = (uint32_t)strlen(src);
    uint8_t *buf = calloc(n + PLAB_PAD, 1);
    memcpy(buf, src, n);
    plab_interner in;
    plab_interner_init(&in);
    plab_tokens t;
    plab_tokens_init(&t, n);
    plab_run_baseline(&in, buf, n, &t);
    char got[4096] = {0};
    size_t k = 0;
    for (uint32_t i = 0; i < t.count; i++)
        k += (size_t)snprintf(got + k, sizeof got - k, "%s%s:%.*s", i ? " " : "", plab_kind_name(t.kind[i]),
                              t.kind[i] == TK_PP_END ? 0 : (int)t.len[i], (const char *)buf + t.start[i]);
    if (strcmp(got, expect)) {
        printf("FAIL %s\n  want %s\n  got  %s\n", src, expect, got);
        failures++;
    }
    plab_tokens_free(&t);
    plab_interner_free(&in);
    free(buf);
}

int main(void) {
    plab_init();
    check("int x = 1;", "keyword:int identifier:x =:= number:1 ;:;");
    check("a->b++ <<= 0x1e+1", "identifier:a ->:-> identifier:b ++:++ <<=:<<= number:0x1e+1");
    check("#include <stdio.h>\nx", "#:# identifier:include header_name:<stdio.h> pp_end: identifier:x");
    check("a < b > c", "identifier:a <:< identifier:b >:> identifier:c");
    check("#define F(x) #x ## y\n", "#:# identifier:define identifier:F (:( identifier:x ):) #:# identifier:x ##:## identifier:y pp_end:");
    check("x /* c\n */ y // z\n", "identifier:x identifier:y");
    check("L\"w\" u8'c' 'a' \"s\\\"q\"", "string:L\"w\" char:u8'c' char:'a' string:\"s\\\"q\"");
    check("<: :> <% %> %: %:%: ...", "<::<: :>::> <%:<% %>:%> %::%: %:%::%:%: ...:...");
    check(".5 1'000 1.e-3", "number:.5 number:1'000 number:1.e-3");
    check("#define A \\\n  1\nb", "#:# identifier:define identifier:A number:1 pp_end: identifier:b");
    check("\"unterminated\nx", "unknown:\" identifier:unterminated identifier:x");
    check("  # if X\n", "#:# keyword:if identifier:X pp_end:");
    check("a # b", "identifier:a #:# identifier:b");
    if (!failures) printf("test_lex: all passed\n");
    return failures ? 1 : 0;
}
