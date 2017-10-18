/**
 * PROJETO E ANÁLISE DE ALGORÍTIMOS - TRABALHO 4
 * @author Victor Guedes Cordeiro Ramos
 * Matrícula: 13/0145688
 * Turma - A
 */
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>  // for strtol

int a,b,c,d,e,ff,g;
FILE *fp_n, *fp_fn;

/**
 * long double f - calcula potenciação para simular a grandeza
 * O(N^m)
 * @param {int} n
 * @param {int} g
 * @return {long double} n^g
 */
long double f (int n, int g) // conta numero iterações de f(n).
{
  return pow(n,g);
}

/**
 *  void funcao_recursao - funcao que calcula recursivamente a operação
 *  T(n) = aT( (n/b) –c ) + dT( (n/e) –f ) + f(n)
 *
 * @param {int} n
 */
void funcao_recursao (int n) // simula a recorrencia
{
  if (n<=1) return;

  for (int cont=1; cont<=a; cont++) {// faz a chamadas de tamanho (n/b) - c
    funcao_recursao( (n/b) - c );
  }
  for (int cont=1; cont<=d; cont++){ // faz d chamadas de tamanho (n/e) - f
    funcao_recursao( (n/e) - ff );
  }
  long double fn = f(n,g);
  for (long double cont=1; cont<= fn; ){ // simula o tempo de f(n) no nível atual
    cont++;
  }
}

/**
 * int main - Função principal do programa. Nela, os argumentos são lidos, e,
 * através de um script em python, o programa é rodado para que o tempo seja
 * mensurado
 *
 * @param  {int} argc           Contador do numero de argumentos do teclado
 * @param  {char const} *argv[] entrada do teclado
 * @return {int}                0
 */
int main (int argc, char const *argv[]) {
  // Define o parametro N, que será passado via linha de comando
  int n;
  // define os intervalos de tempo baseado na biblioteca time.h do unix
  struct timeval tempo_inicio, tempo_final;

  a = strtol(argv[2],(char **)&a,10);
  b = strtol(argv[3],(char **)&b,10);
  c = strtol(argv[4],(char **)&c,10);
  d = strtol(argv[5],(char **)&d,10);
  e = strtol(argv[6],(char **)&e,10);
  ff = strtol(argv[7],(char **)&ff,10);
  g = strtol(argv[8],(char **)&g,10);
  n = strtol(argv[1],(char **)&n,10);

  // define o tempo multiplicador, uma vez que o tempo vem com casas decimais
  // quebradas, e necessitamos de um tempo maior para plotar em um gráfico
  int const multi = 1000000;
  // define variaveis auxiliares de tempo
  unsigned long tempo, ta, tb;

  printf("%d\n", n);
  printf("%d\n", a);
  printf("%d\n", b);
  printf("%d\n", c);
  printf("%d\n", d);
  printf("%d\n", e);
  printf("%d\n", ff);
  printf("%d\n", g);

  gettimeofday(&tempo_inicio, NULL);
  // Chamada da função funt_t(n) da especificação do trabalho
  funcao_recursao(n);
  gettimeofday(&tempo_final, NULL);

  ta = tempo_final.tv_sec * multi + tempo_final.tv_usec;
  tb = tempo_inicio.tv_sec * multi + tempo_inicio.tv_usec;
  tempo = ta - tb;
  // Printa o tempo dividido por 1000, visto que o tempo deve ser medido em ms, e não us
  printf("%ld\n", tempo);

  return 0;
}
