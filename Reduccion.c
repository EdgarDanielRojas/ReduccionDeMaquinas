#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

typedef struct myData_{
    int    	i;                         /**< number is an unsigned int */
    int  	j;               /**< theString is a pointer to a char */
}myData; 
typedef struct myData_ *node_p;  /**< Simplify declaration of ptr to node */

//GList * theList_p = NULL;           // Used to test the list operations

node_p NewItem (int num1, int num2){
	node_p node = (node_p)malloc(sizeof(struct myData_)); // We create a new space in memory for our myData structure and assign it to a pointer
	node->i = num1; // We assign the number that is passed as a parameter to the structure
	node->j = num2; // We assign the string that is passed as a paramter to the structure
	return node; // We return the pointer to the structure
}

void dist(int index1,int index2,int *matrix,int size,GList **matrixs){
	//printf("\n%d %d Entered dist\n",index1,index2);
	*((matrix+index1*size) + index2) = 1;
	//printf("Changed matrix succesfully\n");
	//printf("%p",*matrixs);
	GList *l; // A temporary pointer is created that will allow us to cycle through our list
	GList *temp = *((matrixs+index1*size)+index2);
	for(l=temp;l!=NULL;l=l->next){ // We cycle through the list
    node_p node = l->data; // We extract the data from the current node (a node_p pointer) and assign it to a variable
    dist(node->i,node->j,matrix,size,matrixs);
  	}
}

void printMatrix(int *matrix,int size){
	int temp;
		printf("\n");
	printf("  0");
	for(int i = 1; i<size;i++)
		printf(" %d",i);
	for(int i =0; i<size;i++){
		printf("\n%d ",i);
		for(int j=0; j<size;j++){
			temp= *((matrix+i*size) + j);
			if(temp == -1){
			printf("  ");
			}
			else{
				printf("%d ",temp);
			}
			
		}
	}
		printf("\n");
}

int main(void){
	int numberNodes=0;
	int numberAlphabet=0;
	int temp=0;
	int destNode=0;
	printf("Ingrese el numero de nodos: ");
	scanf("%d",&numberNodes);
	printf("\nIngrese el size del alfabeto: ");
	scanf("%d",&numberAlphabet);
	int goalNodes[numberNodes];
	int nodeConnection[numberNodes][numberAlphabet];
	//int listS[numberNodes][numberNodes];
	GList * theList_p[numberNodes][numberNodes];           // Used to test the list operations
	int nodesTable[numberNodes][numberNodes];

	for(int i =0;i<numberNodes;i++){
		for(int j=0;j<numberNodes;j++){
			theList_p[i][j]=NULL;
			nodesTable[i][j]=-1;
		}
		goalNodes[i]=0;
	}
	//printMatrix((int *)nodesTable,numberNodes);
	printf("\nA continuacion agregue los nodos que sean estado final\nSi ya no quieres capturar ingrese -1\n");
	do{
		printf("Ingrese el nodo estado final: ");
		scanf("%d",&temp);
		if(temp>numberNodes)
			printf("Nodo fuera de rango");
		else if(temp>-1)
			goalNodes[temp]=1;
	}while(temp!=-1);

	for(int i = 0 ; i<numberNodes ; i++)
		printf("%d ",goalNodes[i]);

	int valid=0;
	printf("\nA continuacion agregaremos las aristas de los nodos.\nTendra que capturar forzosamente cada letra de cada nodo.\n");
	for(int i=0;i<numberNodes;i++){
		for(int j=0;j<numberAlphabet;j++){
			do{
				printf("Nodo %d con letra '%c' va a nodo:",i,'a'+j);
				scanf("%d",&destNode);
				if(destNode<0 || destNode>numberNodes){
					valid = 1;
				}
				else{
					nodeConnection[i][j]=destNode;
					valid=0;
				}
			}while(valid!=0);
		}
	}

	for(int i = 1; i < numberNodes; i++){
		for(int j = 0;j<numberNodes; j++){
			if(j<i){
				if(j<i && goalNodes[i]!=goalNodes[j])
					nodesTable[i][j] = 1;
				else
					nodesTable[i][j] = 0;
			}else{
				break;
			}
		}
	}

	// Print current matrix

	printMatrix((int *)nodesTable,numberNodes);

	int nodeM,nodeN;

	for(int i = 1; i < numberNodes; i++){
		for(int j = 0;j<numberNodes; j++){
			if(j<i){
				if(nodesTable[i][j]==0){
					for(int k = 0 ; k<numberAlphabet;k++){
						nodeM=nodeConnection[j][k];
						nodeN=nodeConnection[i][k];
						if(nodesTable[nodeM][nodeN]==1 || nodesTable[nodeN][nodeM]==1)
							dist(i,j,(int *)nodesTable,numberNodes,(GList **)theList_p);
						else{
							//printf("\n%d %d are going to append\n",i,j );
							if(nodeM<nodeN && j!=nodeM && i!=nodeN)
								theList_p[nodeM][nodeN] = g_list_append(theList_p[nodeM][nodeN], NewItem(i,j));
							else if(nodeN<nodeM && i!=nodeM && j!=nodeN){
								theList_p[nodeN][nodeM] = g_list_append(theList_p[nodeN][nodeM], NewItem(i,j));
							}
						}
					}
				}
			}else{
				break;
			}
				}
		}
		printMatrix((int *)nodesTable,numberNodes);
		for(int i = 1; i < numberNodes; i++){
		for(int j = 0;j<numberNodes; j++){
			if(j<i){
				if(nodesTable[i][j] == 0)
					printf("\n%d %d are reducible\n",i,j);
			}else{
				break;
			}
		}
	}
	}

