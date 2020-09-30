#ifndef filapedidos_h
#define filapedidos_h


#include <stdlib.h>
#include <stdio.h>

#define TAMANHO_MAX 300


typedef struct filapedidos FilaPedidos;


FilaPedidos *cria_fila_pedidos_fabrica();
FilaPedidos *cria_fila_pedidos_maquina();

void set_pedido_fila(FilaPedidos *filaPedidos, void *pedido);
// void imprime_fila(FilaPedidos *filapedidos);

void *pop_pedido_fila(FilaPedidos *filaPedidos);

int tem_elementos_fila(FilaPedidos *filaPedidos);


#endif