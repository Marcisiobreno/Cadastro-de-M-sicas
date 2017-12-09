#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

enum Opcao{
	ADICAO=1,   //1
	REMOCAO,    //2
	ALTERACAO,  //3
	BUSCA,      //4
	AJUDA,      //5
	SAIDA       //6
};

enum Retornos{
    SUCESSO=1,
    ARQUIVO_INEXISTENTE,
    MUSICA_JA_EXISTE,
    NADA_FOI_ENCONTRADO,

};

struct Musica{
    char nome[30];
	char artista[20];
	char album[30];
	char genero[15];
	unsigned int ano;
	char duracao[6];
};

enum Retornos adicao(){
	int opcao,i,tam;
    do{
        system("cls");

		struct Musica aux;

        fflush(stdin);
        printf("Digite o nome da m�sica: \n");
		scanf("%s",&aux.nome);

        FILE *file;
        file=fopen("musicas.db", "ab+");

		fseek(file,0,SEEK_END);

		tam = ftell(file);
		tam = tam/sizeof(struct Musica);

		fseek(file,0,SEEK_SET);

    	struct Musica mzk[tam];

		for(i=0;i<tam;i++){
	    	fread(&mzk[i], sizeof(struct Musica),1,file);
			if(strcmp(mzk[i].nome,aux.nome)==0){
				printf("\t\tESTA M�SICAS J� EXISTE\n");
				system("pause");
				return MUSICA_JA_EXISTE;
			}
        }

		fflush(stdin);
		printf("Digite o artista da m�sica: \n");
		scanf("%s",&aux.artista);

		fflush(stdin);
		printf("Digite o nome do �lbum: \n");
		scanf("%s",&aux.album);

		fflush(stdin);
		printf("Digite o g�nero da m�sica: \n");
		scanf("%s",&aux.genero);

		fflush(stdin);
		printf("Digite o ano em que ela foi lan�ada (aaaa): \n");
		scanf("%i",&aux.ano);

		fflush(stdin);
		printf("Digite sua dura��o (mm:ss): \n");
        scanf("%s",&aux.duracao);

        fseek(file,0,SEEK_END);

		fwrite(&aux,sizeof(struct Musica),1,file);

        system("cls");

        printf("\n\nM�SICA ADICIONADA COM SUCESSO\n\n");
        printf("Escolha uma das op��es abaixo\n");
		printf("1 - Continuar inserindo m�sicas\n0 - Sair\n");
		printf("Escolha feita: \n");

        scanf("%i",&opcao);
        fclose(file);
	}while(opcao==1);
        return SUCESSO;
}

enum Retornos remocao(){
    system("cls");

	int tam,i,j=0;
	char nome_comp[30];

	FILE*file;
	file=fopen("musicas.db","rb");

	if(file==NULL){
        printf("ARQUIVO INEXISTENTE\n");
        return ARQUIVO_INEXISTENTE;
        getch();
    }

	fseek(file,0,SEEK_END);
	tam = ftell(file);
	tam = tam / sizeof(struct Musica);
	fseek(file,0,SEEK_SET);

	struct Musica aux[tam];
	struct Musica final[tam];

	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct Musica),1,file);
	}

    printf("\nDigite o nome da m�sica que ser� removida: ");
    scanf("%s",&nome_comp);

    for(i=0;i<tam;i++){
        if(strcmp(aux[i].nome,nome_comp) == 0){
		}else{
				final[j]=aux[i];
				j++;
			}
        }

       for(i=0;i<tam;i++){
        if(strcmp(aux[i].nome,nome_comp) == 0){

    		freopen("musicas.db","w+b",file);

    		for(i=0;i<tam-1;i++){
    		fwrite(&final[i], sizeof(struct Musica),1,file);
    		}
    		printf("\n\t\tREMO��O REALIZADA COM SUCESSO\n");
    		system("pause");
    		return SUCESSO;
		}
}
	fclose(file);
	printf("NADA FOI ENCONTRADO\n");
	return NADA_FOI_ENCONTRADO;
       getch();
}

enum Retornos alteracao(){
    system("cls");

	int tam,i,opcao;
	char nome_comp[30];

	FILE*file;
	file=fopen("musicas.db","rb");

	if(file==NULL){
        printf("ARQUIVO INEXISTENTE\n");
        getch();
        return ARQUIVO_INEXISTENTE;
    }

	fseek(file,0,SEEK_END);
	tam = ftell(file);
	tam = tam / sizeof(struct Musica);
	fseek(file,0,SEEK_SET);

	struct Musica aux[tam];

	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct Musica),1,file);
	}

    printf("\nDigite o nome da m�sica que ser� alterada: ");
    scanf("%s",&nome_comp);

    for(i=0;i<tam;i++){
		if(strcmp(aux[i].nome,nome_comp)==0){

            printf("O que deseja alterar?\n");
            printf("1 - Nome\n");
            printf("2 - Artista\n");
            printf("3 - �lbum\n");
            printf("4 - G�nero\n");
            printf("5 - Ano\n");
            printf("6 - Dura��o\n");
            scanf("%i",&opcao);

            switch(opcao){

            case 1: system("cls");
                    fflush(stdin);
                    printf("Digite o nome da m�sica: \n");

                    scanf("%s",&aux[i].nome);
                    break;

            case 2: system("cls");
                    fflush(stdin);
                    printf("Digite o artista da m�sica: \n");

                    scanf("%s",&aux[i].artista);
                    fclose(file);
                    break;

            case 3: system("cls");
                    fflush(stdin);
                    printf("Digite o nome do �lbum: \n");

                    scanf("%s",&aux[i].album);
                    break;

            case 4: system("cls");
                    fflush(stdin);
                    printf("Digite o g�nero da m�sica: \n");
 
                    scanf("%s",&aux[i].genero);
                    break;

            case 5: system("cls");
                    fflush(stdin);
                    printf("Digite o ano em que ela foi lan�ada (aaaa): \n");

                    scanf("%4i",&aux[i].ano);
                    break;

            case 6: system("cls");
                    fflush(stdin);
                    printf("Digite sua dura��o (mm:ss): \n");

                    scanf("%6s",&aux[i].duracao);
                    break;
            }
    }

	   for(i=0;i<tam;i++){
        if(strcmp(aux[i].nome,nome_comp)==0){

    		freopen("musicas.db","w+b",file);

    		for(i=0;i<tam;i++){
    		fwrite(&aux[i], sizeof(struct Musica),1,file);
    		}
    		break;
		}
}
    fclose(file);
	printf("ALTERA��O FEITA COM SUCESSO\n");
    getch();
    return SUCESSO;
}
}

enum Retornos busca(){
    system("cls");

	int tam = 0,i,opc;
	char nome_comp[30];

	FILE*file;
	file=fopen("musicas.db","rb");

	if(file==NULL){
        printf("ARQUIVO INEXISTENTE\n");
        getch();
        return ARQUIVO_INEXISTENTE;
    }

	fseek(file,0,SEEK_END);
	tam = ftell(file);
	tam = tam / sizeof(struct Musica);
	fseek(file,0,SEEK_SET);

	struct Musica aux[tam];

	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct Musica),1,file);
	}
	printf("\nDigite o nome da m�sica que deseja localizar: ");
    scanf("%s",&nome_comp);
    for(i=0;i<tam;i++){
        if(strcmp(aux[i].nome,nome_comp)==0){
            printf("\t\t\tM�SICA LOCALIZADA\n");
            printf("Nome:  %s\n",aux[i].nome);
            printf("Artista: %s\n",aux[i].artista);
            printf("�lbum:   %s\n",aux[i].album);
            printf("G�nero:  %s\n",aux[i].genero);
            printf("Ano:     %i\n",aux[i].ano);
            printf("Dura��o: %s\n",aux[i].duracao);
       }
    }
    fclose(file);
    getch();
    return SUCESSO;
}

enum Retornos ajuda(){
    system("cls");

    printf("Programa feito por: Marc�sio Breno\n");
    printf("Contato: marcisiobreno@outlook.com\n\n\n");

    printf("O programa lhe ajudar� a cadastrar as suas m�sicas favoritas.\n");
    printf("Al�m do nome dela vo� pode cadastrar:\n");
    printf("* O artista que a comp�s\n");
    printf("* O �lbum no qual ela est� gravada\n");
    printf("* O g�nero da m�sica\n");
    printf("* O seu ano de lan�amento\n");
    printf("* A sua dura��o\n");

    printf("\nPressione qualquer tecla\n");
    getch();
    return SUCESSO;
}

enum Retornos menu(){
	while(1){
        system("cls");
        int resp;
        printf("CADASTRO DE M�SICAS\n");
        printf("1 - Adicionar uma m�sica\n");
		printf("2 - Remover uma m�sica\n");
        printf("3 - Alterar uma m�sica\n");
		printf("4 - Encontrar uma m�sica\n");
		printf("5 - Pedir ajuda\n");
        printf("6 - Sair\n");

		fflush(stdin);

        printf("Escolha feita: ");

		scanf("%i",&resp);
		switch(resp){
            case ADICAO:    adicao();           //opcao 1
                            break;

            case REMOCAO:   remocao();          //opcao 2
                            break;

            case ALTERACAO: alteracao();        //opcao 3
                            break;

            case BUSCA:     busca();            //opcao 4
                            break;

            case AJUDA:     ajuda();            //opcao 6
                            break;

			case SAIDA:     exit(0);            //opcao 7

            default:        printf("ENTRADA INVALIDA\n");
                            system("pause");
		}
	}
}

void main(){
    setlocale(LC_ALL,"");
	menu();
}
