//Faz a chamadas da bibliotecas utilizadas no projeto.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição das structs
typedef struct professor{
    int matricula;
    char nome[50];
    // mestrado, doutorado, graduação
    char maior_titulacao[50];
    //engenharia de software, rede de computadores.
    char area_pesquisa[50];
}Prof;

typedef struct disciplina{
    int num_disc;
    char nome_disc[50];
    int semestre;
    int creditos;
}Disciplina;

typedef struct associado{
    int mat_prof;
    int num_disc;
}Associado;

/*void aloca(Associado **associacao){
        *associacao= (Associado *) realloc(*associacao, sizeof(Associado)*strlen(*associacao)+2);
        if(*associacao == NULL){
            puts("** Memoria insuficiente**");
            exit(0);
        }
    }*/

void inserir_professores(){
    FILE *p = fopen("professor.txt", "ab");
    int opc;
    Prof profe;
    do{
        printf("Digite a matricula, nome, maior titulação e area de pesquisa do professor\n");
        scanf(" %d", &profe.matricula);
        scanf(" %[^\n]", profe.nome);
        scanf(" %[^\n]", profe.maior_titulacao);
        scanf(" %[^\n]", profe.area_pesquisa);

        fwrite(&profe, sizeof(Prof), 1, p);

        printf("Deseja adicionar outro?\n 1- sim \n 0- nao");
        scanf("%d", &opc);
    }while(opc != 0);

    fclose(p);
}
void remover_professores(){
    FILE *pr = fopen("professor.txt","rb");
    int opc;
    int cont=0;
    int mat;
    Prof profe;
    Prof *profs = (Prof *) malloc(sizeof(Prof));
    
    printf("Digite a matricula do professor que deseja remover.\n");
    scanf(" %d", &mat);

        
    while(fread(&profe,sizeof(Prof), 1, pr)){
        if(profe.matricula != mat){
            *(profs+cont) = profe;
            cont++;
            profs = (Prof *) realloc(profs, (cont+1)*sizeof(Prof));
        }   
    }
    fclose(pr);

    FILE *pw = fopen("professor.txt", "wb");
    for(int i=0; i<cont; i++){
       fwrite(profs+i, sizeof(Prof), 1, pw); 
    }
    fclose(pw);
}
void inserir_disciplinas(){
    FILE *d = fopen("disciplina.txt", "ab");
    Disciplina disc; 
    int opc;

    printf("Digite o numero, nome, semestre e creditos da disciplina\n");
    scanf(" %d", &disc.num_disc);
    scanf(" %[^\n]", disc.nome_disc);
    scanf(" %d", &disc.semestre);
    scanf(" %d", &disc.creditos);
     fwrite(&disc, sizeof(Disciplina), 1, d);

    fclose(d);
}
void remover_disciplinas(){
    FILE *d = fopen("disciplina.txt", "rb");
    int cont = 0;
    int n;

    Disciplina disc;
    Disciplina *disciplinas =  malloc(sizeof(Disciplina));

    printf("Digite o numero da disciplina a ser removida.");
    scanf("%d", &n);

    while(fread(&disc,sizeof(Disciplina), 1, d)){
        if(disc.num_disc != n){
            *(disciplinas+cont) = disc;
            cont++;
            disciplinas = (Disciplina *) realloc(disciplinas, (cont+1)*sizeof(Disciplina));
        }
    }
    fclose(d);

    FILE *dw = fopen("disciplina.txt", "wb");
    for(int i=0; i<cont; i++){
       fwrite(disciplinas+i, sizeof(Disciplina), 1, dw); 
    }
    fclose(dw);
}
void associar_diciplinas(){
    
    //criacao do arquivo de associacao do prof e da disc.
    FILE *p_m = fopen("associacao.txt", "ab");

    //leitura dos arquivos existentes.
    FILE *pr = fopen("professor.txt", "rb");
    FILE *dr = fopen("disciplina.txt", "rb");

    //estrutura que contém todos os dados de professor e disciplina reunidos.
    Associado associado;
    Disciplina disc;
    Prof profe;

    int mat_prof, num_disciplina;

    printf("\nDigite a matricula do professor e o numero da disciplina que quer associar.\n");
    scanf("%d %d", &mat_prof, &num_disciplina);

    while(fread(&profe,sizeof(Prof), 1, pr)){
        if(profe.matricula == mat_prof){
            associado.mat_prof = mat_prof;
        }   
    }
    while(fread(&disc,sizeof(Disciplina), 1, dr)){
        if(disc.num_disc==num_disciplina){
             associado.num_disc = num_disciplina;
        }
    }
     fwrite(&associado, sizeof(Associado), 1, p_m);

    fclose(p_m);
    fclose(pr);
    fclose(dr);

}
void imprimir_associacoes(){
    FILE *p_m = fopen("associacao.txt", "rb");
    FILE *pr = fopen("professor.txt", "rb");
    FILE *dr = fopen("disciplina.txt", "rb");

    Disciplina disc;
    Prof profe;
    Associado associado;
    Associado *associacao = (Associado *) malloc(sizeof(Associado));

    int cont = 0;
    int conte = 0;
    while(fread(&associado,sizeof(Associado), 1, p_m)){
            *(associacao+cont) = associado;
            cont++;
            associacao = (Associado *) realloc(associacao, (cont+1)*sizeof(Associado));
            //aloca(associacao);
        }
        
    
    do {
        int temp;
        fscanf(p_m, "%d", &temp);
        fread(&associado,sizeof(Associado), 1, p_m); printf("Nome: %s \n", profe.nome);
        printf("Disciplina: %s \n", disc.nome_disc);
        
        
    } while (!feof(p_m)); // enquanto não chegar ao final do arquivo

    
    
    free(associacao);
    fclose(pr);
    fclose(p_m);
    fclose(dr);
}
int main(){
    //Variável responsável por armazenar a opção do usuário
    int opc;
    do{
        //Cria o menu de opção e ler o valor
        printf("Selecione a opcao desejada:\n1- Inserir professor\n 2-Remover professor\n 3- Inserir disciplina\n 4- Remover disciplina\n 5-Associar professor a disciplina \n 6- Imprimir\n 7- Encerrar\n");
        scanf("%d", &opc);
        
        //Verifica qual opção foi passada pelo usuário e verifica dentro de um switch
        switch(opc){
            case 1:
                //Chamada a função de inserir professores
                inserir_professores();
                break;
            case 2:
                //Chamada a função de remover professores
                remover_professores();
                break;
            case 3:
                inserir_disciplinas();
                break;
            case 4:
                remover_disciplinas();
                break;
            case 5:
                associar_diciplinas();
                break;
            case 6:
                imprimir_associacoes();
                break;
            case 7:
                //Encerra o programa
                printf("Encerrando");
                break;
            default:
                //Cai aqui caso o usuário digite algum valor inválido
                printf("Opcao invalida!\n");
        }
        
    }while(opc!=7);
      
    return(0);
}
