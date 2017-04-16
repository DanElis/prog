#include <stdlib.h>
#include <stdio.h>

typedef struct node_tree{
	int frequence;
	int element;
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

void read_data (int *frequency, int *number);
char build_tree (Queue *queue, Tree *tree, int *number);
void build_queue (int *frequencym , int *number, Queue *queue);
void push (int element, int frequence, node_queue **head);
void Q_push (int element, int frequence, node_queue **head);
void T_push (Queue *queue, Tree *tree);
int main (){
	char t;
	int *frequency = (int*)calloc(256, sizeof(int));
	if (frequency == NULL){
		printf("error\n");
		return 1;
	}

	t = getchar();
	Queue *queue = malloc(sizeof(Queue*));
	queue->head = NULL;
	int *number = malloc(sizeof(int*));
	*number = 256;
	read_data(frequency, number);
	fprintf(stderr, "1\n" );
	build_queue(frequency, number, queue);
	fprintf(stderr, "2\n" );
	Tree *tree = malloc(sizeof(Tree*));
	tree->head = malloc(sizeof(node_tree**));
	*tree->head = NULL;
	fprintf(stderr, "3\n" );
	build_tree(queue, tree, number);
	if (t == 'd'){

	}
	else if(t == 'c'){
		//read_data(frequency);
	}
	return 0;

}

void read_data (int *frequency, int *number){
	char tmp; 	
	
	while ((tmp = getchar()) != '!'){
		if (!frequency[tmp])
			number--;
		frequency[tmp]++;
	}
	*number = 256 - *number;
	fprintf(stderr, "0\n" );

}


char build_tree (Queue *queue, Tree *tree, int *number){
	for (int i = 0; i < *number - 1; i++){
		T_push(queue, tree);
	}
	
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

void Q_push (int element, int frequence, node_queue **head){
	node_queue *tmp = NULL;
	if((tmp = malloc(sizeof(node_queue))) == NULL){
		exit(1);
	}
	tmp->data = malloc(sizeof(node_tree));
	tmp->data->element = element;
	tmp->data->frequence = frequence;
	tmp->next = *head;
	*head = tmp;
/*	queue[i].frequence = frequence;
	queue[i].element = element;
	queue[i].left_child = NULL;
	queue[i].rihgt_child = NULL;*/
}
void T_push (Queue *queue, Tree *tree){
	node_tree *tmp = malloc(sizeof(node_tree*));
	tmp->left_child = malloc(sizeof(node_tree*));
	tmp->rihgt_child = malloc(sizeof(node_tree*));

	tmp->left_child->frequence = (*queue->head)->data->frequence;
	tmp->left_child->element = (*queue->head)->data->element;
	tmp->rihgt_child->frequence = (*queue->head)->data->frequence;
	tmp->rihgt_child->element = (*queue->head)->data->element;

	tmp->frequence = tmp->left_child->frequence + tmp->rihgt_child->frequence;
	tmp->element = -1;

	*tree->head = tmp;

	node_queue *tmp1 = *queue->head;
	*queue->head = (*queue->head)->next;
	free(tmp1);
	tmp1 = *queue->head;
	*queue->head = (*queue->head)->next;
	tmp1->data->frequence = (*tree->head)->left_child->frequence + (*tree->head)->rihgt_child->frequence;
	tmp1->data->element = -1;

	node_queue *tmp2 = *queue->head;
	while (tmp2->next){
		if (tmp1->data->frequence < tmp2->next->data->frequence){
			tmp1->next = tmp2->next;
			tmp2->next = tmp1;
			break;
		}	
	}
	if (!tmp2->next)
		tmp2->next = tmp1;	
		
}



