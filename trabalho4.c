#include <stdio.h>
#include <math.h>
#include <time.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol


int a,b,c,d,e,ff,g,*tam, cont_tam=1, tam_esq =0, tam_dir=0;
FILE *fp;

int f (int n, int g) // conta numero iterações de f(n).
{
  int resultado;
  // printf("n=%d, n=%d\n",n,g);
  resultado = pow(n,g);
  return resultado ; // retorna n^g
}

void registra_trabalho_por_f_n(int fn, time_t tempo){
  fprintf(fp,"Trabalho por F(n) = %d: %d\n", fn, tempo);
  printf("Trabalho por F(n) = %d: %d\n", fn, tempo);
}
void registra_trabalho_por_n(int n, time_t tempo){
  fprintf(fp,"Trabalho por n = %d: %d\n", n, tempo);
  printf("Trabalho por n = %d: %d\n", n, tempo);
}

void registra_trabalho_nivel_atual_arvore(int nivel, time_t tempo){
  fprintf(fp,"Trabalho por nivel = %d: %d\n", nivel, tempo);
  printf("Trabalho por nivel = %d: %d\n", nivel, tempo);
}

int Calcula_nivel_atual_arvore(int tamanho){
  tam = realloc(&tam,sizeof(int)*tamanho);
  tam[cont_tam] =
  cont_tam++;
}

void func_t (int n) // simula a recorrencia
{
  int nivel;
  time_t tempo_inicial, tempo_final, tempo;
  if (n<=1) return;

  for (int cont=1; cont<=a; cont++) {// faz a chamadas de tamanho (n/b) - c
    printf("Esquerda: %d\n",  n/b - c);
    tam_esq ++;
    nivel = Calcula_nivel_atual_arvore(tam_esq);
    func_t( (n/b) - c );
  }
  for (int cont=1; cont<=d; cont++){ // faz d chamadas de tamanho (n/e) - f
    printf("direita: %d\n",  n/e - ff);
    tam_dir++;
    nivel = Calcula_nivel_atual_arvore(tam_dir);
    func_t( (n/e) - ff );
  }
  int fn = f(n,g);
  time(&tempo_inicial);
  for (int cont=1; cont<= f(n,g); ){ // simula o tempo de f(n) no nível atual
    cont++;
  }
  time(&tempo_final);

  tempo = difftime(tempo_final, tempo_inicial);
  // printf("%ld\n", tempo);
  registra_trabalho_nivel_atual_arvore(nivel,tempo);
  registra_trabalho_por_n(n,tempo);
  registra_trabalho_por_f_n(fn,tempo);
}

int main(int argc, char const *argv[]) {

  char* char_a,*char_b,*char_c,*char_d,*char_e,*char_f,*char_g,*char_n;
  int n;
  a = strtol(argv[1],&a,10);
  b = strtol(argv[2],&b,10);
  c = strtol(argv[3],&c,10);
  d = strtol(argv[4],&d,10);
  e = strtol(argv[5],&e,10);
  ff = strtol(argv[6],&ff,10);
  g = strtol(argv[7],&g,10);
  n = strtol(argv[8],&n,10);

  printf("a=%d,b=%d,c=%d,d=%d,e=%d,f=%d,g=%d,n=%d,\n",a,b,c,d,e,ff,g,n);
  // printf("%d\n", a);
  fp = fopen("resultado.txt","w");
// T(n) = aT( (n/b) –c ) + dT( (n/e) –f ) + f(n)
  func_t(n);

  fclose(fp);
  return 0;
}
