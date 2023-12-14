#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
}TVetor ;
int lervetor(TVetor *vetor) {
    printf("Digite o valor de x: ");
    scanf("%f", &vetor->x);
    printf("Digite o valor de y: ");
    scanf("%f", &vetor->y);
    printf("Digite o valor de z: ");
    scanf("%f", &vetor->z);
    return 0;
}
int somarV(TVetor *vetor1, TVetor *vetor2, TVetor *soma) {
    soma->x = vetor1->x + vetor2->x;
    soma->y = vetor1->y + vetor2->y;
    soma->z = vetor1->z + vetor2->z;
    return 0;
}
int mostrarV(TVetor *vetor) {
    printf("Vetor: (%.1f, %.1f, %.1f)\n", vetor->x, vetor->y, vetor->z);
    return 0;
}
int main() {
    TVetor vetor1, vetor2, soma;

    // Atribuindo valores às coordenadas dos vetores
    printf("Digite as coordenadas do primeiro vetor:\n");
    lervetor(&vetor1);
    mostrarV(&vetor1);
    printf("Digite as coordenadas do segundo vetor:\n");
    lervetor(&vetor2);
    mostrarV(&vetor2);
    // Calculando a soma dos vetores
    somarV(&vetor1, &vetor2, &soma);
    // Exibindo o resultado
    mostrarV(&soma);

    return 0;
}
