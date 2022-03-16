#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

#define TAM 50

#define ERRO_OPCAO printf("\nOPCAO INVALIDA!\nTENTE NOVAMENTE . . .\n\n")
#define ERRO_VENDA printf("\nNENHUMA VENDA FOI CADASTRADA AINDA!")
#define ERRO_CLIENTE printf("\nNAO EXISTE NENHUM CLIENTE CADASTRADO AINDA!")
#define ERRO_CARRO printf("\nNAO EXISTE NENHUM CARRO CADASTRADO AINDA!")
#define ERRO_DISPONIBILIDADE_CARRO printf("\nNENHUM CARRO ESTA DISPONIVEL PARA VENDA!")
#define ERRO_LIMITE printf("\nLIMITE DE CADASTROS ATINGIDO!")
#define RETORNA printf("\nRETORNANDO . . .")

#define QUANTIDADE_ELEMENTOS(matriz) (sizeof(matriz) / sizeof(*matriz))

char opcionais[][TAM] = {{"4.portas"}, {"cambio.automatico"}, {"vidros.eletricos"}, {"abs"}, {"air.bag"}, {"ar.condicionado"}, {"banco.couro"}, {"sensor.estacionamento"}};

char estados[][3] = {{"AC"}, {"AL"}, {"AP"}, {"AM"}, {"BA"}, {"CE"}, {"DF"}, {"ES"}, {"GO"}, {"MA"}, {"MT"}, {"MS"}, {"MG"}, {"PA"}, {"PB"}, {"PR"}, {"PE"}, {"PI"}, {"RJ"}, {"RN"}, {"RS"}, {"RO"}, {"RR"}, {"SC"}, {"SP"}, {"SE"}, {"TO"}};

char cidades[][TAM] = {{"Rio Branco"}, {"Maceio"}, {"Macapa"}, {"Manaus"}, {"Salvador"}, {"Fortaleza"}, {"Brasilia"}, {"Vitoria"}, {"Goiania"}, {"Sao Luis"}, {"Cuiaba"}, {"Campo Grande"}, {"Belo Horizonte"}, {"Belem"}, {"Joao Pessoa"}, {"Curitiba"}, {"Recife"}, {"Teresina"}, {"Rio de Janeiro"}, {"Natal"}, {"Porto Alegre"}, {"Porto Velho"}, {"Boa Vista"}, {"Florianopolis"}, {"Sao Paulo"}, {"Aracaju"}, {"Palmas"}};

char nomes[][TAM] = {{"Maria"}, {"Jose"}, {"Antonio"}, {"Joao"}, {"Francisco"}, {"Ana"}, {"Luiz"}, {"Paulo"}, {"Adriana"}, {"Marcia"}, {"Vera"}, {"Sandra"}, {"Edson"}, {"Roberto"}, {"Rita"}};

char sobrenomes[][TAM] = {{"Silva"}, {"Santos"}, {"Oliveira"}, {"Souza"}, {"Lima"}, {"Pereira"}, {"Ferreira"}, {"Costa"}, {"Rodrigues"}, {"Almeida"}, {"Nascimento"}, {"Alves"}, {"Carvalho"}, {"Araujo"}, {"Ribeiro"}};

char carrosModelos[][15] = {{"Astra"}, {"Corsa"}, {"Cruze"}, {"Opala"}, {"Prisma"}, {"Palio"}, {"Siena"}, {"Uno"}, {"Punto"}, {"Linea"}, {"Taro"}, {"Fox"}, {"Gol"}, {"Voyage"}, {"Polo"}};

char carrosFabricantes[][15] = {{"Fiat"}, {"Chevrolet"}, {"Volkswagen"}};

struct CARRO
{
    char placa[9];         // AAA-1234
    char modelo[TAM];      // gol, celta, palio, ...
    char fabricante[TAM];  // chevrolet, fiat, ...
    int ano_fabricacao;    // 1980 à 2016
    int ano_modelo;        // 1980 à 2017
    char combustivel[TAM]; // alcool, gasolina, flex, diesel
    char cor[TAM];         // branca, prata, preta
    int opcional[8];       // ver matriz opcionais
    float preco_compra;
};

struct ENDERECO
{
    char rua[TAM];
    int numero;
    char bairro[TAM];
    char cidade[TAM];
    char estado[3];
    char cep[11]; // 99.999-999
};

struct TELEFONE
{
    char telefone[14]; // 99 99999-9999
};

struct CLIENTE
{
    int cod_cli;
    char nome[TAM];
    struct ENDERECO endereco;
    struct TELEFONE residencial;
    struct TELEFONE celular[5];
    float renda_mensal;
};

struct DATA
{
    int dia, mes, ano;
};

struct VENDA_CARRO
{
    char placa[9]; // AAA-1234
    int cod_cli;
    float preco_venda;
    struct DATA data_venda;
};

// Funções auxiliares: ---------------------------------------------------------------------------------------------------------------------------

// Limpeza do Buffer
void flush_in()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n')
    {
    }
}

// Abrir um arquivo e informar se ocorreu algum erro
FILE *abreArquivo(char *nomeArquivo, char *modo, char *localERRO)
{
    FILE *arquivo;

    if ((arquivo = fopen(nomeArquivo, modo)) == NULL)
    {
        printf("\nERRO AO ABRIR [%s]\nLOCAL_ERRO: [%s]\n\n", nomeArquivo, localERRO);
        exit(1);
    }
    return arquivo;
}

// Fechar um arquivo e informar se ocorreu algum erro
void fechaArquivo(FILE *arquivo, char *nomeArquivo, char *localERRO)
{
    if (fclose(arquivo) == EOF)
    {
        printf("\nERRO AO FECHAR [%s]\nLOCAL_ERRO: [%s]\n\n", nomeArquivo, localERRO);
        exit(1);
    }
}

// Gerar uma letra aleatória do alfabeto
char geraAlfabeto()
{
    int i;
    char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    i = rand() % QUANTIDADE_ELEMENTOS(letras);
    return (letras[i]);
}

// Gerar um número aleatório do tipo char
char geraNumero()
{
    int i;
    char numeros[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    i = rand() % QUANTIDADE_ELEMENTOS(numeros);
    return (numeros[i]);
}

// Gerar um valor de ponto flutuante aleatório somado ao um valor inteiro gerado aleatóriamente
// int inteiroMin e int inteiroMax: Gerar um número inteiro de inteiroMin até inteiroMax
float geraNumeroFloat(int inteiroMin, int inteiroMax)
{
    float min = 0.0, max = 1.0;
    float numeroFloat = rand() / (float)RAND_MAX;
    int numeroInt = rand() % inteiroMax + inteiroMin;

    return roundf((min + numeroFloat * (max - min)) * 100) / 100 + numeroInt;
}

// Retornar a quantidade de dados do arquivo com os cadastros dos carros
int quantidadeDadosArquivoCarros(FILE *arquivoCarros)
{
    struct CARRO dadosCarro;
    int quantidade = 0;

    fseek(arquivoCarros, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
            quantidade++;
    } while (!feof(arquivoCarros));

    return quantidade;
}

// Retornar a quantidade de dados do arquivo com os cadastros dos clientes
int quantidadeDadosArquivoClientes(FILE *arquivoClientes)
{
    struct CLIENTE dadosCliente;
    int quantidade = 0;

    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
            quantidade++;
    } while (!feof(arquivoClientes));

    return quantidade;
}

// Retornar a quantidade de dados do arquivo com os cadastros das vendas
int quantidadeDadosArquivoVendas(FILE *arquivoVendas)
{
    struct VENDA_CARRO dadosVenda;
    int quantidade = 0;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVenda, sizeof(dadosVenda), 1, arquivoVendas) > 0)
            quantidade++;
    } while (!feof(arquivoVendas));

    return quantidade;
}

// Retorna 0 se o carro existe no cadastro ou um número diferente de 0 se caso não exista
int verificaExistenciaCarro(FILE *arquivoCarros, char *placaCarro)
{
    struct CARRO dadosCarro;
    int verificadorPlaca;

    fseek(arquivoCarros, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
            verificadorPlaca = strcmp(dadosCarro.placa, placaCarro);
    } while (!feof(arquivoCarros) && verificadorPlaca != 0);

    return verificadorPlaca;
}

// Retorna 0 se o cliente existe no cadastro ou um número diferente de 0 se caso não exista
int verificaExistenciaCliente(FILE *arquivoClientes, int codigoCliente)
{
    struct CLIENTE dadosCliente;
    int verificadorCodigo = 1;

    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
        {
            if (dadosCliente.cod_cli == codigoCliente)
                verificadorCodigo = 0;
        }
    } while (!feof(arquivoClientes) && verificadorCodigo != 0);

    return verificadorCodigo;
}

// Retorna 0 se o carro já foi vendido ou um número diferente de 0 se ainda não foi vendido
int verificaExistenciaVendaCarro(FILE *arquivoVendas, char *placaCarro)
{
    struct VENDA_CARRO dadosVendas;
    int verificadorPlaca = 1;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVendas, sizeof(dadosVendas), 1, arquivoVendas) > 0)
            verificadorPlaca = strcmp(dadosVendas.placa, placaCarro);
    } while (!feof(arquivoVendas) && verificadorPlaca != 0);

    return verificadorPlaca;
}

// Retorna 0 se existe uma venda registrada no código do cliente
int verificaExistenciaVendaCliente(FILE *arquivoVendas, int codigoCliente)
{
    struct VENDA_CARRO dadosVendas;
    int verificadorCodigo = 1;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVendas, sizeof(dadosVendas), 1, arquivoVendas) > 0)
        {
            if (dadosVendas.cod_cli == codigoCliente)
                verificadorCodigo = 0;
        }
    } while (!feof(arquivoVendas) && verificadorCodigo != 0);

    return verificadorCodigo;
}

// Retorna a posção exata do cadastro de um carro no arquivo
int localizaPosicaoCarroArquivo(FILE *arquivoCarros, char *placaCarro)
{
    struct CARRO dadosCarro;
    int posicaoCarro, indice = 0;

    fseek(arquivoCarros, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            if (strcmp(dadosCarro.placa, placaCarro) == 0)
                posicaoCarro = indice;
        }
        indice++;
    } while (!feof(arquivoCarros));

    return posicaoCarro;
}

// Retorna a posção exata do cadastro de um cliente no arquivo
int localizaPosicaoClienteArquivo(FILE *arquivoClientes, int codigoCliente)
{
    struct CLIENTE dadosCliente;
    int posicaoCliente, indice = 0;

    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
        {
            if (dadosCliente.cod_cli == codigoCliente)
                posicaoCliente = indice;
        }
        indice++;
    } while (!feof(arquivoClientes));

    return posicaoCliente;
}

// Retorna a posção exata do cadastro de uma venda no arquivo
int localizaPosicaoVendaArquivo(FILE *arquivoVendas, char *placaCarro)
{
    struct VENDA_CARRO dadosVenda;
    int posicaoVenda, indice = 0;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVenda, sizeof(dadosVenda), 1, arquivoVendas) > 0)
        {
            if (strcmp(dadosVenda.placa, placaCarro) == 0)
                posicaoVenda = indice;
        }
        indice++;
    } while (!feof(arquivoVendas));

    return posicaoVenda;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

// CARRO:

// Funções necessárias para gerar os dados dos carros: -------------------------------------------------------------------------------------------

void auxGeraPlaca(char *vetorPlaca)
{
    int i;
    vetorPlaca[0] = '\0';
    for (i = 0; i < 8; i++)
    {
        if (i < 3)
            vetorPlaca[i] = geraAlfabeto();
        if (i == 3)
            vetorPlaca[i] = '-';
        if (i > 3)
            vetorPlaca[i] = geraNumero();
    }

    vetorPlaca[8] = '\0';
}

void geraPlacaCarro(FILE *arquivoCarros, char *placaCarro)
{
    char placaAuxiliar[9];
    int verifica;

    if (quantidadeDadosArquivoCarros(arquivoCarros) > 0)
    {
        do
        {
            auxGeraPlaca(placaAuxiliar);
            verifica = verificaExistenciaCarro(arquivoCarros, placaAuxiliar);
        } while (verifica == 0);
    }
    else
        auxGeraPlaca(placaAuxiliar);

    strcpy(placaCarro, placaAuxiliar);
}

void geraModeloCarro(char *modelo)
{
    int i = rand() % QUANTIDADE_ELEMENTOS(carrosModelos);
    strcpy(modelo, carrosModelos[i]);
}

void geraFabricanteCarro(char *fabricante, char *modelo)
{
    char marcas[][15] = {{"Fiat"}, {"Chevrolet"}, {"Volkswagen"}};
    char modelos_fiat[][10] = {{"Palio"}, {"Siena"}, {"Uno"}, {"Punto"}, {"Linea"}};
    char modelos_chevrolet[][10] = {{"Astra"}, {"Corsa"}, {"Cruze"}, {"Opala"}, {"Prisma"}};
    char modelos_volkswagen[][10] = {{"Taro"}, {"Fox"}, {"Gol"}, {"Voyage"}, {"Polo"}};
    int i = 0, verifica;

    do
    {
        verifica = strcmp(modelo, modelos_fiat[i]);

        if (verifica == 0)
            strcpy(fabricante, marcas[0]);

        i++;
    } while (verifica != 0 && i != 5);

    if (i == 5 && verifica != 0)
    {
        i = 0;
        do
        {
            verifica = strcmp(modelo, modelos_chevrolet[i]);

            if (verifica == 0)
                strcpy(fabricante, marcas[1]);

            i++;
        } while (verifica != 0 && i != 5);
    }
    if (i == 5 && verifica != 0)
    {
        i = 0;
        do
        {
            verifica = strcmp(modelo, modelos_volkswagen[i]);

            if (verifica == 0)
                strcpy(fabricante, marcas[2]);

            i++;
        } while (verifica != 0 && i != 5);
    }
}

int geraAnoFabricacaoCarro()
{
    int anoFabricacaoCarro = rand() % 36 + 1980;
    return anoFabricacaoCarro;
}

int geraAnoModeloCarro(int anoFabricacaoCarro)
{
    int anosModelo[2], i;

    anosModelo[0] = anoFabricacaoCarro;
    if (anoFabricacaoCarro < 2015)
        anosModelo[1] = anoFabricacaoCarro + (rand() % 2 + 1);
    else
        anosModelo[1] = anoFabricacaoCarro + 1;

    i = rand() % 2;
    return anosModelo[i];
}

void geraCombustivelCarro(char *combustivelCarro)
{
    int i;
    char tiposCombustivel[][10] = {{"Alcool"}, {"Gasolina"}, {"Flex"}, {"Diesel"}};

    i = rand() % QUANTIDADE_ELEMENTOS(tiposCombustivel);
    strcpy(combustivelCarro, tiposCombustivel[i]);
}

void geraCorCarro(char *corCarro)
{
    int i;
    char cores[][10] = {{"Branco"}, {"Prata"}, {"Preto"}};

    i = rand() % QUANTIDADE_ELEMENTOS(cores);
    strcpy(corCarro, cores[i]);
}

//------------------------------------------------------------------------------------------------------------------------------------------------

// Mostrar os dados do carro
void mostraCarro(struct CARRO carro)
{
    long unsigned int i;
    printf("\n\tPLACA: %s", carro.placa);
    printf("\n\tMODELO: %s", carro.modelo);
    printf("\n\tFABRICANTE: %s", carro.fabricante);
    printf("\n\tANO DE FABRICACAO: %d", carro.ano_fabricacao);
    printf("\n\tANO DO MODELO: %d", carro.ano_modelo);
    printf("\n\tCOMBUSTIVEL: %s", carro.combustivel);
    printf("\n\tCOR: %s", carro.cor);
    printf("\n\tOPCIONAIS:\n");
    for (i = 0; i < QUANTIDADE_ELEMENTOS(opcionais); i++)
    {
        if (carro.opcional[i] == 1)
            printf("\t\t  %s\n", opcionais[i]);
    }
    printf("\tPRECO DE COMPRA: R$ %.2f REAIS", carro.preco_compra);
}

// Gerar os dados do carro
void geraCarro(FILE *arquivoCarros, struct CARRO *carro)
{
    long unsigned int i;
    geraPlacaCarro(arquivoCarros, carro->placa);
    geraModeloCarro(carro->modelo);
    geraFabricanteCarro(carro->fabricante, carro->modelo);
    carro->ano_fabricacao = geraAnoFabricacaoCarro();
    carro->ano_modelo = geraAnoModeloCarro(carro->ano_fabricacao);
    geraCombustivelCarro(carro->combustivel);
    geraCorCarro(carro->cor);
    for (i = 0; i < QUANTIDADE_ELEMENTOS(opcionais); i++)
        carro->opcional[i] = rand() % 2;
    carro->preco_compra = geraNumeroFloat(20000, 99999);
}

// Cadastro do carro
void cadastrosCarro(FILE *arquivoCarros)
{
    struct CARRO carro;
    char escolha;

    if (quantidadeDadosArquivoCarros(arquivoCarros) < TAM) // Verificar o limite de cadastros
    {
        do
        {
            system("clear");
            geraCarro(arquivoCarros, &carro);
            flush_in();
            printf("INFORMACOES DO CARRO:\n");
            mostraCarro(carro);

            printf("\n\nDESEJA INCLUIR ESTE CARRO (S/N) ? ");
            scanf("%c", &escolha);

            escolha = tolower(escolha);

            if (escolha != 's' && escolha != 'n')
            {
                do
                {
                    system("clear");
                    printf("INFORMACOES DO CARRO:\n");
                    mostraCarro(carro);
                    printf("\n\nATENCAO!! INFORME: (S - SIM) OU (N - NAO)\nDESEJA INCLUIR ESTE CARRO? ");
                    scanf("%c", &escolha);
                } while (escolha != 's' && escolha != 'n');
            }

        } while (escolha != 's');

        printf("\nINCLUINDO . . .");
        fwrite(&carro, sizeof(carro), 1, arquivoCarros); // Registrar os dados do carro no arquivo
        flush_in();
    }
    else
        ERRO_LIMITE;
}

// Copia os dados do arquivo para um vetor de struct
void leituraArquivoCarro(FILE *arquivoCarros, struct CARRO *carro)
{
    struct CARRO dadosCarro;
    int i = 0;

    fseek(arquivoCarros, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
            carro[i++] = dadosCarro;
    } while (!feof(arquivoCarros));
}

// Realiza a troca de dados
void trocaStructCarro(struct CARRO *dadosA, struct CARRO *dadosB)
{
    struct CARRO dadosAux;

    dadosAux = *dadosA;
    *dadosA = *dadosB;
    *dadosB = dadosAux;
}

// Copia os dados do vetor de struct para um arquivo
void copiaArquivoCarro(FILE *arquivoCarros, struct CARRO *dadosCarro, int tamanho)
{
    int i;

    fseek(arquivoCarros, 0, SEEK_SET);
    for (i = 0; i < tamanho; i++)
        fwrite(&dadosCarro[i], sizeof(dadosCarro[i]), 1, arquivoCarros);
}

// Ordena crescentemente os fabricantes e modelos dos carros
void ordenaFabricanteModeloCarros(struct CARRO *dadosCarro, int tamanho)
{
    int i, j, verificadorFabricante, verificadorModelo;

    for (i = 0; i < tamanho; i++)
    {
        for (j = i; j < tamanho; j++)
        {
            verificadorFabricante = strcmp(dadosCarro[i].fabricante, dadosCarro[j].fabricante);
            verificadorModelo = strcmp(dadosCarro[i].modelo, dadosCarro[j].modelo);

            if (verificadorFabricante > 0)
                trocaStructCarro(&dadosCarro[i], &dadosCarro[j]);
            if (verificadorFabricante == 0 && verificadorModelo > 0)
                trocaStructCarro(&dadosCarro[i], &dadosCarro[j]);
        }
    }
}

// Separa os dados dos carros que correspondem à quantidade de opcionais informada pelo o usuário em outro arquivo
void selecionaOpcionais(FILE *arquivoCarros, FILE *arquivoTemp, int quantidadeOpcionais)
{
    long unsigned int i;
    int contadorOpcionais = 0;
    struct CARRO dadosCarro;

    fseek(arquivoCarros, 0, SEEK_SET);
    fseek(arquivoTemp, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            for (i = 0; i < QUANTIDADE_ELEMENTOS(opcionais); i++)
            {
                if (dadosCarro.opcional[i] == 1)
                    contadorOpcionais++;
            }
            if (contadorOpcionais == quantidadeOpcionais)
                fwrite(&dadosCarro, sizeof(dadosCarro), 1, arquivoTemp);
            contadorOpcionais = 0;
        }
    } while (!feof(arquivoCarros));
}

// Separa os dados dos carros que correspondem à faixa de ano de fabricação informada pelo o usuário em outro arquivo
void selecionaFaixaAnoFabricacao(FILE *arquivoCarros, FILE *arquivoTemp, int anoMin, int anoMax)
{
    struct CARRO dadosCarro;

    fseek(arquivoCarros, 0, SEEK_SET);
    fseek(arquivoTemp, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            if (dadosCarro.ano_fabricacao >= anoMin && dadosCarro.ano_fabricacao <= anoMax)
                fwrite(&dadosCarro, sizeof(dadosCarro), 1, arquivoTemp);
        }
    } while (!feof(arquivoCarros));
}

// Determina uma quantidade de opcionais informada pelo o usário para a fução:
// void listarCarrosSelecaoOpcionais(FILE *arquivoCarros)
void determinaQuantidadeOpcionais(int *quantidadeOpcionais)
{
    long unsigned int i;
    int escolha;
    do
    {
        system("clear");
        printf("OPCIONAIS:\n");
        for (i = 0; i < QUANTIDADE_ELEMENTOS(opcionais); i++)
            printf("\t- %s\n", opcionais[i]);
        printf("\nINFORME A QUANTIDADE DE OPCIONAIS: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > 8)
        {
            printf("\nQUANTIDADE INVALIDA!\nMININMO: 1 | MAXIMO : 8\n\n");
            system("read -p \"Pressione enter\" saindo");
        }
    } while (escolha < 1 || escolha > 8);

    *quantidadeOpcionais = escolha;
}

// Determina uma faixa de ano de fabricação informada pelo o usuário para a função:
// void listarCarrosSelecaoAnoFabricacao(FILE *arquivoCarros)
void determinaFaixaAnoFabricacao(int *min, int *max)
{
    int anoMin = 0, anoMax = 0;
    do
    {
        system("clear");
        printf("\nINFORMAR UMA FAIXA DE ANO DE FABRICACAO:\nANO MINIMO: 1980 | ANO MAXIMO: 2016\n");
        do
        {
            printf("\nANO MINIMO: ");
            scanf("%d", &anoMin);

            if (anoMin < 1980 || anoMin >= 2016)
                printf("\nANO INVALIDO!\n");

        } while (anoMin < 1980 || anoMin >= 2016);
        do
        {
            printf("\nANO MAXIMO: ");
            scanf("%d", &anoMax);

            if (anoMax <= 1980 || anoMax > 2016)
                printf("\nANO INVALIDO!\n");

        } while (anoMax <= 1980 || anoMax > 2016);
        if (anoMin > anoMax)
        {
            printf("\nFAIXA DE ANO DE FABRICACAO INVALIDA!\nO ANO MAXIMO DEVE SER MAIOR QUE O ANO MINIMO!\n\n");
            system("read -p \"Pressione enter\" saindo");
        }
    } while (anoMin > anoMax);

    *min = anoMin;
    *max = anoMax;
}

// Listar os dados dos clientes com auxílio da função:
// void mostraCarro(struct CARRO carro)
void listarCarros(FILE *arquivoCarros)
{
    struct CARRO dadosCarro;

    fseek(arquivoCarros, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            printf("INFORMACOES DO CARRO:\n");
            mostraCarro(dadosCarro);
            printf("\n\n-----------------------------------------------------------\n\n");
        }
    } while (!feof(arquivoCarros));
}

// Separa em outro arquivo os carros disponíveis para a venda
void selecionaCarrosDisponiveis(FILE *arquivoCarros, FILE *arquivoDisponiveis, FILE *arquivoVendas)
{
    int verificadorVenda;
    struct CARRO dadosCarro;

    fseek(arquivoCarros, 0, SEEK_SET);
    fseek(arquivoDisponiveis, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            verificadorVenda = verificaExistenciaVendaCarro(arquivoVendas, dadosCarro.placa);
            if (verificadorVenda != 0)
                fwrite(&dadosCarro, sizeof(dadosCarro), 1, arquivoDisponiveis);
        }
    } while (!feof(arquivoCarros));
}

// Listar os carros cadastrados ordenados crescentemente pelo fabicante de modelo
void listarCarrosFabricanteModeloOredenados(FILE *arquivoCarros, FILE *arquivoVendas)
{
    struct CARRO dadosCarros[TAM];

    char *fileDisponiveisTemp = "./carros.disponiveis.dat";
    char *fileOrdenaTemp = "./carros.ordenados.dat";
    char *local = "void listarCarrosFabricanteModeloOredenados(FILE *arquivoCarros, FILE *arquivoVendas)";

    int tamanhoArquivoDisponiveis;

    if (quantidadeDadosArquivoCarros(arquivoCarros) > 0) // Verificar se existem carros cadastrados
    {
        FILE *arquivoDisponiveisTemp = abreArquivo(fileDisponiveisTemp, "w+b", local);
        FILE *arquivoOrdenaTemp = abreArquivo(fileOrdenaTemp, "w+b", local);

        selecionaCarrosDisponiveis(arquivoCarros, arquivoDisponiveisTemp, arquivoVendas); // Separa os carros que estão disponíveis para venda
        tamanhoArquivoDisponiveis = quantidadeDadosArquivoCarros(arquivoDisponiveisTemp); // Pegar a quantidade de dados do arquivo

        if (tamanhoArquivoDisponiveis != 0) //  Verificar se ainda existem carros disponíveis para venda
        {
            leituraArquivoCarro(arquivoDisponiveisTemp, dadosCarros);                     // Ler o arquivo e passar os dados para o vetor de struct
            ordenaFabricanteModeloCarros(dadosCarros, tamanhoArquivoDisponiveis);         // Ordenar os Fabricantes e modelos
            copiaArquivoCarro(arquivoOrdenaTemp, dadosCarros, tamanhoArquivoDisponiveis); // Copiar os dados do vetor de struct para um outro arquivo

            system("clear");
            printf("\nOPCAO: LISTAR OS CARROS DISPONIVEIS PARA A VENDA ORDENADOS CESCENTEMENTE POR FABRICANTES E MODELO\n\n");
            listarCarros(arquivoOrdenaTemp);
        }
        else
            ERRO_DISPONIBILIDADE_CARRO;

        fechaArquivo(arquivoDisponiveisTemp, fileDisponiveisTemp, local); // Fechar o arquivo
        fechaArquivo(arquivoOrdenaTemp, fileOrdenaTemp, local);           // Fechar o arquivo

        remove(fileDisponiveisTemp); // Excluir o arquivo
        remove(fileOrdenaTemp);      // Excluir o arquivo
    }
    else
        ERRO_CARRO;
}

// Listar os carros cadastrados por seleção de um ou mais opcionais
void listarCarrosSelecaoOpcionais(FILE *arquivoCarros, FILE *arquivoVendas)
{
    char *fileDisponiveisTemp = "./carros.disponiveis.dat";
    char *fileSelecaoTemp = "./carros.selecao.dat";
    char *local = "void listarCarrosSelecaoOpcionais(FILE *arquivoCarros, FILE *arquivoVendas)";

    int quantidadeOpcionais;

    if (quantidadeDadosArquivoCarros(arquivoCarros) > 0) // Verificar se existem carros cadastrados
    {
        FILE *arquivoDisponiveisTemp = abreArquivo(fileDisponiveisTemp, "w+b", local);
        FILE *arquivoSelecaoTemp = abreArquivo(fileSelecaoTemp, "w+b", local);

        selecionaCarrosDisponiveis(arquivoCarros, arquivoDisponiveisTemp, arquivoVendas); // Separa os carros que estão disponíveis para venda

        if (quantidadeDadosArquivoCarros(arquivoDisponiveisTemp) != 0) // Verificar se ainda existem carros disponíveis para venda
        {
            determinaQuantidadeOpcionais(&quantidadeOpcionais);                                  // Pegar a quantidade de opcionais determinado pelo o usuário
            selecionaOpcionais(arquivoDisponiveisTemp, arquivoSelecaoTemp, quantidadeOpcionais); // Separar em outro arquivo os dados dos carros que corresponde à quantidade de opcionais

            if (quantidadeDadosArquivoCarros(arquivoSelecaoTemp) > 0) // Verificar se existem carros disponíveis com a quantidade de opcionais fornecida
            {
                system("clear");
                printf("\nOPCAO: LISTAR OS CARROS DISPONIVEIS PARA A VENDA POR SELECAO DE UM OU MAIS OPICIONAIS\n\n");
                printf("CARRO(S) DISPONIVEL(IS) PARA VENDA COM %d OPCIONAL(IS):\n\n", quantidadeOpcionais);
                listarCarros(arquivoSelecaoTemp);
            }
            else
                printf("\nNAO FOI ENCONTRADO NENHUM CARRO DISPONIVEL COM ESSA QUANTIDADE DE OPCIONAIS!");
        }
        else
            ERRO_DISPONIBILIDADE_CARRO;

        fechaArquivo(arquivoDisponiveisTemp, fileDisponiveisTemp, local); // Fechar o arquivo
        fechaArquivo(arquivoSelecaoTemp, fileSelecaoTemp, local);         // Fechar o arquivo

        remove(fileDisponiveisTemp); // Apagar o arquivo
        remove(fileSelecaoTemp);     // Apagar o arquivo
    }
    else
        ERRO_CARRO;
}

// Listar os carros cadastrados por seleção da faixa de ano de fabricação
void listarCarrosSelecaoAnoFabricacao(FILE *arquivoCarros, FILE *arquivoVendas)
{
    char *fileDisponiveisTemp = "./carros.disponiveis.dat";
    char *fileSelecaoTemp = "./carros.selecao.dat";
    char *local = "void listarCarrosSelecaoAnoFabricacao(FILE *arquivoCarros, FILE *arquivoVendas)";

    int anoMin = 0, anoMax = 0;

    if (quantidadeDadosArquivoCarros(arquivoCarros) > 0) // Verificar se existem carros cadastrados
    {
        FILE *arquivoDisponiveisTemp = abreArquivo(fileDisponiveisTemp, "w+b", local);
        FILE *arquivoSelecaoTemp = abreArquivo(fileSelecaoTemp, "w+b", local);

        selecionaCarrosDisponiveis(arquivoCarros, arquivoDisponiveisTemp, arquivoVendas); // Separa os carros que estão disponíveis para venda

        if (quantidadeDadosArquivoCarros(arquivoDisponiveisTemp) != 0) // Verificar se ainda existem carros disponíveis para venda
        {
            determinaFaixaAnoFabricacao(&anoMin, &anoMax);                                           // Pegar uma faixa de ano de fabricação determinada pelo o usuário
            selecionaFaixaAnoFabricacao(arquivoDisponiveisTemp, arquivoSelecaoTemp, anoMin, anoMax); // Separar em outro arquivo os dados dos carros que correspondem à faixa de ano de fabricação

            if (quantidadeDadosArquivoCarros(arquivoSelecaoTemp) > 0) // Verificar se existem carros disponíveis na faixa de ano de fabricação determinada
            {
                system("clear");
                printf("\nOPCAO: LISTAR OS CARROS DISPONIVEIS PARA A VENDA POR SELECAO DA FAIXA DE ANO ADE FABRICACAO\n\n");
                printf("FAIXA DE ANO DE FABRICACAO SELECIONADA: DE %d ATE %d\n\n", anoMin, anoMax);
                listarCarros(arquivoSelecaoTemp);
            }
            else
                printf("\nNAO EXISTE NENHUM CARRO DISPONIVEL NESTA FAIXA DE ANO DE FABRICACAO!");
        }
        else
            ERRO_DISPONIBILIDADE_CARRO;

        fechaArquivo(arquivoDisponiveisTemp, fileDisponiveisTemp, local); // Fecha o arquivo
        fechaArquivo(arquivoSelecaoTemp, fileSelecaoTemp, local);         // Fecha o arquivo

        remove(fileDisponiveisTemp); // Remove o arquivo
        remove(fileSelecaoTemp);     // Remove o arquivo
    }
    else
        ERRO_CARRO;
}

// Auxilia na exclusão do cadastro de um carro
void realocaIndicesExcluirCarro(int indiceCarro, FILE *arquivoCarros, char *fileCarros)
{
    struct CARRO dadosCarros[TAM];

    char *local = "void realocaIndicesExcluirCarro(int indiceCarro, FILE *arquivoCarros, char *fileCarros)";

    int tamanhoArquivoCarros, i;

    tamanhoArquivoCarros = quantidadeDadosArquivoCarros(arquivoCarros); // Pegar a quantidade de dados do arquivo
    leituraArquivoCarro(arquivoCarros, dadosCarros);                    // Ler o arquivo e passar os dados para o vetor de struct

    for (i = indiceCarro; i < tamanhoArquivoCarros; i++)
        memcpy(&dadosCarros[i], &dadosCarros[i + 1], sizeof(dadosCarros[i])); // Realocar os indices do vetor de struct

    fechaArquivo(arquivoCarros, fileCarros, local);        // Fecha o arquivo
    arquivoCarros = abreArquivo(fileCarros, "w+b", local); // Abre/Cria o arquivo para reescrevver os dados nele

    tamanhoArquivoCarros--; // Reduz um índice

    copiaArquivoCarro(arquivoCarros, dadosCarros, tamanhoArquivoCarros); // Copiar os dados do vetor de struct para o arquivo
}

// Excluir um carro do cadastro
void excluirCarro(FILE *arquivoCarros, FILE *arquivoVendas, char *fileCarros)
{
    char *fileDisponiveisTemp = "./carros.disponiveis.dat";
    char *local = "void excluirCarro(FILE *arquivoCarro, FILE *arquivoVenda)";
    char placaCarro[9];

    int verificadorVenda, verificadorCarro, posicaoCarro;

    if (quantidadeDadosArquivoCarros(arquivoCarros) > 0) // Verificar se existem carros cadastrados
    {
        FILE *arquivoDisponiveisTemp = abreArquivo(fileDisponiveisTemp, "w+b", local);
        selecionaCarrosDisponiveis(arquivoCarros, arquivoDisponiveisTemp, arquivoVendas);

        if (quantidadeDadosArquivoCarros(arquivoDisponiveisTemp) != 0) // Verificar se existem carros disponíveis
        {
            do
            {
                system("clear");
                printf("\nOPCAO: EXCLUIR UM CARRO DO CADASTRO\n\n");
                printf("INFORME A PLACA DO CARRO QUE DESEJA EXCLUIR NO FORMATO (AAA-1234) OU (-1) PARA RETORNAR: ");
                scanf("%9s", placaCarro);

                if (placaCarro[0] == '-' && placaCarro[1] == '1')
                    RETORNA;
                else
                {
                    verificadorCarro = verificaExistenciaCarro(arquivoCarros, placaCarro);
                    verificadorVenda = verificaExistenciaVendaCarro(arquivoVendas, placaCarro);
                    if (verificadorCarro == 0 && verificadorVenda == 0)
                    {
                        printf("\nVERIFICAMOS QUE ESTE VEICULO JA FOI VENDIDO\nNAO SERA POSSIVEL EXCLUIR O CADASTRO!\n\n");
                        system("read -p \"Pressione enter\" saindo");
                    }
                    else if (verificadorCarro != 0 && verificadorVenda != 0)
                    {
                        printf("\nPLACA INVALIDA!\nNAO FOI ENCONTRADO NENHUM CADASTRO.\n\n");
                        system("read -p \"Pressione enter\" saindo");
                    }
                }
            } while ((placaCarro[0] != '-' && placaCarro[1] != '1') && (verificadorCarro != 0 || verificadorVenda == 0));

            if (verificadorCarro == 0 && verificadorVenda != 0)
            {
                posicaoCarro = localizaPosicaoCarroArquivo(arquivoCarros, placaCarro); // Pagar a posição do cadastro do carro no arquivo
                realocaIndicesExcluirCarro(posicaoCarro, arquivoCarros, fileCarros);   // Realizar a exclusão do carro
                printf("\nCARRO EXCLUIDO COM SUCESSO!");
            }
        }
        else
            printf("\nTODOS OS CARROS CADASTRADOS ESTAO VENDIDOS!\nNAO SERA POSSIVEL EXCUIR QUALQUER CARRO!");

        fechaArquivo(arquivoDisponiveisTemp, fileDisponiveisTemp, local); // Fechar o arquivo

        remove(fileDisponiveisTemp); // Excluir o arquivo
    }
    else
        ERRO_CARRO;
}

// CLIENTE:

// Funções necessárias para gerar os dados dos clientes: -----------------------------------------------------------------------------------------

int geraCodigoCliente(FILE *arquivoClientes)
{
    int verifica, codigo;

    if (quantidadeDadosArquivoClientes(arquivoClientes) > 0)
    {
        do
        {
            codigo = rand() % 1000 + 1;
            verifica = verificaExistenciaCliente(arquivoClientes, codigo);
        } while (verifica == 0);
    }
    else
        codigo = rand() % 1000 + 1;

    return codigo;
}

void geraNomeCliente(char *nomeCLiente)
{
    int n = rand() % QUANTIDADE_ELEMENTOS(nomes);
    int s = rand() % QUANTIDADE_ELEMENTOS(sobrenomes);

    strcpy(nomeCLiente, nomes[n]);
    strcat(nomeCLiente, " ");
    strcat(nomeCLiente, sobrenomes[s]);
}

void geraRuaCliente(char *ruaCliente)
{
    char identificacao[3];

    identificacao[0] = geraNumero();
    identificacao[1] = geraNumero();
    identificacao[2] = '\0';

    strcpy(ruaCliente, "Rua ");
    strcat(ruaCliente, identificacao);
}

void geraBairroCliente(char *bairroCliente)
{
    char identificacao[2];

    identificacao[0] = geraAlfabeto();
    identificacao[1] = '\0';

    strcpy(bairroCliente, "Bairro ");
    strcat(bairroCliente, identificacao);
}

void geraEstadoCliente(char *siglaEstadoCliente)
{
    int i = rand() % QUANTIDADE_ELEMENTOS(estados);
    strcpy(siglaEstadoCliente, estados[i]);
}

void geraCidadeCliente(char *cidadeCliente, char *siglaEstadoCliente)
{
    int indentificador, i = 0;

    do
    {
        if (strcmp(siglaEstadoCliente, estados[i]) == 0)
            indentificador = i;
    } while (i++ != QUANTIDADE_ELEMENTOS(estados));

    strcpy(cidadeCliente, cidades[indentificador]);
}

void geraCepCliente(char *cepCliente)
{
    int i;

    cepCliente[0] = '\0';
    for (i = 0; i < 10; i++)
    {
        if (i == 2)
            cepCliente[i] = '.';
        else if (i == 6)
            cepCliente[i] = '-';
        else
            cepCliente[i] = geraNumero();
    }

    cepCliente[10] = '\0';
}

void geraTelefoneCliente(char *telefoneCliente)
{
    int i;

    telefoneCliente[0] = '\0';
    for (i = 0; i < 13; i++)
    {
        if (i == 2)
            telefoneCliente[i] = ' ';
        else if (i == 8)
            telefoneCliente[i] = '-';
        else
            telefoneCliente[i] = geraNumero();
    }

    telefoneCliente[13] = '\0';
}

//------------------------------------------------------------------------------------------------------------------------------------------------

// Mostrar os dados do cliente
void mostraCliente(struct CLIENTE cliente)
{
    int i;
    printf("\n\tCODIGO: %d", cliente.cod_cli);
    printf("\n\tNOME: %s", cliente.nome);
    printf("\n\tCEP: %s", cliente.endereco.cep);
    printf("\n\tBAIRRO: %s", cliente.endereco.bairro);
    printf("\n\tRUA: %s", cliente.endereco.rua);
    printf("\n\tNUMERO: %d", cliente.endereco.numero);
    printf("\n\tCIDADE: %s", cliente.endereco.cidade);
    printf("\n\tESTADO: %s", cliente.endereco.estado);
    printf("\n\tTELEFONE: %s", cliente.residencial.telefone);
    for (i = 0; i < 5; i++)
        printf("\n\tCELULAR %d: %s", i + 1, cliente.celular[i].telefone);
    printf("\n\tRENDA MENSAL: R$ %.2f REAIS", cliente.renda_mensal);
}

// Gerar os dados do cliente
void geraCliente(FILE *arquivoClientes, struct CLIENTE *cliente)
{
    int i;

    cliente->cod_cli = geraCodigoCliente(arquivoClientes);
    geraNomeCliente(cliente->nome);
    geraRuaCliente(cliente->endereco.rua);
    cliente->endereco.numero = rand() % 3999 + 1;
    geraBairroCliente(cliente->endereco.bairro);
    geraEstadoCliente(cliente->endereco.estado);
    geraCidadeCliente(cliente->endereco.cidade, cliente->endereco.estado);
    geraCepCliente(cliente->endereco.cep);
    geraTelefoneCliente(cliente->residencial.telefone);
    for (i = 0; i < 5; i++)
        geraTelefoneCliente(cliente->celular[i].telefone);
    cliente->renda_mensal = geraNumeroFloat(900, 89999);
}

// Cadastro do cliente
void cadastrosCliente(FILE *arquivoClientes)
{
    struct CLIENTE cliente;
    char escolha;

    if (quantidadeDadosArquivoClientes(arquivoClientes) < TAM) // Verificar o limite de cadastros
    {
        do
        {
            system("clear");
            geraCliente(arquivoClientes, &cliente);
            flush_in();
            printf("INFORMACOES DO CLIENTE:\n");
            mostraCliente(cliente);
            printf("\n\nDESEJA INCLUIR ESTE CLIENTE (S/N) ? ");
            scanf("%c", &escolha);

            escolha = tolower(escolha);

            if (escolha != 's' && escolha != 'n')
            {
                do
                {
                    system("clear");
                    printf("INFORMACOES DO CLIENTE:\n");
                    mostraCliente(cliente);
                    printf("\n\nATENCAO!! INFORME: ('S' - SIM) OU ('N' - NAO)\nDESEJA INCLUIR ESTE CLIENTE ? ");
                    scanf("%c", &escolha);
                } while (escolha != 's' && escolha != 'n');
            }

        } while (escolha != 's');

        printf("\nINCLUINDO . . .");
        fwrite(&cliente, sizeof(cliente), 1, arquivoClientes); // Registrar os dados do cliente no arquivo
        flush_in();
    }
    else
        ERRO_LIMITE;
}

// Copia os dados do arquivo para um vetor de struct
void leituraArquivoCliente(FILE *arquivoClientes, struct CLIENTE *cliente)
{
    struct CLIENTE dadosCliente;
    int i = 0;

    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
            cliente[i++] = dadosCliente;
    } while (!feof(arquivoClientes));
}

// Realiza a troca de dados
void trocaStructClientes(struct CLIENTE *dadosA, struct CLIENTE *dadosB)
{
    struct CLIENTE dadosAux;

    dadosAux = *dadosA;
    *dadosA = *dadosB;
    *dadosB = dadosAux;
}

// Copia os dados do vetor de struct para um arquivo
void copiaArquivoCliente(FILE *arquivoClientes, struct CLIENTE *dadosCliente, int tamanho)
{
    int i;

    fseek(arquivoClientes, 0, SEEK_SET);
    for (i = 0; i < tamanho; i++)
        fwrite(&dadosCliente[i], sizeof(dadosCliente[i]), 1, arquivoClientes);
}

// Ordena crescentemente os nomes dos clientes
void ordenaNomesClientes(struct CLIENTE *dadosCliente, int tamanho)
{
    int i, j;

    for (i = 0; i < tamanho; i++)
    {
        for (j = i; j < tamanho; j++)
        {
            if (strcmp(dadosCliente[i].nome, dadosCliente[j].nome) > 0)
                trocaStructClientes(&dadosCliente[i], &dadosCliente[j]);
        }
    }
}

// Separa os dados dos clientes que correspondes à faixa salarial informada pelo o usuário em outro arquivo
void selecionaFaixaSalarial(FILE *arquivoClientes, FILE *arquivoTemp, float valorMin, float valorMax)
{
    struct CLIENTE dadosCliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    fseek(arquivoTemp, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
        {
            if (dadosCliente.renda_mensal >= valorMin && dadosCliente.renda_mensal <= valorMax)
                fwrite(&dadosCliente, sizeof(dadosCliente), 1, arquivoTemp);
        }
    } while (!feof(arquivoClientes));
}

// Determina uma faixa salarial informada pelo usuário para a função:
// void listarClientesSelecaoSalarial(FILE *arquivoClientes)
void determinaFaixaSalarial(float *min, float *max)
{
    float valorMinimo = 0.0, valorMaximo = 0.0;
    do
    {
        system("clear");
        printf("\nINFORMAR UMA FAIXA SALARIAL MENSAL:\nMINIMO: R$ 900,00 | MAXIMO: R$ 90.900,00\n");
        do
        {
            printf("\nVALOR MINIMO: ");
            scanf("%f", &valorMinimo);

            if (valorMinimo < 900.0 || valorMinimo >= 90900.0)
                printf("\nVALOR INVALIDO!");

        } while (valorMinimo < 900.0 || valorMinimo >= 90900.0);

        do
        {
            printf("\nVALOR MAXIMO: ");
            scanf("%f", &valorMaximo);

            if (valorMaximo <= 900.0 || valorMaximo > 90900.0)
                printf("\nVALOR INVALIDO!");

        } while (valorMaximo <= 900.0 || valorMaximo > 90900.0);

        if (valorMinimo > valorMaximo)
        {
            printf("\nFAIXA SALARIAL INVALIDA!\nO VALOR MAXIMO DEVE SER MAIOR QUE O VALOR MINIMO!\n\n");
            system("read -p \"Pressione enter\" saindo");
        }
    } while (valorMinimo > valorMaximo);

    *min = roundf(valorMinimo * 100) / 100;
    *max = roundf(valorMaximo * 100) / 100;
}

// Listar os dados dos clientes com auxílio da função: void mostraCliente(struct CLIENTE cliente)
void listarClientes(FILE *arquivoClientes)
{
    struct CLIENTE dadosCliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
        {
            printf("INFORMACOES DO CLIENTE:\n");
            mostraCliente(dadosCliente);
            printf("\n\n-----------------------------------------------------------\n\n");
        }
    } while (!feof(arquivoClientes));
}

// Listar os clientes cadastrados ordenados crescentemente pelo nome
void listarClientesNomesOrdenados(FILE *arquivoClientes)
{
    struct CLIENTE dadosClientes[TAM];

    char *fileOrdenaTemp = "./cli.ordenados.dat";
    char *local = "void listarClientesNomesOrdenados(FILE *arquivoClientes)";

    int tamanhoArquivoClientes;

    tamanhoArquivoClientes = quantidadeDadosArquivoClientes(arquivoClientes); // Pegar a quantidade de dados do arquivo

    if (tamanhoArquivoClientes > 0)
    {
        FILE *arquivoOrdenaTemp = abreArquivo(fileOrdenaTemp, "w+b", local);

        leituraArquivoCliente(arquivoClientes, dadosClientes);                         // Ler o arquivo e passar os dados para o vetor de struct
        ordenaNomesClientes(dadosClientes, tamanhoArquivoClientes);                    // Ordenar os nomes
        copiaArquivoCliente(arquivoOrdenaTemp, dadosClientes, tamanhoArquivoClientes); // Copiar os dados do vetor de struct para um outro arquivo

        system("clear");
        printf("\nOPCAO: LISTAR OS CLIENTES NO CADASTRO ORDENADOS CRESCENTEMENTE PELO NOME\n\n");
        listarClientes(arquivoOrdenaTemp);

        fechaArquivo(arquivoOrdenaTemp, fileOrdenaTemp, local); // Fechar o arquivo

        remove(fileOrdenaTemp); // Excluir o arquivo
    }
    else
        ERRO_CLIENTE;
}

// Listar os clientes cadastrados ordenados crescentemente pelo nome por seleção de uma faixa salarial mensal
void listarClientesSelecaoSalarial(FILE *arquivoClientes)
{
    struct CLIENTE dadosCliente[TAM];

    char *fileSelecaoTemp = "./cli.selecao.dat";
    char *fileOrdenaTemp = "./cli.ordenado.dat";
    char *local = "void listarClientesSelecaoSalarial(FILE *arquivoClientes)";

    int tamanhoArquivoClientes;
    float valorMin = 0.0, valorMax = 0.0;

    if (quantidadeDadosArquivoCarros(arquivoClientes) > 0)
    {
        FILE *arquivoSelecaoTemp = abreArquivo(fileSelecaoTemp, "w+b", local);
        FILE *arquivoOrdenaTemp = abreArquivo(fileOrdenaTemp, "w+b", local);

        determinaFaixaSalarial(&valorMin, &valorMax);
        selecionaFaixaSalarial(arquivoClientes, arquivoSelecaoTemp, valorMin, valorMax); // Pegar os cadastros que corresponde à faixa salarial definida
        tamanhoArquivoClientes = quantidadeDadosArquivoClientes(arquivoSelecaoTemp);     // Pegar a quantidade de dados do arquivo

        if (tamanhoArquivoClientes > 0) // Verificar se existem clintes cadastrados com faixa salarial determinada
        {
            leituraArquivoCliente(arquivoSelecaoTemp, dadosCliente);                      // Ler o arquivo e passar os dados para o vetor de struct
            ordenaNomesClientes(dadosCliente, tamanhoArquivoClientes);                    // Ordenar os nomes
            copiaArquivoCliente(arquivoOrdenaTemp, dadosCliente, tamanhoArquivoClientes); // Copiar os dados do vetor de struct para um outro arquivo

            system("clear");
            printf("\nOPCAO: LISTAR OS CLIENTES NO CADASTRO ORDENADOS CRESCENTEMENTE PELO NOME POR SELECAO DE FAIXA DE RENDA SALARIAL MENSAL\n\n");
            printf("FAIXA SALARIAL MENSAL SELECIONADA: DE R$ %.2f REAIS | ATE R$ %.2f REAIS\n\n", valorMin, valorMax);
            listarClientes(arquivoOrdenaTemp);
        }
        else
            printf("\nNAO EXISTEM CLINTES CADASTRADOS COM ESTA FAIXA SALARIAL!");

        fechaArquivo(arquivoSelecaoTemp, fileSelecaoTemp, local); // Fecha o arquivo
        fechaArquivo(arquivoOrdenaTemp, fileOrdenaTemp, local);   // Fecha o arquivo

        remove(fileSelecaoTemp); // Exclui o arquivo
        remove(fileOrdenaTemp);  // Exclui o arquivo
    }
    else
        ERRO_CLIENTE;
}

// Auxilia na exclusão do cadastro de um cliente
void realocaIndicesExcluirClientes(int indiceCliente, FILE *arquivoClientes, char *fileClientes)
{
    struct CLIENTE dadosCliente[TAM];

    char *local = "void realocaIndicesExcluirClientes(int indiceCliente, FILE *arquivoClientes, char *fileClientes)";

    int tamanhoArquivoClientes, i;

    tamanhoArquivoClientes = quantidadeDadosArquivoClientes(arquivoClientes); // Pegar a quantidade de dados do arquivo
    leituraArquivoCliente(arquivoClientes, dadosCliente);                     // Ler o arquivo e passar os dados para o vetor de struct

    for (i = indiceCliente; i < tamanhoArquivoClientes; i++)
        memcpy(&dadosCliente[i], &dadosCliente[i + 1], sizeof(dadosCliente[i])); // Realocar os indices do vetor de struct

    fechaArquivo(arquivoClientes, fileClientes, local);        // Fecha o arquivo
    arquivoClientes = abreArquivo(fileClientes, "w+b", local); // Abre/Cria o arquivo para reescrevver os dados nele

    tamanhoArquivoClientes--; // Reduz um índice

    copiaArquivoCliente(arquivoClientes, dadosCliente, tamanhoArquivoClientes); // Copiar os dados do vetor de struct para o arquivo
}

//  Excluir um cliente do cadastro
void excluirCliente(FILE *arquivoClientes, FILE *arquivoVendas, char *fileClientes)
{
    int codigoCliente, verificadorVenda, verificadorCliente, posicaoCliente;

    if (quantidadeDadosArquivoClientes(arquivoClientes) > 0) // Verificar se existem clientes cadastrados
    {
        do
        {
            system("clear");
            printf("\nOPCAO: INSERIR UM CLIENTE NO CADASTRO\n\n");
            printf("INFORME O CODIGO DO CLIENTE QUE DESEJA EXCLUIR OU (-1) PARA RETORNAR: ");
            scanf("%d", &codigoCliente);

            if (codigoCliente == -1)
                RETORNA;
            else
            {
                verificadorCliente = verificaExistenciaCliente(arquivoClientes, codigoCliente);
                verificadorVenda = verificaExistenciaVendaCliente(arquivoVendas, codigoCliente);

                if (verificadorCliente == 0 && verificadorVenda == 0)
                {
                    printf("\nVERIFICAMOS UMA VENDA REGISTRADA NESTE CLIENTE\nNAO SERA POSSIVEL EXCLUIR O CADASTRO!\n\n");
                    system("read -p \"Pressione enter\" saindo");
                }
                else if (verificadorCliente != 0 && verificadorVenda != 0)
                {
                    printf("\nCODIGO INVALIDO!\nNAO FOI ENCONTRADO NENHUM CADASTRO.\n\n");
                    system("read -p \"Pressione enter\" saindo");
                }
            }
        } while (codigoCliente != -1 && (verificadorCliente != 0 || verificadorVenda == 0));

        if (verificadorCliente == 0 && verificadorVenda != 0)
        {
            posicaoCliente = localizaPosicaoClienteArquivo(arquivoClientes, codigoCliente); // Pagar a posição do cadastro do cliente no arquivo
            realocaIndicesExcluirClientes(posicaoCliente, arquivoClientes, fileClientes);   // Realizar a exclusão do cleinte
            printf("\nCLIENTE EXCLUIDO COM SUCESSO!");
        }
    }
    else
        ERRO_CLIENTE;
}

// VENDA:

// Copia os dados do arquivo para um vetor de struct
void leituraArquivoVenda(FILE *arquivoVendas, struct VENDA_CARRO *venda)
{
    struct VENDA_CARRO dadosVenda;
    int i = 0;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVenda, sizeof(dadosVenda), 1, arquivoVendas) > 0)
            venda[i++] = dadosVenda;
    } while (!feof(arquivoVendas));
}

// Copia os dados do vetor de struct para um arquivo
void copiaArquivoVenda(FILE *arquivoVendas, struct VENDA_CARRO *dadosVenda, int tamanho)
{
    int i;

    fseek(arquivoVendas, 0, SEEK_SET);
    for (i = 0; i < tamanho; i++)
        fwrite(&dadosVenda[i], sizeof(dadosVenda[i]), 1, arquivoVendas);
}

// Separa em um arquivo os carros vendidos
void separaCarrosVendas(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoCarrosVendas)
{
    struct CARRO dadosCarros[TAM];
    struct CARRO dadosCarrosVendas[TAM];
    struct VENDA_CARRO dadosVendas[TAM];

    int tamanhoArquivoCarros = quantidadeDadosArquivoCarros(arquivoCarros); // Pega a quantidade de dados do arquivo
    int tamanhoArquivoVendas = quantidadeDadosArquivoVendas(arquivoVendas); // Pega a quantidade de dados do arquivo
    int i, j, indiceCarros = 0;

    leituraArquivoCarro(arquivoCarros, dadosCarros); // Ler o arquivo e passar os dados para o vetor de struct
    leituraArquivoVenda(arquivoVendas, dadosVendas); // Ler o arquivo e passr os dados para o vetor de struct

    for (i = 0; i < tamanhoArquivoVendas; i++) // Separar os cadastros em outro vetor de struct
    {
        for (j = 0; j < tamanhoArquivoCarros; j++)
        {
            if (strcmp(dadosVendas[i].placa, dadosCarros[j].placa) == 0)
                dadosCarrosVendas[indiceCarros++] = dadosCarros[j];
        }
    }

    copiaArquivoCarro(arquivoCarrosVendas, dadosCarrosVendas, indiceCarros); // Copia os dados do vetor de struct em outro arquivo
}

// Separa em um arquivo os clientes que possuem venda cadastrada
void separaClientesVendas(FILE *arquivoClientes, FILE *arquivoVendas, FILE *arquivoClientesVendas)
{
    struct CLIENTE dadosClientes[TAM];
    struct CLIENTE dadosClientesVendas[TAM];
    struct VENDA_CARRO dadosVendas[TAM];

    int tamanhoArquivoClientes = quantidadeDadosArquivoClientes(arquivoClientes); // Pega a quantidade de dados do arquivo
    int tamanhoArquivoVendas = quantidadeDadosArquivoVendas(arquivoVendas);       // Pega a quantidade de dados do arquivo
    int i, j, indiceClientes = 0;

    leituraArquivoCliente(arquivoClientes, dadosClientes); // Ler o arquivo e passar os dados para o vetor de struct
    leituraArquivoVenda(arquivoVendas, dadosVendas);       // Ler o arquivo e passar os dados para o vetor de struct

    for (i = 0; i < tamanhoArquivoVendas; i++) // Separar os cadastros em outro vetor de struct
    {
        for (j = 0; j < tamanhoArquivoClientes; j++)
        {
            if (dadosVendas[i].cod_cli == dadosClientes[j].cod_cli)
                dadosClientesVendas[indiceClientes++] = dadosClientes[j];
        }
    }

    copiaArquivoCliente(arquivoClientesVendas, dadosClientesVendas, indiceClientes); // Copia os dados do vetor de struct em outro arquivo
}

// Determina a data da venda para a função:
// void inserirVenda(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
void determinaDataVenda(int vetorDatas[], int anoModelo)
{
    int data[3], i;
    printf("\nINFORME A DATA NO FORMATO NUMERICO:\n");
    do
    {
        printf("\nDIA: ");
        scanf("%d", &data[0]);

        if (data[0] > 31 || data[0] < 1)
            printf("\nDIA INVALIDO!\n");

    } while (data[0] > 31 || data[0] < 1);
    do
    {
        printf("\nMES: ");
        scanf("%d", &data[1]);

        if (data[1] > 12 || data[1] < 1)
            printf("\nMES INVALIDO!\n");

    } while (data[1] > 12 || data[1] < 1);
    do
    {
        printf("\nANO: ");
        scanf("%d", &data[2]);

        if (data[2] < anoModelo || data[2] > 2021)
            printf("\nANO INVALIDO!\n");

    } while (data[2] < anoModelo || data[2] > 2021);

    for (i = 0; i < 3; i++)
        vetorDatas[i] = data[i];
}

// Mostra os detalhes da venda para o usuários
void mostraVendaFinalizada(struct VENDA_CARRO venda)
{
    printf("\nDETALHES DA VENDA:\n");
    printf("\n\tPLACA DO CARRO: %s", venda.placa);
    printf("\n\tCODIGO DO CLIENTE: %d", venda.cod_cli);
    printf("\n\tPRECO DA VENDA: R$ %.2f", venda.preco_venda);
    printf("\n\tDATA: %d/%d/%d", venda.data_venda.dia, venda.data_venda.mes, venda.data_venda.ano);
    printf("\n\n-----------------------------------------------------------\n\n");
}

// Cadastro da venda
void cadastroVenda(FILE *arquivoVendas, struct CARRO carro, struct CLIENTE cliente, int dataVenda[], float precoVenda)
{
    struct VENDA_CARRO venda;

    venda.cod_cli = cliente.cod_cli;
    venda.data_venda.dia = dataVenda[0];
    venda.data_venda.mes = dataVenda[1];
    venda.data_venda.ano = dataVenda[2];
    strcpy(venda.placa, carro.placa);
    venda.preco_venda = precoVenda;

    mostraVendaFinalizada(venda);

    fwrite(&venda, sizeof(venda), 1, arquivoVendas);
    flush_in();
}

// Inserir uma venda
void inserirVenda(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
{
    char *fileDisponiveisTemp = "./carros.disponiveis.dat";
    char *local = "void inserirVenda(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)";

    char placaCarro[9];
    int codigoCliente;

    int verificadorCarro, verificadorVenda, verificadorCliente = 1;
    int posicaoCarro, posicaoCliente;
    int data[3];
    float precoVenda;

    if (quantidadeDadosArquivoClientes(arquivoClientes) > 0 && quantidadeDadosArquivoCarros(arquivoCarros) > 0) // Verificar se existem clientes e carros cadastrados
    {
        FILE *arquivoDisponiveisTemp = abreArquivo(fileDisponiveisTemp, "w+b", local);

        selecionaCarrosDisponiveis(arquivoCarros, arquivoDisponiveisTemp, arquivoVendas); // Separar os carros disponíveis para venda em outro arquivo
        if (quantidadeDadosArquivoCarros(arquivoDisponiveisTemp) != 0)                    // Verificar se existem carros disponíveis para venda
        {
            do
            {
                system("clear");
                printf("\nOPCAO: INSERIR UMA VENDA\n\n");
                printf("INFORME A PLACA DO VEICULO NO FORMATO (AAA-1234) OU (-1) PARA RETORNAR: ");
                scanf("%9s", placaCarro);

                if (placaCarro[0] == '-' && placaCarro[1] == '1')
                    RETORNA;
                else
                {
                    verificadorCarro = verificaExistenciaCarro(arquivoCarros, placaCarro);
                    verificadorVenda = verificaExistenciaVendaCarro(arquivoVendas, placaCarro);
                    if (verificadorCarro == 0 && verificadorVenda == 0)
                    {
                        printf("\nESTE VEICULO JA FOI VENDIDO!\n\n");
                        system("read -p \"Pressione enter\" saindo");
                    }
                    else if (verificadorCarro != 0 && verificadorVenda != 0)
                    {
                        printf("\nPLACA INVALIDA!\nNAO FOI ENCONTRADO NENHUM CADASTRO.\n\n");
                        system("read -p \"Pressione enter\" saindo");
                    }
                }
            } while ((placaCarro[0] != '-' && placaCarro[1] != '1') && (verificadorCarro != 0 || verificadorVenda == 0));

            if (verificadorCarro == 0 && verificadorVenda != 0)
            {
                do
                {
                    system("clear");
                    printf("\nINFORME O CODIGO DO CLIENTE OU (-1) PARA RETORNAR: ");
                    scanf("%d", &codigoCliente);

                    if (codigoCliente == -1)
                        RETORNA;
                    else
                    {
                        verificadorCliente = verificaExistenciaCliente(arquivoClientes, codigoCliente);
                        if (verificadorCliente != 0)
                        {
                            printf("\nCODIGO INVALIDO!\nNAO FOI ENCONTRADO NENHUM CADASTRO.\n\n");
                            system("read -p \"Pressione enter\" saindo");
                        }
                    }
                } while (codigoCliente != -1 && verificadorCliente != 0);
            }

            if (verificadorCliente == 0)
            {
                struct CARRO carro;
                struct CLIENTE cliente;

                posicaoCarro = localizaPosicaoCarroArquivo(arquivoCarros, placaCarro);
                posicaoCliente = localizaPosicaoClienteArquivo(arquivoClientes, codigoCliente);

                do
                {
                    system("clear");

                    printf("\nDADOS DO VEICULO:\n");
                    fseek(arquivoCarros, sizeof(carro) * posicaoCarro, SEEK_SET);
                    if (fread(&carro, sizeof(carro), 1, arquivoCarros) > 0)
                        mostraCarro(carro);

                    printf("\nDADOS DO CLIENTE:\n");
                    fseek(arquivoClientes, sizeof(cliente) * posicaoCliente, SEEK_SET);
                    if (fread(&cliente, sizeof(cliente), 1, arquivoClientes) > 0)
                        mostraCliente(cliente);

                    printf("\n\nINFORME O VALOR DA VENDA OU (-1) PARA CANCELAR: ");
                    scanf("%f", &precoVenda);

                    if (precoVenda == -1)
                        printf("\nVENDA CANCELADA!\nRETORNANDO . . .");
                    else if (precoVenda < carro.preco_compra)
                    {
                        printf("\nO VEICULO NAO PODE SER VENDIDO POR UM VALOR INFERIOR DO SEU PRECO DE COMPRA!\n\n");
                        system("read -p \"Pressione enter\" saindo");
                    }
                } while (precoVenda != -1 && precoVenda < carro.preco_compra);

                if (precoVenda > carro.preco_compra)
                {
                    determinaDataVenda(data, carro.ano_modelo);
                    printf("\nVENDA REGISTRADA COM SUCESSO!\n");
                    cadastroVenda(arquivoVendas, carro, cliente, data, precoVenda); // Cadastrar a venda
                }
            }
        }
        else
            ERRO_DISPONIBILIDADE_CARRO;

        fechaArquivo(arquivoDisponiveisTemp, fileDisponiveisTemp, local); // Fechar o arquivo

        remove(fileDisponiveisTemp); // Excluir o arquivo
    }
    if (quantidadeDadosArquivoClientes(arquivoClientes) == 0)
        ERRO_CLIENTE;
    if (quantidadeDadosArquivoCarros(arquivoCarros) == 0)
        ERRO_CARRO;
}

// Mostrar os fabricantes cadastrados para o usuário
void mostraFabricantes()
{
    long unsigned int i;
    printf("FABRICANTES CADASTRADOS:");
    for (i = 0; i < QUANTIDADE_ELEMENTOS(carrosFabricantes); i++)
        printf("\n- %s", carrosFabricantes[i]);
}

// Mostrar os modelos cadastrados para o usuário
void mostraModelos()
{
    long unsigned int i;
    int ii = 1;
    printf("MODELOS CADASTRADOS:\n\n");
    for (i = 0; i < QUANTIDADE_ELEMENTOS(carrosModelos); i++)
    {
        if (ii < 5)
            printf("%s, ", carrosModelos[i]);
        if (ii == 5)
        {
            printf("%s\n", carrosModelos[i]);
            ii = 0;
        }
        ii++;
    }
}

// Verifica se o fabricante informado pelo o usuário existe
int procuraFabricante(char *nomeFabricante, int *indiceFabricante)
{
    long unsigned int i = 0;
    int verificador;
    do
    {
        if ((verificador = strcmp(nomeFabricante, carrosFabricantes[i])) == 0)
            *indiceFabricante = i;
    } while (verificador != 0 && i++ < QUANTIDADE_ELEMENTOS(carrosFabricantes));

    return verificador;
}

// Verifica se o modelo informado pelo o usuário existe
int procuraModelo(char *nomeModelo, int *indiceModelo)
{
    long unsigned int i = 0;
    int verificador;
    do
    {
        if ((verificador = strcmp(nomeModelo, carrosModelos[i])) == 0)
            *indiceModelo = i;
    } while (verificador != 0 && i++ < QUANTIDADE_ELEMENTOS(carrosModelos));

    return verificador;
}

// Determina um fabricante informado pelo o usuário para a função:
// void listarVendasModelosOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
void determinaFabricante(char *nomeFabricante)
{
    int verificador, indiceFabricante;
    char escolha[20];
    do
    {
        system("clear");
        printf("\nOPCAO: LISTAR OS CARROS VENDIDOS DE UM DETERMINADO FABRICANTE, ORDENADOS CRESCENTEMENTE PELO MODELO\n\n");
        mostraFabricantes();
        printf("\n\nINFORME O NOME DO FABRICANTE: ");
        scanf("%s", escolha);

        if ((verificador = procuraFabricante(escolha, &indiceFabricante)) != 0)
        {
            printf("\nFABRICANTE INVALIDO, TENTE NOVAMENTE . . .\n\n");
            system("read -p \"Pressione enter\" saindo");
        }
    } while (verificador != 0);

    strcpy(nomeFabricante, carrosFabricantes[indiceFabricante]);
}

// Determina um modelo de carro para a função:
// void listarVendasAnoFabricacaoOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
void determinaModelo(char *nomeModelo)
{
    int verificador, indiceModelo;
    char escolha[20];
    do
    {
        system("clear");
        printf("\nOPCAO: LISTAR OS CARROS VENDIDOS DE UM DETERMINADO MODELO, ORDENADOS CRESCENTEMENTE PELO ANO DE FABRICACAO\n\n");
        mostraModelos();
        printf("\nINFORME O NOME DO MODELO: ");
        scanf("%s", escolha);

        if ((verificador = procuraModelo(escolha, &indiceModelo)) != 0)
        {
            printf("\nMODELO INVALIDO, TENTE NOVAMENTE . . .\n\n");
            system("read -p \"Pressione enter\" saindo");
        }
    } while (verificador != 0);

    strcpy(nomeModelo, carrosModelos[indiceModelo]);
}

// Separa os carros vendidos de um determinado fabricante ordenados crescentemente em outro arquivo
void separaCarrosPorFabricante(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoCarroTemp, char *nomeFabricante)
{
    struct CARRO dadosCarros[TAM];
    struct CARRO dadosCarrosFabricante[TAM];

    char *fileCarrosVendas = "./carros.vendidos.dat";
    char *local = "void separaCarrosPorFabricante(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoFabricante, char *nomeFabricante)";

    FILE *arquivoCarrosVendidos = abreArquivo(fileCarrosVendas, "w+b", local); // Abrir/Criar o arquivo

    separaCarrosVendas(arquivoCarros, arquivoVendas, arquivoCarrosVendidos); // Separar os cadastros dos carros vendidos

    int tamanhoArquivoCarro = quantidadeDadosArquivoCarros(arquivoCarrosVendidos); // Pegar a quantidade de dados do arquivo
    int i, indiceCarros = 0;

    leituraArquivoCarro(arquivoCarrosVendidos, dadosCarros); // Ler o arquivo e passar os dados para um vetor de struct

    for (i = 0; i < tamanhoArquivoCarro; i++) // Separar os cadastros de carros que correspondem ao fabricante informado
    {
        if (strcmp(nomeFabricante, dadosCarros[i].fabricante) == 0)
            dadosCarrosFabricante[indiceCarros++] = dadosCarros[i];
    }

    ordenaFabricanteModeloCarros(dadosCarrosFabricante, indiceCarros); // Ordena crescentemente os modelos dos carros

    copiaArquivoCarro(arquivoCarroTemp, dadosCarrosFabricante, indiceCarros); // Copia os dados do vetor de struct em outro arquivo

    fechaArquivo(arquivoCarrosVendidos, fileCarrosVendas, local); // Fechar o arquivo

    remove(fileCarrosVendas); // Remover o arquivo
}

// Ordena crescentemente os dados dos carros pelo ano de fabricação
void ordenaAnoDeFabricacaoCarros(struct CARRO *dadosCarro, int tamanho)
{
    int i, j;

    for (i = 0; i < tamanho; i++)
    {
        for (j = i + 1; j < tamanho; j++)
        {
            if (dadosCarro[i].ano_modelo > dadosCarro[j].ano_modelo)
                trocaStructCarro(&dadosCarro[i], &dadosCarro[j]);
        }
    }
}

// Separa os carros vendidos de um determinado modelo ordenados crescentemente pelo ano de fabricação em outro arquivo
void separaCarrosPorModelo(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoCarroTemp, char *nomeModelo)
{
    struct CARRO dadosCarros[TAM];
    struct CARRO dadosCarrosModelo[TAM];

    char *fileCarrosVendas = "./carros.vendidos.dat";
    char *local = "void separaCarrosPorFabricante(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoFabricante, char *nomeFabricante)";

    FILE *arquivoCarrosVendidos = abreArquivo(fileCarrosVendas, "w+b", local); // Abrir/Criar o arquivo

    separaCarrosVendas(arquivoCarros, arquivoVendas, arquivoCarrosVendidos); // Separar os cadastros dos carros vendidos

    int tamanhoArquivoCarro = quantidadeDadosArquivoCarros(arquivoCarrosVendidos); // Pegar a quantidade de dados do arquivo
    int i, indiceCarros = 0;

    leituraArquivoCarro(arquivoCarrosVendidos, dadosCarros); // Ler o arquivo e passar os dados para um vetor de struct

    for (i = 0; i < tamanhoArquivoCarro; i++) // Separar os cadastros de carros que correspondem ao modelo informado
    {
        if (strcmp(nomeModelo, dadosCarros[i].modelo) == 0)
            dadosCarrosModelo[indiceCarros++] = dadosCarros[i];
    }

    ordenaAnoDeFabricacaoCarros(dadosCarrosModelo, indiceCarros); // Ordena os cadastros dos carros crescentemente pelo ano de fabricação

    copiaArquivoCarro(arquivoCarroTemp, dadosCarrosModelo, indiceCarros); // Copia os dados do vetor de struct em outro arquivo

    fechaArquivo(arquivoCarrosVendidos, fileCarrosVendas, local); // Fechar o arquivo

    remove(fileCarrosVendas); // Remover o arquivo
}

// Separa os dados vendas correspondentes com os dados dos carros em outro arquivo
void separaVendasCorrespondente(FILE *arquivoCarros, FILE *arquivoVendas, FILE *arquivoVendasTemp)
{
    struct CARRO dadosCarros[TAM];
    struct VENDA_CARRO dadosVendas[TAM];
    struct VENDA_CARRO dadosVendasCorrespondentes[TAM];

    int tamanhoArquivoVendas = quantidadeDadosArquivoVendas(arquivoVendas); // Pegar a quantidade de dados do arquivo
    int tamanhoArquivoCarros = quantidadeDadosArquivoCarros(arquivoCarros); // Pegar a quantidade de dados do arquivo
    int i, j, indiceVendas = 0;

    leituraArquivoCarro(arquivoCarros, dadosCarros); // Ler os dados de um arquivo e passar para um vetor de struct
    leituraArquivoVenda(arquivoVendas, dadosVendas); // Ler os dados de um arquivo e passar para um vetor de struct

    for (i = 0; i < tamanhoArquivoCarros; i++) // Separar os dados das vendas com os dados dos carros em outro vetor de struct
    {
        for (j = 0; j < tamanhoArquivoVendas; j++)
        {
            if (strcmp(dadosCarros[i].placa, dadosVendas[j].placa) == 0)
                dadosVendasCorrespondentes[indiceVendas++] = dadosVendas[j];
        }
    }

    copiaArquivoVenda(arquivoVendasTemp, dadosVendasCorrespondentes, indiceVendas); // Copia os dados do vetor de struct em outro arquivo
}

// Separa os dados dos clientes correspondentes com os dados das vendas em outro arquivo
void separaClientesCorrespondente(FILE *arquivoVendas, FILE *arquivoClientes, FILE *arquivoClientesTemp)
{
    struct CLIENTE dadosClientesCorrespondente[TAM];

    char *fileClientesVendas = "./clientes.vendas.dat";
    char *local = "void separaClientesCorrespondente(FILE *arquivoVendas, FILE *arquivoClientes, FILE *arquivoClientesTemp)";

    FILE *arquivoClientesVendas = abreArquivo(fileClientesVendas, "w+b", local); // Abrir/Criar o arquivo

    separaClientesVendas(arquivoClientes, arquivoVendas, arquivoClientesVendas); // Separar os cadastros dos clientes que possuem venda registrada

    int tamanhoArquivoClientes = quantidadeDadosArquivoClientes(arquivoClientesVendas); // Pegar a quantidade de dados de um a

    leituraArquivoCliente(arquivoClientesVendas, dadosClientesCorrespondente); // Ler o arquivo e passar os dados para um vetor de struct

    copiaArquivoCliente(arquivoClientesTemp, dadosClientesCorrespondente, tamanhoArquivoClientes); // Copia os dados do vetor de struct em outro arquivo

    fechaArquivo(arquivoClientesVendas, fileClientesVendas, local); // Fechar o arquivo

    remove(fileClientesVendas); // Remover o arquivo
}

// Mostra as seguintes informações: modelo do carro, placa do carro, ano de fabricação e nome do cliente
void mostraVendaPorFabricante(struct CARRO carro, struct CLIENTE cliente)
{
    printf("\n\tMODELO DO CARRO: %s", carro.modelo);
    printf("\n\tPLACA DO CARRO: %s", carro.placa);
    printf("\n\tANO DE FABRICACAO: %d", carro.ano_fabricacao);
    printf("\n\tNOME DO CLIENTE: %s", cliente.nome);
}

// Mostra as seguintes informações: ano de fabricação, placa do carro e nome do cliente
void mostraVendaPorModelo(struct CARRO carro, struct CLIENTE cliente)
{
    printf("\n\tANO DE FABRICACAO: %d", carro.ano_fabricacao);
    printf("\n\tPLACA DO CARRO: %s", carro.placa);
    printf("\n\tNOME DO CLIENTE: %s", cliente.nome);
}

// Lista os carros vendidos de um determinado fabricante, ordenados crescentemente pelo modelo
// Recebe os dados da função:
// void listarVendasModelosOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
void listarVendasPorFabricante(FILE *arquivoCarros, FILE *arquivoClientes)
{
    struct CARRO dadosCarro;
    struct CLIENTE dadosCliente;

    fseek(arquivoCarros, 0, SEEK_SET);
    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
            {
                printf("INFORMACOES DA VENDA:\n");
                mostraVendaPorFabricante(dadosCarro, dadosCliente);
                printf("\n\n-----------------------------------------------------------\n\n");
            }
        }
    } while (!feof(arquivoCarros) && !feof(arquivoClientes));
}

// Lista os carros vendidos de um determinado modelo, ordenados crescentemente pelo ano de fabricação
// Recebe dados da função:
// void listarVendasAnoFabricacaoOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
void listarVendasPorModelo(FILE *arquivoCarros, FILE *arquivoClientes)
{
    struct CARRO dadosCarro;
    struct CLIENTE dadosCliente;

    fseek(arquivoCarros, 0, SEEK_SET);
    fseek(arquivoClientes, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarros) > 0)
        {
            if (fread(&dadosCliente, sizeof(dadosCliente), 1, arquivoClientes) > 0)
            {
                printf("INFORMACOES DA VENDA:\n");
                mostraVendaPorModelo(dadosCarro, dadosCliente);
                printf("\n\n-----------------------------------------------------------\n\n");
            }
        }
    } while (!feof(arquivoCarros) && !feof(arquivoClientes));
}

// Lista os carros vendidos de um determinado fabricante, ordenados crescentemente pelo modelo
// Passa os dados para a função:
// void listarVendasPorFabricante(FILE *arquivoCarros, FILE *arquivoClientes)
void listarVendasModelosOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
{
    char *fileCarrosTemp = "carros.temp.dat";
    char *fileClientesTemp = "clientes.temp.dat";
    char *fileVendasTemp = "vendas.temp.dat";

    char *local = "void listarVendasModelosOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)";

    char nomeFabricante[20];

    if (quantidadeDadosArquivoVendas(arquivoVendas) > 0) // Verificar se existem vendas cadastradas
    {
        FILE *arquivoCarrosTemp = abreArquivo(fileCarrosTemp, "w+b", local);     // Abrir/Criar o arquivo
        FILE *arquivoClientesTemp = abreArquivo(fileClientesTemp, "w+b", local); // Abrir/Criar o arquivo
        FILE *arquivoVendasTemp = abreArquivo(fileVendasTemp, "w+b", local);     // Abrir/Criar o arquivo

        determinaFabricante(nomeFabricante);                                                        // Determina um fabricante informado pelo usuário
        separaCarrosPorFabricante(arquivoCarros, arquivoVendas, arquivoCarrosTemp, nomeFabricante); // Separar os cadastros dos carros que correspondem cm o fabricante informado

        if (quantidadeDadosArquivoCarros(arquivoCarrosTemp) > 0) // Verifica se existem carros vendidos do fabricante informado
        {
            separaVendasCorrespondente(arquivoCarrosTemp, arquivoVendas, arquivoVendasTemp);       // Separar as vendas que correspondem com os dados dos carros
            separaClientesCorrespondente(arquivoVendasTemp, arquivoClientes, arquivoClientesTemp); // Separar os clientes que correspondem com os dados das vendas
            system("clear");
            printf("\n\nFABRICANTE SELECIONADO: %s\n\n", nomeFabricante);
            listarVendasPorFabricante(arquivoCarrosTemp, arquivoClientesTemp);
        }
        else
            printf("\nNAO EXISTEM VENDAS DESTE FABRICANTE CADASTRADAS AINDA!");

        fechaArquivo(arquivoCarrosTemp, fileCarrosTemp, local);     // Fechar o arquivo
        fechaArquivo(arquivoClientesTemp, fileClientesTemp, local); // Fechar o arquivo
        fechaArquivo(arquivoVendasTemp, fileVendasTemp, local);     // Fechar o arquivo

        remove(fileCarrosTemp);   // Remover o arquivo
        remove(fileClientesTemp); // Remover o arquivo
        remove(fileVendasTemp);   // Remover o arquivo
    }
    else
        ERRO_VENDA;
}

// Lista os carros vendidos de um determinado modelo, ordenados crescentemente pelo ano de fabricação
// Passa os dados para a função:
// void listarVendasPorModelo(FILE *arquivoCarros, FILE *arquivoClientes)
void listarVendasAnoFabricacaoOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)
{
    char *fileCarrosTemp = "carros.temp.dat";
    char *fileClientesTemp = "clientes.temp.dat";
    char *fileVendasTemp = "vendas.temp.dat";

    char *local = "void listarVendasAnoFabricacaoOrdenados(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas)";

    char nomeModelo[20];

    if (quantidadeDadosArquivoVendas(arquivoVendas) > 0) // Verificar se existem vendas cadastradas
    {
        FILE *arquivoCarrosTemp = abreArquivo(fileCarrosTemp, "w+b", local);     // Abrir/Criar o arquivo
        FILE *arquivoClientesTemp = abreArquivo(fileClientesTemp, "w+b", local); // Abrir/Criar o arquivo
        FILE *arquivoVendasTemp = abreArquivo(fileVendasTemp, "w+b", local);     // Abrir/Criar o arquivo

        determinaModelo(nomeModelo);                                                        // Determina um modelo de carro informado pelo o usuário
        separaCarrosPorModelo(arquivoCarros, arquivoVendas, arquivoCarrosTemp, nomeModelo); // Separar os cadastros dos carros que correspondem com o modelo informado

        if (quantidadeDadosArquivoCarros(arquivoCarrosTemp) > 0) // verificar se existem carros vendidos do modelo informado
        {
            separaVendasCorrespondente(arquivoCarrosTemp, arquivoVendas, arquivoVendasTemp);       // Separar as vendas que correspondem com os dados dos carros
            separaClientesCorrespondente(arquivoVendasTemp, arquivoClientes, arquivoClientesTemp); // Separar os clientes que correspondem com os dados das vendas
            system("clear");
            printf("\n\nMODELO SELECIONADO: %s\n\n", nomeModelo);
            listarVendasPorModelo(arquivoCarrosTemp, arquivoClientesTemp);
        }
        else
            printf("\nNAO EXISTEM VENDAS DESTE MODELO CADASTRADAS AINDA!");

        fechaArquivo(arquivoCarrosTemp, fileCarrosTemp, local);     // Fechar o arquivo
        fechaArquivo(arquivoClientesTemp, fileClientesTemp, local); // Fechar o arquivo
        fechaArquivo(arquivoVendasTemp, fileVendasTemp, local);     // Fechar o arquivo

        remove(fileCarrosTemp);   // Remover o arquivo
        remove(fileClientesTemp); // Remover o arquivo
        remove(fileVendasTemp);   // Remover o arquivo
    }
    else
        ERRO_VENDA;
}

// Calcula o valor total das vendas
float determinaValorTotalVendas(FILE *arquivoVendas)
{
    int i = 0;
    float valoresVenda[TAM], totalValoresVendas = 0.0;
    struct VENDA_CARRO dadosVenda;

    fseek(arquivoVendas, 0, SEEK_SET);
    do
    {
        if (fread(&dadosVenda, sizeof(dadosVenda), 1, arquivoVendas) > 0)
            valoresVenda[i++] = dadosVenda.preco_venda;
    } while (!feof(arquivoVendas));

    for (i = 0; i < quantidadeDadosArquivoVendas(arquivoVendas); i++)
        totalValoresVendas += valoresVenda[i];

    return totalValoresVendas;
}

// Calcula o lucro total das vendas
float determinaLucroTotal(FILE *arquivoCarros, FILE *arquivoVendas)
{
    int i = 0;
    float valoresCarros[TAM], totalValoresCarros = 0.0, totalValoresVendas = 0.0;

    struct CARRO dadosCarro;

    char *fileCarrosVendidos = "./carros.vendidos.dat";
    char *local = "float determinaValorTotalVendas(FILE *arquivoCarros, FILE *arquivoVendas)";

    FILE *arquivoCarrosVendidos = abreArquivo(fileCarrosVendidos, "w+b", local); // Abre/Cria o arquivo

    separaCarrosVendas(arquivoCarros, arquivoVendas, arquivoCarrosVendidos); // Pega os cadastros dos carros vendidos

    fseek(arquivoCarrosVendidos, 0, SEEK_SET);
    do
    {
        if (fread(&dadosCarro, sizeof(dadosCarro), 1, arquivoCarrosVendidos) > 0)
            valoresCarros[i++] = dadosCarro.preco_compra;
    } while (!feof(arquivoCarrosVendidos));

    for (i = 0; i < quantidadeDadosArquivoCarros(arquivoCarrosVendidos); i++) // Realiza a somatória dos valores
        totalValoresCarros += valoresCarros[i];

    totalValoresVendas = determinaValorTotalVendas(arquivoVendas); // Pega o valor total das vendas para fazer a diferença

    fechaArquivo(arquivoCarrosVendidos, fileCarrosVendidos, local); // Fecha o arquivo

    remove(fileCarrosVendidos); // Remove o arquivo

    return (totalValoresVendas - totalValoresCarros); // Retorna o lucro total
}

// Informa a quantidade de carros vendidos e o valor total das vendas
void informaQuantidadePrecoVendas(FILE *arquivoVendas)
{
    int quantidadeCarrosVendidos = quantidadeDadosArquivoVendas(arquivoVendas); // Verificar se existem vendas cadastradas

    if (quantidadeCarrosVendidos > 0)
    {
        system("clear");
        printf("\nOPCAO: INFORMAR A QUANTIDADE DE CARROS VENDIDOS COM O VALOR TOTALIZADO DOS PRECOS VENDIDOS\n\n");
        printf("\nQUANTIDADE DE CARROS VENDIDOS: %d", quantidadeCarrosVendidos);
        printf("\nVALOR TOTAL DAS VENDAS: R$ %.2f REAIS", determinaValorTotalVendas(arquivoVendas));
    }
    else
        ERRO_VENDA;
}

// Informa o lucro total das vendas
void informaLucroTotalVendas(FILE *arquivoCarros, FILE *arquivoVendas)
{
    if (quantidadeDadosArquivoVendas(arquivoVendas) > 0) // Verificar se existem vendas cadastradas
    {
        system("clear");
        printf("\nOPCAO: INFORMAR O LUCRO TOTAL DAS VENDAS\n\n");
        printf("\nLUCRO TOTAL DAS VENDAS: R$ %.2f", determinaLucroTotal(arquivoCarros, arquivoVendas));
    }
    else
        ERRO_VENDA;
}

// Auxilia na exclusão do cadastro de uma venda
void realocaIndicesExcluirVendas(int IndiceVenda, FILE *arquivoVendas, char *fileVendas)
{
    struct VENDA_CARRO dadosVendas[TAM];

    char *local = "void realocaIndicesExcluirVendas(int IndiceVenda, FILE *arquivoVendas, char *fileVendas)";

    int tamanhoArquivoVendas, i;

    tamanhoArquivoVendas = quantidadeDadosArquivoVendas(arquivoVendas); // Pegar a quantidade de dados do arquivo
    leituraArquivoVenda(arquivoVendas, dadosVendas);                    // Ler o arquivo e passar os dados para o vetor de struct

    for (i = IndiceVenda; i < tamanhoArquivoVendas; i++)
        memcpy(&dadosVendas[i], &dadosVendas[i + 1], sizeof(dadosVendas[i])); // Realocar os indices do vetor de struct

    fechaArquivo(arquivoVendas, fileVendas, local);        // Fecha o arquivo
    arquivoVendas = abreArquivo(fileVendas, "w+b", local); // Abre/Cria o arquivo para reescrevver os dados nele

    tamanhoArquivoVendas--; // Reduz um índice

    copiaArquivoVenda(arquivoVendas, dadosVendas, tamanhoArquivoVendas); // Copiar os dados do vetor de struct para o arquivo
}

// Excluir uma venda do cadastro
void excluirVenda(FILE *arquivoCarros, FILE *arquivoVendas, char *fileVendas)
{
    char placaCarro[9];

    int verificadorCarro, verificadorVenda, posicaoVenda;

    if (quantidadeDadosArquivoVendas(arquivoVendas) > 0) // Verificar se existem vendas cadastradas
    {
        do
        {
            system("clear");
            printf("\nOPCAO: EXCLUIR UMA VENDA\n\n");
            printf("INFORME A PLACA DO CARRO REGISTRADO NA VENDA NO FORMATO (AAA-1234) OU (-1) PARA RETORNAR: ");
            scanf("%9s", placaCarro);

            if (placaCarro[0] == '-' && placaCarro[1] == '1')
                RETORNA;
            else
            {
                verificadorCarro = verificaExistenciaCarro(arquivoCarros, placaCarro);
                verificadorVenda = verificaExistenciaVendaCarro(arquivoVendas, placaCarro);
                if (!(verificadorCarro == 0 && verificadorVenda == 0))
                {
                    printf("\nPLACA INVALIDA!\nNAO FOI ENCONTRADO NENHUM CADASTRO.\n\n");
                    system("read -p \"Pressione enter\" saindo");
                }
            }
        } while ((placaCarro[0] != '-' && placaCarro[1] != '1') && !(verificadorCarro == 0 && verificadorVenda == 0));

        if (verificadorCarro == 0 && verificadorVenda == 0)
        {
            posicaoVenda = localizaPosicaoVendaArquivo(arquivoVendas, placaCarro); // Pagar a posição do cadastro da venda no arquivo
            realocaIndicesExcluirVendas(posicaoVenda, arquivoVendas, fileVendas);  // Realizar a exclusão da venda
            printf("\nVENDA EXCLUIDA COM SUCESSO!");
        }
    }
    else
        ERRO_VENDA;
}

// MENUS:

void menuCarro(FILE *arquivoCarros, FILE *arquivoVendas, char *fileCarros)
{
    int opc;
    do
    {
        system("clear");
        printf("OPCOES:\n\n1 - INSERIR UM CARRO NO CADASTRO\n2 - EXCLUIR UM CARRO DO CADASTRO");
        printf("\n3 - LISTAR OS CARROS DISPONIVEIS PARA A VENDA ORDENADOS CESCENTEMENTE POR FABRICANTES E MODELO");
        printf("\n4 - LISTAR OS CARROS DISPONIVEIS PARA A VENDA POR SELECAO DE UM OU MAIS OPICIONAIS");
        printf("\n5 - LISTAR OS CARROS DISPONIVEIS PARA A VENDA POR SELECAO DA FAIXA DE ANO ADE FABRICACAO");
        printf("\n0 - RETORNAR\n\nINFORME A SUA OPCAO: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 0:
            RETORNA;
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 1:
            cadastrosCarro(arquivoCarros);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 2:
            excluirCarro(arquivoCarros, arquivoVendas, fileCarros);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 3:
            listarCarrosFabricanteModeloOredenados(arquivoCarros, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 4:
            listarCarrosSelecaoOpcionais(arquivoCarros, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 5:
            listarCarrosSelecaoAnoFabricacao(arquivoCarros, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;

        default:
            ERRO_OPCAO;
            system("read -p \"Pressione enter\" saindo");
            break;
        }
    } while (opc != 0);
}

void menuCliente(FILE *arquivoClientes, FILE *arquivoVendas, char *fileClientes)
{
    int opc;
    do
    {
        system("clear");
        printf("OPCOES:\n\n1 - INSERIR UM CLIENTE NO CADASTRO\n2 - EXCLUIR UM CLIENTE DO CADASTRO");
        printf("\n3 - LISTAR OS CLIENTES NO CADASTRO ORDENADOS CRESCENTEMENTE PELO NOME");
        printf("\n4 - LISTAR OS CLIENTES NO CADASTRO ORDENADOS CRESCENTEMENTE PELO NOME POR SELECAO DE FAIXA DE RENDA SALARIAL MENSAL");
        printf("\n0 - RETORNAR\n\nINFORME A SUA OPCAO: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 0:
            RETORNA;
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 1:
            cadastrosCliente(arquivoClientes);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 2:
            excluirCliente(arquivoClientes, arquivoVendas, fileClientes);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 3:
            listarClientesNomesOrdenados(arquivoClientes);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 4:
            listarClientesSelecaoSalarial(arquivoClientes);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;

        default:
            ERRO_OPCAO;
            system("read -p \"Pressione enter\" saindo");
            break;
        }
    } while (opc != 0);
}

void menuVenda(FILE *arquivoCarros, FILE *arquivoClientes, FILE *arquivoVendas, char *fileVendas)
{
    int opc;
    do
    {
        system("clear");
        printf("OPCOES:\n\n1 - INSERIR UMA VENDA\n2 - EXCLUIR UMA VENDA");
        printf("\n3 - LISTAR OS CARROS VENDIDOS DE UM DETERMINADO FABRICANTE, ORDENADOS CRESCENTEMENTE PELO MODELO");
        printf("\n4 - LISTAR OS CARROS VENDIDOS DE UM DETERMINADO MODELO, ORDENADOS CRESCENTEMENTE PELO ANO DE FABRICACAO");
        printf("\n5 - INFORMAR A QUANTIDADE DE CARROS VENDIDOS COM O VALOR TOTALIZADO DOS PRECOS VENDIDOS");
        printf("\n6 - INFORMAR O LUCRO TOTAL DAS VENDAS\n0 - RETORNAR\n\nINFORME A SUA OPCAO: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 0:
            RETORNA;
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 1:
            inserirVenda(arquivoCarros, arquivoClientes, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 2:
            excluirVenda(arquivoCarros, arquivoVendas, fileVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 3:
            listarVendasModelosOrdenados(arquivoCarros, arquivoClientes, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 4:
            listarVendasAnoFabricacaoOrdenados(arquivoCarros, arquivoClientes, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 5:
            informaQuantidadePrecoVendas(arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;
        case 6:
            informaLucroTotalVendas(arquivoCarros, arquivoVendas);
            printf("\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;

        default:
            ERRO_OPCAO;
            system("read -p \"Pressione enter\" saindo");
            break;
        }
    } while (opc != 0);
}

void menuPrincipal(char *fileCarros, char *fileClientes, char *fileVendas)
{
    int opc;
    char *local = "void menuPrincipal(char *fileCarros, char *fileClientes, char *fileVendas)";
    FILE *arquivoCarros, *arquivoClientes, *arquivoVendas;

    if ((arquivoCarros = fopen(fileCarros, "r+b")) == NULL)
        arquivoCarros = abreArquivo(fileCarros, "w+b", local);

    if ((arquivoClientes = fopen(fileClientes, "r+b")) == NULL)
        arquivoClientes = abreArquivo(fileClientes, "w+b", local);

    if ((arquivoVendas = fopen(fileVendas, "r+b")) == NULL)
        arquivoVendas = abreArquivo(fileVendas, "w+b", local);

    do
    {
        system("clear");
        printf("OPCOES:\n\n1 - CARRO\n2 - CLIENTE\n3 - VENDA\n4 - SAIR DO PROGRAMA\n\nINFORME SUA OPCAO: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            system("clear");
            menuCarro(arquivoCarros, arquivoVendas, fileCarros);
            break;
        case 2:
            system("clear");
            menuCliente(arquivoClientes, arquivoVendas, fileClientes);
            break;
        case 3:
            system("clear");
            menuVenda(arquivoCarros, arquivoClientes, arquivoVendas, fileVendas);
            break;
        case 4:
            fechaArquivo(arquivoCarros, fileCarros, local);
            fechaArquivo(arquivoClientes, fileClientes, local);
            fechaArquivo(arquivoVendas, fileVendas, local);
            printf("\nOPERACAO FINALIZADA COM SUCESSO!\n\n");
            system("read -p \"Pressione enter\" saindo");
            break;

        default:
            ERRO_OPCAO;
            system("read -p \"Pressione enter\" saindo");
            break;
        }
    } while (opc != 4);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    char *fileCarros = "./cadastros.carros.dat";
    char *fileClientes = "./cadastros.clientes.dat";
    char *fileVendas = "./cadastros.vendas.dat";

    menuPrincipal(fileCarros, fileClientes, fileVendas);

    return 0;
}