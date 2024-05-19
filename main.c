/******************************************************************************

Autor: Gilson Santos
Data: 19/05/2024

Calculadora Duty Cycle

Fórmula base: D = (Ton/T)*100

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void telaInicial();
void escolha();
void calcDuty();
void calcTon();
void calcPeriodo();
void printResult();
void verificaTon();     //Ton não pode ser maior que período(t)
void verificaDuty();    //Duty deve ser menor que 100

double freq;  //frequência
double ton;   //time on
double toff;  //time off
double t;     //período
double dut;   //duty cycle

int main()
{
    setlocale(LC_ALL,"pt-BR");    //Utilizando caracteres e acentuação da língua portuguesa
    char op;
    do{
    telaInicial();
    escolha();
    printResult();
    printf("\n\nContinuar?\nPressione 0 para encerrar ou qualquer outra tecla para continuar: ");
    scanf(" %c",&op);
    }while(op != '0');
    return 0;
}

void telaInicial()
{
    system("cls");
    printf("**************************\n");
    printf("* CALCULADORA DUTY CYCLE *\n");
    printf("**************************\n");
    printf("\nAlgoritmo para auxiliar no ajuste\nde Duty Cycle de conversores DC/DC,\nfontes chaveadas ou outras aplicacoes...\n\n");
}

void escolha()
{   int opcao;
    do{
        printf("O que deseja calcular?\n[1]duty cycle\n[2]ton\n[3]toff\n[4]periodo\n[5]frequencia: ");
        scanf("%d", &opcao);
        switch(opcao)
        {
            case 1:
                calcDuty();
            break;
            case 2:
                calcTon();
            break;
            case 3:
                calcDuty();     //Reaproveitando a função calcDuty()
            break;
            case 4:
                calcPeriodo();
            break;
            case 5:
                calcPeriodo();  //Reaproveitando a função calcPeriodo()
            break;
            default:
                printf("\n\nOpcão invalida\n\n");
        }
    }while ((opcao < 1)||(opcao > 5));
}

void calcDuty()
{
    printf("Informe a frequencia (em KHz): ");
    scanf("%lf",&freq);
    printf("Informe a largura do pulso (em microssegundos): ");
    scanf("%lf",&ton);
    ton /= 1000000;
    freq *= 1000;
    t = (1/freq);
    dut = (ton/t)*100;
    verificaTon();
    toff = t-ton;
}

void calcTon()
{
    printf("Informe a frequencia (em KHz): ");
    scanf("%lf",&freq);
    verificaDuty();
    freq *= 1000;
    t = 1/freq;
    ton = (dut/100)*t;
    verificaTon();
    toff = t-ton;
}

void calcPeriodo()
{
  printf("Informe a largura do pulso (em microssegundos): ");
  scanf("%lf",&ton);
  verificaDuty();
  ton /= 1000000;
  t = ton/(dut/100);
  freq = 1/t;
  verificaTon();
  toff = t-ton;
}

void printResult()
{
    system("cls");
    if(freq>=1000000)
    {
        freq /= 1000000;    //Convertendo de Hz para MHz
        ton *= 1000000000;  //Convertendo de segundos para microsegundos
        toff *= 1000000000;
        t *= 1000000000;
        printf("\nFrequencia: %.4lfMHz\nPeriodo: %.6lfnS\nTon: %lfnS\nToff: %lfnS\nDuty: %.2lf%%", freq, t, ton, toff, dut);
    }
    else
    {
        freq /= 1000;       //Convertendo de Hz para KHz
        ton *= 1000000;     //Convertendo de segundos para milisegundos
        toff *= 1000000;
        t *= 1000000;
        printf("\nFrequencia: %.4lfKHz\nPeriodo: %.6lfuS\nTon: %lfuS\nToff: %lfuS\nDuty: %.2lf%%", freq, t, ton, toff, dut);
    }
}

void verificaTon()
{
    if(ton>=t)
    {
        printf("Erro nos dados recebidos...\nO Programa sera encerrado...");
        exit(EXIT_FAILURE);
    }
}

void verificaDuty()
{
    do{
    printf("Informe o duty cycle desejado: ");
    scanf("%lf",&dut);
    if(dut>=100)
        printf("O Duty Cycle deve ser menor que 100\n");
    }while(dut>=100);
}




