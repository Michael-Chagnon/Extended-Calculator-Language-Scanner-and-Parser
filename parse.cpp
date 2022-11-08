/* Complete recursive descent parser for the calculator language.
    Builds on figure 2.16.  Prints a trace of productions predicted and
    tokens matched.  Does no error recovery: prints "syntax error" and
    dies on invalid input.
    Michael L. Scott, 2008-2020.
*/

#include <iostream>
#include <stdio.h>

#include "scan.h"

const char* names[] = {"read", "write", "id", "literal", "gets",
                       "add", "sub", "mul", "div", "lparen", "rparen", "eof",
                       "while", "greater than", "greater or equal", "less than", "less or equal", "if", "equal", "end", "not equal"};

static token input_token;

void error () {
    std::cout << "syntax error" << std::endl;
    exit (1);
}

void match (token expected) {
    if (input_token == expected) {
        std::cout << "matched " << names[input_token];
        if (input_token == t_id || input_token == t_literal)
            std::cout << ": " << token_image;
        std::cout << std::endl;
        input_token = scan ();
    }
    else error ();
}

void program ();
void stmt_list ();
void stmt ();
void expr ();
void term ();
void term_tail ();
void factor ();
void factor_tail ();
void add_op ();
void mul_op ();

void cond ();
void rel_op ();

void cond() {
  switch (input_token) {
    case t_id:
    case t_literal:
    case t_lparen:
      std::cout << "predict cond --> expr ro expr" << std::endl;
      expr();
      rel_op();
      expr();
      break;
    default:
      error();
  }
}

void rel_op () {
    switch (input_token) {
        case t_gt:
            std::cout << "predict rel_op --> greater than" << std::endl;
            match (t_gt);
            break;
        case t_ge:
            std::cout << "predict rel_op --> greater or equal" << std::endl;
            match (t_ge);
            break;
        case t_lt:
            std::cout << "predict rel_op --> less than" << std::endl;
            match (t_lt);
            break;
        case t_le:
            std::cout << "predict rel_op --> less or equal" << std::endl;
            match (t_le);
            break;
        case t_equal:
            std::cout << "predict rel_op --> equal" << std::endl;
            match (t_equal);
            break;
        case t_notequal:
            std::cout << "predict rel_op --> not equal" << std::endl;
            match (t_notequal);
            break;
        default: error ();
    }
}


void program () {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_while:
        case t_eof:
            std::cout << "predict program --> stmt_list eof" << std::endl;
            stmt_list ();
            match (t_eof);
            break;
        default: error ();
    }
}

void stmt_list () {
    switch (input_token) {
        case t_id:
        std::cout << "predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_read:
        std::cout << "predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_write:
            std::cout << "predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_if:
            std::cout << "predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_while:
            std::cout << "predict stmt_list --> stmt stmt_list" << std::endl;
            stmt ();
            stmt_list ();
            break;
        case t_end:
            std::cout << "predict stmt_list --> epsilon" << std::endl;
            break;          /* epsilon production */
        case t_eof:
            std::cout << "predict stmt_list --> epsilon" << std::endl;
            break;          /* epsilon production */
        default: error ();
    }
}

void stmt () {
    switch (input_token) {
        case t_id:
            std::cout << "predict stmt --> id gets expr" << std::endl;
            match (t_id);
            match (t_gets);
            expr ();
            break;
        case t_read:
            std::cout << "predict stmt --> read id" << std::endl;
            match (t_read);
            match (t_id);
            break;
        case t_write:
            std::cout << "predict stmt --> write expr" << std::endl;
            match (t_write);
            expr ();
            break;
        case t_while:
            std::cout << "predict stmt --> while cond stmt_list end" << std::endl;
            match (t_while);
            cond ();
            stmt_list ();
            match (t_end);
            break;
        case t_if:
            std::cout << "predict stmt --> if cond stmt_list end" << std::endl;
            match (t_if);
            cond ();
            stmt_list ();
            match (t_end);
            break;
        default: error ();
    }
}


void expr () {
    switch (input_token) {
        case t_id:
            std::cout << "predict expr --> term term_tail" << std::endl;
            term ();
            term_tail ();
            break;
        case t_literal:
            std::cout << "predict expr --> term term_tail" << std::endl;
            term ();
            term_tail ();
            break;
        case t_lparen:
            std::cout << "predict expr --> term term_tail" << std::endl;
            term ();
            term_tail ();
            break;
        default: error ();
    }
}

void term () {
    switch (input_token) {
        case t_id:
            std::cout << "predict term --> factor factor_tail" << std::endl;
            factor ();
            factor_tail ();
            break;
        case t_literal:
            std::cout << "predict term --> factor factor_tail" << std::endl;
            factor ();
            factor_tail ();
            break;
        case t_lparen:
            std::cout << "predict term --> factor factor_tail" << std::endl;
            factor ();
            factor_tail ();
            break;
        default: error ();
    }
}

void term_tail () {
    switch (input_token) {
        case t_add:
            std::cout << "predict term_tail --> add_op term term_tail" << std::endl;
            add_op ();
            term ();
            term_tail ();
            break;
        case t_sub:
            std::cout << "predict term_tail --> add_op term term_tail" << std::endl;
            add_op ();
            term ();
            term_tail ();
            break;
        case t_rparen:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_id:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_read:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_write:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_if:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_while:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_end:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_gt:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_ge:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_lt:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_le:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_equal:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_notequal:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_eof:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;          /* epsilon production */
        default: error ();
    }
}

void factor () {
    switch (input_token) {
        case t_literal:
            std::cout << "predict factor --> literal" << std::endl;
            match (t_literal);
            break;
        case t_id :
            std::cout << "predict factor --> id" << std::endl;
            match (t_id);
            break;
        case t_lparen:
            std::cout << "predict factor --> lparen expr rparen" << std::endl;
            match (t_lparen);
            expr ();
            match (t_rparen);
            break;
        default: error ();
    }
}

void factor_tail () {
    switch (input_token) {
        case t_mul:
            std::cout << "predict factor_tail --> mul_op factor factor_tail" << std::endl;
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_div:
            std::cout << "predict factor_tail --> mul_op factor factor_tail" << std::endl;
            mul_op ();
            factor ();
            factor_tail ();
            break;
        case t_add:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_sub:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_rparen:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_id:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_read:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_write:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_if:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_while:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_end:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_gt:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_ge:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_lt:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_le:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_equal:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_notequal:
            std::cout << "predict term_tail --> epsilon" << std::endl;
            break;   
        case t_eof:
            std::cout << "predict factor_tail --> epsilon" << std::endl;
            break;          /* epsilon production */
        default: error ();
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            std::cout << "predict add_op --> add" << std::endl;
            match (t_add);
            break;
        case t_sub:
            std::cout << "predict add_op --> sub" << std::endl;
            match (t_sub);
            break;
        default: error ();
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            std::cout << "predict mul_op --> mul" << std::endl;
            match (t_mul);
            break;
        case t_div:
            std::cout << "predict mul_op --> div" << std::endl;
            match (t_div);
            break;
        default: error ();
    }
}

int main () {
    input_token = scan ();
    program ();
    return 0;
}
