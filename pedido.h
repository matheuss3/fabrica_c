#ifndef pedido_h
#define pedido_h


#include "cilindrico.h"
#include "conico.h"


typedef struct pedido Pedido;


char *get_tipo_pedido(Pedido *pedido);

void *get_maquina_atual_pedido(Pedido *pedido);

float get_tempo_pedido(Pedido *pedido);
float get_tempo_estadia_torno_pedido(Pedido *pedido);
float get_tempo_estadia_fresa_pedido(Pedido *pedido);
float get_tempo_estadia_mandril_pedido(Pedido *pedido);

int get_local_pedido(Pedido *pedido);
int get_prioridade_pedido(Pedido *pedido);

void incrementa_maquina_pedido(Pedido *pedido);
void atende_pedido(Pedido *pedido, void *fabrica);
void set_prox_maquina_pedido(Pedido *pedido);
void finaliza_etapa_ped(Pedido *pedido, void *fabrica);
void set_tempo_pedido(Pedido *pedido, float tempo);
void atualiza_tempo_pedido(Pedido *pedido, float tempo);

Pedido *cria_pedido_cilindrico(void *fabrica);
Pedido *cria_pedido_conico(void *fabrica);

#endif