#ifndef maquina_h
#define maquina_h


// includes necessários para o funcionamento das máquinas
#include "filapedidos.h"

// Tamanho máximo da fila de espera de uma máquina
#define TAMANHO_MAXIMO_FILA 100


// Tipo máquina qualquer
typedef struct maquina Maquina;


int maquina_liberada(Maquina *maquina);

void set_pedido_maquina(void *fabrica, Maquina *maquina, void *pedido);
void set_pedido_slot_maquina(void *fabrica, Maquina *maquina, void *pedido);
void finaliza_pedido_maquina(Maquina *maquina, void *pedido);
void transfere_fila_slot_maquina(Maquina *maquina, void *fabrica);
void get_func_pedido_maquina(void *fabrica, Maquina *maquina, void *pedido);

void *get_pedido_maquina(Maquina *maquina);
void *get_fila_pedidos_maquina(Maquina *maquina);

Maquina *cria_torno(FilaPedidos *fila);
Maquina *cria_fresa(FilaPedidos *fila);
Maquina *cria_mandril(FilaPedidos *fila);


#endif