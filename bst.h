
// typedef int ELEM_TYPE;

typedef struct bst *BST_PTR;

extern BST_PTR bst_create();

extern void bst_free(BST_PTR t);

extern void bst_insert(BST_PTR t, int x);

extern int bst_remove(BST_PTR t, int x);

extern int bst_contains(BST_PTR t, int x);


extern int bst_size(BST_PTR t);

extern int bst_height(BST_PTR t);

extern int bst_min(BST_PTR t);

extern int bst_max(BST_PTR t);

extern void bst_inorder(BST_PTR t);

extern void bst_preorder(BST_PTR t);

extern BST_PTR bst_from_sorted_arr(int *a, int n);

extern int * bst_to_array(BST_PTR t);

extern int bst_get_ith(BST_PTR t, int i);

extern int bst_get_nearest(BST_PTR t, int x);

extern int bst_num_geq(BST_PTR t, int x);

extern int bst_num_leq(BST_PTR t, int x);
