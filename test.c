#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int main(){
    int i;

    /* PART 1 */

    int a[] = {8, 2, 6, 9, 11, 3, 7};

    BST_PTR t = bst_create();

    for(i=0; i<7; i++)
        bst_insert(t, a[i]);

    assert(bst_size(t) == 7);

    /* PART 2 */
    
    bst_inorder(t);

    bst_preorder(t);

    bst_postorder(t);

    /* MY TESTS */
    //test variables
    int x = 4;
    i = 2;
    int n = bst_size(t);
    int *inorder = (int*)malloc(n*sizeof(int));
    int j;
    inorder = bst_to_array(t);

    printf("\nTEST FUNCTION OUTPUT:\nARRAY: ");
    for (j = 0; j < n; j++)
       printf("%d ", inorder[j]);
    
    printf("\n");
    int ith = bst_get_ith(t, i);
    printf("The %dnd smallest value is %d\n",i,ith);

    int nearest = bst_get_nearest(t, x); 
    printf("The nearest value to %d is %d\n", x, nearest);

    int geq = bst_num_geq(t, x);
    printf("The number of elements that are >= %d is %d\n", x, geq);

    int leq =  bst_num_leq(t, x);
    printf("The number of elements that are <= %d is %d\n\n", x, leq);
   
    bst_free(t);
    
    /* PART 3 (extra) */
    
    int sorted_a[] = {2, 3, 6, 7, 8, 9, 11};
    
    t = bst_from_sorted_arr(sorted_a, 7);
    
    bst_inorder(t);

    bst_preorder(t);
    
    bst_free(t);

}
