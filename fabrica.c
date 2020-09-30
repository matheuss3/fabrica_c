#include "fabrica.h"

typedef struct fabrica {
  FilaPedidos *pedidos;

  float somaTemposCilindrico;
  int contCilindrico;
  float somaTemposConicos;
  int contConico;
  float somaTemposEsfericosAco;
  int contEsfericoAco;
  float somaTemposEsfericosTitanio;
  int contEsfericoTitanio;

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

void inc_cont_cilindrico(float tempoProd, Fabrica *fabrica) {
  fabrica->somaTemposCilindrico += tempoProd;
  // printf("cilin: %.2f;%.2f\n",tempoProd,fabrica->somaTemposCilindrico);
  fabrica->contCilindrico++;
}

void inc_cont_conico(float tempoProd, Fabrica *fabrica) {
  fabrica->somaTemposConicos += tempoProd;
  // printf("con: %.2f;%.2f\n",tempoProd,fabrica->somaTemposConicos);
  fabrica->contConico++;
}

void inc_cont_esferico_aco(float tempoProd, Fabrica *fabrica) {
  fabrica->somaTemposEsfericosAco += tempoProd;
  // printf("con: %.2f;%.2f\n",tempoProd,fabrica->somaTemposConicos);
  fabrica->contEsfericoAco++;
}

void inc_cont_esferico_titanio(float tempoProd, Fabrica *fabrica) {
  fabrica->somaTemposEsfericosTitanio += tempoProd;
  // printf("con: %.2f;%.2f\n",tempoProd,fabrica->somaTemposConicos);
  fabrica->contEsfericoTitanio++;
}

void set_pedido_fila_fabrica(Fabrica *fabrica, Pedido *pedido) {
  set_pedido_fila(fabrica->pedidos, pedido);
}

void set_tempo_fabrica(Fabrica *fabrica, float tempo) {
  fabrica->tempoAtu = tempo;
}

float get_tempo_fabrica(Fabrica *fabrica) {
  return fabrica->tempoAtu;
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

void atende_menor_tempo(Fabrica *fabrica) {
  while (fabrica->tempoAtu <= fabrica->tempoFim) { // Verificando se o tempo acabou
    // Primeiro pedido da fila de espera da fábrica é retirado da fila para ser atendido
    Pedido *pedido = (Pedido *) pop_pedido_fila(fabrica->pedidos);
    // printf("%.2f\n", fabrica->tempoAtu);
    // Atualizando o tempo da fabrica para o tempo em que o pedido foi atendido
    set_tempo_fabrica(fabrica, get_tempo_pedido(pedido));
    // Atendendo o pedido retirado
    atende_pedido(pedido, fabrica);
  }
  
  printf("CILINDRICO:       %.2f \t %d\n", (fabrica->somaTemposCilindrico / fabrica->contCilindrico), fabrica->contCilindrico);
  printf("CONICO:           %.2f \t %d\n", (fabrica->somaTemposConicos / fabrica->contConico), fabrica->contConico);
  printf("ESFERICO ACO:     %.3f \t %d\n", (fabrica->somaTemposEsfericosAco / fabrica->contEsfericoAco), fabrica->contEsfericoAco);
  printf("ESFERICO TITANIO: %.3f \t %d\n", (fabrica->somaTemposEsfericosTitanio / fabrica->contEsfericoTitanio), fabrica->contEsfericoTitanio);

}

void cria_fabrica(float tempoFim) {
  // Alocação de memória para a fábrica
  Fabrica *fabrica = (Fabrica *) malloc(sizeof(Fabrica));

  // Atributos default da fábrica
  fabrica->somaTemposCilindrico = 0.0;
  fabrica->contCilindrico = 0;
  fabrica->somaTemposConicos = 0.0;
  fabrica->contConico = 0;
  fabrica->somaTemposEsfericosAco = 0.0;
  fabrica->contEsfericoAco = 0;
  fabrica->somaTemposEsfericosTitanio = 0.0;
  fabrica->contEsfericoTitanio = 0;
  fabrica->tempoAtu = 0;
  fabrica->tempoFim = tempoFim;

  // Máquinas da fábrica
  // Os tornos compartilham a mesma fila de pedidos
  FilaPedidos *filatorno = cria_fila_pedidos_maquina();
  fabrica->torno1 = cria_torno(filatorno);
  fabrica->torno2 = cria_torno(filatorno);

  fabrica->fresa = cria_fresa(cria_fila_pedidos_maquina());

  fabrica->mandril = cria_mandril(cria_fila_pedidos_maquina());

  fabrica->pedidos = cria_fila_pedidos_fabrica();
  
  // Os primeiros pedidos da fábrica
  set_pedido_fila(fabrica->pedidos, cria_pedido_cilindrico(fabrica));
  set_pedido_fila(fabrica->pedidos, cria_pedido_conico(fabrica));
  set_pedido_fila(fabrica->pedidos, cria_pedido_esferico(fabrica));

  // Inicio dos atendimentos
  atende_menor_tempo(fabrica);
}