#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_tree{
	int frequence;
	int element;
	long long int code;
	struct node_tree *left_child;
	struct node_tree *rihgt_child;
}node_tree;

typedef struct node_queue{
	node_tree *data;
	struct node_queue *next;
}node_queue;

typedef struct Tree{
	struct node_tree **head;
}Tree;

typedef struct Queue{
	struct node_queue **head;
}Queue;

void fread_data (int *frequency, int *number);
char build_tree (Queue *queue, Tree *tree, int *number, char **codes);
void build_queue (int *frequencym , int *number, Queue *queue);
void push (int element, int frequence, node_queue **head);
void Q_push (int element, int frequence, node_queue **head);
void T_push (Queue *queue, Tree *tree);
char fprint_data (Tree *tree, char **codes);
char write_code (Tree *tree, char **codes);
char dfs (node_tree *parent,node_tree *recurring,char **codes, int number,  int code);
//long long int find_elemnt(Tree *tree, int *frequency, char element);



int main (){
	char t;
	int *frequency = (int*)calloc(256, sizeof(int));
	if (frequency == NULL){
		printf("error\n");
		return 1;
	}

	t = getchar();
	
	if (t == 'd'){

	}
	else if(t == 'c'){
		Queue *queue = malloc(sizeof(Queue*));
		queue->head = NULL;
		int *number = malloc(sizeof(int*));
		*number = 256;

		fread_data(frequency, number);

		fprintf(stderr, "1\n" );

		build_queue(frequency, number, queue);

		fprintf(stderr, "2\n" );
		Tree *tree = malloc(sizeof(Tree*));
		tree->head = malloc(sizeof(node_tree**));
		*tree->head = NULL;
		fprintf(stderr, "3\n" );

		char **codes = malloc(sizeof(char*)*256);
		for (int i = 0; i < 256; i++){
			codes[i] = malloc(sizeof(char)*256);
		}
		fprintf(stderr, "4\n" );
		build_tree(queue, tree, number, codes);

		fprint_data (tree, codes);
	}
	return 0;

}

void fread_data (int *frequency, int *number){
	FILE *file = fopen("in.txt", "r");
	if (!file){
		printf("error\n");
		exit(1);
	}
	char tmp; 	
	while ((tmp = fgetc(file)) != EOF){
		if (!frequency[tmp])
			number--;
		frequency[tmp]++;
	}
	*number = 256 - *number;
	if (fclose(file)){
		printf("error\n");
		exit(1);
	}
	fprintf(stderr, "0\n" );


}


char build_tree (Queue *queue, Tree *tree, int *number, char **codes){
	for (int i = 0; i < *number - 1; i++){
		T_push(queue, tree);
		fprintf(stderr, "5\n" );
	}

	write_code(tree, codes);

	
}
char write_code(Tree *tree, char **codes){
	dfs(NULL,*tree->head,codes, 0,0);
}

char dfs (node_tree *parent, node_tree *recurring, char **codes, int number, int code){
	if (recurring->element != -1){
		if (parent)
			strcpy(codes[recurring->element], codes[parent->element]);
		codes[recurring->element][number] = code;
		codes[recurring->element][number+1] = '\0';
	}
	if (recurring->left_child)
		dfs(recurring, recurring->left_child, codes, number+1,0);
	else if (recurring,recurring->rihgt_child)
		dfs (recurring, recurring->rihgt_child,codes,number, 1);


}
void build_queue (int *frequency , int *number, Queue *queue){
	
	queue->head = malloc(sizeof(node_queue**));
	//queue->tail = malloc(sizeof(node_tree**));
	*queue->head = NULL;
	//*queue->tail = NULL;

	int j = 0;
	int max = 0, element = 0;
	for (int j = 0; j < *number; j++){
		max = 0;
		for (int i = 0; i < 256; i++){
			if (frequency[i] > max){
				max = frequency[i];
				element = i;
			}
		}
		Q_push(element, max, queue->head);
	}
	
}

char fprint_data (Tree *tree, char **codes){
	FILE *file1 = fopen("in.txt", "r");
	if (!file1){
		printf("error\n");
		exit(1);
	}
	FILE *file2 = fopen("out.txt	", "w");
	if (!file2){
		printf("error\n");
		exit(1);
	}
	char tmp; 
	while ((tmp = fgetc(file1)) != EOF){
		fprintf(file2, "%s\n", codes[tmp]);
		
	}
	//find_elemnt (tree, frequency, tmp);

}

/*char find_elemnt(Tree *tree, int *frequency, char element){
	node_tree *tmp = *tree->head;
	while (tmp->frequence == frequency[element] && tmp->element == element){

		if (frequency[element] < tmp->frequence){
			tmp = tmp->
		}
	}	
}*/

void Q_push (int element, int frequence, node_queue **head){
	node_queue *tmp = NULL;
	fprintf(stderr, "f1 = %d\n",frequence );
	if((tmp = malloc(sizeof(node_queue))) == NULL){
		exit(1);
	}
	tmp->data = malloc(sizeof(node_tree));
	tmp->data->element = element;
	tmp->data->frequence = frequence;
	tmp->next = *head;
	*head = tmp;
	if (!(*head)->next){
		fprintf(stderr, "NULL\n" );
	}
	fprintf(stderr, "f2 = %d\n",(*head)->data->frequence );
/*	queue[i].frequence = frequence;
	queue[i].element = element;
	queue[i].left_child = NULL;
	queue[i].rihgt_child = NULL;*/
}
void T_push (Queue *queue, Tree *tree){
	node_tree *NewNodeTree = malloc(sizeof(node_tree*));
	NewNodeTree->left_child = malloc(sizeof(node_tree*));
	NewNodeTree->rihgt_child = malloc(sizeof(node_tree*));
	fprintf(stderr, "6\n" );
	NewNodeTree->left_child->frequence = (*queue->head)->data->frequence;
	NewNodeTree->left_child->element = (*queue->head)->data->element;
	NewNodeTree->rihgt_child->frequence = (*queue->head)->data->frequence;
	NewNodeTree->rihgt_child->element = (*queue->head)->data->element;
	fprintf(stderr, "7\n" );
	NewNodeTree->frequence = NewNodeTree->left_child->frequence + NewNodeTree->rihgt_child->frequence;
	NewNodeTree->element = -1;
	//tmp->code = -1;

	*tree->head = NewNodeTree;
	fprintf(stderr, "8\n" );
	node_queue *NewNodeQueue = *queue->head;
	*queue->head = (*queue->head)->next;
	fprintf(stderr, "12\n" );
	free(NewNodeQueue);
	NewNodeQueue = *queue->head;
	*queue->head = (*queue->head)->next;
	fprintf(stderr, "13\n" );
	NewNodeQueue->data->frequence = (*tree->head)->left_child->frequence + (*tree->head)->rihgt_child->frequence;
	NewNodeQueue->data->element = -1;
	fprintf(stderr, "14\n" );
	node_queue *tmp = *queue->head;
	if (!tmp){
		*queue->head = NewNodeQueue;
		return;
	}
	fprintf(stderr, "15\n" );
	while (tmp->next){
		fprintf(stderr, "9\n" );
		if (NewNodeQueue->data->frequence < tmp->next->data->frequence){
			fprintf(stderr, "10\n" );
			NewNodeQueue->next = tmp->next;
			tmp->next = NewNodeQueue;
			
			break;
		}
		tmp = tmp->next;	
	}
	if (!tmp->next){
		fprintf(stderr, "11\n" );
		tmp->next = NewNodeQueue;	
	}
		
}



