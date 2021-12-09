/* 

PROGRAMMING ASSIGNMENT-1;
Multiplying two polynomials

By: Suyash Srivastava and Mohan Krishna

A polynomial is represented by a list.

This program assumes that the exponents of polynomial given as input are given in 
ascending order and no coefficient is zero(according to statement of the problem). 
Structures NODE, LIST are used. 
Functions cnd(create node),clst(create list),append,delete,rmvz(remove zeroes),
add, inlist(input list), plist(print list) are used; and a rough description has been 
provided at the beginning of it. 
For adding, first we traverse the two list and store the sum in a third list.
If the exponents of the current node are same, we add the coefficients 
and store(append) them in a node of sum list.
If the exponent of current node of list a is smaller than that of list b 
(exponents are given in ascending order) then we append the smaller node into sum list
(so that the resulting sum has exponents in ascending order); 
and vice versa.
For Multiplication, we first multiply one list with the first element of other list, store it into
the final list, then we multiply second element of other list with whole list, and add it into the final
list within constaints (exponents in increasing order etc). And so on, we multiply each element of one list
with whole of second list and we add all such lists.
*/
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>//for INT_MAX

struct NODE//creates a node element of list
{
  int cf;//coefficient
  int exp;//exponent
  struct NODE* next;
  struct NODE* prev;
};

struct LIST//creates a list; basically sentinel of a list
{
  struct NODE * nil;
};

typedef struct NODE node;
typedef struct LIST list;

node * cnd(int c, int e) //allocs memory for a node, initializes it and returns a pointer to it
{
  //c=coefficient, e=exponent
  node* nd = (node *) malloc (sizeof (node));
  nd -> cf = c;
  nd -> exp = e;
  nd -> next = nd;
  nd -> prev = nd;
  return nd;
}

list clst()//creates a list, initializes the exponent of sentinel node to INT_MAX
{
  list lst;
  lst.nil = cnd (0,INT_MAX);
  return lst;
}
/*append is used to add the node at the end of the linked list.*/
list append (list lst, node* nd)
{
  nd -> next = lst.nil;
  nd -> prev = lst.nil->prev;
  lst . nil -> prev -> next = nd;
  lst . nil -> prev = nd;
  return lst;
}
void delete (node* nd)//used to delete a node in the linked list
{
  nd ->prev->next = nd->next;
  nd ->next->prev = nd -> prev;
      free(nd);
}

list empty(list lst)//empties the list, deletes all the nodes of that list
{
  node * nx;
  while ((nx=lst.nil->next)!=lst.nil)
  {
    delete(nx);
  }
  return lst;
}

list rmvz(list lst)//removes all the elements with 0 coefficient in list
{
  node * nx = lst.nil->next, *na;
  while (nx!= lst.nil)
  {
      na = nx->next;//traverses the list
    if (nx -> cf== 0)
    {
      
      delete(nx);
      
    }
    nx = na;
  }
  return lst;//list without 0 coefficient nodes
}

void plist (list lst)//prints the elements of the list
{
  node * nx=lst.nil;
  while ((nx = nx->next)!=lst.nil)//traverses the list till it reaches the end
  {
    printf("%d %d ", nx->cf, nx->exp);
  }
}

list add (list a, list b)
{
  list s = clst();//sum
  node* na = a.nil->next, *nb = b.nil->next;//we start from first non-nil element of the list
  while (!(na == a.nil) || !(nb == b.nil))//the loop runs till BOTH lists aren't exhausted
  {
    //if one list is completely exhausted then we return back to the sentinel node
    //because the exponent of sentinel node is infinity(max. value which can be stored as an integer)
    //the elements of other list are appended directly.
    //We use the fact that exponents in a list are in increasing order, and after
    //one list is completely exhausted, the elements remaining in second list
    //are in increasing order and all are greater than those in first(exhausted) list.
    if ((na->exp==nb->exp))//exponents same, directly add the elements and store in sum
      {
          s = append (s, cnd(na->cf+nb->cf, na->exp));
          if (na != a.nil) na = na-> next;//move one element forward in list
          if (nb != b.nil) nb = nb -> next;//move one element forward in list
      }
    else if ((na->exp > nb->exp))
     {
       s = append (s, cnd (nb->cf, nb->exp));
       nb = nb -> next;//move one element forward in list
     }
    else 
     {
       
       s = append (s, cnd (na-> cf, na -> exp));
       na = na -> next;//move one element forward in list
     }
   }
  return s;
}

list mult1 (list b, node * na)
//multiplies the elements of a linked list with a constant, which is the coefficient of a node
{
  list p1 = clst();//creates list
  node * nb = b.nil;
    while (!((nb=nb->next) == b.nil))
    {
      p1 = append(p1,cnd(nb->cf*na->cf, nb->exp+na->exp));
    }

  return p1;
}

list mult (list a, list b)//multiplies two lists
{//to multiply two lists, we multiply each element of one list with complete second list using
//mult1 and then we add all such sub-lists into a main list; ensuring constraints while adding.

  list p = clst();//creates a list
  node * na = a.nil;
  while (!((na=na->next) == a.nil))
  {
    list q = mult1(b, na);
    p = add (p, q);
    empty(q);//we empty this list
  }
  return p;
}

list inlist (int len)//takes input of the list
{
  list a = clst();//creates list
  node * na = a.nil;
  int c, e;
  for(int i=0;i<len;i++)
  {
    scanf ("%d %d",&c,&e);
    a= append(a,cnd (c, e));
  }
  return a;
}

int main()
{
  int plen, qlen;
  scanf ("%d %d",&plen,&qlen);//takes in lengths of lists
  list p = inlist (plen);
  list q = inlist (qlen);
  plist(rmvz(mult(p,q)));//adds the two lists, removes zero coefficients and prints it
}
