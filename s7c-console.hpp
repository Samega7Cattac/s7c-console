#ifndef S7C_CONSOLE_HPP
#define S7C_CONSOLE_HPP

#include <iostream>
#include <vector>

class s7c_console
{
public:
    
    // Compare string a and b - speed improved
    // NOTE: Remove any sanatizer options from ur compiler (or use sanatized_argcmp() instead)
    static int fast_argcmp(const char * a, const char * b, int b_len);
    
    // Compare string a and b - sanatized version of fast_argcmp()
    static int sanatized_argcmp(const char * a, const char * b, unsigned int a_len, unsigned int b_len);
    
    static std::vector<std::string> get_args(std::string msg, std::vector<std::string> * v);
    
    std::vector<std::string> get_args(std::string msg, std::vector<std::string> * v, unsigned int n_args);
    
    static void draw_msg(std::vector<std::string> &args, unsigned int offset_draw, unsigned int offset_pos, unsigned int start, unsigned int length, std::string msg);
    
    static std::vector<std::string> extract(const std::string& Text);
    
    static std::vector<std::string> vectorize_input(const char * prefix);
    
    static std::vector<std::string> vectorize_input(const char * prefix, std::vector<std::string> &args);
};

#endif // S7C_CONSOLE_HPP
