#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void logo() {        
               
  printf("\n                         ur d$$$$$$$$$$$$$$Nu" );
  printf("\n                       d$$$ \"$$$$$$$$$$$$$$$$$$e.");
  printf("\n                   u$$c   \"\"   ^\"^**$$$$$$$$$$$$$b.");
  printf("\n                 z$$#\"\"\"           `!?$$$$$$$$$$$$$N.");
  printf("\n               .$P                   ~!R$$$$$$$$$$$$$b");
  printf("\n              x$F                 **$b. '\"R).$$$$$$$$$$");
  printf("\n             J^\"                           #$$$$$$$$$$$$.");
  printf("\n            z$e                      ..      \"**$$$$$$$$$");
  printf("\n           :$P           .        .$$$$$b.    ..  \"  #$$$$");
  printf("\n           $$            L          ^*$$$$b   \"      4$$$$L");
  printf("\n          4$$            ^u    .e$$$$e.\"*$$$N.       @$$$$$");
  printf("\n          $$E            d$$$$$$$$$$$$$$L \"$$$$$  mu $$$$$$F");
  printf("\n          $$&            $$$$$$$$$$$$$$$$N   \"#* * ?$$$$$$$N");
  printf("\n          $$F            '$$$$$$$$$$$$$$$$$bec...z$ $$$$$$$$");
  printf("\n         '$$F             `$$$$$$$$$$$$$$$$$$$$$$$$ '$$$$E\"$");
  printf("\n          $$                  ^\"\"\"\"\"\"`       ^\"*$$$& 9$$$$N");
  printf("\n          k  u$                                  \"$$. \"$$P r");
  printf("\n          4$$$$L                                   \"$. eeeR");
  printf("\n           $$$$$k                                   '$e. .@");
  printf("\n           3$$$$$b                                   '$$$$");
  printf("\n            $$$$$$                                    3$$\"");
  printf("\n             $$$$$  dc                                4$F");
  printf("\n              RF** <$$                                J\"");
  printf("\n               #bue$$$LJ$$$Nc.                        \"");
  printf("\n                ^$$$$$$$$$$$$$r");
  printf("\n                 `\"*$$$$$$$$$");
  printf("\n          $. .$ $~$ $~$ ~$~  $  $    $ $ $~$ $. .$ $~$  $  ~$~");
  printf("\n          $$ $$ $ $ $ $  $  $.$ $    $$  $ $ $$ $$ $.$ $.$  $");
  printf("\n         $`$'$ $ $ $~k  $  $~$ $    $$  $ $ $`$'$ $ $ $~$  $");
  printf("\n          $ $ $ $o$ $ $  $  $ $ $oo  $ $ $o$ $ $ $ $o$ $ $  $");
  
}
// Definição da estrutura Lutador
typedef struct {
  char nome[20];
  float ataque;
  float defesa;
  float vida;
  int vitoria;
} Lutador;
 
// Função para preencher o array com os lutadores
void preencherLutadores(Lutador *lutadores) {
  // Semente para a geração de números aleatórios
  srand(time(NULL));
  // Nomes dos lutadores
  char *nomes[] = {
      "Scorpion",    "Sub-Zero", "Liu Kang", "Johnny Cage", "Sonya Blade",
      "Raiden",      "Kano",     "Goro",     "Shang Tsung", "Reptile",
      "Kitana",      "Jax",      "Mileena",  "Baraka",      "Kabal",
      "Noob Saibot", "Smoke",    "Jade",     "Cyrax",       "Sektor",
      "Nightwolf",   "Sheeva",   "Sindel",   "Ermac",       "Rain",
      "Fujin",       "Quan Chi", "Shinnok",  "Tanya",       "Tremor"};

  // Preenchimento dos lutadores com valores aleatórios
  for (int i = 0; i < 30; i++) {
    Lutador lutador;
    strcpy(lutador.nome, nomes[i]);
    lutador.ataque =
        rand() % 10 + 1; // Se o ataque de dois lutadores for 0 a luta nao para
    lutador.defesa =
        rand() % 10 + 1; // Se a defesa for 0 o calculo de ataque não funciona
    lutador.vida = 100;
    lutador.vitoria = 0;
    lutadores[i] = lutador;
  }
}

void inicializar_time(Lutador *lutadores, Lutador *time, int numero_time) {
  int posicao;
  int posicaoVetor[30];
  static int escolhidos[30];
  // guarda o array todo com 0 so na primeira entrada, quando for escolhido o
  // espaço específico passa a ser o numero do time que o personagem está.
  if (numero_time == 1) {
    for (int i = 0; i < 30; i++) {
      escolhidos[i] = 0;
    }
  }
  // guarda o array todo com o número de sua posicao
  for (int i = 0; i < 30; i++) {
    posicaoVetor[i] = i;
  }

  // Inicializa os jogadores com as informações dos lutadores escolhidos
  for (int i = 0; i < 3;) {
    posicao = rand() % 30;
    while (escolhidos[posicaoVetor[posicao]] == 0) {
      strcpy(time[i].nome, lutadores[posicaoVetor[posicao]].nome);
      time[i].ataque = lutadores[posicao].ataque;
      time[i].defesa = lutadores[posicao].defesa;
      time[i].vida = lutadores[posicao].vida;
      time[i].vitoria = lutadores[posicao].vitoria;
      if (escolhidos[posicaoVetor[posicao]] == 0) {
        escolhidos[posicaoVetor[posicao]] = numero_time;
      }
      i++;
    }
  }
}
// definir qual jogador do time vai comecar e quais vem depois se ele morrer.
int definir_proximo_jogador(Lutador *time) {
  int lutador_morto = 0;
  for (int i = 0; i < 3; i++) {
    if (time[i].vida <= 0.0) {
      lutador_morto++;
    }
  }
  if (lutador_morto == 3) {
    return -1; // time derrotado
  }
  int posicao;
  do {
    posicao = rand() % 3;
  } while (time[posicao].vida <= 0.0);
  return posicao;
}

// define que time começa, se for 1, seu time começa, se for 2 o adversário
// começa.
int definir_time_que_comeca() {
  srand(time(NULL));
  int comeca = rand() % 2 + 1;
  return comeca;
}
// define se o jogador irá acertar o golpe.
// atualiza a vida do jogador que levou o ataque.
void atualizar_vida(Lutador lutador_ataque[], Lutador lutador_defesa[]) {
  lutador_defesa->vida =
      lutador_defesa->vida -
      (lutador_ataque->ataque) / (lutador_defesa->defesa / 10.0);
}

// Fuçao para realizar um ataque
void atacar(Lutador lutador_ataque[], int lutador_que_ataca, Lutador lutador_defesa[], int lutador_que_defende) {
  srand(time(NULL));
  printf("\n%s vai atacar %s ", lutador_ataque[lutador_que_ataca].nome, lutador_defesa[lutador_que_defende].nome);
  float precisao_ideal;
  precisao_ideal = rand() % 100 - 15; // se esse número for alto  os lutadores vão errar
  precisao_ideal = precisao_ideal / 100; // os golpes infinitamente

  float precisao;
  precisao = 1 - (lutador_ataque[lutador_que_ataca].vida * lutador_ataque[lutador_que_ataca].ataque) / 1000;

  if (precisao >= precisao_ideal) {
    atualizar_vida(&lutador_ataque[lutador_que_ataca],
                   &lutador_defesa[lutador_que_defende]);
    printf("\nATAQUE! %s agora tem %.1f de vida",
           lutador_defesa[lutador_que_defende].nome,
           lutador_defesa[lutador_que_defende].vida);
  } else {
    printf("\nERROU! a precisao do lutador é %.2f a minima é %.2f",
           (1 - (lutador_ataque[lutador_que_ataca].vida * lutador_ataque[lutador_que_ataca].ataque) / 1000), precisao_ideal);
  }
}

// funcao jogar time 1 = seu time
int jogar(Lutador *lutadores, Lutador *time1, Lutador *time2, int continuar) {
  int ganhou = 0;
  //Imprime os time que irão lutar
  printf("\n          TIMES");
  printf("\nSeu time: \n");
  for(int i = 0;i<3;i++){
    printf("\n Lutador : %s", time1[i].nome);
    printf("\n Ataque : %.1f", time1[i].ataque);
    printf("\n Defesa : %.1f\n", time1[i].defesa);  
  }
  printf("\n***************************");
  printf("\n            x     ");
  printf("\n***************************");
  printf("\n\nTime adversário: \n");
  for(int i = 0;i<3;i++){
    printf("\n Lutador : %s", time2[i].nome);
    printf("\n Ataque : %.1f", time2[i].ataque);
    printf("\n Defesa : %.1f\n", time2[i].defesa);  
  }
  //define qual lutador de cada time irá começar
  int lutador_time = definir_proximo_jogador(time1);
  int lutador_oponente = definir_proximo_jogador(time2);
  printf("\nComeçou a luta!\n");
  printf("\n%s x %s\n\n", time1[lutador_time].nome, time2[lutador_oponente].nome);
  //define que time começa
  if (definir_time_que_comeca() == 1) {
    printf("Seu time começa atacando!");
    
    //FASE 1// faz a batalha acontecer 
    while(lutador_time != -1 && lutador_oponente != -1){
      //so começa a batalha se o usuário digitar enter
      printf("\nPressione a tecla 'enter' para começar a luta:\n");
      while (getchar() != '\n') {
        // não faz nada
    }
      while (time1[lutador_time].vida > 0.0 && time2[lutador_oponente].vida > 0.0) {
        atacar(time1, lutador_time, time2, lutador_oponente);
        atacar(time2, lutador_oponente, time1, lutador_time);
      }//Troca os lutadores quando morrerem e se não tiver mais lutadoes o time perde ou ganha
      if (time1[lutador_time].vida <= 0.0) {
        printf("\n\n%s do seu time morreu!", time1[lutador_time].nome);
        lutador_time = definir_proximo_jogador(time1);
        if(lutador_time == -1){
          printf("\n\nSEU TIME PERDEU!");
          if(continuar > 0){
            continuar--;
            //restaurar a vida dos lutadores do seu time e do adversário para dar outra chance
            for(int i = 0; i < 3; i++){
              time1[i].vida = 100.0;
              time2[i].vida = 100.0;
             }
            lutador_time = definir_proximo_jogador(time1);
            printf("\nVocê tem %d continue, terá mais uma chance", continuar +1);
            continue;
          }
          break;
        }
        printf("\n\nQuem vai lutar agora é %s", time1[lutador_time].nome);
      } else if (time2[lutador_oponente].vida <= 0.0) {
        printf("\n\n%s do time adversário, morreu!", time2[lutador_oponente].nome);
        lutador_oponente = definir_proximo_jogador(time2);
        if(lutador_oponente == -1){
           printf("\n\nSEU TIME GANHOU!\n");
          //restaurar a vida dos lutadores do seu time e atribuir uma vitória após uma vitória
          for(int i = 0; i < 3; i++){
            time1[i].vida = 100.0;
            time1[i].vitoria++;       
           }
          ganhou = 1;
          break;
        }
        printf("\n\nQuem vai lutar agora é %s", time2[lutador_oponente].nome);
      }
      printf("\nAgora a luta é!\n");
      printf("\n%s x %s\n\n", time1[lutador_time].nome, time2[lutador_oponente].nome);
      }////////////////////////////////////
  } else {
    printf("O oponete começa atacando!");
    while(lutador_time != -1 && lutador_oponente != -1){
      //so começa a batalha se o usuário digitar enter
      printf("\nPressione a tecla 'enter' para começar a luta:\n");
      while (getchar() != '\n') {
        // não faz nada
    }
      while (time1[lutador_time].vida > 0.0 && time2[lutador_oponente].vida > 0.0) {
        atacar(time2, lutador_oponente, time1, lutador_oponente);
        atacar(time1, lutador_time, time2, lutador_oponente);
      }////////////////////////////////////////
     if (time1[lutador_time].vida <= 0.0) {
        printf("\n\n%s do seu time morreu!", time1[lutador_time].nome);
        lutador_time = definir_proximo_jogador(time1);
        if(lutador_time == -1){
          printf("\n\nSEU TIME PERDEU!\n");
          if(continuar > 0){
            continuar--;
            //restaurar a vida dos lutadores do seu time e do adversário para dar outra chance
            for(int i = 0; i < 3; i++){
              time1[i].vida = 100.0;
              time2[i].vida = 100.0;
             }
            lutador_time = definir_proximo_jogador(time1);
            printf("\nVocê tem %d continue, terá mais uma chance", continuar +1);
            continue;
          }
          break;
        }
        printf("\n\nQuem vai lutar agora é %s", time1[lutador_time].nome);
      } else if (time2[lutador_oponente].vida <= 0.0) {
        printf("\n\n%s do time adversário, morreu!", time2[lutador_oponente].nome);
        lutador_oponente = definir_proximo_jogador(time2);
        if(lutador_oponente == -1){
          printf("\n\nSEU TIME GANHOU!\n");
          //restaurar a vida dos lutadores do seu time
          for(int i = 0; i < 3; i++){
            time1[i].vida = 100.0;
            time1[i].vitoria++;
           }
          ganhou = 1;
          break;
        }
        printf("\n\nQuem vai lutar agora é %s", time2[lutador_oponente].nome);
      }
      printf("\nAgora a luta é!\n");
      printf("\n%s x %s\n\n", time1[lutador_time].nome, time2[lutador_oponente].nome);
      }
  }
  return ganhou;
}
// onde ocorre a liga da morte e ocorrerá as batalhas 
void torre_da_morte(Lutador *lutadores, Lutador *time, Lutador *oponente1, Lutador *oponente2, Lutador *oponente3, Lutador *oponente4, Lutador *oponente5, Lutador *oponente6, Lutador *oponente7, Lutador *oponente8, Lutador *oponente9){
  //inicializar times
  inicializar_time(lutadores, time, 1);
  inicializar_time(lutadores, oponente1,2);
  inicializar_time(lutadores, oponente2,3);
  inicializar_time(lutadores, oponente3,4);
  inicializar_time(lutadores, oponente4,5);
  inicializar_time(lutadores, oponente5,6);
  inicializar_time(lutadores, oponente6,7);
  inicializar_time(lutadores, oponente7,8);
  inicializar_time(lutadores, oponente8,9);
  inicializar_time(lutadores, oponente9,10);
  int continuar = 2;
  int ganhou = 1;
  logo();
  printf("\n\nCOMECOU A LIGA DA MORTE!!!\n\n");
  for (int fase = 1; fase <= 9 && ganhou == 1; fase++) {
    printf("\nFASE %d!!!\n", fase);
    ganhou = jogar(lutadores, time, 
                   fase == 1 ? oponente1 : 
                   (fase == 2 ? oponente2 : 
                   (fase == 3 ? oponente3 :
                   (fase == 4 ? oponente4 :
                   (fase == 5 ? oponente5 :
                   (fase == 6 ? oponente6 :
                   (fase == 7 ? oponente7 :
                   (fase == 8 ? oponente8 : oponente9))))))), continuar);
  }
  
  if (ganhou == 1) {
    printf("\n\n**********VOCÊ VENCEU A LIGA DA MORTE!!!**********\n");
  } else {
    printf("**********GAME OVER!!!**********\n");
  }
}

int main() {
  srand(time(NULL));
  // Array de lutadores
  Lutador lutadores[30];
  Lutador time[3];
  Lutador oponente1[3];
  Lutador oponente2[3];
  Lutador oponente3[3];
  Lutador oponente4[3];
  Lutador oponente5[3];
  Lutador oponente6[3];
  Lutador oponente7[3];
  Lutador oponente8[3];
  Lutador oponente9[3];

   
  // Preenchimento dos lutadores
  preencherLutadores(lutadores);

  torre_da_morte(lutadores, time, oponente1, oponente2, oponente3, oponente4, oponente5, oponente6, oponente7, oponente8, oponente9);
  

  return 0;
}
