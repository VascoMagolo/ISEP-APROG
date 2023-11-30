#include <stdio.h>
void lerVetor(int *v, int n) {
    for (int i=0; i<n; i++) {
        printf("Digite o valor da posicao %d:  \n", i);
        scanf("%d", &v[i]);
    }
}
void mostrarVetor(int *v, int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
void ordenarVetor(int *v, int n) {
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (v[i] > v[j]) {
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    printf("vetor ordenado:");
    mostrarVetor(v, n);
}
int main() {
    int n=5, vec[5];
    lerVetor(vec, n);
    mostrarVetor(vec, n);
    ordenarVetor(vec, n);
    return 0;
}
