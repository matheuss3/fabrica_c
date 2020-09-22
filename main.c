#include "fabrica.h"

int main(int argc, char *argv[]) {
  srand(time(NULL));

  // argv possui o tempo passado como argumento pelo usuário
  float user_time = atof(argv[1]);
  
  // criação da fábrica e o tempo de funcionamento
  cria_fabrica(user_time);

  return 0;
}