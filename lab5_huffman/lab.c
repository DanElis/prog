#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_tree{
	int Frequence;
	char Element;
	//long long int code;
	struct node_tree *LeftChild;
	struct node_tree *RightChild;
}node_tree;

typedef struct node_queue{
	node_tree *Data;
	struct node_queue *next;
}node_queue;

typedef struct Tree{
	struct node_tree **head;
}Tree;

typedef struct Queue{
	struct node_queue **head;
}Queue;

void fread_Data_c (int *frequency, unsigned char *Number_symbols , FILE *file);
void fread_Data_d (char *elements, char **codes);
char build_tree (Queue *queue, Tree *tree, unsigned char *Number_symbols , char *code, char *elements, int *Number_Bit, char **codes, int *tmp);
void build_queue (int *frequency , unsigned char *Number_symbols, Queue *queue);
void push (char Element, int Frequence, node_queue **head);
void Q_push (char Element, int Frequence, node_queue **head);
void T_push (Queue *queue, Tree *tree, int j, unsigned char *Number_symbols);
char fprint_Data (Tree *tree, char **codes, int *Number_Bit, FILE *file_out,char *code ,int *number);
char write_code (Queue *queue, char *code, char *elements, int *Number_Bit, char **codes, int *tmp);
char dfs (node_tree *recurring,int number_code, int *number_element , char *code , char *elements, int *Number_Bit, char **codes,char tmp_code[32], int *tmp);
char Get(int i,char *code);
unsigned char pow_2 (int j);
void Set(char *code,int j);
void fprintf_tree (unsigned char Number_symbols,  FILE *file_out, char *elements);
//long long int find_elemnt(Tree *tree, int *frequency, char Element);



int main (){
	char t;
	int *frequency = (int*)calloc(256, sizeof(int));
	if (frequency == NULL){
		printf("error\n");
		return 1;
	}
	FILE *file = fopen("in.txt", "r");
	if (!file){
		printf("error\n");
		exit(1);
	}
	t = fgetc(file);
	
	if (t == 'd'){
		char *elements = NULL;
		char **codes = malloc(sizeof(char**)*256);
		for (int i = 0; i < 256; i++){
			codes[i] = calloc(8, sizeof(char));
		}
		fread_Data_d(elements, codes);
	}
	else if(t == 'c'){
		Queue *queue = malloc(sizeof(Queue*));
		queue->head = NULL;
		unsigned char *Number_symbols = malloc(sizeof(unsigned char*));
		*Number_symbols = 0;

		fread_Data_c(frequency, Number_symbols, file);

		fprintf(stderr, "1\n" );

		build_queue(frequency, Number_symbols, queue);

		fprintf(stderr, "2\n" );
		Tree *tree = malloc(sizeof(Tree*));
		tree->head = malloc(sizeof(node_tree**));
		*tree->head = NULL;
		fprintf(stderr, "3\n" );
		char **codes = malloc(sizeof(char**)*256);
		for (int i = 0; i < 256; i++){
			codes[i] = calloc(8, sizeof(char));
		}

		char *code = calloc (64, sizeof(char));
		char *elements = calloc (256, sizeof(char)); //!!!
		int *Number_Bit = calloc(256, sizeof(int));
		int *tmp = malloc(sizeof(int*));
		*tmp = 0;
		build_tree(queue, tree, Number_symbols, code, elements, Number_Bit, codes, tmp);

		FILE *file_out = fopen("out.txt", "w");
		if (!file_out){
			printf("error\n");
			exit(1);
		}

		fprintf_tree (*Number_symbols,  file_out, elements);
		fprint_Data (tree, codes, Number_Bit, file_out, code, tmp);
	}
	return 1;

}

void fread_Data_d (char *elements, char **codes){
	char tmp = 0;
	char code = 0;
	char number_elements = 0;
	FILE *file_in = fopen("in.txt", "r");
	if (!file_in){
		printf("error\n");
		exit(1);
	}
	if (fscanf(file_in,"%c",number_elements) != 1){
		exit(0);
	}
	elements = malloc(sizeof(char)*number_elements);
	for (int i = 0; i < number_elements; i++){
		fscanf(file_in,"%c", elements[i]);
	}
	int i = 0;
	while (i < number_elements){
		fscanf(file_in, "%c", code);
		for (int j = 0; j < 8; j++){
			if ((tmp = (code/pow_2(j)%2)) == 1){

			}
			else{}
		}
	}
}






void fread_Data_c (int *frequency,unsigned char *Number_symbols, FILE *file ){
	char tmp;
	int t = 0; 	
	while ((tmp = fgetc(file)) != EOF){
		if (!frequency[tmp]){
			t++;			
		}
		frequency[tmp]++;
	}
	*Number_symbols = t;
	if (fclose(file)){
		printf("error\n");
		exit(1);
	}
	fprintf(stderr, "0\n" );


}


char build_tree (Queue *queue, Tree *tree,unsigned char *Number_symbols, char *code, char *elements, int *Number_Bit, char **codes, int *tmp){
	for (int i = 0; i < *Number_symbols - 1; i++){
		T_push(queue, tree, i, Number_symbols);
		fprintf(stderr, "%d\n", i );
		//fprintf(stderr, "i  = %d\n",i );
	}
	//(*tree->head) = (*queue->head);
	write_code(queue, code,  elements, Number_Bit, codes, tmp);

	
}
char write_code(Queue *queue, char *code, char *elements, int *Number_Bit, char **codes, int *tmp){

	char tmp_code[32];
	for(int i = 0 ; i < 32; i++){
		tmp_code[i] = 0;
	}

	int *number_element = malloc(sizeof(int*));
	*number_element = 0;
	fprintf(stderr, "123\n" );
	dfs((*queue->head)->Data, 0,number_element,code, elements, Number_Bit, codes, tmp_code, tmp);
}

char dfs ( node_tree *recurring, int number_code, int *number_element,  char *code, char *elements,int *Number_Bit, char **codes, char tmp_code[32], int *tmp){
	//fprintf(stderr, "wr\n" );
	if (recurring->Element != -1){
		//fprintf(stderr, "r = %d\n", recurring->Element);
		//fprintf(stderr, "p = %d\n",parent->Element );
		elements[*number_element] = recurring->Element;
		(*number_element)++;
		strcpy(codes[recurring->Element], tmp_code);
		fprintf(stderr, "c = %s\n",codes[recurring->Element	]);
		Number_Bit[recurring->Element] = number_code;

		codes[recurring->Element][number_code+1] = '\0';
		//fprintf(stderr, "!%s\n",codes[recurring->Element] );
	}
	if (recurring->LeftChild){
		//fprintf(stderr, "left\n" );
		dfs(recurring->LeftChild,  number_code+1,number_element, code, elements, Number_Bit, codes, tmp_code, tmp);
		(*tmp)++;
	}
	if (recurring->RightChild){
		//fprintf(stderr, "RightChildt\n" );
		(*tmp)++;
		Set(code, *tmp);
		Set(tmp_code, number_code+1);	
		dfs ( recurring->RightChild,number_code+1,number_element, code, elements, Number_Bit, codes, tmp_code, tmp);
	}


}

char Get(int i,char *code){
	int k = code[i/8];
	return(( k/pow_2(i%8))%2);
}	

unsigned char pow_2 (int j){
	int k = 1;
	k = k << j;
	return k; 
}
void Set(char *code,int i){
	code[i/8] += pow_2(i%8);
} 

void build_queue (int *frequency , unsigned char *Number_symbols, Queue *queue){
	
	queue->head = malloc(sizeof(node_queue**));
	//queue->tail = malloc(sizeof(node_tree**));
	*queue->head = NULL;
	//*queue->tail = NULL;

	int j = 0;
	int max = 0, Element = 0;
	for (int j = 0; j < *Number_symbols; j++){
		max = 0;
		for (int i = 0; i < 256; i++){
			if (frequency[i] > max){
				max = frequency[i];
				Element = i;
			}

		}
		frequency[Element] = 0;
		Q_push(Element, max, queue->head);
	}
	
}

char fprint_Data (Tree *tree, char **codes, int *Number_Bit, FILE * file_out, char *code, int *number){
	char buf[4];
	char tmp; 
	int i = 0;
	FILE *file_in = fopen("in.txt", "r");
	if (!file_in){
		printf("error\n");
		exit(1);
	}
	for (int j = 0; j < *number; j++){
		if (j == 15){
			fprintf(file_out, "%c%c",buf[0],buf[1] );
		}
		else if (j == 31){
			fprintf(file_out, "%c%c",buf[2],buf[3] );
			j = j % 32;
		}
		if(Get(j, code))
			Set(buf, i);
		j++;
	}
	
	
	while ((tmp = fgetc(file_in)) != EOF){
		i = i % 32;
		for (int j = 0; j < Number_Bit[tmp]; j++){
			if (i == 15){
				fprintf(file_out, "%c%c",buf[0],buf[1] );
			}
			else if (i == 31){
				fprintf(file_out, "%c%c",buf[2],buf[3] );
				i = i % 32;
			}
			if(Get(j, codes[tmp]))
				Set(buf, i);
			
			i++;
		}
		
		//fprintf(stderr, "end !%s\n",codes[tmp] );
	}
	if (fclose(file_out)){
		printf("error\n");
		exit(1);
	}
	if (fclose(file_in)){
		printf("error\n");
		exit(1);
	}
	//find_elemnt (tree, frequency, tmp);

}

void fprintf_tree (unsigned char Number_symbols,  FILE *file_out, char *elements){
	fprintf(file_out, "%c",Number_symbols);
	for (int i = 0; elements[i]; i++){
		fprintf(file_out, "%c",elements[i] );
	}

	/*int tmp = 0;
	char buf[4];
	char j = 0;
	char k = 8;
	for (unsigned char i = 0; Number_symbols > 0; i++){
		if (codes[i]){
			tmp = i;
			k  = 8;
			while (k){
				//fprintf(stderr, "!%d\n",tmp );
				k--;
				if (j == 15){
					fprintf(file_out, "%c%c",buf[0],buf[1] );
				}
				else if (j == 31){
					fprintf(file_out, "%c%c",buf[2],buf[3] );
					j = j % 32;
				}
				
				if (tmp % 2)
					Set(buf, j);

				tmp = tmp/2;
				
				j++;
			}
			fprintf(stderr, "12\n" );
			k = 8;
			tmp = Number_Bit[i];
			while (k){
				k--;
				fprintf(stderr, "!!%d\n",tmp );
				if (j == 15){
					fprintf(file_out, "%c%c",buf[0],buf[1] );
				}
				else if (j == 31){
					fprintf(file_out, "%c%c",buf[2],buf[3] );
					j = j % 32;
				}
				if (tmp % 2)
					Set(buf, j);
				
				tmp /= 2;
				j++;
			}
			
			for (int j = 0; j < Number_Bit[i]; j++){
				fprintf(stderr, "!!!%d\n",tmp );

				if (j == 15){
					fprintf(file_out, "%c%c",buf[0],buf[1] );
				}
				else if (j == 31){
					fprintf(file_out, "%c%c",buf[2],buf[3] );
					j = j % 32;
				}
				if (Get(j, codes[i]))
					Set(buf, j);
				
				j++;
				
			}
			Number_symbols--;

		}
	}*/
}	

/*char find_elemnt(Tree *tree, int *frequency, char Element){
	node_tree *tmp = *tree->head;
	while (tmp->Frequence == frequency[Element] && tmp->Element == Element){

		if (frequency[Element] < tmp->Frequence){
			tmp = tmp->
		}
	}	
}*/

void Q_push (char Element, int Frequence, node_queue **head){
	node_queue *tmp = NULL;
	fprintf(stderr, "f1 = %d\n",Element );
	if((tmp = malloc(sizeof(node_queue))) == NULL){
		exit(1);
	}
	tmp->Data = malloc(sizeof(node_tree));
	tmp->Data->Element = Element;
	tmp->Data->Frequence = Frequence;
	tmp->next = *head;
	*head = tmp;
	//if (!(*head)->next){
	//	fprintf(stderr, "NULL\n" );
	//}
	tmp->Data->LeftChild = NULL;
	tmp->Data->RightChild = NULL;

	//fprintf(stderr, "f2 = %d\n",(*head)->Data->Frequence );
/*	queue[i].Frequence = Frequence;
	queue[i].Element = Element;
	queue[i].LeftChild = NULL;
	queue[i].RightChild = NULL;*/
}
void T_push (Queue *queue, Tree *tree, int j, unsigned char *Number_symbols ){
/*	node_tree *NewNodeTree = malloc(sizeof(node_tree*));
	NewNodeTree->LeftChild = malloc(sizeof(node_tree*));
	NewNodeTree->RightChild = malloc(sizeof(node_tree*));
	//fprintf(stderr, "6\n" );
	NewNodeTree->LeftChild->Frequence = (*queue->head)->Data->Frequence;
	NewNodeTree->LeftChild->Element = (*queue->head)->Data->Element;
	NewNodeTree->RightChild->Frequence = (*queue->head)->next->Data->Frequence;
	NewNodeTree->RightChild->Element = (*queue->head)->next->Data->Element;
	//fprintf(stderr, "7\n" );
	NewNodeTree->Frequence = NewNodeTree->LeftChild->Frequence + NewNodeTree->RightChild->Frequence;
	NewNodeTree->Element = -1;
	//tmp->code = -1;
	//переделать все!!!!!!
	*tree->head = NewNodeTree;
	//fprintf(stderr, "8\n" );
	node_queue *NewNodeQueue = *queue->head;
	*queue->head = (*queue->head)->next;
	//fprintf(stderr, "12\n" );
	free(NewNodeQueue);
	NewNodeQueue = *queue->head;
	*queue->head = (*queue->head)->next;
	//fprintf(stderr, "13\n" );
	NewNodeQueue->Data->Frequence = (*tree->head)->LeftChild->Frequence + (*tree->head)->RightChild->Frequence;
	NewNodeQueue->Data->Element = -1;
	//fprintf(stderr, "14\n" );
	node_queue *tmp = *queue->head;*/

	node_queue *NewNodeQueue = malloc(sizeof(node_queue*));
	NewNodeQueue->Data = malloc(sizeof(node_tree*));

	NewNodeQueue->Data->Frequence = (*queue->head)->Data->Frequence + (*queue->head)->next->Data->Frequence;

	NewNodeQueue->Data->Element = -1;
	fprintf(stderr, "01\n" );
	NewNodeQueue->Data->LeftChild = (*queue->head)->Data;
	NewNodeQueue->Data->RightChild = (*queue->head)->next->Data;
	(*queue->head) = (*queue->head)->next->next;	

	node_queue *tmp = *queue->head;
	if (!tmp){
		*queue->head = NewNodeQueue;
		//fprintf(stderr, "!!%d\n" ,NewNodeQueue->Data->Frequence);
		return;
	}
	//fprintf(stderr, " i = %d n = %d\n", j, *Number_symbols  );
	while (tmp->next){
		//fprintf(stderr, "9\n" );
		if (NewNodeQueue->Data->Frequence <= tmp->next->Data->Frequence){
			//fprintf(stderr, "10\n" );
			NewNodeQueue->next = tmp->next;
			tmp->next = NewNodeQueue;
			
			break;
		}
		tmp = tmp->next;	
	}

	if (!tmp->next){
		//fprintf(stderr, "11\n" );
		tmp->next = NewNodeQueue;
		NewNodeQueue->next = NULL;	
	}
	//fprintf(stderr, "11\n" );
		
}
