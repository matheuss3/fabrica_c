#include "filapedidos.h"
#include "pedido.h"

typedef struct filapedidos {
  Pedido *pedidos[TAMANHO_MAX];
  int tamFila;
  int (*functionComp)(Pedido *ped1, Pedido *ped2);
} FilaPedidos;

int comp_tempo(Pedido *ped1, Pedido *ped2) {
  return get_tempo_pedido(ped1) < get_tempo_pedido(ped2);
}

int comp_prioridade(Pedido *ped1, Pedido *ped2) {
  return get_prioridade_pedido(ped1) > get_prioridade_pedido(ped2);
}

void set_pedido_fila(FilaPedidos *filaPedidos, void *pedido) {
  int i = filaPedidos->tamFila - 1;
  Pedido *pedidoFila = filaPedidos->pedidos[i];

  while (i >= 0 && (filaPedidos->functionComp(pedido, pedidoFila))) {
    filaPedidos->pedidos[i + 1] = pedidoFila;

    i--;
    pedidoFila = filaPedidos->pedidos[i];
  }
  
  if (!tem_elementos_fila(filaPedidos)) filaPedidos->pedidos[0] = pedido; // Saiu pq a fila está vazia
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

void imprime_fila(FilaPedidos *filapedidos) {
  printf("Tamanho: %d\n", filapedidos->tamFila);
  printf("|| ");
  if (tem_elementos_fila(filapedidos)) {

    for (int i = 0; i < filapedidos->tamFila; i++) {
      printf("%d - ", i + 1);
      printf("%c;%.2f\t", get_id_pedido(filapedidos->pedidos[i]), get_tempo_pedido(filapedidos->pedidos[i]));
    }
  }
  printf("\n");
}

FilaPedidos *cria_fila_pedidos_fabrica() {
  // Alocação de memória para a fila
  FilaPedidos *filaPedidos = (FilaPedidos *) malloc(sizeof(FilaPedidos));

  // Valores default
  filaPedidos->tamFila = 0;

  // Função de comparar prioridade
  filaPedidos->functionComp = comp_tempo;
  
  return filaPedidos;
}

FilaPedidos *cria_fila_pedidos_maquina() {
  // Alocação de memória para a fila
  FilaPedidos *filaPedidos = (FilaPedidos *) malloc(sizeof(FilaPedidos));

  // Valores default
  filaPedidos->tamFila = 0;

  // Função de comparar prioridade
  filaPedidos->functionComp = comp_prioridade;

  return filaPedidos;
}