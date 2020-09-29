#include "pedido.h"
#include "fabrica.h"
#include "maquina.h"

// Definindo as prioridades
#define BAIXA 1
#define MEDIA 2
#define ALTA 3

typedef struct pedido {
  int prioridade;
  
  float tempo;
  float estadiaTorno;
  float estadiaFresa;
  float estadiaMandril;

  Maquina *maquinas[5];
  Maquina *maquinaAtu;
  int itMaquinaAtu;

  char *(*tipoPedido)();
  void (*atendePedido)(void *pedido, void *fabrica);
} Pedido;

char *get_tipo_pedido(Pedido *pedido) {
  return pedido->tipoPedido();
}

void set_tempo_pedido(Pedido *pedido, float tempo) {
  pedido->tempo = tempo;
}

void atualiza_tempo_pedido(Pedido *pedido, float tempo) {
  pedido->tempo = tempo;
}

int get_local_pedido(Pedido *pedido) {
  return pedido->itMaquinaAtu;
}

void *get_maquina_atual_pedido(Pedido *pedido) {
  return pedido->maquinaAtu;
}

float tempo_de_maquina(float Estadia_Equipamento_Rolamento) { 
  // Tempo que o rolamento vai ficar no maquinario
  float u = ((float) rand()) / ((float) RAND_MAX);

  return 2.0 * Estadia_Equipamento_Rolamento * u;
}

float get_tempo_estadia_torno_pedido(Pedido *pedido) {
  return tempo_de_maquina(pedido->estadiaTorno);
}

float get_tempo_estadia_fresa_pedido(Pedido *pedido) {
  return tempo_de_maquina(pedido->estadiaFresa);
}

float get_tempo_estadia_mandril_pedido(Pedido *pedido) {
  return tempo_de_maquina(pedido->estadiaMandril);
}

float get_estadia_torno(Pedido *pedido) {
  return pedido->estadiaTorno;
}

float get_tempo_pedido(Pedido *pedido) {
  return pedido->tempo;
}

float gera_tempo_pedido(float avg) {
  float u = 0; /* Gera randomicamente um numero entre 0 e 1 */
  
  do 
    u = ((float)rand()) / ((float) RAND_MAX);
  while ((u == 0) || (u == 1));
  
  return (-avg * log (u));
}

Pedido* cria_pedido_cilindrico(void *fabrica) {
  // Alocação de espaço para o pedido
  Pedido *pedidoCilindrico = (Pedido *) malloc(sizeof(Pedido));
  
  // Valores default para um pedido do tipo cilindrico
  pedidoCilindrico->prioridade = BAIXA;
  pedidoCilindrico->itMaquinaAtu = -1;
  pedidoCilindrico->estadiaTorno = 0.8;
  pedidoCilindrico->estadiaFresa = 0.5;
  pedidoCilindrico->estadiaMandril = 1.2;

  // Inserindo máquinas na ordem em que elas serão utilizadas pelo pedido
  pedidoCilindrico->maquinas[0] = get_torno1_fabrica((Fabrica *)fabrica);
  pedidoCilindrico->maquinas[1] = get_fresa_fabrica((Fabrica *)fabrica);
  pedidoCilindrico->maquinas[2] = get_mandril_fabrica((Fabrica *)fabrica);
  pedidoCilindrico->maquinas[3] = get_torno1_fabrica((Fabrica *)fabrica);
  pedidoCilindrico->maquinas[4] = NULL; // Valor NULL para indicar que o pedido saiu da fábrica

  // Tempo do pedido = tempo da fábrica + um valor "aleatório"
  pedidoCilindrico->tempo = get_tempo_fabrica((Fabrica *)fabrica) + gera_tempo_pedido(21.5);
  
  // Ponteiros para funções necessários para um pedido cilindrico
  pedidoCilindrico->tipoPedido = tipo_cilindrico;
  pedidoCilindrico->atendePedido = atende_cilindrico;

  return pedidoCilindrico;
}

Pedido* cria_pedido_conico(void *fabrica) {
  // Alocação de espaço para o pedido
  Pedido *pedidoConico = (Pedido *) malloc(sizeof(Pedido));
  
  // Valores default para um pedido do tipo conico
  pedidoConico->prioridade = MEDIA;
  pedidoConico->itMaquinaAtu = -1;
  pedidoConico->estadiaTorno = 1.8;
  pedidoConico->estadiaFresa = 0;
  pedidoConico->estadiaMandril = 2.1;

  // Inserindo máquinas na ordem em que elas serão utilizadas pelo pedido
  pedidoConico->maquinas[0] = get_torno1_fabrica((Fabrica *)fabrica);
  pedidoConico->maquinas[1] = get_mandril_fabrica((Fabrica *)fabrica);
  pedidoConico->maquinas[2] = get_torno1_fabrica((Fabrica *)fabrica);
  pedidoConico->maquinas[3] = NULL; // Valor NULL para indicar que o pedido saiu da fábrica

  // Tempo do pedido = tempo da fábrica + um valor "aleatório"
  pedidoConico->tempo = get_tempo_fabrica((Fabrica *)fabrica) + gera_tempo_pedido(19.1);
  
  // Ponteiros para funções necessários para um pedido conico
  pedidoConico->tipoPedido = tipo_conico;
  pedidoConico->atendePedido = atende_conico;

  return pedidoConico;
}

void set_atende_pedido(Pedido *pedido, void (*proxFunction)(void *pedido, void *fabrica)) {
  pedido->atendePedido = proxFunction;
}

void atende_pedido(Pedido *pedido, void *fabrica) {
  pedido->atendePedido(pedido, fabrica);
}

void set_maquina_atu_pedido(Pedido *pedido, void *maquina) {
  pedido->maquinaAtu = (Maquina *) maquina;
}

void incrementa_maquina_pedido(Pedido *pedido) {
  pedido->itMaquinaAtu++;
  pedido->maquinaAtu = pedido->maquinas[pedido->itMaquinaAtu];
}

int get_prioridade_pedido(Pedido *pedido) {
  return pedido->prioridade;
}

int pedido_em_alguma_maquina(Pedido *pedido) {
  return pedido->itMaquinaAtu == -1;
}