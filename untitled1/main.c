/// Teste de Algoritmia e Programação
/// Dezembro de 2023

/// NOME   :Vasco Magolo
/// Número : 1231562

#include <stdio.h>

/// a)
///
/// Escreva uma função que recebe um vetor de numeros reais v e
/// a respetiva quantidade de elementos n e 'devolve' por referência
/// os índices (posições) dos seus maior e menor elemento.

//funcao que recebe  o Vetor V,o numero de elementos n e
// que devolve por referencia as posicoes do seu menor e maior elemento
void maior_menor(float v[], int n, int *maior, int *menor)
{
    *maior = 0;
    *menor = 0;
    for(int i = 1; i < n; i++)
    {
        if(v[i] > v[*maior])
        {
            *maior = i;
        }
        if(v[i] < v[*menor])
        {
            *menor = i;
        }
    }
}
/// b)
///
/// Escreva uma função que recebe um vetor v de n elementos reais e
/// uma posição p e remove do vetor v o elemento da posição p.
/// Deve devolver o novo número de elementos do vetor.

//funcao que recebe o vetor V, o numero de elementos N e a posicao P do elemento
// e que remove o elemento da posicao P dada
int removeElem(float v[], int n, int p)
{
    for(int i = p; i < n; i++)
    {
        v[i] = v[i+1];
    }
    return n-1;
}
/// c)
///
/// Escreva uma função que recebe um vetor v de n elementos reais e
/// Devolve a sua média.

//funcao que recebe o vetor V e o numero de elementos N e devolve a media
float media(float v[], int n)
{
    float soma = 0;
    for(int i = 0; i < n; i++)
    {
        soma += v[i];
    }
    return soma/n;
}
int main()
{
    /// d)
    ///
    /// O desempenho de um atleta de ginástica ritmica é avaliado por um juri
    /// de 9 elementos. Cada elemento do juri atribui uma nota (valor real)
    /// entre 0 e 10. A classificação do atleta é obtida calculando a média das
    /// classificações dadas pelos elementos do juri EXCLUINDO a mais alta e
    /// a mais baixa. (só 7 das 9 classificações é que entram para a média)
    ///
    /// Escreva um programa que leia as notas dos 9 elementos do juri
    /// (validando entre 0 e 10) e escreva qual a classificação obtida pelo atleta.
    ///
    /// Deve usar as funções anteriores.
    ///
    /// Deve ler as 9 notas para um vetor,
    /// eliminar do vetor a nota mais alta e a nota mais baixa
    /// e calcular a média do vetor com as 7 notas.

    //declaração do vetor e da variavel maior e menor
    float notas[9];
    int maior, menor;

    for(int i = 0; i < 9; i++)
    {
        do
        {
            //lê as notas validando se os valores estão entre 0 e 10
            printf("Digite a %d nota(1-10): ", i+1);
            scanf("%f", &notas[i]);
        }
        while(notas[i] < 0 || notas[i] > 10);
    }
    //chama as funcoes maiorMenor e removeElem
    maior_menor(notas, 9, &maior, &menor);
    removeElem(notas, 9, maior);
    removeElem(notas, 8, menor);

    printf("Classificacao do atleta: %.2f", media(notas, 7));
    getchar();
    return 0;
}
