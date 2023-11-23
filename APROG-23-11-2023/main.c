#include <stdio.h>

float m(int n, int *v){
    int soma=0;
    for(int i=0;i<n;i++){
        soma+=v[i];
    }
    return (float)soma/n;
}
void LV(int n, int *v){
    for(int i=0;i<n;i++){
        printf("Digite um numero: ");
        scanf("%d",&v[i]);
    }
}
int main() {
    int soma=0,vet[]={};
    int count;
    printf("Digite quantos numeros deseja digitar: ");
    scanf("%d",&count);
    LV(count,vet);
    float media=m(count,vet);
    printf("A media dos numeros digitados e: %.2f",media);
    return 0;
}
