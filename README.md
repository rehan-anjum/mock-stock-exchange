# Mock Stock Exchange

## Summary
This project is a mock stock exchange. We use TCP connections to host a multi-threaded web server that can receive orders from multiple clients. We aim to route all orders through the TCP Server to a limit orderbook such that on every bid or ask, the client receives a view of the orderbook and also by request. 

*Note: This is a work in progress. We aim to add the following features*

- Packet Encryption
- Limit Orderboook
- Market Data Feed

## Usage

Run the Server:

```bash 
$ cd src/server
$ g++ -std=c++17 tcp_server.cpp server.cpp -o server
$ ./server
```

Run multiple instances of the client:

```bash 
$ cd src/client
$ g++ -std=c++17 tcp_client.cpp client.cpp -o client
$ ./client
```

