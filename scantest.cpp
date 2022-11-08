#include <iostream>
#include <stdio.h>
#include "scan.h"

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof",
                       "while", "greater than", "greater or equal", "less than", "less or equal", "if", "equal", "end", "not equal"};

static token input_token;

int main() {

    do {
        input_token = scan ();
        std::cout << "scanned " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
            printf (": %s", token_image);
        std::cout << "\n";
    } while (input_token != t_eof);

    return 0;
}
