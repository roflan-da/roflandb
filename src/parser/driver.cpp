
#include "driver.h"
#include "scanner.h"

namespace roflan_parser {

Driver::Driver()
        : trace_scanning(false),
          trace_parsing(false),
          sql_parser_result(new cmd::Command())
{
}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    lexer = std::make_unique<Scanner>(&in);
    lexer->set_debug(trace_scanning);
    Parser parser(*this);
    //parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
                   const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

} // namespace example
