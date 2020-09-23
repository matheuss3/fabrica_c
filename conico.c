#include "conico.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

char *tipo_pedido_conico() {
  return "Conico";
}

void atende_conico(void *pedido, void *fabrica) {
  // Ao atender um pedido conico, outro pedido do mesmo tipo é criado
  // e adicionado na fábrica
  set_prox_pedido_conico(fabrica, cria_pedido_conico(fabrica));

  // Setando a proxima máquina que o pedido irá
  set_prox_maquina_conico(pedido);
}

void set_prox_maquina_conico(void *pedido) {
  // Passando o pedido para o proximo local
  incrementa_maquina_pedido(pedido);

  if (get_maquina_atual_pedido(pedido) != NULL) { // Pedido ainda dentro da fabrica
    // Setando o pedido na maquina referente
    set_pedido_maquina(get_maquina_atual_pedido(pedido), pedido);
  }
}

void finaliza_pedido_conico(void *fabrica) {
  // Quando o pedido é finalizado o contador é incrementado em 1
  inc_cont_conico(fabrica);
  printf("Contador de pedidos conicos incrementado\n");
}