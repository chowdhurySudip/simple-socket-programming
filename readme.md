# Simple Socket Programming in C

This projects implements a simple socket program using C language. Here, the server keeps running in a loop, and once the client is run, it sends a message to the server and server sends the message back to the client. I have included two version of the same task.

## Getting Started

### Simple Socket

A very simple implementation of the socket program. It does not include all the necessary checks; but it works. It is just for getting started.

To run this code - 
```
cd simple_socket/
make
./server (in one terminal)
./client (in another terminal)
```

### Better Socket

A better solution to the socket programming task. It includes all the necessary checks like using getaddrinfo which helps in DNS and service name lookup, making the code IP version agnostic etc.

To run this code - 
```
cd better_socket/
make
./echoserver (in one terminal)
./echoclient (in another terminal)
```

## References
- [Beej’s Guide to Network Programming](http://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf)
