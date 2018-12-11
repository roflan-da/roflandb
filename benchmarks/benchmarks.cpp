#define BENCHPRESS_CONFIG_MAIN
#include "benchpress.hpp"
#include <iostream>
#include "driver.h"

#include <chrono>
#include <iostream>

BENCHMARK("create table", [](benchpress::context* ctx) {
    roflan_parser::Driver parser_driver;
    std::string error_message;
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        parser_driver.parse_string("create table test"+std::to_string(i)+ "(id int, phone int);", error_message);
        parser_driver.sql_parser_result->execute();
    }
})

BENCHMARK("insert table", [](benchpress::context* ctx) {
    roflan_parser::Driver parser_driver;
    std::string error_message;
    parser_driver.parse_string("create table test (id int, phone int);", error_message);
    parser_driver.sql_parser_result->execute();
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        parser_driver.parse_string("insert test(id,phone) values("+std::to_string(i)+","+std::to_string(i)+");", error_message);
        parser_driver.sql_parser_result->execute();
    }
})

BENCHMARK("drop table", [](benchpress::context* ctx) {
    roflan_parser::Driver parser_driver;
    std::string error_message;
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        parser_driver.parse_string("create table test"+std::to_string(i)+ "(id int, phone int);", error_message);
        parser_driver.sql_parser_result->execute();
    }
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        parser_driver.parse_string("drop table test"+std::to_string(i)+ ";", error_message);
        parser_driver.sql_parser_result->execute();
    }
})