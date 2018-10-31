#pragma once

#include "string"
#include "../../commands/inc/storage_engine.h"

class parser {
    static bool parse(const std::string& sql, Command* result);

};
