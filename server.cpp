#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <sstream>

using namespace std;

// Server side
int main(int argc, char *argv[]) {
  // For the server, we only need to specify a port number
  if (argc != 2) {
    cerr << "Usage: port" << endl;
    exit(0);
  }

  // Load file
  string moviesData[78][8];
  int flag = 0;
  ifstream input("movies.csv");
  for (string line; getline(input, line);) {
    vector <string> tokens; 
    stringstream check1(line); 
    string intermediate; 
    // Tokenizing w.r.t. space ',' 
    while (getline(check1, intermediate, ',')) { 
      tokens.push_back(intermediate); 
    } 
    // Iterating over row fields
    for (int i = 0; i < tokens.size(); i++) {
      moviesData[flag][i] = tokens[i];
    }
    flag++;
  }

  // Grab the port number
  int port = atoi(argv[1]);
  // Buffer to send and receive messages with
  char message[1500];

  // Setup a socket and connection tools
  sockaddr_in servAddr;
  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(port);

  // Open stream
  int serverSd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSd < 0) {
    cerr << "Error establishing the server socket" << endl;
    exit(0);
  }
  //bind the socket to its local address
  int bindStatus = bind(serverSd, (struct sockaddr *)&servAddr, sizeof(servAddr));
  if (bindStatus < 0) {
    cerr << "Error binding socket to local address" << endl;
    exit(0);
  }

  // Listen to requests
  listen(serverSd, 5);
  cout << "Running server on port " << port << endl;
  // New address to connect with the client
  sockaddr_in newSockAddr;
  socklen_t newSockAddrSize = sizeof(newSockAddr);
  int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
  if (newSd < 0) {
    cerr << "Error accepting request from client!" << endl;
    exit(0);
  }

  // Receive instructions from client
  memset(&message, 0, sizeof(message)); 
  recv(newSd, (char *)&message, sizeof(message), 0);
  vector <string> tokens; 
  stringstream check1(message); 
  string intermediate; 
  // Tokenizing w.r.t. space ',' 
  while (getline(check1, intermediate, ',')) tokens.push_back(intermediate);

  stringstream geek(tokens[0]);
  int option = 0;
  int operationCode = 0;
  geek >> option;
  string response = "0";

  // Search film
  for (int i = 1; i < 78; i++) {
    if (tokens[1] == moviesData[i][0]) {
      response = moviesData[i][option - 1];
      operationCode = 1;
      break;
    }
  }
  
  // Send response to client
  response = to_string(operationCode) + "," + response;
  memset(&message, 0, sizeof(message)); //clear the buffer
  strcpy(message, response.c_str());
  send(newSd, (char *)&message, strlen(message), 0);
  close(newSd);
  close(serverSd);

  return 0;
}