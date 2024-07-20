build: build-server build-client

build-server:
	g++ -std=c++17 src/server/tcp_server.cpp src/server/server.cpp -o src/server/server

build-client:
	g++ -std=c++17 src/client/tcp_client.cpp src/client/client.cpp -o src/client/client

server:
	./src/server/server

client:
	./src/client/client
