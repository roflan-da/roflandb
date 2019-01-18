#pragma once

#include <string>

namespace roflan_cli {

// Meyers singleton. Thread unsafe.
class Cli
{
public:
    Cli( const Cli&) = delete;
    Cli& operator=(Cli&) = delete;

    static Cli& get_instance();

    // return exit code;
    int start();
private:
    Cli() = default;
    bool is_starts_with(const std::string& hay, const std::string& needle) const;
};

} // namespace roflan_cli
