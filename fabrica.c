#include "fabrica.h"

typedef struct fabrica {
  FilaPedidos *pedidos;

  int contCilindrico;
  int contConico;

  Maquina *torno1;
  Maquina *torno2;
  Maquina *fresa;
  Maquina *mandril;

  float tempoAtu;
  float tempoFim;
} Fabrica;

void print_line(char *menssagem) {
  printf("%s\n", menssagem);
}

void inc_cont_cilindrico(Fabrica *fabrica) {
  fabrica->contCilindrico++;
}

void inc_cont_conico(Fabrica *fabrica) {
  fabrica->contConico++;
}

void atende_menor_tempo(Fabrica *fabrica) {
  if (fabrica->tempoAtu <= fabrica->tempoFim) { // Verificando se o tempo acabou
    Pedido *pedido = (Pedido *) pop_pedido_fila(fabrica->pedidos); // Pedido a ser atendido
    fabrica->tempoAtu = get_tempo_pedido(pedido);

    atende_pedido(pedido, fabrica);

    imprime_fila(fabrica->pedidos);

    printf("contador de pedido conico: %d\n", fabrica->contConico);
    printf("contador de pedido cilindrico: %d\n", fabrica->contCilindrico);

    atende_menor_tempo(fabrica);


  } else {
    print_line("Horario comercial finalizado");
  }
}

void set_tempo_fabrica(Fabrica *fabrica, float tempo) {
  fabrica->tempoAtu = tempo;
}

Maquina *get_torno1_fabrica(Fabrica *fabrica) {
  return fabrica->torno1;
}

Maquina *get_torno2_fabrica(Fabrica *fabrica) {
  return fabrica->torno2;
}

Maquina *get_fresa_fabrica(Fabrica *fabrica) {
  return fabrica->fresa;
}

Maquina *get_mandril_fabrica(Fabrica *fabrica) {
  return fabrica->mandril;
}

float get_tempo_fabrica(Fabrica *fabrica) {
  return fabrica->tempoAtu;
}

void set_pedido_fila_fabrica(Fabrica *fabrica, Pedido *pedido) {
  set_pedido_fila(fabrica->pedidos, pedido);
}

void cria_fabrica(float tempoFim) {
  // Alocação de memória para a fábrica
  Fabrica *fabrica = (Fabrica *) malloc(sizeof(Fabrica));
  print_line("Fabrica alocada");

  // Atributos default da fábrica
  fabrica->contCilindrico = 0;
  fabrica->contConico = 0;
  fabrica->tempoAtu = 0;
  fabrica->tempoFim = tempoFim;

  // Máquinas da fábrica
  FilaPedidos *filatorno = cria_fila_pedidos_maquina();
  fabrica->torno1 = cria_torno(filatorno);
  print_line("Torno1 criado");
  fabrica->torno2 = cria_torno(filatorno);
  print_line("Torno2 criado");
  fabrica->fresa = cria_fresa(cria_fila_pedidos_maquina());
  print_line("Fresa criada");
  fabrica->mandril = cria_mandril(cria_fila_pedidos_maquina());
  print_line("Mandril criada");

  fabrica->pedidos = cria_fila_pedidos_fabrica();
  print_line("Fila criada");
  set_pedido_fila(fabrica->pedidos, cria_pedido_cilindrico(fabrica));
  set_pedido_fila(fabrica->pedidos, cria_pedido_conico(fabrica));
  imprime_fila(fabrica->pedidos);

  atende_menor_tempo(fabrica);
}