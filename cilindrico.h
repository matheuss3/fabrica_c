#ifndef cilindrico_h
#define cilindrico_h


char *tipo_pedido_cilindrico();

void atende_cilindrico(void *fabrica, void *pedido);
void set_prox_maquina_cilindrico(void *pedido);
void finaliza_pedido_cilindrico(void *fabrica);


#endif