#include "esfericoaco.h"
#include "fabrica.h"
#include "maquina.h"
#include "pedido.h"

void atende_esferico_aco(void *pedido, void *fabrica) {
  // Ao atender um pedido conico, outro pedido do mesmo tipo é criado
  // e adicionado na fábrica
  set_pedido_fila_fabrica(fabrica, cria_pedido_esferico(fabrica));
  // Setando a proxima máquina que o pedido irá
  set_prox_maquina_esferico_aco(pedido, fabrica);

  set_atende_pedido(pedido, &set_prox_maquina_esferico_aco);
}

void finaliza_pedido_esferico_aco(void *pedido, void *fabrica) {
  // Quando o pedido é finalizado o contador é incrementado em 1
  float tempoProducao = (get_tempo_fabrica(fabrica)) - get_tempo_chegada_pedido(pedido);
  inc_cont_esferico_aco(tempoProducao, fabrica);

  free(pedido);
}

void set_prox_maquina_esferico_aco(void *pedido, void *fabrica) {
  if(!pedido_em_alguma_maquina(pedido)) { 
    // Removendo pedido da maquina atual
    transfere_fila_slot_maquina(get_maquina_atual_pedido(pedido), fabrica);
  }

  // Passando o pedido para o proximo local
  incrementa_maquina_pedido(pedido);

  if (!pedido_pronto(pedido)) { // Pedido ainda dentro da fabrica
    Maquina *maquina = (Maquina *) get_maquina_atual_pedido(pedido);
    get_func_set_pedido_maquina(fabrica, maquina, pedido);
  } else {
    finaliza_pedido_esferico_aco(pedido, fabrica);
  }
}