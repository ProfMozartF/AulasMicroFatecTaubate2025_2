#include <stdio.h>

int main() {
    int numero;
    
    // Solicita ao usuário que digite um número
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    
    // Verifica se o número é par ou ímpar
    if (numero % 2 == 0) {
        printf("O numero %d e par.\n", numero);
    } else {
        printf("O numero %d e impar.\n", numero);
    }
    
    return 0;
}
