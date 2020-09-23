#ifndef conico_h
#define conico_h


char *tipo_pedido_conico();

void atende_conico(void *fabrica, void *pedido);
void set_prox_maquina_conico(void *pedido);
void finaliza_pedido_conico(void *fabrica);


#endif