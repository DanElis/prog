#include <stdio.h>
#include <stdlib.h>
#define ERROR 1

struct stack{
	int value;
	char priory;
	struct stack *next;
};
char read_data(struct stack **head, struct stack **ExitStr);
void push (struct stack **head, int value, int priory);
char pop (struct stack **head);
char f_calc (int operation, struct stack **ExitStr);


int main(){
	struct stack **head = malloc(sizeof(struct stack**));
	(*head) = NULL;
	struct stack **ExitStr = malloc(sizeof(struct stack**));
	(*ExitStr) = NULL;
	
	if(read_data(head,ExitStr)){
		printf("syntax error\n");
		return 0;	
	}

	int tmp = 1, tmp2;

	if((*ExitStr) && !(*head) && !((*ExitStr)->next)){
		printf("%d\n",(*ExitStr)->value );
		return 0;
	}

	while (((tmp = pop(head)) != 0) && ((*ExitStr) != NULL) ){
		if ((((tmp2 = f_calc(tmp, ExitStr)) == 1) && (*head)) ){
			printf("syntax error\n");
			return 0;
		}
	}
	if ((tmp2 == 1) || ((*ExitStr) == NULL) || (*ExitStr)->next){
		printf("syntax error\n" );
		return 0;
	}
	printf("%d\n",(*ExitStr)->value );
	return 0;

}

char read_data(struct stack **head, struct stack **ExitStr){

	int t, tmp, x;
	if((t = getchar()) != EOF){
		if(t == '-'){
			t = '`';
			push(head, t ,2);
		}
		else {
			ungetc(t,stdin);
		}
	}

	while (((t = getchar()) != EOF) && (t != '\n')){
		switch(t){
			case'(' :{
				push(head, t , 1);
				if ((t = getchar()) == ')'){
					ungetc(t,stdin);
					
					return ERROR;
				}
				else if (t == '-'){
					t = '`';
					push(head, t , 2);
				}
				else
					ungetc(t,stdin);
				break;
			}

			case')':{
				while ((tmp = pop(head)) != '('){
					if (( f_calc(tmp, ExitStr) != 0) ){
						return ERROR;
					}
					
				}
				break;
			}	
			case'+':{
				while (( (*head) && (*head)->priory >= 2)){
					
					if(f_calc(pop(head), ExitStr) == 3){
						return ERROR;

					}
				}
				push(head,t,2);
				break;
			}
			case'-':{
				
				while (((*head) && (*head)->priory >= 2) ){
					if(f_calc(pop(head), ExitStr) == 3){
						return ERROR;

					}
				}	
			push (head, t ,2);
			break;
			}
			case'*':{
				while (( (*head) && (*head)->priory >= 3)){
					if(f_calc(pop(head), ExitStr) == 3){
						return ERROR;

					}
				}	
				push (head,t,3);
				break;
			}	

			case'/':{
				while ( (*head) && ((*head)->priory >= 3)){
					if(f_calc(pop(head), ExitStr) == 3){
						return ERROR;

					}
				}	
				push(head,t,3);
				break;
			}	
			default:{
				ungetc(t,stdin);
				if (scanf("%d",&x) != 1){
					
					return ERROR;
				}	
				else{
					push(ExitStr, x, 0);
				}
				break;
			}	


		}		



	}
	return 0;

}

void push (struct stack **head, int value, int priory){
	
	struct stack *tmp = NULL;
	if((tmp = malloc(sizeof(struct stack))) == NULL){
		exit(1);
	}
	tmp->value = value;
	tmp->priory = priory;
	tmp->next = *head;
	*head = tmp;
}	


char pop (struct stack **head){

	if ((*head) == NULL){
		return 0;
	}

	char t = (*head)->value;
	struct stack *tmp = (*head);
	*head = (*head)->next;
	free(tmp);
	
	return t;
}

char f_calc (int operation, struct stack **ExitStr){
	if (*ExitStr == NULL){
		return ERROR;
	}
	if ((*ExitStr)->next == NULL && (operation != '`')){
		return ERROR;
	}
	

	struct stack *tmp = *ExitStr;

	int t1 = tmp->value;
	int t2 = 0;
	if ((tmp->next))
		t2 = (tmp->next)->value;
	switch(operation){
		case'+':
			(tmp->next)->value = t1 + t2;
			*ExitStr = (*ExitStr)->next;
			free(tmp);
			break;
		case'-':
			(tmp->next)->value = t2 - t1;
			*ExitStr = (*ExitStr)->next;
			free(tmp);
			break;
		case'*':
			(tmp->next)->value = t1 * t2;
			*ExitStr = (*ExitStr)->next;
			free(tmp);
			break;
		case'`':
			tmp->value = -t1;
			break;
		case'/':
			if (t1 == 0){
				printf("division by zero\n");
				exit (0);
			}
			(tmp->next)->value = t2/t1;
			*ExitStr = (*ExitStr)->next;
			free(tmp);
			break;			
	}
	return 0;

}

