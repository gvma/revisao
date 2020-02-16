#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node NODE;

struct node {
    struct node *left, *right;
    int data;
};

NODE *createEmptyTree() {
    return NULL;
}

NODE *createNode(NODE *left, NODE *right, int newData) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = newData;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}



char *createStr() {
    int quantAberto = 0, quantFechado = 0;
	char *str = (char *)malloc(sizeof(char) * 256);
	// printf("asdasd\n");
	char caractere;
	int i = 0;
	scanf("%c", &caractere);
	// printf("%c ", caractere);
	// printf("aber: %d ## fech %d\n", quantAberto, quantFechado);
	while(1) {
		if(caractere != ' ' && caractere != '\n' && caractere != '\0') {
			str[i] = caractere;
			i++;
		}
		if(caractere == '(') {
			quantAberto += 1; 
		} else if(caractere == ')') {
			quantFechado += 1;
		}
		// printf("aber: %d ## fech %d\n", quantAberto, quantFechado);
		if(quantAberto == quantFechado) {
			break;
		}
		scanf("%c", &caractere);
		// printf("%c ", caractere);
	}
	str[i] = '\0';
	// printf("\n");
	// printf("### %s\n", str);

	// printf("ARVORE: %s\n", str);

	return str;

}

NODE *makeBT(char string[], int *position) {
	NODE *bt = NULL;
	
	int numT;
	int i = 0;

	while(string[*position] == ' ' || string[*position] == '(') {
		*position += 1;
	}

	if(string[*position] != ')') {
		char num[10];
		for(i=0;string[*position] != '(';i++) {
			num[i] = string[*position];
			*position += 1;
		}
		num[i] = '\0';
		numT = atoi(num);

		bt = createNode(NULL, NULL, numT);
		bt->left = makeBT(string, position);
		bt->right = makeBT(string, position);
	} else {
		*position += 1;
		return NULL;
	}

	*position += 1;

	return bt;
}

NODE *addFromString(char *tree, /*MUITO IMPORTANTE ESSE PARAMETRO SER REFERENCIADO*/ int *index /*<---*/) {
    NODE *root = createEmptyTree();
    if (tree[*index] == '(') {
        //Caso seja um parentese abrindo, estou esperando receber 2 filhos, sendo eles nulos ou nao
        *index += 1;
        if (tree[*index] == ')') {
            //Caso seja um parentese fechando, o meu filho sera nulo
            *index += 1;
            return NULL;
        }
        char temp[20];
        int value = 0, j = 0;
        //Como eu sei que o meu valor anterior nao eh um parentese fechando, ou seja, meu filho possuira
        //um valor, vou pegando os numeros para montar meu filho
        while (tree[*index] != '(') {
            temp[j++] = tree[*index]; //adicionando no final da string
            *index += 1;
        }
        temp[j] = '\0';
        //Valor totalmente adquirido!
        int count = 0;
        //"Funcao" para transformar um valor de uma cadeia de caracteres em um inteiro
        while (count != strlen(temp)) {
            value += (int)pow(10, strlen(temp) - 1 - count) * (temp[count] - '0');
            count++;
        }
        //Crio o no e vou em busca de seus outros dois filhos
        root = createNode(NULL, NULL, value);
        root->left = addFromString(tree, index);
        root->right = addFromString(tree, index);
    }
    //Adiciono um valor no meu indice para poder continuar a adicionar os meus filhos
    *index += 1;
    //Retorno a ra?z da ?rvore
    return root;
}

void searchForNum(NODE *root, int expected, int actual, int *flag) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL && actual + root->data == expected) {
        *flag = 1;
        return;
    }
    searchForNum(root->left, expected, actual + root->data, flag);
    searchForNum(root->right, expected, actual + root->data, flag);
}

void checkSum(NODE *bt, int *soma, int total, int *resp) {
	if(bt) {
		// printf("tot: %d\n", bt->num);
		total += bt->data;
		if(total == *soma && (!bt->left && !bt->right)) {
			*resp = 1;
		}
		checkSum(bt->left, soma, total, resp);
		checkSum(bt->right, soma, total, resp);
	}
}

void printPreOrderTree(NODE *root)
{
	printf("(");
	if(root == NULL){
		printf(")");
		return;
	}
	printf("%d", root->data);
	printPreOrderTree(root->left);
	printPreOrderTree(root->right);
	printf(")");
}
int main() {
	int resp = 0, position = 0, quantAberto = 0, quantFechado = 0, soma;

	for(;;) {
		char *string = (char *)malloc(sizeof(char) * 256);
		scanf("%d ", &soma);
		NODE *bt = NULL;
		if(soma == -1000) {
			break;
		}
		string = createStr();
		quantFechado = 0;
		quantAberto = 0;
		bt = makeBT(string, &position);
		position = 0;
		printPreOrderTree(bt);
        // printf("%s\n", string);
		free(string);
		
		checkSum(bt, &soma, 0, &resp);

		if(resp == 1) {
			printf("sim\n");
		} else {
			printf("nao\n");
		}

		resp = 0;
		bt = NULL;

	}

	// print_pre_order(bt);

	// printf("FOI");
	return 0;
}