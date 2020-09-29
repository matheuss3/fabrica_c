#include "maquina.h"
#include "fabrica.h"
#include "pedido.h"
#include "torno.h"
#include "fresa.h"
#include "mandril.h"

typedef struct maquina {
  Pedido *slotPedido;

  FilaPedidos *filaPedidos;

  void (*setPedidoMaquina)(void *fabrica, struct maquina *maquina, void *pedido);
  void *(*atendeMaquina)(void *maquina, void *fabrica);
  float (*tempoEstadiaPedido)(void *pedido);
} Maquina;

void set_pedido_slot_maquina(void *fabrica, Maquina *maquina, void *pedido) {
    maquina->slotPedido = (Pedido *) pedido;
    
    // Tempo em que o pedido foi para o slot da máquina para
    // ser produzido
    float tempoPedido = get_tempo_pedido(pedido);
    // Tempo de produção do pedido
    float tempoEstadia = maquina->tempoEstadiaPedido(pedido);
    // Tempo em que o pedido foi para o slot + tempo de produção
    set_tempo_pedido(pedido, tempoPedido + tempoEstadia);

    set_pedido_fila_fabrica(fabrica, pedido);
}

int maquina_liberada(Maquina *maquina) {
  return maquina->slotPedido == NULL;
}

void set_pedido_maquina(void *fabrica, Maquina *maquina, void *pedido) {
  if (maquina_liberada(maquina)) { // Não existe pedido no slot
    set_pedido_slot_maquina(fabrica, maquina, pedido);
  } else {
    // Inserindo pedido na fila de espera
    set_pedido_fila(get_fila_pedidos_maquina(maquina), pedido);

    printf("\nPedido inserido na fila de espera da maquina\n");
  }
  printf("Fila de espera ");
  imprime_fila(get_fila_pedidos_maquina(maquina));
}

void *get_pedido_maquina(Maquina *maquina) {
  return maquina->slotPedido;
}

void *get_fila_pedidos_maquina(Maquina *maquina) {
  return maquina->filaPedidos;
}

Maquina *cria_torno(FilaPedidos *fila) {
  // Alocação de memória para a máquina
  Maquina *torno = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  torno->slotPedido = NULL;
  torno->filaPedidos = fila;
  
  torno->setPedidoMaquina = set_pedido_maquina_torno;
  
  // Ponteiros específicos para funções de um torno
  torno->tempoEstadiaPedido = tempo_estadia_torno;
  
  return torno;
}

Maquina *cria_fresa(FilaPedidos *fila) {
  // Alocação de memória para a máquina
  Maquina *fresa = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  fresa->slotPedido = NULL;
  fresa->filaPedidos = fila;

  fresa->setPedidoMaquina = set_pedido_maquina;

  // Ponteiros específicos para funções de um fresa
  fresa->tempoEstadiaPedido = tempo_estadia_fresa;

  return fresa;
}

Maquina *cria_mandril(FilaPedidos *fila) {
  // Alocação de memória para a máquina
  Maquina *mandril = (Maquina *) malloc(sizeof(Maquina));

  // Valores default para os atributos da máquina
  mandril->slotPedido = NULL;
  mandril->filaPedidos = fila;

  mandril->setPedidoMaquina = set_pedido_maquina;

  // Ponteiros específicos para funções de um mandril
  mandril->tempoEstadiaPedido = tempo_estadia_mandril;

  return mandril;
}

void get_func_pedido_maquina(void *fabrica, Maquina *maquina, void *pedido) {
  maquina->setPedidoMaquina(fabrica, maquina, pedido);
}

void transfere_fila_slot_maquina(Maquina *maquina, void *fabrica) {
  // Setando null no slot para indicar que o slot está vazio
  maquina->slotPedido = NULL;

  printf("Pedido do slot removido.\n");
  imprime_fila(maquina->filaPedidos);
  if (tem_elementos_fila(maquina->filaPedidos)) { // Se existe alguem na fila
    // Pedido na primeira posição da fila será atendido
    Pedido *proxPedido = (Pedido *) pop_pedido_fila(maquina->filaPedidos);

    // Setando o tempo chegada na máquina para o tempo atual da fábrica
    set_tempo_pedido(proxPedido, get_tempo_fabrica(fabrica));

    // Inserindo pedido no slot da máquina
    printf("Setando proximo pedido da fila no slot de producao\n");
    
    get_func_pedido_maquina(fabrica, maquina, proxPedido);
    
    printf("Pedido transferido da fila para producao.\n");
  } else { // Não existem pedidos na fila
    printf("Nenhum pedido na fila de espera\n");
  }
}