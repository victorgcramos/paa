#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // for strtol
#include <sys/time.h>

int a,b,c,d,e,ff,g,*tam, cont_tam=1, tam_esq =0, tam_dir=0;
FILE *fp;

long double f (int n, int g) // conta numero iterações de f(n).
{
  long double resultado;
  resultado = pow(n,g);
  return resultado ; // retorna n^g
}

void registra_trabalho_por_f_n(long double fn, time_t tempo){
  fprintf(fp,"Trabalho por F(n) = %.0Lf: %ld micro segundos\n", fn, tempo);
  printf("Trabalho por F(n) = %.0Lf: %ld micro segundos\n", fn, tempo);
}
void registra_trabalho_por_n(int n, time_t tempo){
  fprintf(fp,"Trabalho por n = %d: %ld\n", n, tempo);
  printf("Trabalho por n = %d: %ld\n", n, tempo);
}

void registra_trabalho_nivel_atual_arvore(int nivel, time_t tempo){
  fprintf(fp,"Trabalho por nivel = %d: %d\n", nivel, tempo);
  printf("Trabalho por nivel = %d: %d\n", nivel, tempo);
}

int Calcula_nivel_atual_arvore (int esq, int dir){

}

void func_t (int n) // simula a recorrencia
{
  struct timeval beginTime, endTime;
  unsigned long tempo;
  if (n<=1) return;

  for (int cont=1; cont<=a; cont++) {// faz a chamadas de tamanho (n/b) - c
    printf("Esquerda: %d\n",  n/b - c);
    tam_esq ++;
    func_t( (n/b) - c );
  }
  for (int cont=1; cont<=d; cont++){ // faz d chamadas de tamanho (n/e) - f
    printf("direita: %d\n",  n/e - ff);
    tam_dir++;
    func_t( (n/e) - ff );
  }

  cont_tam = tam_dir > tam_esq ? tam_dir : tam_esq;

  long double fn = f(n,g);
  gettimeofday(&beginTime, NULL);
  for (int cont=1; cont<= f(n,g); ){ // simula o tempo de f(n) no nível atual
    cont++;
  }
  gettimeofday(&endTime, NULL);

  tempo = ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (beginTime.tv_sec * 1000000 + beginTime.tv_usec));
  tempo = tempo / 1000;
  // int nivel = Calcula_nivel_atual_arvore(tam_esq, tam_dir)
  // registra_trabalho_nivel_atual_arvore(nivel,tempo);
  registra_trabalho_por_n(n,tempo);
  registra_trabalho_por_f_n(fn,tempo);
}

int main(int argc, char const *argv[]) {
  int n;
  scanf("%d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e,&ff,&g,&n);
  printf("\n%d  %d  %d  %d  %d  %d  %d  %d\n",a,b,c,d,e,ff,g,n);
  fp = fopen("resultado.txt","w");
// T(n) = aT( (n/b) –c ) + dT( (n/e) –f ) + f(n)
  func_t(n);

  fclose(fp);
  return 0;
}
