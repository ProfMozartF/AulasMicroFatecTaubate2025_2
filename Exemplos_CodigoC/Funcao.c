#include <stdio.h>
//variaveis
int med_ia;
int numero_dados;
int media (int numero_ds); // Protótiopo da função

int main() {
    
    printf("DIGITE NUM ALUNOS: ");
    scanf("%d", &numero_dados);
    //med_ia = media(numero_dados);
    printf("media da sala = %d", media(numero_dados));
  
   
}//FIM DO MAIN

int media(int numero_ds) {
    int soma=0;
    int media_local=0;
    int valor=0;
    int i=0;
   
      for (i = 0; i < numero_ds; i++)
      {
        printf("Digitar a nota: ");
        scanf("%d", &valor);
        soma+=valor;
      }
    
    media_local=soma/numero_ds;
    printf("Na Funcao - Media local = %d\n", media_local);
    return media_local;
}