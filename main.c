#include <stdio.h>
#include <stdlib.h>

char nome_prof[50];
char disciplina[50];

char adc_prof[50];

typedef struct professor{
    int matricula;
    char nome[50];
}Prof;

typedef struct disciplina{
    int num_disc;
    char nome_disc[50];
}Disciplina;

void inserir_professores(){
    FILE *p = fopen("professor.txt", "a");
    int opc;
    Prof profe;
    do{
        printf("Digite o numero e nome do professor\n");
        scanf(" %d", &profe.matricula);
        scanf(" %[^\n]", profe.nome);

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
    FILE *d = fopen("disciplina.txt", "a");
    Disciplina disc; 
    int opc;

    printf("Digite o numero e nome da disciplina\n");
    scanf(" %d", &disc.num_disc);
    scanf(" %[^\n]", disc.nome_disc);

     fwrite(&disc, sizeof(Disciplina), 1, d);

    fclose(d);
}
void remover_disciplinas(){
    FILE *d = fopen("disciplina.txt", "rb");
    int cont = 0;
    int n;

    Disciplina disc;
    Disciplina disciplinas = (Disciplina) malloc(sizeof(Disciplina));

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

}
void imprimir_associacoes(){

}
int main(){
    FILE *f = fopen("cadastro_professores.txt","a");

    int opc;
    int n=1;
    do{
        printf("Selecione a opção desejada:\n1- Inserir professor\n 2-Remover professor\n 3- Inserir disciplina\n 4- Remover disciplina\n 5-Associar professor a disciplina \n 6- Imprimir\n 7- Encerrar\n");
        scanf("%d", &opc);
        
        switch(opc){
            case 1:
                inserir_professores();
                n++;
                break;
            case 2:
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
                printf("Encerrando");
                break;
            default:
                printf("Opcao invalida!");
        }
        
    }while(opc!=7);
      
    return(0);
}