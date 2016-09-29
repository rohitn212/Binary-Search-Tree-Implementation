#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
	int val;
	struct bst_node *left;
	struct bst_node *right;

};
typedef struct bst_node NODE;


struct bst {
	NODE *root;
	int size;
};

BST_PTR bst_create(){
	BST_PTR t = malloc(sizeof(struct bst));
	t->root = NULL;
	t->size = 0;
	return t;
}


static void free_r(NODE *r){
	if(r==NULL) return;
	free_r(r->left);
	free_r(r->right);
	free(r);
}
void bst_free(BST_PTR t){
	free_r(t->root);
	free(t);
}

static NODE * insert(NODE *r, int x){
	NODE *leaf;
	if(r == NULL){
		leaf = malloc(sizeof(NODE));
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->val = x;
		return leaf;
	}

	if(r->val == x)
		return r;
	if(x < r->val){
		r->left = insert(r->left, x);
		return r;
	}
	else {
		r->right = insert(r->right, x);
		return r;
	}
}

void bst_insert(BST_PTR t, int x){
	t->root = insert(t->root, x);
}

int bst_contains(BST_PTR t, int x){
	NODE *p = t->root;

	while(p != NULL){

		if(p->val == x)
			return 1;
		if(x < p->val){
			p = p->left;
		}
		else
			p = p->right;
	}
	return 0;  
}

static int min_h(NODE *r){
	if(r==NULL)
    return -1; // should never happen!
while(r->left != NULL)
	r = r->left;
return r->val;
}

static int max_h(NODE *r){
	if(r==NULL)
    return -1; // should never happen!
while(r->right != NULL)
	r = r->right;
return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success){
	NODE   *tmp;
	int sanity;

	if(r==NULL){
		*success = 0;
		return NULL;
	}
	if(r->val == x){
		*success = 1;

		if(r->left == NULL){
			tmp = r->right;
			free(r);
			return tmp;
		}
		if(r->right == NULL){
			tmp = r->left;
			free(r);
			return tmp;
		}
    // if we get here, r has two children
		r->val = min_h(r->right);
		r->right = remove_r(r->right, r->val, &sanity);
		if(!sanity)
			printf("ERROR:  remove() failed to delete promoted value?\n");
		return r;
	}
	if(x < r->val){
		r->left = remove_r(r->left, x, success);
	}
	else {
		r->right = remove_r(r->right, x, success);
	}
	return r;

}


int bst_remove(BST_PTR t, int x){
	int success;
	t->root = remove_r(t->root, x, &success);
	return success;
}

static int size(NODE *r){

	if(r==NULL) return 0;
	return size(r->left) + size(r->right) + 1;
}

int bst_size(BST_PTR t){
	t->size = size(t->root);
	return t->size;
}

static int height(NODE *r){
	int l_h, r_h;

	if(r==NULL) return -1;
	l_h = height(r->left);
	r_h = height(r->right);
	return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
	return height(t->root);
}

int bst_min(BST_PTR t){
	return min_h(t->root);
}

int bst_max(BST_PTR t){
	return max_h(t->root);
}

static void indent(int m){
	int i;
	for(i=0; i<m; i++)
		printf("-");
}

static void inorder(NODE *r){
	if(r==NULL) return;
	inorder(r->left);
	printf("[%d]\n", r->val);
	inorder(r->right);

}
void bst_inorder(BST_PTR t){

	printf("========BEGIN INORDER============\n");
	inorder(t->root);
	printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
	if(r==NULL) {
		indent(margin);
		printf("NULL \n");
	} else {
		indent(margin);
		printf("%d\n", r->val);
		preorder(r->left, margin+3);
		preorder(r->right, margin+3);
	}
}

void bst_preorder(BST_PTR t){

	printf("========BEGIN PREORDER============\n");
	preorder(t->root, 0);
	printf("=========END PREORDER============\n");

}

/* 
 * The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
	int m;
	NODE *root;

	if(n <= 0) return NULL;
	m = n/2;
	root = malloc(sizeof(NODE));
	root->val = a[m];
	root->left = from_arr(a, m);
	root->right = from_arr(&(a[m+1]), n-(m+1));
	return root;

}

BST_PTR bst_from_sorted_arr(int *a, int n){

	BST_PTR t = bst_create();

	t->root = from_arr(a, n);

	return t;
}


/***********************/
/* BEGIN NEW FUNCTIONS */
/***********************/

int cmpval (const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

int *store_array(NODE *r, int arr[], int *index) {
	
   /* Base Case */
	if (r == NULL) 
		return;

   /* Store left sub-tree and copy data*/
	store_array (r->left, arr, index);\

	arr[*index] = r->val;
	(*index)++;

   /* Store right sub-tree */
	store_array (r->right, arr, index);

	return arr; 
} 

extern int * bst_to_array(BST_PTR t) {
	int size = bst_size(t);
	int i = 0;
	int *arr = (int*)malloc(size * sizeof(int));

	store_array (t->root, arr, &i);
	
	return arr;
}

int smallest(NODE *p, int i) {
   //base case
	if (p == NULL)
		return -1;
	
	int target;
	target = smallest(p->left, i);

	if (target >= 0) return target;
	
	if (--i == 0) return p->val;

	target = smallest(p->right, i);

	if (target >= 0) return target;

	return -1; 
}

int bst_get_ith(BST_PTR t, int i) {
	int x = smallest(t->root, i);
	return x;   
}

int nearest(NODE *p, int x) {
   //base case
	if (p == NULL) return 0;
	
	int target = p->val;

	while (p != NULL) {
		if (x - (p->val) == 0)
			return p->val;
		else if (x - p->val < 0) {
			if (x - p->val >= x - p->val){
				target = p->val;
			}
			p = p->left;            
		}

		else if (x - p->val > 0) {
			if (x - p->val <= x-target) {
				target = p->val;
			}
			p = p->right;
		}
	}
	
	return target;
}

extern int bst_get_nearest(BST_PTR t, int x) {
	return nearest(t->root, x);
}

extern int bst_num_geq(BST_PTR t, int x) {
	int n = t->size;
	int *darr = (int*)malloc(n*sizeof(int));
	int count = 0;
	darr = bst_to_array(t);

	int i;
	for (i = 0; i < n; i++) {
		if (darr[i] >= x)
			count++;     
	}
	free (darr);

	return count;  
}

extern int bst_num_leq(BST_PTR t, int x) {
	int n = t->size;
	int *darr = (int*)malloc(n*sizeof(int));
	int count = 0;
	darr = bst_to_array(t);

	int i;
	for (i = 0; i < n; i++) {
		if (darr[i] <= x)
			count++;
	}
	free (darr);
	
	return count;
}
