#include <stdio.h>
#include <stdint.h>
int soma (num1,num2)
{
    int soma;
    soma = num1+num2;
    return(soma);
    
}

int main()
{
    printf("TESTE SOMA = %d\n",soma(2,3) );
     printf("TESTE SOMA = %d\n",soma(1,3) );
      printf("TESTE SOMA = %d\n",soma(2,9) );
       printf("TESTE SOMA = %d\n",soma(3,5) );
        printf("TESTE SOMA = %d\n",soma(12,3) );
         printf("TESTE SOMA = %d\n",soma(23,3) );
   
    return 0;
}