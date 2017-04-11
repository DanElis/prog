#include <stdio.h>
#include <stdlib.h>
#define ERROR 1

struct BSTree // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	struct BSTree* left;
	struct BSTree* right;
};
char read_data (struct BSTree **Tr);
struct BSTree* balance(struct BSTree* p);
struct BSTree* insert(struct BSTree* p, int k);
struct BSTree* rotateleft(struct BSTree* q);
struct BSTree* rotateright(struct BSTree* p);
void fixheight(struct BSTree* p);
int bfactor(struct BSTree* p);
unsigned char height(struct BSTree* p);
struct BSTree *construct(int key);

int main (){
	struct BSTree **Tr = malloc(sizeof(struct BSTree**));
	*Tr = NULL;
	if (read_data(Tr)){
		printf("ERROR\n" );
		return 0;
	}
	(*Tr) ? printf("%d",(*Tr)->height) : printf("0\n");


	return 0;

}

char read_data (struct BSTree **Tr){
	int n = 0 ;
	if (scanf("%d",&n) != 1){
		return ERROR;
	}
	int key;
	for (int i = 0; i < n; i++){
		if (scanf("%d", &key) != 1){
			return ERROR;
		}
		*Tr = insert(*Tr, key);
	}
	return 0;
}


struct BSTree* balance(struct BSTree* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

struct BSTree* insert(struct BSTree* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return construct(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

struct BSTree* rotateleft(struct BSTree* q) // левый поворот вокруг q
{
	struct BSTree* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

struct BSTree* rotateright(struct BSTree* p) // правый поворот вокруг p
{
	struct BSTree* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}
void fixheight(struct BSTree* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

int bfactor(struct BSTree* p)
{
	return height(p->right)-height(p->left);
}

unsigned char height(struct BSTree* p)
{
	return p?p->height:0;
}

struct BSTree *construct(int key){
	struct BSTree *tmp = malloc(sizeof(struct BSTree*));
	tmp->key = key;
	tmp->height = 1;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
