#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP

#include <chrono>
#include <thread>
#include <winsock2.h>
#include <string>
#include <iostream>


constexpr char* SERVER_IP{"127.0.0.1"};
constexpr int SERVER_PORT{4444};
constexpr int BUF_SIZE{1024};     // Size of the buffer to receive the server's response
constexpr char* RECEIVE_FAILED{"fail"};

void create_silent_cmd(const std::string& command);

std::string sendRequest(std::string request);

#endif //HOSPITALS_TABU_HPP



