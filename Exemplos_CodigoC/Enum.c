#include <stdio.h>

enum DiasSemana {DOMINGO, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO};

int main() {
    enum DiasSemana hoje = QUARTA;
    printf("Hoje = %d\n", hoje);
    return 0;
}
