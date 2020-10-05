#ifndef torno_h
#define torno_h


#include "maquina.h"


float tempo_estadia_torno(void *pedido);

void set_pedido_maquina_torno(void *fabrica, Maquina *t1, void *pedido);


#endif