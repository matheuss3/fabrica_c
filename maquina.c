#include "maquina.h"
#include "fabrica.h"
#include "pedido.h"

typedef struct maquina {
  float tempo;
  
  Pedido *slotPedido;

  FilaPedidos *filaPedidos;

  void *(*atendeMaquina)(void *maquina, void *fabrica);
  float (*tempoEstadiaPedido)(void *pedido);
} Maquina;

void set_pedido_maquina(Maquina *maquina, void *pedido) {
  // Pedido posicionado no slod de produção
  Pedido *pedidoSlot = get_pedido_maquina(maquina);
  
  if (pedidoSlot == NULL) { // Não existe pedido no slot
    maquina->slotPedido = (Pedido *) pedido;
    
    // Tempo em que o pedido foi para o slot da máquina para
    // ser produzido
    float tempoPedido = get_tempo_pedido(pedido);
    // Tempo de produção do pedido
    float tempoEstadia = maquina->tempoEstadiaPedido(pedido);
    // Tempo em que o pedido foi para o slot + tempo de produção
    maquina->tempo = tempoPedido + tempoEstadia;

    printf("\nPedido setado no slot da maquina\n");
    printf("Tempo de chegada: %.2f\n", tempoPedido);
    printf("Tempo de estadia: %.2f\n", tempoEstadia);
    printf("Tempo de saida: %.2f\n", maquina->tempo);
  } else {
    // Inserindo pedido na fila de espera
    set_pedido_fila(maquina->filaPedidos, pedido);

    printf("\nPedido inserido na fila de espera da maquina\n");
  }
}

float get_tempo_maquina(Maquina *maquina) {
  return maquina->tempo;
}

void *get_pedido_maquina(Maquina *maquina) {
  return maquina->slotPedido;
}

Maquina *cria_torno() {
  // Alocação de memória para a máquina
  Maquina *torno = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  torno->tempo = 0;
  torno->slotPedido = NULL;
  torno->filaPedidos = cria_fila_pedidos();

  // Ponteiros específicos para funções de um torno
  torno->tempoEstadiaPedido = tempo_estadia_torno;
  torno->atendeMaquina = atende_torno;

  return torno;
}

Maquina *cria_fresa() {
  // Alocação de memória para a máquina
  Maquina *fresa = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  fresa->tempo = 0;
  fresa->slotPedido = NULL;
  fresa->filaPedidos = cria_fila_pedidos();

  // Ponteiros específicos para funções de um fresa
  fresa->tempoEstadiaPedido = tempo_estadia_fresa;
  fresa->atendeMaquina = atende_fresa;

  return fresa;
}

Maquina *cria_mandril() {
  // Alocação de memória para a máquina
  Maquina *fresa = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  fresa->tempo = 0;
  fresa->slotPedido = NULL;
  fresa->filaPedidos = cria_fila_pedidos();

  // Ponteiros específicos para funções de um fresa
  fresa->tempoEstadiaPedido = tempo_estadia_mandril;
  fresa->atendeMaquina = atende_mandril;

  return fresa;
}

void atende_maquina(Maquina *maquina, void *fabrica) {
  // Ao atender uma máquina quer dizer que, o pedido que está
  // no slot da máquina terminou de ser produzido.
  // A função de atendimento de uma máquina retorna o pedido que
  // estava no slot
  Pedido *pedidoSlot = maquina->atendeMaquina(maquina, fabrica);

  // Mandando o pedido para sua proxima máquina
  set_prox_maquina_pedido(pedidoSlot);
  
  // Verificando se o pedido foi finalizado totalmente
  finaliza_etapa_ped(pedidoSlot, fabrica);
}

void transfere_fila_slot_maquina(Maquina *maquina, void *fabrica) {
  // Setando null no slot para indicar que o slot está vazio
  maquina->slotPedido = NULL;

  printf("Pedido do slot removido.\n");

  if (tem_elementos_fila(maquina->filaPedidos)) { // Se existe alguem na fila
    // Pedido na primeira posição da fila será atendido
    Pedido *proxPedido = (Pedido *) pop_pedido_fila(maquina->filaPedidos);

    // Setando o tempo chegada na máquina para o tempo atual da fábrica
    set_tempo_pedido(proxPedido, get_tempo_fabrica(fabrica));

    // Inserindo pedido no slot da máquina
    printf("Setando proximo pedido da fila no slot de produção");
    set_pedido_maquina(maquina, proxPedido);

    printf("Pedido transferido da fila para producao.\n");
  } else { // Não existem pedidos na fila
    maquina->tempo = 0.0;

    printf("Nenhum pedido na fila de espera\n");
  }
}