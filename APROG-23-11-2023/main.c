#include <stdio.h>

float m(int n, int *v){
    int soma=0;
    for(int i=0;i<5;i++){
        soma+=v[i];
    }
    return (float)soma/5;
}
void LV(int n, int *v){
    for(int i=0;i<n;i++){
        printf("Digite um numero: ");
        scanf("%d",&v[i]);
    }
}
int main() {
    int soma=0,vet[5];
    LV(5,vet);
    float media=m(5,vet);
    printf("A media dos numeros digitados e: %.2f",media);
    return 0;
}
