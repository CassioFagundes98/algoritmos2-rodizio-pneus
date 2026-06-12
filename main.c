#include <stdio.h>
#include <string.h>

typedef struct
{
    int tipoVeiculo;
    int linhas;
    int colunas;
    int pneus[4][2];
} Veiculo;

/* PROTOTIPOS */
int login();
void escolherVeiculo(Veiculo *v);
void cadastrarPneus(Veiculo *v);
void mostrarPneus(Veiculo v);
void realizarRodizio(Veiculo *v);
void mostrarLegenda(Veiculo v);
int verificarNumeroRepetido(Veiculo v, int numero);

/* MAIN */
int main()
{
    Veiculo veiculo;
    int opcao;

    if (!login())
    {
        printf("\nAcesso negado!\n");
        return 0;
    }

    escolherVeiculo(&veiculo);

    do
    {
        printf("\n=====================================\n");
        printf("     SISTEMA CONTROLE DE PNEUS\n");
        printf("=====================================\n");
        printf("1 - Cadastrar Pneus\n");
        printf("2 - Mostrar Pneus\n");
        printf("3 - Realizar Rodizio\n");
        printf("4 - Mostrar Legenda\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                cadastrarPneus(&veiculo);
                break;

            case 2:
                mostrarPneus(veiculo);
                break;

            case 3:
                realizarRodizio(&veiculo);
                break;

            case 4:
                mostrarLegenda(veiculo);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

/* LOGIN */
int login()
{
    char usuario[20];
    char senha[20];

    printf("=====================================\n");
    printf("     SISTEMA CONTROLE DE PNEUS\n");
    printf("=====================================\n");

    printf("Login: ");
    scanf("%s", usuario);

    printf("Senha: ");
    scanf("%s", senha);

    if(strcmp(usuario, "uniavan") == 0 &&
       strcmp(senha, "123") == 0)
    {
        return 1;
    }

    return 0;
}

/* ESCOLHER VEICULO */
void escolherVeiculo(Veiculo *v)
{
    int opcao;

    printf("\nEscolha o tipo de veiculo:\n");
    printf("1 - Truck\n");
    printf("2 - Toco\n");
    printf("3 - Carreta 3 Eixos\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    v->tipoVeiculo = opcao;

    switch(opcao)
    {
        case 1:
            v->linhas = 2;
            v->colunas = 2;
            break;

        case 2:
            v->linhas = 3;
            v->colunas = 2;
            break;

        case 3:
            v->linhas = 4;
            v->colunas = 2;
            break;

        default:
            printf("Opcao invalida! Definido Truck.\n");
            v->linhas = 2;
            v->colunas = 2;
    }
}

/* VERIFICAR REPETIDO */
int verificarNumeroRepetido(Veiculo v, int numero)
{
    int i, j;

    for(i = 0; i < v.linhas; i++)
    {
        for(j = 0; j < v.colunas; j++)
        {
            if(v.pneus[i][j] == numero)
            {
                return 1;
            }
        }
    }

    return 0;
}

/* CADASTRAR PNEUS */
void cadastrarPneus(Veiculo *v)
{
    int i, j;
    int numero;

    printf("\n=== CADASTRO DE PNEUS ===\n");

    for(i = 0; i < v->linhas; i++)
    {
        for(j = 0; j < v->colunas; j++)
        {
            do
            {
                printf("Numero do pneu [%d][%d]: ",
                       i + 1, j + 1);

                scanf("%d", &numero);

                if(verificarNumeroRepetido(*v, numero))
                {
                    printf("Numero ja cadastrado!\n");
                }

            } while(verificarNumeroRepetido(*v, numero));

            v->pneus[i][j] = numero;
        }
    }

    printf("\nCadastro concluido!\n");
}

/* MOSTRAR PNEUS */
void mostrarPneus(Veiculo v)
{
    int i, j;

    printf("\n=== POSICAO DOS PNEUS ===\n");

    for(i = 0; i < v.linhas; i++)
    {
        for(j = 0; j < v.colunas; j++)
        {
            printf("%8d", v.pneus[i][j]);
        }

        printf("\n");
    }
}

/* RODIZIO */
void realizarRodizio(Veiculo *v)
{
    int l1, c1;
    int l2, c2;
    int aux;

    printf("\n=== RODIZIO DE PNEUS ===\n");

    printf("Primeiro pneu\n");
    printf("Linha: ");
    scanf("%d", &l1);
    printf("Coluna: ");
    scanf("%d", &c1);

    printf("\nSegundo pneu\n");
    printf("Linha: ");
    scanf("%d", &l2);
    printf("Coluna: ");
    scanf("%d", &c2);

    l1--;
    c1--;
    l2--;
    c2--;

    if(l1 < 0 || l1 >= v->linhas ||
       l2 < 0 || l2 >= v->linhas ||
       c1 < 0 || c1 >= v->colunas ||
       c2 < 0 || c2 >= v->colunas)
    {
        printf("\nPosicao invalida!\n");
        return;
    }

    aux = v->pneus[l1][c1];
    v->pneus[l1][c1] = v->pneus[l2][c2];
    v->pneus[l2][c2] = aux;

    printf("\nRodizio realizado com sucesso!\n");
}

/* LEGENDA */
void mostrarLegenda(Veiculo v)
{
    printf("\n=== LEGENDA ===\n");

    if(v.tipoVeiculo == 1)
    {
        printf("[1][1] Dianteiro Esquerdo\n");
        printf("[1][2] Dianteiro Direito\n");
        printf("[2][1] Traseiro Esquerdo\n");
        printf("[2][2] Traseiro Direito\n");
    }
    else if(v.tipoVeiculo == 2)
    {
        printf("Linha 1 = Eixo Dianteiro\n");
        printf("Linha 2 = Eixo Central\n");
        printf("Linha 3 = Eixo Traseiro\n");
    }
    else
    {
        printf("Linha 1 = Eixo Dianteiro\n");
        printf("Linha 2 = Eixo 1\n");
        printf("Linha 3 = Eixo 2\n");
        printf("Linha 4 = Eixo 3\n");
    }
}
