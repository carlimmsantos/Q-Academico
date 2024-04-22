#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura dos discentes
typedef struct {
    long int matricula;
    char nome[40];
    double nota1, nota2, nota3;
    double recuperacao;
    double media;
    char situacao[20];
} rMatricula;

// Função responsável por imprimir na tela
void ImprimeDiscente(rMatricula aluno) {
    if (aluno.recuperacao < 0.01) {
        printf("\t%-12ld %-20s %-6.1f %-6.1f %-6.1f %-11s %-6.1f %-10s\n",
               aluno.matricula, aluno.nome, aluno.nota1, aluno.nota2, aluno.nota3, "-", aluno.media, aluno.situacao);
    } else {
        printf("\t%-12ld %-20s %-6.1f %-6.1f %-6.1f %-11.1f %-6.1f %-10s\n",
               aluno.matricula, aluno.nome, aluno.nota1, aluno.nota2, aluno.nota3, aluno.recuperacao, aluno.media, aluno.situacao);
    }
}

// Função que faz a leitura dos dados da Matricula e aluno
rMatricula *LeDiscente(rMatricula *retorno) {
    printf("\nMatricula do aluno: ");
    scanf("%ld", &retorno->matricula);
    getchar();
    printf("\nNome do aluno: ");
    fgets(retorno->nome, sizeof(retorno->nome), stdin);
   
    if (retorno->nome[strlen(retorno->nome) - 1] == '\n') {
        retorno->nome[strlen(retorno->nome) - 1] = '\0';
    }
    return retorno;
}

// Função que faz a leitura das notas
rMatricula *LeNotas(rMatricula *retorno) {
    printf("\nCadastrando as notas de %s.\n", retorno->nome);
    printf("Primeira nota: ");
    scanf("%lf", &retorno->nota1);
    printf("Segunda nota: ");
    scanf("%lf", &retorno->nota2);
    printf("Terceira nota: ");
    scanf("%lf", &retorno->nota3);
   
   
    return retorno;
}

// Função que faz leitura da recuperação
rMatricula *LeRecuperacao(rMatricula *retorno) {
    printf("Nota recuperacao: ");
    scanf("%lf", &retorno->recuperacao);
   
    return retorno;
}

// Função que calcula a média
double Media(rMatricula aluno) {
    return (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
}

// Função que calcula a média final
double MediaFinal(rMatricula aluno) {
    return (aluno.media * 6 + aluno.recuperacao * 4) / 10;
}

// Função responsavel pelo salvamentos dos discente
void SalvarArquivo (rMatricula alunos[], int qntAlunos){

    FILE *fp = fopen("matricula.txt", "w+");
   
    if (!fp) {
        puts("Erro ao abrir o arquivo!");
    } else {
       
        for (int i = 0; i < qntAlunos; i++) {
           
            fprintf(fp, "%ld %s %s\n", alunos[i].matricula, alunos[i].nome, alunos[i].situacao);
            fprintf(fp, "%lf %lf %lf %lf %lf\n", alunos[i].nota1, alunos[i].nota2, alunos[i].nota3, alunos[i].media, alunos[i].recuperacao);
            }
    }
}

//Função responsavel pela entrada dos discente

void LerArquivo(rMatricula alunos[], int *valor){

    FILE *fp = fopen("matricula.txt", "r");
   
    if (!fp) {
        puts("Erro ao abrir as matriculas o arquivo!");
    }
        int aux = 0;
        while(1){
           
            if ( aux >= 30){
                puts("Chegamos ao limite de alunos");
                break;
            }

            if (fscanf(fp, "%ld %s %s", &alunos[aux].matricula, alunos[aux].nome, alunos[aux].situacao) != 3) {
               
            break;
            }
       
            if (fscanf(fp, "%lf %lf %lf %lf %lf", &alunos[aux].nota1, &alunos[aux].nota2, &alunos[aux].nota3, &alunos[aux].media, &alunos[aux].recuperacao) != 5) {
            puts("Erro ao ler as notas!");
            break;
            }

            aux++;}

            *valor = aux;
}



int main() {
    char disciplina[50], resposta[6];
    int qntAlunos, aux = 0;
    rMatricula alunos[30];
   
    puts("---------------Fase 1--------------\n");
   
    printf("----Bem-vindo(a) ao Qacademico----\n\n");
   
    printf("Deseja continuar o arquivo antigo, sim ou nao? ");
    scanf ("%s", resposta);
    getchar();

    if (strcmp (resposta, "sim") == 0){
    LerArquivo(alunos, &aux);
    }
    

    printf("Digite nome da disciplina: ");
    fgets(disciplina, sizeof(disciplina), stdin);
   
    if (disciplina[strlen(disciplina) - 1] == '\n') {
        disciplina[strlen(disciplina) - 1] = '\0';
    }
   
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &qntAlunos);
   
   
    puts("\n---------------Fase 2---------------");
    for (int i = aux; i < qntAlunos + aux; i++) {
        LeDiscente(&alunos[i]);
        alunos[i].recuperacao = 0.001;
    }

    puts("\n---------------Fase 3---------------\n");
    for (int i = aux; i < qntAlunos + aux; i++) {
        LeNotas(&alunos[i]);
        alunos[i].media = Media(alunos[i]);
       
        if (alunos[i].media >= 4.0 && alunos[i].media < 7.0) {
            puts("");
            printf("O aluno %s nao atingiu a media, ficou com %.2lf e esta em recuperacao.\n", alunos[i].nome, alunos[i].media);
            LeRecuperacao(&alunos[i]);
            alunos[i].media = MediaFinal(alunos[i]);
           
            if (alunos[i].media >= 5.0) {
                strcpy(alunos[i].situacao, "Aprovado");
            }
             else {
                printf("O aluno %s teve media %.2lf e foi reprovado!\n", alunos[i].nome, alunos[i].media);
                strcpy(alunos[i].situacao, "Reprovado");
            }
        }

        else if (alunos[i].media < 4.0) {
            printf("O aluno %s teve media %.2lf e foi reprovado!\n", alunos[i].nome, alunos[i].media);
            strcpy(alunos[i].situacao, "Reprovado");
        }

        else {
            strcpy(alunos[i].situacao, "Aprovado");
        }
    }
   
    qntAlunos += aux;
    puts("\n");
    puts("\t-----------------------------------------------------");
    printf("\tRelatorio de Alunos da Disciplina: %s\n", disciplina);
    puts("\t-----------------------------------------------------");
   
    puts("\n");
    printf("\t%-12s %-20s %-6s %-6s %-6s %-11s %-6s %-10s\n", "Matricula", "Nome", "Nota1", "Nota2", "Nota3", "Recuperacao", "Media", "Situacao");

    printf("\t-----------------------------------" "-------------------" "------" "------" "------" "-----------" "------" "---------\n");
   
    for (int i = 0; i < qntAlunos; i++) {
        ImprimeDiscente(alunos[i]);
    }
   
 
    SalvarArquivo(alunos, qntAlunos);

    return 0;
}