#include "s7c-console.hpp"

#include <string.h>
#include <sstream>

int s7c_console::fast_argcmp(const char * a, const char * b, int b_len)
{
    return *(a + b_len) == '\0' && !memcmp(a, b, b_len);
}

int s7c_console::sanatized_argcmp(const char * a, const char * b, unsigned int a_len, unsigned int b_len)
{
    return a_len == b_len && !memcmp(a, b, b_len);
}

std::vector<std::string> s7c_console::get_args(std::string msg, std::vector<std::string> * v)
{
    std::string arg;
    std::vector<std::string> args;
    do
    {
        std::cout << msg << " (\"exit\" to cancel):" << std::endl << ">> ";
        getline(std::cin, arg);
        args = extract(arg);
    }while(arg.empty());
    v->insert(v->end(), args.begin(), args.end());
    return args;
}

std::vector<std::string> s7c_console::get_args(std::string msg, std::vector<std::string> * v, unsigned int n_args)
{
    std::string arg;
    std::vector<std::string> args;
    do
    {
        std::cout << msg << " (\"exit\" to cancel):" << std::endl << ">> ";
        getline(std::cin, arg);
        args = extract(arg);
    }while(arg.size() < n_args || !fast_argcmp(args[0].c_str(), "exit", 4));
    v->insert(v->end(), args.begin(), args.end());
    return args;
}

void s7c_console::draw_msg(std::vector<std::string> &args, unsigned int offset_draw, unsigned int offset_pos, unsigned long start, unsigned long length, std::string msg)
{
    std::string str = "";
    for (unsigned int i = 0; i < offset_draw; ++i)
        str.append(" ");
    for (unsigned int it = offset_pos; it < start; ++it)
    {
        for (unsigned int i = 0; i < args[it].length(); ++i)
            str.append(" ");
        str.append(" ");
    }
    str.append("^");
    if (args.size() > start)
    {
        for (unsigned int it = start; it < start + length; ++it)
        {
            for (unsigned int i = 0; i < args[it].length(); ++i)
                str.append("~");
            str.append("~");
        }
        if (length)
        {
            str.pop_back();
            str.pop_back();
        }
    }
    std::cout << str << std::endl;
    std::cerr << msg << std::endl;
}

std::vector<std::string> s7c_console::extract(const std::string& Text)
{
	std::vector<std::string> Words;
	std::istringstream ss(Text);
	std::string Buf;
	while (ss >> Buf) {
		Words.push_back(Buf);
	}
	return Words;
}

std::vector<std::string> s7c_console::vectorize_input(const char* prefix)
{
    if (prefix) std::cout << prefix;
    std::string cmd;
    std::getline(std::cin, cmd);
    return extract(cmd);
}

std::vector<std::string> s7c_console::vectorize_input(const char * prefix, std::vector<std::string> &args)
{
    if (prefix) std::cout << prefix;
    std::string cmd;
    std::getline(std::cin, cmd);
    std::vector<std::string> v = extract(cmd);
    args.insert(args.end(), v.begin(), v.end());
    return args;
}
