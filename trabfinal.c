#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 10
typedef struct Produto{
    char desc[30];
    int quant;
    float precoU;
    short usado;
}Produto;
//global
int totalUsado = 0;
void cadastraNova(Produto *p){

	printf("\nDigite o nome da Produto:");
	scanf("%s", p->desc);
	printf("\nDigite a quantidade:");
	scanf("%d",&p->quant);
	printf("\nDigite o preco:");
	scanf("%f",&p->precoU);

}
void iniciaCadastro(Produto vet[], int tam){
  int i;
  for(i=0; i<tam; i++)
    vet[i].usado = 0;
}
void leTodosProdutos(FILE *arq, Produto *vet, int n){
	int i;
	//fscanf(arq," %d ",&n);
	for(i=0;i<n;i++){


                fscanf(arq," %[^\n] ",vet[i].desc);
                fscanf(arq," %d ",&vet[i].quant);
                fscanf(arq," %f",&vet[i].precoU);
                fscanf(arq,"%d",&vet[i].usado);

            }
            printf("Quantidade de produtos cadastrados - %d \n",n);
}
void imprimeMenu(){
	printf("|-----------------------MENU DE OPCOES-------------------\n");
        printf("|1-RELATORIO DE TODOS ITENS CADASTRADOS NO ESTOQUE\n");
        printf("|2-CADASTRAR NOVO PRODUTO NO ESTOQUE\n");
        printf("|3-REMOVER PRODUTO DO ESTOQUE\n");
        printf("|4-ATUALIZAR PRODUTO DO ESTOQUE\n");
        printf("|5-EXIBIR A QUANTIDADE TOTAL DE ITENS NO ESTOQUE \n");
        printf("|6-GRAVAR PRODUTOS CADASTRADOS EM UM ARQUIVO TEXTO\n");
        printf("|7-FAZER O BACKUP DOS PRODUTOS EM UM ARQUIVO BINARIO \n");
        printf("|8-CARREGAR UM ARQUIVO BINARIO \n");
        printf("|9-SAIR DO PROGRAMA \n");
        printf("|---------------------------------------------------------\n");
        printf("\n\nDigite uma das opcoes:");

}
void relatorio(Produto *vet, int n){
	int i;
	float total=0;

	for(i=0;i<n;i++){
		if(vet[i].usado){

				printf("\n-----------Produto %d -----------\n",i+1);
				printf("Nome - %s \n",vet[i].desc);
				printf("Quantidade de produtos - %d \n",vet[i].quant);
				printf("Preco unitario - R$ %.2f \n",vet[i].precoU);
				total = total + (vet[i].quant*vet[i].precoU);

			}
	}
	printf("\n Preco total do estoque e : R$ %.2f \n",total);

}
void imprimeArquivo(FILE *arq, Produto *vet, int tam){
	int i;
	fprintf(arq,"\n%d",totalUsado);
	//arq=fopen("trabfinal.txt","a+");


	for(i=0;i<tam;i++){
		if(vet[i].usado==1){

		fprintf(arq,"\n%s",vet[i].desc);
		fprintf(arq,"\n%d",vet[i].quant);
		fprintf(arq,"\n%.2f",vet[i].precoU);
		fprintf(arq,"\n%d",vet[i].usado);

	}
	}
	fclose(arq);

}
int insereProduto(Produto vet[], int tam, Produto p){
  int i;

  for(i=0; i<tam; i++){
    if(vet[i].usado == 0){ //se posicao i estiver vaga
      vet[i] = p;
      vet[i].usado = 1; //posicao i passa a estar usada
      totalUsado++;
      return 1;
    }
  }
  return 0; //cadastro está cheio
}

int removeProduto(FILE *arq ,Produto vet[],int tam,char nome[]){
	int i;
	//fscanf(arq,"%d",&n);
	for(i=0;i<tam;i++){
		if(strcmp(nome,vet[i].desc)==0)
		{
			vet[i].usado=0;
            totalUsado--;
			return 1;
		}


	}
	return 0;
}
  void alteraNome(char nome[], Produto *vet, int tam)
{
	char novoNome[30];
    int i,qtd;
    float preco;

	printf("\nDigite o novo nome:");
	gets(novoNome);
	fflush(stdin);
	printf("\nDigite a nova quantidade:");
	scanf("%d",&qtd);
	printf("\nDigite o novo preco:");
	scanf("%f",&preco);

	for(i=0;i<tam;i++){
        //printf("%s/n", vet[i].desc);
		if(strcmp(nome,vet[i].desc)==0){
            strcpy(vet[i].desc, novoNome); //Altera nome
            vet[i].quant=qtd;
            vet[i].precoU=preco;
            printf("Alterado com sucesso\n");
            break;
        }

	}
}

int main(){

    Produto *mercado,p;
    char nome[10], nomeEx[10], nome2[10],nome3[10];
    int i,n=0;

    printf("Nome do arquivo: ");
    scanf("%s", nome);
    int  op,op1,aux;
    FILE *arq;
    FILE *arq2;
    FILE *arq3;
    mercado = calloc(MAX,sizeof(Produto));

     if(mercado == NULL){

			printf("Nao foi possivel alocar memoria.\n");
			return -1;
    }
	iniciaCadastro(mercado,MAX);
	arq = fopen( nome, "r+");
	fscanf(arq,"%d",&n);
	totalUsado = n;
	leTodosProdutos(arq,mercado,n);

	if(arq == NULL){

			printf("Erro ao tentar abrir o arquivo (%s).\n",nome);
			return -1;
	}else{

		    while(op !=9){
		    	imprimeMenu();
		    	scanf("%d",&op);
		    	getchar();
				switch(op){




					case 1:{
					relatorio(mercado,n);
						system("pause");
						system("cls");

						break;
					}

			    	case 2:{
			    		 		cadastraNova(&p);
						      aux = insereProduto(mercado, MAX, p);

						      if(aux){
							  	system("cls");
								printf("\n\nProduto cadastrada com sucesso!\n");
								n++;

								arq=fopen(nome,"w");
								imprimeArquivo(arq,mercado,n);
							}
						      else
								printf("\n\nProblema: Cadastro ja esta cheio!\n");

					break;
				   }
			    	case 3:{
			    		  printf("Digite o nome do produto: ");
					      scanf("%[^\n]", nomeEx);
					      getchar();

					      aux = removeProduto(arq,mercado,n, nomeEx);
					      if(aux){
					      	system("cls");

						printf("\n\nProduto removido com sucesso!\n");
						n-1;

							arq=fopen(nome,"w");
							imprimeArquivo(arq,mercado,n);

						}
					      else
						printf("\n\nProblema: Produto nao encontrada!\n");
					      break;
    					}


			        case 4:{
			        	printf("\nDigite o nome do produto que deseja alterar:");
			        	gets(nome);
			        	fflush(stdin);
			        	alteraNome(nome,mercado,n);
			        	system("clear || cls");
			        	//arq=fopen(nome,"w");
						imprimeArquivo(arq,mercado,n);


			        	//printf("\nDigite o nome do produto que deseja alterar:");
						break;
					}
			        case 5:{
			        	 printf("Quantidade de itens em estoque - %d \n",n);
						break;
					}

			        case 6:{
			        		printf("Nome do arquivo: ");
				            scanf("%s", nome2);
				            arq2 = fopen( nome2, "w");
				            if (arq2 == NULL){

				                printf("Erro ao tentar abrir o arquivo (%s).\n",nome2);
				                return -1;
				            }
				            else{
				            	int i=0;
							fprintf(arq2,"%d",totalUsado);
							//arq2=fopen(nome2,"a+");


							for(i=0;i<n;i++){
								if(mercado[i].usado==1){

								fprintf(arq2,"\n%s",mercado[i].desc);
								fprintf(arq2,"\n%d",mercado[i].quant);
								fprintf(arq2,"\n%.2f",mercado[i].precoU);
								fprintf(arq2,"\n%d",mercado[i].usado);

							}
							}
							fclose(arq2);

							}
			                break;
			            }





			        case 7:{
			        	printf("Nome do arquivo: ");
			            scanf("%s", nome3);
			            arq3 = fopen( nome3, "w+b");
			            if (arq3 == NULL){

			                printf("Erro ao tentar abrir o arquivo (%s).\n",nome3);
			                return -1;
			            }
			            else{
			            	fprintf(arq3,"\n%d",n);
			            	for(i=0;i<n;i++){
								if(mercado[i].usado==1){

								fprintf(arq3,"\n%s",mercado[i].desc);
								fprintf(arq3,"\n%d",mercado[i].quant);
								fprintf(arq3,"\n%.2f",mercado[i].precoU);
								fprintf(arq3,"\n%d",mercado[i].usado);

							}

			            }
			            break;
			        }
			    }





			       case 8:{
			       	 printf("Nome do arquivo: ");
			            scanf("%s", nome3);
			            arq3 = fopen( nome3, "r+b");

			            if (arq3 == NULL){
			                printf("Erro ao tentar abrir o arquivo (%s).\n",nome3);
			                return -1;
			            }
			            else{

			            	int i;
							fscanf(arq3," %d ",&n);
							for(i=0;i<n;i++){


				                fscanf(arq3," %[^\n] ",mercado[i].desc);
				                fscanf(arq3," %d ",&mercado[i].quant);
				                fscanf(arq3," %f",&mercado[i].precoU);
				                fscanf(arq3,"%d",&mercado[i].usado);

            }
            printf("Quantidade de produtos cadastrados - %d \n",n);
            for(i=0;i<n;i++){

				printf("\n-----------Produto %d -----------\n",i+1);
				printf("Nome - %s \n",mercado[i].desc);
				printf("Quantidade de produtos - %d \n",mercado[i].quant);
				printf("Preco unitario - R$ %.2f \n",mercado[i].precoU);
			}
				system("pause");
			    system("cls");

			}



					break;

				   }
				   //system("pause");





		    fclose(arq);
		    free(mercado);
		    }
	}

return(0);
}
}


