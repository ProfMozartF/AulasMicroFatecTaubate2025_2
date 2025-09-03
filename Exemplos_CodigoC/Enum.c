#include <stdio.h>

enum DiasSemana {DOMINGO =1, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO};

int main() {
    enum DiasSemana hoje = QUARTA;
    enum DiasSemana ontem = SEGUNDA;
    printf("Hoje = %d\n", hoje);
    printf("Hoje = %d\n", ontem);
    return 0;
}
