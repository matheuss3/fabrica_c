#include "torno.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

float tempo_estadia_torno(void *pedido) {
  return get_tempo_estadia_torno_pedido(pedido);
}

void *atende_torno(void *torno, void *fabrica) {
  // Pedido do slot da máquina que será retirado
  Pedido *pedidoSlot = get_pedido_maquina(torno);
  atualiza_tempo_pedido(pedidoSlot, get_tempo_maquina(torno));
  
  // Transferindo o proximo pedido da fila para a produção
  transfere_fila_slot_maquina(torno, fabrica);

  return pedidoSlot;
}