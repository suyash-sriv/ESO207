/*
ReadMe:
The functions readTree and WriteTree are written if we want the user to input the two trees. In that case, the user has to enter the full tree in the following input format:

n is the number of nodes of the tree.
Input format(readTree): 
n
2 a 3 x y 2 r 1 a 1 b 1 c 1 w 1 g

writeTree prints in the following format:
Output format(WriteTree): 2 a 3 x y 2 r 1 a 1 b 1 c 1 w 1 g

2 implies it's a 2-node
3 implies it's a 3 node
1 implies it's a leaf node

x y r a b c w g are all integers in accordance to the rules of a 2-3 tree.

The above is the level order traversal format for the following  tree:

               2 a 

     3 x y              2 r 

1 a 1 b 1 c           1 w 1 g

The program doesn't call these functions; but if needed appropriate modifications can be made. The program forms the trees using a for loop in the main function. 

Extract prints only the leaves of the tree (using pre-order traversal).

ParseSet takes the input in the following format:
n
1 2 3 4 5 6 7 8 9 

Where n is the number of elements in the set. 

ParseSet returns a 2-3 tree which stores the set elements(data) at the leaves.

TestSet calls ParseSet twice, and stores the two 2-3 trees thus returned. It then prints the Set represented by the tree formed by merging them.

The user should enter the sets (during input) such that the elements in the first set are strictly less than the elements in the second set.

ReadMe:
The functions readTree and WriteTree are written if we want the user to input the two trees. In that case, the user has to enter the full tree in the following input format:

n is the number of nodes of the tree(<=5000(LENTH), can be changed if needed).
Input format(readTree):
n
2 a 3 x y 2 r 1 a 1 b 1 c 1 w 1 g

writeTree prints in the following format:
Output format(WriteTree): 2 a 3 x y 2 r 1 a 1 b 1 c 1 w 1 g

2 implies it's a 2-node
3 implies it's a 3 node
1 implies it's a leaf node

x y r a b c w g are all integers in accordance to the rules of a 2-3 tree.

The above is the level order traversal format for the following  tree:

               2 a

     3 x y              2 r

1 a 1 b 1 c           1 w 1 g

The program doesn't call these functions; but if needed appropriate modifications can be made. The program forms the trees using a for loop in the main function.

Extract prints only the leaves of the tree (using pre-order traversal).

ParseSet takes the input in the following format:
n
1 2 3 4 5 6 7 8 9

Where n is the number of elements in the set.

ParseSet returns a 2-3 tree which stores the set elements(data) at the leaves.

TestSet calls ParseSet twice, and stores the two 2-3 trees thus returned. It then prints the Set represented by the tree formed by merging them.

The user should enter the sets (during input) such that the elements in the first set are strictly less than the elements in the second set.

*/
#include <stdio.h>
#include<limits.h>
#include <stdlib.h>
#define NMR INT_MIN
#define LENGTH 5000

typedef struct NODE 
{
  int mid ; //stores min of middle subtree 
  int rt ; //stores min of right subtree
} NODE ;

typedef struct tree
{
  NODE * root ;
 //stores vals on that node
  struct tree * left ;
  struct tree * right ;
  struct tree * middle ;
  struct tree * parent ;
} TREE ;

NODE * cnd (int MID, int RT)
//creates a node with MID=smallest element in middle subtree, RT=smallest element in right subtree
{
  NODE * pnd = (NODE *) malloc (sizeof (NODE)) ;
  pnd -> mid = MID;
  pnd -> rt = RT;
  return pnd;
}

TREE * ctr (NODE * ROOT,  TREE * PARENT, TREE * LEFT, TREE * MIDDLE, TREE *RIGHT) {
        //creates a subtree ; we give root, parent of that subtree (nil if it's a full tree)
        //left,middle,right subtrees (nil if it's a leaf)
  TREE * ptree = (TREE *) malloc (sizeof(TREE)) ;
  ptree -> root = ROOT ;
  ptree -> left = LEFT ;
  ptree -> middle = MIDDLE ;
  ptree -> right = RIGHT ;
  ptree -> parent = PARENT;
  if(ptree->left!=NULL)
  ptree -> left -> parent = ptree;
  if(ptree->middle!=NULL)
  ptree -> middle -> parent = ptree;
  if(ptree->right!=NULL)
  ptree -> right -> parent = ptree;

  return ptree ;
}

TREE ** cpp (TREE * a, TREE * b, int c) //a and b are TREE * s, c is an integer (min of TREE b)
{
  TREE ** pp = (TREE **) malloc (sizeof (TREE *) * 3) ;
  pp [0] = a ;
  pp [1] = b ;
  pp [2] = ctr (cnd (c , NMR), NULL, NULL, NULL, NULL) ;//returns
  return pp ;
}

void printRoot (TREE * ptree)
{//prints the type of node; 1 if it's a leaf, 2 if it has 2 children and 3 if it has 3 children
//along with data in it; if it's a leaf then value stored in it;
//if it has 2 children then minimum value in the right subtree
//else it prints the minimum value in middle subtree and minimum value in right subtree
  NODE * pnd = ptree -> root;
  if (!(ptree-> left)) printf("1 %d ", pnd -> mid);
  else if (!(ptree-> right)) printf("2 %d ", pnd -> mid);
  else printf("3 %d %d ",pnd -> mid,pnd -> rt);
}
void wrTr (TREE ** ptrs)
{//Level order Tree Traversal; function takes in root of the tree and prints the elements level-wise.
//if x->left =NULL then x is a leaf; if x->right=NULL then x has 2 children else x has 3 children
  int i = 0, j = 1;
  while (i < j)
  {
    TREE * x = ptrs[i++];//pop element from queue and print it
//    printf("%d %d ", i, j);
    printRoot (x);
    if (x -> left) ptrs[j++] = x-> left;//push children of the element at index i into the queue
    if (x -> middle) ptrs [j++] = x-> middle;//"       "        "         "        "         "
    if (x-> right) ptrs [j++] = x-> right;// "       "        "         "        "         "
  }
}
void writeTree (TREE * ptree)
{
  TREE * ptrs [LENGTH];
  for (int i = 0; i< LENGTH; i++)
  {
          ptrs [i] = NULL;
  }
  if (ptree)
  {
    ptrs[0] = ptree;//store pointer to root in 0th index of array
    wrTr (ptrs);
  }
  //printf("writeTree");

}
TREE * readTree(int a)//a is number of nodes in the tree
{//returns the root of the tree; which is stored in 0th index
  TREE* ptrs [LENGTH];//ptrs is an array of pointers which stores pointers to elements of trees
  for (int i = 0; i< LENGTH; i++)
  {
          ptrs [i] = NULL;//initializing pointers
  }
  int k = 0, i = 0, j = 1, mid, rt, flag = 1;
  /*i gets incremented as soon as all the children of a node are linked with that(parent) node
ptrs[i] stores the current parent node whose children are being scanned into the array

k keeps track of the total number of tree elements which are stored in ptrs
When the root is scanned; k gets the value 1; and so on.

j represents (one more than) the number of nodes which have been linked with their parents.
Because root has no parent we start from j=1.

When k-j equals the number of children for ptrs[i](2 or 3); we then have
all the children of ith element stored in array; hence we make links between ith node and it's children;
and increment j as we make links. After we have made all links for ptrs[i]; we increment i.

mid is for the maximum value in middle subtree; rt is for max value in right subtree(if element has 3 children)
If it has 2 children; we rt=NMR; and it isn't acessed*/
while (a--)
  {
    int type;//element has 2 children or 3 children
    scanf ("%d", &type);
    if (type < 1) { flag = 0; continue; }
    scanf ("%d", &mid);
    if (type == 3) scanf ("%d", &rt);//3 children
    else rt = NMR;//2 children
    TREE * temp = ctr (cnd (mid, rt), NULL, NULL, NULL, NULL);//create the element(and allocate memory for it)
    ptrs [k++] = temp;//store the pointer to the element in array; increment k.
    if ((k - j) >= ((ptrs [i] -> root -> rt > NMR)? 3: 2))
    {//if the right entry is NMR then it is a 2-child element; else 3. 
      ptrs [i] -> left = ptrs [j++];//make links; and increment j
      ptrs [i] -> middle = ptrs [j++];
      ptrs [i] -> left -> parent = ptrs[i];
      ptrs [i] -> middle -> parent = ptrs[i];
      if (ptrs [i]-> root ->rt > NMR)//if 3-child element; make further links
      {
        ptrs [i] -> right = ptrs [j++];
        ptrs[i] -> right -> parent = ptrs[i];
      }
      i++;//increment i after all links have been made
    }
//    writeTree(ptrs[0]);
//    printf("\n");
//    printf("k %d i %d j %d mid %d rt %d \n", k, i, j, mid, rt);
  }
   return ptrs [0];

}
int height (TREE * A)//returns height of tree
{
    TREE * child = A; int height = - 1;
    while (A = child, height ++,  child = A -> left) { }
    return height ;
}
int min (TREE * A)//returns minimum item in the subtree
{
    TREE * child = A ;
    while (A = child, child = A -> left) { }
    return A -> root -> mid ;
}
TREE * trunk (TREE * branch)//RETURNS root of the tree
{
    return branch -> parent ? trunk (branch -> parent) : branch;
}
TREE * Combo (TREE * A, TREE * B)//returns a tree; create a node and make A and B trees children of it.
{
    return ctr (cnd (min (B), NMR), NULL, A, B, NULL) ; 
}

TREE * MergeIntoLeft (TREE * ptr, TREE * Second)
{//Make Second a right-sibling of ptr
    TREE * ancestor ;
    if (ancestor = ptr -> parent)
    {
        if (ptr == ancestor -> right)//ancestor has 3 children 
        {
            ancestor -> right = NULL ;
            return MergeIntoLeft (ancestor, Combo (ptr , Second)) ;
        }//Ancestor has 2 children, directly add second as right sibing
        ancestor -> right = Second ;
        ancestor -> root -> rt = min (Second) ;
        Second -> parent = ancestor;
        return trunk(ancestor) ;
    }
    return Combo (ptr, Second) ;
}

TREE * MergeIntoRight (TREE * First, TREE * ptr)
{//Make First a left sibling of ptr
    TREE * Ancestor = ptr -> parent ;
    if (Ancestor)
    {
        if (Ancestor -> right)//Ancestor has 3 children
        {
            TREE * temp = Ancestor -> left ;
            temp -> parent = NULL ;
            Ancestor -> left = Ancestor -> middle; 
            Ancestor -> middle = Ancestor -> right;    
            Ancestor -> right = NULL;
        return   MergeIntoRight (Combo (First, temp), Ancestor);//insert recursively
        }//Ancestor has 2 children; add First as leftmost child.
        Ancestor -> right =  Ancestor -> middle;
        Ancestor -> middle = Ancestor -> left;
        Ancestor -> left = First;
        First -> parent = Ancestor;
        Ancestor -> root -> rt = Ancestor -> root -> mid;
        Ancestor -> root -> mid = min (Ancestor -> middle);
        return trunk(Ancestor);
    }
    return Combo (First, ptr);
}

TREE * Merge (TREE * First, TREE * Second)
{//Merge such that the leaves corresponding to A (in resultant tree)
 //are on the left side of leaves corresponding to B
    if (!First) return Second;
    if (!Second) return First;
    int A = height (First) ;
    int B = height (Second) ;
    if (A < B)//make root of "First" child of appropriate node in Second
    {
        TREE * ptr = Second ;
         for (int i = 0 ; i < B - A ; i ++, ptr = (ptr -> left)) { }
        return (MergeIntoRight (First, ptr));
    }
    TREE * ptr = First ;//Opposite
    for (int i = 0 ; i < A - B ; i ++, ptr = (ptr -> right) ? (ptr -> right) : (ptr -> middle)) { }
    return (MergeIntoLeft (ptr, Second)) ;
}            
TREE * MakeSingleton (int val)//returns a tree with one element
{
    return (ctr (cnd (val, NMR), NULL, NULL, NULL, NULL)) ;
}
void Extract (TREE * A)//prints all the leaf(data) elements of a tree
{
    if (! (A -> left)) printf ("%d " , (A -> root -> mid)) ;
    else
    {
        Extract (A -> left) ;
        Extract (A -> middle) ;
        if (A -> right) Extract (A -> right) ;
    }
}

void Test ( )//test program
{
    int a,b;
    TREE * A = MakeSingleton (1) ; 
    for (int a = 2 ; a < 501 ; a++) 
    {
        A = Merge (A , MakeSingleton (a)) ;
    }
    TREE * B = MakeSingleton (777) ;
    for (int b = 778 ; b < 1001 ; b ++ )    
    {
        B = Merge (B , MakeSingleton (b)) ;
    }
    TREE * C = Merge (A, B) ;
    Extract (C) ;
}
TREE * ParseSet ( )
{
	int i, a;
	scanf("%d" , &a);
	TREE * A = NULL;
	while (a--)
	{
		scanf("%d", &i);
		A = Merge (A, MakeSingleton(i));
	} 
	return A;
}
void TestSet ()
{
	int a, b;
	TREE * A = ParseSet( );
	TREE * B = ParseSet( );
	Extract (Merge (A, B));
}	


int main()
{
    Test ( ) ;
    //TestSet ( );
    return 0;
}
//SplitTree Change reverse order of union of forests
