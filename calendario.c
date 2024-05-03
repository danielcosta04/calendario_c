#include <stdio.h>

// Definição de constantes para os meses e dias da semana
#define MESES 12
#define DIAS_SEMANA 7
#define DIAS_ANO 366

// Função para exibir o calendário
void mostrarCalendario(int ano, int dia_semana_inicio, int dias_fevereiro);

// Função para inserir agendamentos
void inserirAgendamentos(int ano, int calendario_agendamentos[], int bissexto);

// Função para exibir o calendário com agendamentos
void mostrarCalendarioAgendamentos(int ano, int calendario_agendamentos[], int dias_fevereiro, int dia_semana_inicio);

int main() {
    int ano, dia_semana_inicio;

    // Solicitar ao usuário o dia da semana em que 1º de janeiro cai e se o ano é bissexto ou não
    printf("Digite o dia da semana em que 1º de janeiro cai (0 - Domingo, 1 - Segunda, 2 - terça, 3 - quarta, 4 - quinta, 5 - sexta, 6 - Sábado): ");
    scanf("%d", &dia_semana_inicio);

    printf("Digite o ano: ");
    scanf("%d", &ano);

    // Solicitar ao usuário se o ano é bissexto ou não
    int bissexto;
    printf("O ano é bissexto? (0 - Não, 1 - Sim): ");
    scanf("%d", &bissexto);

    // Ajustar o número de dias de fevereiro se o ano for bissexto
    int dias_fevereiro = (bissexto == 1) ? 29 : 28;

    // Chamar função para exibir o calendário
    mostrarCalendario(ano, dia_semana_inicio, dias_fevereiro);

    int calendario_agendamentos[DIAS_ANO] = {0};

    // Loop do menu
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Mostrar o calendário\n");
        printf("2. Inserir agendamentos\n");
        printf("3. Mostrar o calendário com agendamentos\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarCalendario(ano, dia_semana_inicio, dias_fevereiro);
                break;
            case 2:
                inserirAgendamentos(ano, calendario_agendamentos, bissexto);
                break;
            case 3:
                mostrarCalendarioAgendamentos(ano, calendario_agendamentos, dias_fevereiro, dia_semana_inicio);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

void mostrarCalendario(int ano, int dia_semana_inicio, int dias_fevereiro) {
    int dias_mes[MESES] = {31, dias_fevereiro, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *nomes_meses[MESES] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    printf("*** CALENDÁRIO ***\n");

    for (int mes = 0; mes < MESES; mes++) {
        printf("\n%s\n", nomes_meses[mes]);
        printf("Dom Seg Ter Qua Qui Sex Sab\n");

        // Espaços iniciais para ajustar o dia da semana em que o mês começa
        for (int i = 0; i < dia_semana_inicio; i++) {
            printf("    ");
        }

        // Preenchimento dos dias do mês
        for (int dia = 1; dia <= dias_mes[mes]; dia++) {
            printf("%3d ", dia);

            // Nova linha para o próximo dia da semana
            if ((dia + dia_semana_inicio) % DIAS_SEMANA == 0 || dia == dias_mes[mes]) {
                printf("\n");
            }
        }

        // Atualizar o dia da semana para o próximo mês
        dia_semana_inicio = (dia_semana_inicio + dias_mes[mes]) % DIAS_SEMANA;
    }
}

void inserirAgendamentos(int ano, int calendario_agendamentos[], int bissexto) {
    int mes, dia, duracao;
    int dias_mes[MESES] = {31, bissexto == 1 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("Digite o mês (1-12): ");
    scanf("%d", &mes);
    printf("Digite o dia (1-31): ");
    scanf("%d", &dia);
    printf("Digite a duração do agendamento: ");
    scanf("%d", &duracao);

    // Verificar se o mês é válido
    if (mes < 1 || mes > MESES) {
        printf("Mês inválido!\n");
        return;
    }

    // Verificar se o dia é válido para o mês
    if (dia < 1 || dia > dias_mes) {
        printf("Dia inválido para este mês!\n");
        return;
    }

    // Calcular o índice do dia no array de agendamentos
    int indice_dia = dia - 1;

    if (mes != 1)  {
        for (int i = 0; i < mes - 1; i++) {
            indice_dia += dias_mes[i];
        }
    }

    // Verificar se há espaço para o agendamento nos dias selecionados
    for (int i = indice_dia; i < indice_dia + duracao; i++) {
        if (calendario_agendamentos[i] >= 5) {
            printf("Não é possível agendar neste dia. Limite de pacientes excedido.\n");
            return;
        }
    }

    // Marcar os dias do agendamento
    for (int i = indice_dia; i < indice_dia + duracao; i++) {
        calendario_agendamentos[i]++;
    }
    printf("Agendamento inserido com sucesso!\n");
}

void mostrarCalendarioAgendamentos(int ano, int calendario_agendamentos[], int dias_fevereiro, int dia_semana_inicio) {
    int dias_mes[MESES] = {31, dias_fevereiro, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *nomes_meses[MESES] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    printf("*** CALENDÁRIO ***\n");

    int ultimo_dia_mes_anterior = 0;

    for (int mes = 0; mes < MESES; mes++) {
        printf("\n%s\n", nomes_meses[mes]);
        printf("Dom Seg Ter Qua Qui Sex Sab\n");

        // Espaços iniciais para ajustar o dia da semana em que o mês começa
        for (int i = 0; i < dia_semana_inicio; i++) {
            printf("    ");
        }

        // Preenchimento dos dias do mês
        for (int dia = 1; dia <= dias_mes[mes]; dia++) {
            int quantidade_agendamentos_dia_atual = calendario_agendamentos[(dia + ultimo_dia_mes_anterior) - 1];
            printf("%3d ", quantidade_agendamentos_dia_atual);

            // Nova linha para o próximo dia da semana
            if ((dia + dia_semana_inicio) % DIAS_SEMANA == 0 || dia == dias_mes[mes]) {
                printf("\n");
            }

            if (dia == dias_mes[mes]) {
                ultimo_dia_mes_anterior += dia;
            }
        }

        // Atualizar o dia da semana para o próximo mês
        dia_semana_inicio = (dia_semana_inicio + dias_mes[mes]) % DIAS_SEMANA;
    }
}
