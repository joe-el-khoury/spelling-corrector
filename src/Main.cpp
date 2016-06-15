#include <iostream>

#include "Token.h"
#include "TokenHistogram.h"

int main (int argc, const char* argv[]) {
    TokenHistogram th;
    th.add_token(Token("hello"));
    th.add_token(Token("goodbye"));
    th.add_token(Token("hello"));
    th.add_token(Token("joe"));
    th.print();
    return 0;
}