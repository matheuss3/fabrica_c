#ifndef filapedidos_h
#define filapedidos_h


#include <stdlib.h>


#define TAMANHO_MAX 100


typedef struct filapedidos FilaPedidos;

FilaPedidos *cria_fila_pedidos();

void set_pedido_fila(FilaPedidos *filaPedidos, void *pedido);

void *pop_pedido_fila(FilaPedidos *filaPedidos);

int tem_elementos_fila(FilaPedidos *filaPedidos);


#endif