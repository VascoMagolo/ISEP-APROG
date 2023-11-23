#include <stdio.h>

float m(int n, int *v){
    int soma = 0;
    for (int i = 0; i < n; i++){
        soma += v[i];
    }
    return (float)soma / n;
}

void LV(int n, int *v){
    for (int i = 0; i < n; i++){
        printf("Digite um numero: ");
        scanf("%d", &v[i]);
    }
}

int encontrarmaior(int n, int *v){
    int maior = 0;
    for (int i = 1; i < n; i++){
        if (v[i] > v[maior]){
            maior = i;
        }
    }
    return maior; 
}

int main() {
    int count;
    printf("Digite quantos numeros deseja digitar: ");
    scanf("%d", &count);

    int vet[count];

    LV(count, vet);

    float media = m(count, vet);
    printf("A media dos numeros digitados e: %.2f \n", media);

    int posicao_maior = encontrarmaior(count, vet);
    printf("O maior numero digitado e: %d", vet[posicao_maior]);

    return 0;
}
