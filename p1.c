#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree TREE;

struct tree{
	int data;
	TREE *left, *right;
};

TREE *create_empty_tree(){
	return NULL;
}

TREE *create_tree(int new_data, TREE *left, TREE *right){
	TREE *new_tree = (TREE*)malloc(sizeof(TREE));
	new_tree->data = new_data;
	new_tree->right = right;
	new_tree->left = left;
	return new_tree;
}

void maior_mult(TREE *tree, int *aux, int soma_de_mult){
	if(tree == NULL){
		return;
	}
	soma_de_mult *= tree->data;
	if(soma_de_mult > *aux){
		*aux = soma_de_mult;
	}
	maior_mult(tree->left,aux,soma_de_mult);
	maior_mult(tree->right,aux,soma_de_mult);
}

void print_tree(TREE *tree)
{
	printf(" (");
	if(tree == NULL){
		printf(") ");
		return;
	}
	printf(" %d ", tree->data);
	print_tree(tree->left);
	print_tree(tree->right);
	printf(") ");
}

TREE *add(TREE *tree, int *values, int i, int max_nodes){
	if(i * 2 > max_nodes || i * 2 + 1 > max_nodes){
		return create_tree(values[i], NULL, NULL);
	}
	tree = create_tree(values[i], NULL, NULL);
	tree->left = add(tree->left, values, i * 2, max_nodes);
	tree->right = add(tree->right, values, i * 2 + 1, max_nodes);
	return tree;
}

int main() {
	TREE *tree = create_empty_tree();
	int height, i = 1, aux = -999;
	scanf("%d",&height);
	int values[(int)pow(2,height)];
	
	while(scanf("%d",&values[i]) != EOF){
		i += 1;
	}

	tree = add(tree,values,1,i-1);
	maior_mult(tree,&aux,1);
	printf("%d\n", aux);

	return 0;
}