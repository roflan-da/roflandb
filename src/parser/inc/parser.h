#pragma once

#include "string"
#include "command.h"

class parser {
    static bool parse(const std::string& sql, cmd::Command* result);

};
