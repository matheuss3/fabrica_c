#include "cilindrico.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

char *tipo_pedido_cilindrico() {
  return "Cilindrico";
}

void atende_cilindrico(void *pedido, void *fabrica) {
  // Ao atender um pedido cilindrico, outro pedido do mesmo tipo é criado
  // e adicionado na fábrica
  set_prox_pedido_cilindrico(fabrica, cria_pedido_cilindrico(fabrica));

  // Setando a proxima máquina que o pedido irá
  set_prox_maquina_cilindrico(pedido);
}

void set_prox_maquina_cilindrico(void *pedido) {
  // Passando o pedido para o proximo local
  incrementa_maquina_pedido(pedido);

  if (get_maquina_atual_pedido(pedido) != NULL) { // Pedido ainda dentro da fabrica
    // Setando o pedido na maquina referente
    set_pedido_maquina(get_maquina_atual_pedido(pedido), pedido);
  }
}

void finaliza_pedido_cilindrico(void *fabrica) {
  // Quando o pedido é finalizado o contador é incrementado em 1
  inc_cont_cilindrico(fabrica);
  printf("Contador de pedidos cilindricos incrementado\n");
}