#include "filapedidos.h"
#include "pedido.h"

typedef struct filapedidos {
  Pedido *pedidos[TAMANHO_MAX];
  int tamFila;
} FilaPedidos;

FilaPedidos *cria_fila_pedidos() {
  // Alocação de memória para a fila
  FilaPedidos *filaPedidos = (FilaPedidos *) malloc(sizeof(FilaPedidos));

  // Valores default
  filaPedidos->tamFila = 0;

  return filaPedidos;
}

int comp_prioridade(Pedido *ped1, Pedido *ped2) {
  return get_prioridade_pedido(ped1) > get_prioridade_pedido(ped2);
}

void set_pedido_fila(FilaPedidos *filaPedidos, void *pedido) {
  int i = filaPedidos->tamFila - 1;
  Pedido *pedidoFila = filaPedidos->pedidos[i];

  while (i > 0 && comp_prioridade(pedido, pedidoFila)) {
    filaPedidos->pedidos[i + 1] = pedidoFila;

    i--;
    pedidoFila = filaPedidos->pedidos[i];
  }

  if (i == 0) filaPedidos->pedidos[i] = pedido; // Saiu pq a fila está vazia
  else filaPedidos->pedidos[i + 1] = pedido; // Saiu pq encontrou pedido com prioridade igual

  filaPedidos->tamFila++;
}

void *pop_pedido_fila(FilaPedidos *filaPedidos) {
  void *pedido = filaPedidos->pedidos[0];

  for (int i = 1; i < filaPedidos->tamFila; i++) {
    filaPedidos->pedidos[i - 1] = filaPedidos->pedidos[i];
  }

  filaPedidos->tamFila--;

  return pedido;
}

int tem_elementos_fila(FilaPedidos *filaPedidos) {
  return filaPedidos->tamFila > 0;
}