#include <stdlib.h>
#include <stdio.h>


#define MAX_VERTEX 5000
#define INT_MAX 2147483647
typedef struct {
    int parent;
    int rank;
} Subset;

typedef struct {
	int src, dest, weight;
} Edge;

typedef struct {
	int n;                 
	int m;                          
	Edge *edges;
	char not_connectivity;  
} *Graph;
void subset_union(Subset *subsets, int x, int y);
int subset_find(Subset *subsets, int i);
int edge_comp (const void *a, const void *b);
char read_data (Graph gr);
void InitGr(Graph gr);
void kruskal (Graph gr, Edge *min_tree);
void push(Edge next_edge, Edge *min_tree, int k);
int edge_comp (const void *a, const void *b);
void print_min_tree (Graph gr, Edge *min_tree);


int main (){
	Graph gr = malloc(sizeof(Graph));
	if ((gr == NULL) ){
		printf("error\n");
		exit(1);
	}

	if (read_data (gr))
		return 0;
	Edge *min_tree = malloc(sizeof(Edge)*gr->n);
	(kruskal(gr, min_tree));
	
	print_min_tree(gr, min_tree);

	return 0;
}



char read_data (Graph gr){

	if (scanf("%d %d", &gr->n, &gr->m) != 2 ){
		printf("bad number of lines\n" );
		return 1;
	}


	if((gr->n < 0) || (gr->n > MAX_VERTEX)){
		printf("bad number of vertices\n");
		return 1;
	}

	if ((gr->m < 0) || (gr->m > gr->n*(gr->n+1)/2)){
		printf("bad number of edges\n");
		return 1;
	}


	InitGr(gr);

	int src = 0, dest = 0, weight = 0;
	for (int i = 0; i < gr->m; i++ ){

		if(scanf("%d %d %d", &src , &dest, &weight) != 3){
			printf("bad number of lines\n" );
			return 1;
		}
		if ((src < 1) || (src > gr->n) || (dest < 1) || (dest > gr->n)){
			printf("bad vertex\n");
			return 1;
		}
		if ((weight < 0) || (weight > INT_MAX)){
			printf("bad length\n");
			return 1;
		}
		src--;
		dest--;
		gr->edges[i].weight = weight;
		gr->edges[i].src = src;
		gr->edges[i].dest = dest;

	}
	return 0;

}


void InitGr(Graph gr){
	if (gr->m)
		gr->edges = malloc(sizeof(Edge)*gr->m);
	else if (gr->n != 1){
		printf("no spanning tree\n");
		exit(0);
	}
	if (gr->edges == NULL){
		printf("error\n");
		exit(1);
	}
	gr->not_connectivity = 0;	
}


void kruskal (Graph gr, Edge *min_tree){
	int x,y;
	qsort(gr->edges, (size_t)gr->m, sizeof(Edge), edge_comp);
	Subset *subsets = (Subset *) malloc (gr->n * sizeof(Subset));
	if (!subsets){
		printf("error\n");
		exit(1);
	}
	for (int i = 0; i < gr->n ; i++){
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	Edge next_edge ;
	int k = 0, i = 0;
	while ((k < gr->n - 1) && (i < gr->m)){
		next_edge = gr->edges[i++];
		x = subset_find(subsets, next_edge.src);
		y = subset_find(subsets, next_edge.dest);
		if (x != y){
			min_tree[k++] = next_edge;
			subset_union(subsets, x , y);
		}	
	}
	gr->not_connectivity += (k == gr->n - 1) ? 0 : 1;
}




int subset_find(Subset *subsets, int i) {
	if (subsets[i].parent != i) {
		subsets[i].parent = subset_find(subsets, subsets[i].parent);
	}
	return subsets[i].parent;
}

void subset_union(Subset *subsets, int x, int y) {
	int xroot = subset_find(subsets, x);
	int yroot = subset_find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	} else if (subsets[xroot].rank > subsets[yroot].rank) {
		subsets[yroot].parent = xroot;
	} else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}


int edge_comp (const void *a, const void *b){
	return ((Edge *) a)->weight > ((Edge *) b)->weight;
}

void push(Edge next_edge, Edge *min_tree, int k){
	min_tree[k] = next_edge;
}

void print_min_tree (Graph gr, Edge *min_tree){
	if ((!gr->n) || (gr->m < (gr->n - 1)) || gr->not_connectivity) {
		printf("no spanning tree\n");
	}
	else{
		for (int i = 0; i < gr->n - 1; i++){
			printf("%d %d\n",min_tree[i].src + 1, min_tree[i].dest + 1 );
		}
	}
}