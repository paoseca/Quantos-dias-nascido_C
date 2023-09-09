#include <stdio.h>
#include <locale.h>

int restoSemSinal(int a, int b)
{
    return (a >= 0L
                ? a % b               // Positivo.
                : (b + (a % b)) % b); // Negativo.
}

int divisaoSemSinal(int a, int b)
{
    return a >= 0L
               ? a / b
               : (a / b) - (a % b == 0 ? 0 : 1);
}

int contarDiasDesde1970(int dia, int mes, int ano)
{
    int anosDesde1970 = ano - 1970;

    int periodosDe400Anos = divisaoSemSinal(anosDesde1970, 400);
    int anoNoPeriodoDe400Anos = restoSemSinal(anosDesde1970, 400);

    int periodosDe4AnosNos400 = anoNoPeriodoDe400Anos / 4;
    int anoNoPeriodoDe4Anos = anoNoPeriodoDe400Anos % 4;

    // Passo 4.
    int diasNosAnosAnterioresDoPeriodoDe4Anos = 365 * anoNoPeriodoDe4Anos + (anoNoPeriodoDe4Anos == 3 ? 1 : 0);

    // Passo 5.
    int diasNoAno = dia - 1;
    int tabelaDeMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i;
    for (i = 0; i < mes - 1; i++)
    {
        diasNoAno += tabelaDeMeses[i];
    }

    // Passo 6.
    int dias = diasNoAno + diasNosAnosAnterioresDoPeriodoDe4Anos + periodosDe4AnosNos400 * 1461 + periodosDe400Anos * 146097;

    if (anoNoPeriodoDe4Anos == 2 && mes > 2)
        dias++;
    if (anoNoPeriodoDe400Anos > 130 || (anoNoPeriodoDe400Anos == 130 && mes > 2))
        dias--;
    if (anoNoPeriodoDe400Anos > 230 || (anoNoPeriodoDe400Anos == 230 && mes > 2))
        dias--;
    if (anoNoPeriodoDe400Anos > 330 || (anoNoPeriodoDe400Anos == 330 && mes > 2))
        dias--;
    return dias;
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    int diaNascimento, diaHoje, mesNascimento, mesHoje, anoNascimento, ano_atual;

    printf("Digite o dia que você nasceu:\n");
    scanf("%d", &diaNascimento);
    printf("Digite o mês que você nasceu:\n");
    scanf("%d", &mesNascimento);
    printf("Digite o ano que você nasceu:\n");
    scanf("%d", &anoNascimento);
    printf("Digite o dia (data de hoje):\n");
    scanf("%d", &diaHoje);
    printf("Digite o mês (data de hoje):\n");
    scanf("%d", &mesHoje);
    printf("Digite o ano (data de hoje):\n");
    scanf("%d", &ano_atual);

    int nascimento = contarDiasDesde1970(diaNascimento, mesNascimento, anoNascimento);
    int hoje = contarDiasDesde1970(diaHoje, mesHoje, ano_atual);
    int diasDeVida = hoje - nascimento;

    printf("Dias: %d", diasDeVida);

    return 0;
}