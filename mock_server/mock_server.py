import socket

# Server configuration
HOST = '127.0.0.1'  # Localhost
PORT = 4444        # Port to listen on

# Set up the server
def start_server():
    # Create a TCP/IP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Bind the socket to the port
    server_address = (HOST, PORT)  # Listen on all interfaces, port 12345
    server_socket.bind(server_address)
    
    # Enable the server to accept connections (max backlog of 5 clients)
    server_socket.listen(5)
    print("Server is listening on port 4444...")
    
    # Continuously listen for incoming connections
    while True:
        # Wait for a client to connect
        client_socket, client_address = server_socket.accept()
        try:
            print(f"Client connected from {client_address}")

            # Send a welcome message to the client
            welcome_message = input("Enter command: ")
            client_socket.sendall(welcome_message.encode('utf-8'))

            # Handle further communication here (e.g., receiving data, processing it)
            # You can receive data from the client using:
            data = client_socket.recv(1024)  # Receives up to 1024 bytes
            print("Received data:", data.decode('utf-8'))

        finally:
            # Close the client connection when done
            client_socket.close()
            print(f"Client {client_address} disconnected")

# Run the server
if __name__ == "__main__":
    start_server()
