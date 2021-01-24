#include "s7c-console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fast_argcmp(char * a, char * b, int b_len)
{
    return *(a + b_len) == '\0' && !memcmp(a, b, b_len);
}

int sanatized_argcmp(char * a, char * b, unsigned int a_len, unsigned int b_len)
{
    return a_len == b_len && !memcmp(a, b, b_len);
}

char ** line_extract(char * line, unsigned int * n_words, char ** old_args)
{
    char ** argv = NULL;
    if (old_args) argv = old_args;
    char * word = strtok(line, " \n\r");
    while(word)
    {
        argv = realloc(argv, sizeof(char *) * (*n_words + 1));
        int word_len = strlen(word) + 1;
        argv[*n_words] = malloc(sizeof(char) * word_len);
        memcpy(argv[(*n_words)++], word, word_len);
        word = strtok(0, " \n\r");
    }
    return argv;
}

char ** get_args(char * msg, unsigned int * argc, char ** old_args)
{
    char line[MAX_ARGS] = "\0";
    do
    {
        if (msg) printf("%s (\"cancel\" to exit):\n", msg);
        printf(">> ");
        fflush(stdout);
        fgets(line, MAX_ARGS, stdin);
    }while(fast_argcmp(line, "\0", 0));
    return line_extract(line, argc, old_args);
}

void free_args(char ** args, unsigned int * n_args)
{
    for (unsigned int i = 0; i < *n_args; ++i)
        free(args[i]);
    free(args);
    *n_args = 0;
}

void draw_msg(char ** args, unsigned int offset_draw, unsigned int offset_pos, unsigned int start, unsigned int length, char * msg)
{
    for (unsigned int i = 0; i < offset_draw; ++i) printf(" ");
    for (unsigned int it = offset_pos; it < start; ++it)
    {
        for (unsigned int i = 0; i < strlen(args[it]); ++i) printf(" ");
        printf(" ");
    }
    printf("^");
    for (unsigned int it = start; it < start + length; ++it)
    {
        for (unsigned int i = 0; i < strlen(args[it]); ++i) printf("~");
        printf("~");
    }
    if (length) printf("\b\b  ");
    printf("\n");
    fprintf(stderr,"%s\n", msg);
}

char ** vectorize_input(char * prefix, unsigned int * argc, char ** old_args)
{
    if (!old_args) *argc = 0;
    char line[MAX_ARGS] = "\0";
    if (prefix)
    {
        printf("%s", prefix);
        fflush(stdout);
    }
    fgets(line, MAX_ARGS, stdin);
    return line_extract(line, argc, old_args);
}
