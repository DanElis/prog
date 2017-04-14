#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char element;
	int frequence;
}node;


char read_data (int *frequency);
char build_tree ();
char build_queue (int *frequencym , int number);
int queue_comp (const void *a, const void *b);
int main (){
	char t;
	int *frequency = (int*)calloc(256, sizeof(int));
	if(scanf("%c",t) != 1){
		printf("error\n" );
		return 0;
	}
	if (t == 'd'){

	}
	else if(t == 'c'){

	}
	return 0;

}

char read_data (int *frequency){
	char tmp;
	int number = 256;
	while ((tmp = getchar()) != EOF){
		if (!frequency[tmp])
			number--;
		frequency[tmp]++;
	}
	number = 256 - number;
	build_queue(frequency, number);

}


char build_tree (){

	
}

char build_queue (int *frequency , int number){
	node *queue = malloc(number*sizeof(node));
	int j = 0;
	for (int i = 0; i < 256; i++){
		if (frequency[i]){
			queue[j].element = i;
			queue[j++].frequence = frequency[i];
		}
	}
	qsort(queue, number,sizeof(node), queue_comp);
	
	
}

int queue_comp (const void *a, const void *b){
	return (((node *)a)->frequence > ((node*)b)->frequence);
}