#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	printf("\nA continuacion agregue los nodos que sean estado final\nSi ya no quieres capturar ingrese -1\n");
	do{
		printf("Ingrese el nodo estado final: ");
		scanf("%d",&temp);
		if(temp>=numberAlphabet)
			printf("Nodo fuera de rango");
		else if(temp>-1)
			goalNodes[temp]=1;
	}while(temp!=-1);
	int valid=0;
	printf("\nA continuacion agregaremos las aristas de los nodos.\n Tendra que capturar forzosamente cada letra de cada nodo.\n")
	for(int i=0;i<numberNodes;i++){
		for(int j=0;j<numberAlphabet;i++){
			do{
				printf("Nodo %d con letra %d va a nodo:",i,j+1);
				scanf("%d",&destNode);
				if(destNode<0 || destNode>numberNodes){
					valid = 1;
				}
				else{
					nodeConnection[i][j]=destNode;
					valid=0;
				}
			}while(valid!=1);
		}
	}
	
}