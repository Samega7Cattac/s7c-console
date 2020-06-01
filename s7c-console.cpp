#include "s7c-console.hpp"

int s7c_console::fast_agrcmp(char * a, char * b, int b_len)
{
    return *(a + b_len) == '\0' && !memcmp(a, b, b_len);
}

std::vector<std::string> s7c_console::get_args(std::string msg, std::vector<std::string> * v)
{
    std::string arg = "";
    std::vector<std::string> args;
    do
    {
        std::cout << msg << " (\"exit\" to cancel):" << std::endl << ">> ";
        getline(std::cin, arg);
        args = Extract(arg);
    }while(arg.empty());
    v->insert(v->end(), args.begin(), args.end());
    return args;
}

void s7c_console::draw_msg(std::vector<std::string> * v, unsigned int offset_draw, unsigned int offset_pos, unsigned int start, unsigned int length, std::string msg)
{
    std::string str = "";
    for (unsigned int i = 0; i < offset_draw; ++i) str.append(" ");
    for (unsigned int it = offset_pos; it < start; ++it)
    {
        for (unsigned int i = 0; i < v->at(it).length(); ++i) str.append(" ");
        str.append(" ");
    }
    str.append("^");
    for (unsigned int it = start; it < start + length; ++it)
    {
        for (unsigned int i = 0; i < v->at(it).length(); ++i) str.append("~");
        str.append("~");
    }
    if (length)
    {
        str.pop_back();
        str.pop_back();
    }
    std::cout << str << std::endl;
    std::cerr << msg << std::endl;
}

std::vector<std::string> s7c_console::Extract(const std::string& Text)
{
	std::vector<std::string> Words;
	std::istringstream ss(Text);
	std::string Buf;
	while (ss >> Buf) {
		Words.push_back(Buf);
	}
	return Words;
}
