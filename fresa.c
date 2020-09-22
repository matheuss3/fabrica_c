#include "fresa.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

float tempo_estadia_fresa(void *pedido) {
  return get_tempo_estadia_fresa_pedido(pedido);
}

void *atende_fresa(void *fresa, void *fabrica) {
  // Pedido do slot da máquina que será retirado
  Pedido *pedidoSlot = get_pedido_maquina(fresa);
  atualiza_tempo_pedido(pedidoSlot, get_tempo_maquina(fresa));

  // Transferindo o proximo pedido da fila para a produção
  transfere_fila_slot_maquina(fresa, fabrica);

  return pedidoSlot;
}