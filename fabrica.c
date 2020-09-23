#include "fabrica.h"

typedef struct fabrica {
  Pedido *pedidoCilindrico;
  int contCilindrico;
  Pedido *pedidoConico;
  int contConico;
  // Pedido *pedidoEsfericoAco;
  // int contEsfericoAco;

  Maquina *torno;
  // Maquina *torno2;
  Maquina *fresa;
  Maquina *mandril;

  float tempoAtu;
  float tempoFim;
  float tempos[5];
} Fabrica;

void print_line(char *menssagem) {
  printf("%s\n", menssagem);
}

void print_infos_fabrica(Fabrica *fabrica) {
  printf(
    "\nFABRICA\n\
    Tempo: %.2f \t Tempo Fim: %.2f\n\
    Tempo torno: %.2f \t Tempo fresa: %.2f \t Tempo mandril: %.2f \t\n\
    Tempo pedido cilindrico: %.2f \t Tempo pedido conico: %.2f\n\
    Quantidade de cilindricos finalizados: %d \t Quantidade de pedidos conicos finalizados: %d\n", 
    fabrica->tempoAtu,
    fabrica->tempoFim,
    fabrica->tempos[2],
    fabrica->tempos[3],
    fabrica->tempos[4],
    fabrica->tempos[0],
    fabrica->tempos[1],
    fabrica->contCilindrico,
    fabrica->contConico
  );
}

int pos_menor_tempo(float *tempos, int qtdTempos) {
  int menor = 0;

  for (int i = 1; i < qtdTempos; i++) {
    if (tempos[i] < tempos[menor] && tempos[i] != 0) {
      menor = i;
    }
  }

  return menor;
}

void atualiza_tempos_fabrica(Fabrica *fabrica) {
  fabrica->tempos[0] = get_tempo_pedido(fabrica->pedidoCilindrico);
  fabrica->tempos[1] = get_tempo_pedido(fabrica->pedidoConico);
  fabrica->tempos[2] = get_tempo_maquina(fabrica->torno);
  fabrica->tempos[3] = get_tempo_maquina(fabrica->fresa);
  fabrica->tempos[4] = get_tempo_maquina(fabrica->mandril);
}

void inc_cont_cilindrico(Fabrica *fabrica) {
  fabrica->contCilindrico++;
}

void inc_cont_conico(Fabrica *fabrica) {
  fabrica->contConico++;
}

void atende_menor_tempo(Fabrica *fabrica) {
  if (fabrica->tempoAtu <= fabrica->tempoFim) { // Verificando se o tempo acabou
    // Posição do menor tempo da fila de tempos
    int posMenor = pos_menor_tempo(fabrica->tempos, 5);
    printf("\nMenor tempo: %.2f\n", fabrica->tempos[posMenor]);
    
    // Setando tempo da fábrica para próximo menor tempo
    fabrica->tempoAtu = fabrica->tempos[posMenor];

    if (posMenor == 0) { // Menor tempo para atender o pedido cilindrico
      atende_pedido(fabrica->pedidoCilindrico, fabrica);
    } else if (posMenor == 1) { // Atender conico
      atende_pedido(fabrica->pedidoConico, fabrica);
    } else if (posMenor == 2) { // Menor tempo para atender torno
      atende_maquina(fabrica->torno, fabrica); 
    } else if (posMenor == 3) { // Atender fresa
      atende_maquina(fabrica->fresa, fabrica);
    } else if (posMenor == 4) { // Mandril
      atende_maquina(fabrica->mandril, fabrica);
    }

    // Atualizando o tempo da fábrica após os processos realizados
    atualiza_tempos_fabrica(fabrica);

    // Imprimindo as novas informações da fábrica
    print_infos_fabrica(fabrica);
    print_line("############################################################################################");
    
    // Tempo de espera para verificar o próximo atendimento da fábrica
    // sleep(5);
    atende_menor_tempo(fabrica);
  } else {
    print_line("Horario comercial finalizado");
  }
}

void set_prox_pedido_cilindrico(Fabrica *fabrica, Pedido *pedido) {
  fabrica->pedidoCilindrico = pedido;

  fabrica->tempos[0] = get_tempo_pedido(fabrica->pedidoCilindrico);
}

void set_prox_pedido_conico(Fabrica *fabrica, Pedido *pedido) {
  fabrica->pedidoConico = pedido;

  fabrica->tempos[1] = get_tempo_pedido(fabrica->pedidoConico);
}

void set_tempo_fabrica(Fabrica *fabrica, float tempo) {
  fabrica->tempoAtu = tempo;
}

Maquina *get_torno_fabrica(Fabrica *fabrica) {
  return fabrica->torno;
}

Maquina *get_fresa_fabrica(Fabrica *fabrica) {
  return fabrica->fresa;
}

Maquina *get_mandril_fabrica(Fabrica *fabrica) {
  return fabrica->mandril;
}

float get_tempo_fabrica(Fabrica *fabrica) {
  return fabrica->tempoAtu;
}

void cria_fabrica(float tempoFim) {
  // Alocação de memória para a fábrica
  Fabrica *fabrica = (Fabrica *) malloc(sizeof(Fabrica));
  print_line("Fabrica alocada");

  // Atributos default da fábrica
  fabrica->contCilindrico = 0;
  fabrica->contConico = 0;
  fabrica->tempoAtu = 0;
  fabrica->tempoFim = tempoFim;

  // Máquinas da fábrica
  fabrica->torno = cria_torno();
  print_line("Torno criado");
  fabrica->fresa = cria_fresa();
  print_line("Fresa criada");
  fabrica->mandril = cria_mandril();
  print_line("Mandril criada");
  // Tempo do torno adicionado em seu lugar na fila de tempos
  // da fábrica
  fabrica->tempos[2] = get_tempo_maquina(fabrica->torno);
  fabrica->tempos[3] = get_tempo_maquina(fabrica->fresa);
  fabrica->tempos[4] = get_tempo_maquina(fabrica->mandril);

  // Pedidos iniciais
  fabrica->pedidoCilindrico = cria_pedido_cilindrico(fabrica);
  print_line("Pedido cilindrico criado");
  fabrica->pedidoConico = cria_pedido_conico(fabrica);
  print_line("Pedido conico criado");
  // Tempo dos pedidos adicionado em seu lugar na fila de tempos
  // da fábrica
  fabrica->tempos[0] = get_tempo_pedido(fabrica->pedidoCilindrico);
  fabrica->tempos[1] = get_tempo_pedido(fabrica->pedidoConico);
  
  // Exibição das informações iniciais da fábrica
  print_infos_fabrica(fabrica);
  
  // Funão para atender o menor tempo da fila
  atende_menor_tempo(fabrica);
}