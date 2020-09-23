#ifndef fabrica_h
#define fabrica_h


// includes necessários para o funcionamento da fábrica
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "maquina.h"
#include "pedido.h"


// Fábrica com os atributos e ponteiros pra pedidos e máquinas
// que a fábrica necessita
typedef struct fabrica Fabrica;


void set_tempo_fabrica(Fabrica *fabrica, float tempo);
void set_prox_pedido_cilindrico(Fabrica *fabrica, Pedido *pedido);
void set_prox_pedido_conico(Fabrica *fabrica, Pedido *pedido);


float get_tempo_fabrica(Fabrica *fabrica);

Maquina *get_torno_fabrica(Fabrica *fabrica);
Maquina *get_fresa_fabrica(Fabrica *fabrica);
Maquina *get_mandril_fabrica(Fabrica *fabrica);

void cria_fabrica(float tempo_fim);

void inc_cont_cilindrico(Fabrica *fabrica);
void inc_cont_conico(Fabrica *fabrica);


#endif