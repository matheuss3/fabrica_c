#ifndef maquina_h
#define maquina_h


// includes necessários para o funcionamento das máquinas
#include "torno.h"
#include "fresa.h"
#include "mandril.h"
#include "filapedidos.h"

// Tamanho máximo da fila de espera de uma máquina
#define TAMANHO_MAXIMO_FILA 100


// Tipo máquina qualquer
typedef struct maquina Maquina;


void set_pedido_maquina(Maquina *maquina, void *pedido);
void atende_maquina(Maquina *maquina, void *fabrica);
void transfere_fila_slot_maquina(Maquina *maquina, void *fabrica);

void *get_pedido_maquina(Maquina *maquina);

float get_tempo_maquina(Maquina *maquina);

Maquina *cria_torno();
Maquina *cria_fresa();
Maquina *cria_mandril();

#endif