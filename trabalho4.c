#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // for strtol
#include <sys/time.h>

int a,b,c,d,e,ff,g,*tam, cont_tam=1, tam_esq =0, tam_dir=0;
int *trabalhos_niveis;
FILE *fp_n, *fp_fn;

long double f (int n, int g) // conta numero iterações de f(n).
{
  long double resultado;
  resultado = pow(n,g);
  return resultado ; // retorna n^g
}

void registra_trabalho_por_f_n(long double fn, time_t tempo){
  fprintf(fp_fn,"{\n\t\"fn\": \"%.0Lf\",\n\t\"tempo\": \"%ld\"\n},\n", fn, tempo);
  // printf("Trabalho por F(n) = %.0Lf: %ld micro segundos\n", fn, tempo);
}
void registra_trabalho_por_n(int n, time_t tempo){
  // fprintf(fp_n,"n = %d: %ld\n", n, tempo);
  fprintf(fp_n,"{\n\t\"n\": \"%d\",\n\t\"tempo\": \"%ld\"\n},\n", n, tempo);
  // printf("Trabalho por n = %d: %ld\n", n, tempo);
}

void registra_trabalho_nivel_atual_arvore(int nivel, time_t tempo){
  // fprintf(fp,"Trabalho por nivel = %d: %d\n", nivel, tempo);
  // printf("Trabalho por nivel = %d: %d\n", nivel, tempo);
}

int Calcula_nivel_atual_arvore () {
  if (tam_dir>tam_esq) {
    tam_dir--;
    return tam_dir;
  } else if (tam_esq>tam_dir) {
    tam_esq--;
    return tam_esq;
  } else {
    tam_esq--;
    tam_dir--;
    return tam_esq;
  }
}

void func_t (int n) // simula a recorrencia
{
  struct timeval beginTime, endTime;
  unsigned long tempo;
  if (n<=1) return;

  for (int cont=1; cont<=a; cont++) {// faz a chamadas de tamanho (n/b) - c
    // printf("Esquerda: %d\n",  n/b - c);
    tam_esq ++;
    func_t( (n/b) - c );
  }
  for (int cont=1; cont<=d; cont++){ // faz d chamadas de tamanho (n/e) - f
    // printf("direita: %d\n",  n/e - ff);
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
  // int nivel = Calcula_nivel_atual_arvore(tam_esq, tam_dir)
  // registra_trabalho_nivel_atual_arvore(nivel,tempo);
  registra_trabalho_por_n(n,tempo);
  registra_trabalho_por_f_n(fn,tempo);
}

int main(int argc, char const *argv[]) {
  int n;
  a = strtol(argv[2],&a,10);
  b = strtol(argv[3],&b,10);
  c = strtol(argv[4],&c,10);
  d = strtol(argv[5],&d,10);
  e = strtol(argv[6],&e,10);
  ff = strtol(argv[7],&ff,10);
  g = strtol(argv[8],&g,10);
  n = strtol(argv[1],&n,10);

  if (b==1) {
    cont_tam = n/c;
  } else if (e==1) {
    cont_tam = n/e;
  } else if (b>e) {
    cont_tam = log(n)/log(e);
  } else {
    cont_tam = log(n)/log(b);
  }
  // printf("Tamanho da arvore: %d\n", cont_tam);
  trabalhos_niveis = malloc(sizeof(time_t)*cont_tam);

  // printf("%d,%d,%d,%d,%d,%d,%d,%d,\n",n,a,b,c,d,e,ff,g);
  printf("%d\n", n);
  printf("%d\n", a);
  printf("%d\n", b);
  printf("%d\n", c);
  printf("%d\n", d);
  printf("%d\n", e);
  printf("%d\n", ff);
  printf("%d\n", g);
  // printf("%d\n", a);
  fp_n = fopen("resultado_n.json","w");
  fp_fn = fopen("resultado_fn.json","w");
// T(n) = aT( (n/b) –c ) + dT( (n/e) –f ) + f(n)
  // getchar();
  fprintf(fp_n, "[");
  fprintf(fp_fn, "[");
  func_t(n);
  fprintf(fp_n, "]\n");
  fprintf(fp_fn, "]\n");

  fclose(fp_n);
  fclose(fp_fn);
  return 0;
}
