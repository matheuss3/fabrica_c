#include "torno.h"
#include "fabrica.h"
#include "pedido.h"

float tempo_estadia_torno(void *pedido) {
  return get_tempo_estadia_torno_pedido(pedido);
}

void set_pedido_maquina_torno(void *fabrica, Maquina *t1, void *pedido) {
  Maquina *t2 = get_torno2_fabrica(fabrica);
  
  if (maquina_liberada(t1)) { // Torno primário
    set_pedido_slot_maquina(fabrica, t1, pedido);
  } else if (maquina_liberada(t2)) {
    set_pedido_slot_maquina(fabrica, t2, pedido);
    set_maquina_atu_pedido(pedido, t2);
  } else {
    // Inserindo pedido na fila de espera, os dois tornos compartilham da mesma fila
    set_pedido_fila(get_fila_pedidos_maquina(t1), pedido);
  }
}