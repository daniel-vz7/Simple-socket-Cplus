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
using namespace std;

//Client side
int main(int argc, char *argv[]) {
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
  // Enter option
  cout << "Ingresa el dato a obtener" << endl << ">";
  string option;
  getline(cin, option);
  // Enter film name
  cout << "Ingresa el nombre de la pelicula" << endl << ">";
  string filmName;
  getline(cin, filmName);

  return 0;
}