#ifndef fabrica_h
#define fabrica_h


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "maquina.h"
#include "pedido.h"
#include "filapedidos.h"


typedef struct fabrica Fabrica;


void set_tempo_fabrica(Fabrica *fabrica, float tempo);
void set_pedido_fila_fabrica(Fabrica *fabrica, Pedido *pedido);

float get_tempo_fabrica(Fabrica *fabrica);

Maquina *get_torno1_fabrica(Fabrica *fabrica);
Maquina *get_fresa_fabrica(Fabrica *fabrica);
Maquina *get_mandril_fabrica(Fabrica *fabrica);
Maquina *get_torno2_fabrica(Fabrica *fabrica);

void cria_fabrica(float tempo_fim);

void inc_cont_cilindrico(float tempoProd, Fabrica *fabrica);
void inc_cont_conico(float tempoProd, Fabrica *fabrica);
void inc_cont_esferico_aco(float tempoProd, Fabrica *fabrica);
void inc_cont_esferico_titanio(float tempoProd, Fabrica *fabrica);

#endif