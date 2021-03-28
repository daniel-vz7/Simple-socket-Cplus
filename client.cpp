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

void printMenu(void) {
  // Display menu
  cout << "Ingresa el dato que deseas obtener" << endl;
  cout << "1. Nombre de pelicula" << endl;
  cout << "2. Genero" << endl;
  cout << "3. Estudio" << endl;
  cout << "4. Puntuacion de audiencia" << endl;
  cout << "5. Ganancia" << endl;
  cout << "6. Rotten Tomatoes" << endl;
  cout << "7. Ganancia global" << endl;
  cout << "8. Año" << endl;
}

//Client side
int main(int argc, char *argv[]) {
  //we need 2 things: ip address and port number, in that order
  if (argc != 3) {
    cerr << "Usage: ip_address port" << endl;
    exit(0);
  } //grab the IP address and port number
  char *serverIp = argv[1];
  int port = atoi(argv[2]);
  char message[1500];

  //setup a socket and connection tools
  struct hostent *host = gethostbyname(serverIp);
  sockaddr_in sendSockAddr;
  bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
  sendSockAddr.sin_family = AF_INET;
  sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
  sendSockAddr.sin_port = htons(port);
  int clientSd = socket(AF_INET, SOCK_STREAM, 0);
  //try to connect...
  int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
  if (status < 0) {
    cout << "Error connecting to socket!" << endl;
    exit(1);
  }

  printMenu();
  // Enter option
  cout << "Ingresa el dato a obtener" << endl << ">";
  string option;
  getline(cin, option);
  // Enter film name
  cout << "Ingresa el nombre de la pelicula" << endl << ">";
  string filmName;
  getline(cin, filmName);

  // Prepare consult
  string instruction = option + "," + filmName;
  strcpy(message, instruction.c_str());
  send(clientSd, (char *)&message, strlen(message), 0);
  memset(&message, 0, sizeof(message)); //clear the buffer

  // Receive response from server
  recv(clientSd, (char *)&message, sizeof(message), 0);
  vector <string> tokens; 
  stringstream check1(message); 
  string intermediate; 
  // Tokenizing w.r.t. space ',' 
  while (getline(check1, intermediate, ',')) tokens.push_back(intermediate);

  stringstream geek(tokens[0]);
  int operationCode = 0;
  geek >> operationCode;
  string response;

  // Display response
  if (operationCode == 1) cout << "La respuesta es: " << tokens[1] << endl;
  else cout << "No se encontro la pelicula" << endl;
  // Close connection
  close(clientSd);

  return 0;
}