#pragma once

#include <string>

namespace roflan_srv {

// Meyers singleton. Thread unsafe.
class Server
{
public:
    Server( const Server&) = delete;
    Server& operator=(Server&) = delete;

    static Server& get_instance();

    // return exit code;
    int start();
private:
    Server() = default;
    bool is_starts_with(const std::string& hay, const std::string& needle) const;
};

} // namespace roflan_srv
