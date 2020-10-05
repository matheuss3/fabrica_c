#include "fresa.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

float tempo_estadia_fresa(void *pedido) {
  return get_tempo_estadia_fresa_pedido(pedido);
}