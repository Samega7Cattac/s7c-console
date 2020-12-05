#ifndef S7C_CONSOLE_HPP
#define S7C_CONSOLE_HPP

#include <iostream>
#include <vector>

class s7c_console
{
public:
    
    static int fast_argcmp(const char * a, const char * b, int b_len);
    
    static std::vector<std::string> get_args(std::string msg, std::vector<std::string> * v);
    
    static void draw_msg(std::vector<std::string> &args, unsigned int offset_draw, unsigned int offset_pos, unsigned int start, unsigned int length, std::string msg);
    
    static std::vector<std::string> extract(const std::string& Text);
    
    static std::vector<std::string> vectorize_input(const char * prefix);
    
    static std::vector<std::string> vectorize_input(const char * prefix, std::vector<std::string> &args);
};

#endif // S7C_CONSOLE_HPP
