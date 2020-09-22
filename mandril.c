#include "mandril.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

float tempo_estadia_mandril(void *pedido) {
  return get_tempo_estadia_mandril_pedido(pedido);
}

void *atende_mandril(void *mandril, void *fabrica) {
  // Pedido do slot da máquina que será retirado
  Pedido *pedidoSlot = get_pedido_maquina(mandril);
  atualiza_tempo_pedido(pedidoSlot, get_tempo_maquina(mandril));
  
  // Transferindo o proximo pedido da fila para a produção
  transfere_fila_slot_maquina(mandril, fabrica);

  return pedidoSlot;
}