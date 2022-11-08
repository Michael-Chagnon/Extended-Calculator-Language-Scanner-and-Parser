/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2020.
*/

typedef enum {t_read, t_write, t_id, t_literal, t_gets,
              t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,
              t_while, t_gt, t_ge, t_lt, t_le, t_if, t_equal, t_end, t_notequal} token;

#define MAX_TOKEN_LEN 128
extern char token_image[MAX_TOKEN_LEN];

extern token scan();
