#include <stdlib.h>
#include <stdio.h>

typedef struct node{
	char element;
	int frequence;
	struct node *next;
}node;

typedef struct {
	node **head;
	node **tail;
}Queue;

char read_data (int *frequency);
char build_tree ();
void build_queue (int *frequencym , int number, Queue *queue);
void push (int element, int frequence, node **head);

int main (){
	char t;
	int *frequency = (int*)calloc(256, sizeof(int));
	if (frequency == NULL){
		printf("error\n");
		return 1;
	}

	t = getchar();
	read_data(frequency);
	if (t == 'd'){

	}
	else if(t == 'c'){
		read_data(frequency);
	}
	return 0;

}

char read_data (int *frequency){
	char tmp;
	int number = 256;
	Queue *queue = NULL;
	fprintf(stderr, "er\n" );
	while ((tmp = getchar()) != '!'){
		if (!frequency[tmp])
			number--;
		frequency[tmp]++;
	}
	number = 256 - number;
	build_queue(frequency, number, queue);

}


char build_tree (Queue *queue){

	
}

void build_queue (int *frequency , int number, Queue *queue){
	queue = malloc(sizeof(Queue*));
	queue->head = malloc(sizeof(node**));
	queue->tail = malloc(sizeof(node**));
	*queue->head = NULL;
	*queue->tail = NULL;

	int j = 0;
	int max = 0, element = 0;
	for (int j = 0; j < number; j++){
		max = 0;
		for (int i = 0; i < 256; i++){
			if (frequency[i] > max){
				max = frequency[i];
				element = i;
			}
		}
		push(element, max, queue->head);
	}
	build_tree(queue);
}

void push (int element, int frequence, node **head){
	node *tmp = NULL;
	if((tmp = malloc(sizeof(node))) == NULL){
		exit(1);
	}
	tmp->element = element;
	tmp->frequence = frequence;
	tmp->next = *head;
	*head = tmp;
}


