# Mock Stock Exchange

## Summary
This project is a mock stock exchange. We use TCP connections to host a multi-threaded web server that can receive orders from multiple clients. We aim to route all orders through the TCP Server to a limit orderbook such that on every bid or ask, the client receives a view of the orderbook and also by request. 

*Note: This is a work in progress. We aim to add the following features*

- Packet Encryption
- Limit Orderboook
- Market Data Feed

## Usage

Simply use the Makefile provided:
```bash
$ make
```

First, start the server with `./server`, then host multiple instances of the client via `./client` as required.
