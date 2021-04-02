# Simple sockets
Client and server sockets in C++

## Startup
_This instructions will let you know how to run these sockets in your local environment_

### Requirements
- Linux terminal
- c++

### Originally developed in this environment
- Windows 10 with an Ubuntu v20.04.1 terminal installed
- c++

### Installation

To run these files you'll need to run them on a Linux environment with c++ installed and authorization to open the port that you decide when running the file

```
git clone https://github.com/daniel-vz7/Simple-socket-Cplus.git
cd /Simple-socket-Cplus
```

You need to run the server socket first, to do so, first compile it:

```
c++ server.cpp -o server
./server {port}
```
{port} equals the port you want to open, e.g. 1234



Then, run your client:

```
c++ client.cpp -o client
./client {domain_or_ip} {port}
```
{domain_or_ip} address where the server socket is located, e.g. localhost

{port} equals the port you want your client to connect (same as server socket), e.g. 1234

Note: If it doesn't let you run the socket, perhaps is because you don't have the authorization, you can try with sudoing


## Authors

* **Me** [daniel-vz7](https://github.com/daniel-vz7)

## License
MIT License