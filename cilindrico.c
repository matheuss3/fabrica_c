#include "cilindrico.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

char *tipo_cilindrico() {
  return "cilindrico";
}

void atende_cilindrico(void *pedido, void *fabrica) {
  // Ao atender um pedido cilindrico, outro pedido do mesmo tipo é criado
  // e adicionado na fábrica
  set_pedido_fila_fabrica(fabrica, cria_pedido_cilindrico(fabrica));

  // Setando a proxima máquina que o pedido irá
  set_prox_maquina_cilindrico(pedido, fabrica);

  set_atende_pedido(pedido, &set_prox_maquina_cilindrico);
}

void finaliza_pedido_cilindrico(void *pedido, void *fabrica) {
  // Quando o pedido é finalizado o contador é incrementado em 1
  inc_cont_cilindrico(fabrica);
  printf("Contador de pedidos cilindricos incrementado\n");
}

void set_prox_maquina_cilindrico(void *pedido, void *fabrica) {
  if(!pedido_em_alguma_maquina(pedido)) { 
    // Removendo pedido da maquina atual
    transfere_fila_slot_maquina(get_maquina_atual_pedido(pedido), fabrica);
  }

  // Passando o pedido para o proximo local
  incrementa_maquina_pedido(pedido);

  Maquina *maquina = (Maquina *) get_maquina_atual_pedido(pedido);

  if (maquina != NULL) { // Pedido ainda dentro da fabrica
    get_func_pedido_maquina(fabrica, maquina, pedido);
  } else {
    finaliza_pedido_cilindrico(pedido, fabrica);
  }
}

