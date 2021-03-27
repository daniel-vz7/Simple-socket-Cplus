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
  // Load file
  string data[78][8];
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
		  cout << "i " << i  << " -> " << tokens[i] << '\n'; 
      data[flag][i] = tokens[i];
    }
    flag++;
  }

  return 0;
}