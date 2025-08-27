#include <stdio.h>
//variaveis
int med_ia;
int numero_dados;
int media (int numero_ds); // Protótiopo da função

int main() {
    
    printf("DIGITE NUM ALUNOS: ");
    scanf("%d", &numero_dados);
    med_ia = media(numero_dados);
    printf("media da sala = %d", med_ia);
  
   
}//FIM DO MAIN

int media(int numero_ds) {
    int soma;
    int media_local;
    int valor;
    int i;
   
      for (i = 0; i < numero_ds; i++)
      {
        printf("Digitar a nota: ");
        scanf("%d", &valor);
        soma+=valor;
      }
    
    media_local=soma/numero_ds;
    return media_local;
}
