#include <stdio.h>
#include <stdlib.h>
int main()
{
    // Declaração de variáveis
    int uni_milhao;  // Unidade de milhão - usado para a verificação do andar fornecido
    int cent_milhar; // Centena de milhar - usado para a verificação do andar fornecido
    int dez_milhar;  // Dezena de milhar - usado para a verificação do andar fornecido
    int uni_milhar;  // Unidade de milhar - usado para a verificação do andar fornecido
    int centena;     // Centena - usado para a verificação do andar fornecido
    int dezena;      // Dezena - usado para a verificação do andar fornecido
    int unidade;     // Unidade - usado para a verificação do andar fornecido
    int cont_1;      // Variável tilizada para verificar a existência do número 4 e 13 e imprimir a saída
    int cont_2;      // Variável contadora do laço
    int andar;       // Andar solicitado pelo o usuário
    // Entrada 1: Andar
    printf("-------------------------| ELEVADOR ESPACIAL |-------------------------\n");
    printf("\n--> Qual andar voce deseja ir : ");
    scanf("%d", &andar);
    // Validação da entrada 1
    if ((andar < 1) || (andar > 1000000))
    {
        do
        {
            printf("\n--> Andar invalido!");
            printf("\n--> Digite um andar de 1 ate 1000000 ");
            printf("\n");
            printf("\n--> Informe novamente o andar que deseja ir: ");
            scanf("%d", &andar);
            printf("\n");
        } while ((andar < 1) || (andar > 1000000));
    }
    // Verificação da entrada 1
    if ((andar >= 1) && (andar <= 1000000))
    {
        // Inicialização das variáveis
        uni_milhao = 0;
        cent_milhar = 0;
        dez_milhar = 0;
        uni_milhar = 0;
        centena = 0;
        dezena = 0;
        unidade = 0;
        cont_1 = 0;
        cont_2 = 0;
        // Laço para separar e verificar cada algarismo que compõe o andar fornecido
        while (cont_2 < andar)
        {
            cont_2 += 1;
            cont_1 += 1;
            // Separação do andar informado em unidade, dezena, centena, unidade de milhar,
            // dezena de milhar, centena de milhar e unidade de milhão
            unidade = (cont_1 % 10);
            dezena = ((cont_1 / 10) % 10);
            centena = ((cont_1 / 100) % 10);
            uni_milhar = ((cont_1 / 1000) % 10);
            dez_milhar = ((cont_1 / 10000) % 10);
            cent_milhar = ((cont_1 / 100000) % 10);
            uni_milhao = ((cont_1 / 1000000) % 10);
            // Verificação do número 13
            if ((uni_milhao == 1) && (cent_milhar == 3))
            {
                cont_1 += 100000;
            }
            if ((cent_milhar == 1) && (dez_milhar == 3))
            {
                cont_1 += 10000;
            }
            if ((dez_milhar == 1) && (uni_milhar == 3))
            {
                cont_1 += 1000;
            }
            if ((uni_milhar == 1) && (centena == 3))
            {
                cont_1 += 100;
            }
            if ((centena == 1) && (dezena == 3))
            {
                cont_1 += 10;
            }
            if ((dezena == 1) && (unidade == 3))
            {
                cont_1 += 1;
            }
            // Separação do andar informado em unidade, dezena, centena, unidade de milhar,
            // dezena de milhar, centena de milhar e unidade de milhão
            unidade = (cont_1 % 10);
            dezena = ((cont_1 / 10) % 10);
            centena = ((cont_1 / 100) % 10);
            uni_milhar = ((cont_1 / 1000) % 10);
            dez_milhar = ((cont_1 / 10000) % 10);
            cent_milhar = ((cont_1 / 100000) % 10);
            uni_milhao = ((cont_1 / 1000000) % 10);
            // Verificação do número 4
            if (unidade == 4)
            {
                cont_1 += 1;
            }
            if (dezena == 4)
            {
                cont_1 += 10;
            }
            if (centena == 4)
            {
                cont_1 += 100;
            }
            if (uni_milhar == 4)
            {
                cont_1 += 1000;
            }
            if (dez_milhar == 4)
            {
                cont_1 += 10000;
            }
            if (cent_milhar == 4)
            {
                cont_1 += 100000;
            }
            if (uni_milhao == 4)
            {
                cont_1 += 1000000;
            }
        }
    }
    // Saída
    printf("--> Seu andar: %d\n", cont_1);
    printf("-----------------------------------------------------------------------\n");

    system("pause");
    return 0;
}