#include "mandril.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

float tempo_estadia_mandril(void *pedido) {
  return get_tempo_estadia_mandril_pedido(pedido);
}