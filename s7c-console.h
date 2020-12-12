#ifndef S7C_CONSOLE_H
#define S7C_CONSOLE_H

#define MAX_ARGS 255

int fast_argcmp(char * a, char * b, unsigned int b_len);

int sanatized_argcmp(char * a, char * b, unsigned int a_len, unsigned int b_len);

char ** line_extract(char* line, unsigned int* n_words, char** old_args);

char ** get_args(char * msg, unsigned int * argc, char ** old_args);

void free_args(char ** args, int * n_args);

void draw_msg(char ** args, unsigned int offset_draw, unsigned int offset_pos, unsigned int start, unsigned int length, char * msg);

char ** vectorize_input(char * prefix, unsigned int * argc, char ** old_args);

#endif
