/*
 * PROGRAMMING ASSIGNMENT-3;
 * Checking if a given connected graph is Biparite
 * If the graph is bipartite, we return a partitioning of its vertices

By: Mohan Krishna and Suyash Srivastava
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node * next;
} vertex;//defining vertex

int flag=1;
//If flag=1 then the graph is bipartite; if it is -1 then it is not bipartite
//It is assumed that initially graph is bipartite. When we encounter a contradiction
//We make flag=-1

void input(vertex *adj[],vertex *tail[],int numvertex,int numedges)//takes in input
{
    //end of adjacency list of vertex i is represented by pointer tail[i]

    for(int i=0;i<numedges;i++)//inputs all the edges into adjacency list
    {
        int startvertex, endvertex;
        //Because the graph is undirected, there will be a symmetric version of each edge
        //i.e. corresponding to each entry, there will be another edge
        //whose endvertex will be equal to the entry's startvertex 
        //and startvertex of symmetric version will be equal to entry's endvertex.
        scanf("%d %d",&startvertex,&endvertex);
        vertex *temp=(vertex *)malloc(sizeof(vertex));//allocate memory for temp
        temp->data=endvertex;//need to insert endvertex into adjacency list of startvertex
        temp->next=NULL;
        if(adj[startvertex]==NULL)//No edge is in adjacency list of startvertex
         {
             adj[startvertex]=temp;
             tail[startvertex]=temp;//correct tail of adjacency list of startvertex
         }
        else 
        {
            tail[startvertex]->next=temp;//add at the end of adjacency list 
            tail[startvertex]=temp;//correct tail of adjacency list of startvertex
        }
        //Symmetric version of entry's edge; invert startvertex and endvertex.
        vertex *temp2=(vertex *)malloc(sizeof(vertex));
        temp2->data=startvertex;
        temp2->next=NULL;
        if(adj[endvertex]==NULL)
         {
             adj[endvertex]=temp2;
             tail[endvertex]=temp2;
         }
        else
        {
            tail[endvertex]->next=temp2;
            tail[endvertex]=temp2;
        }
    }
}
void assignset(vertex *adj[],int setnumber[],int i, int set)
//use depth first search to assign sets to each vertex
{
    int neighbour;//set which should be assigned to neighbouring vertices of i
    if(setnumber[i]==0)
      setnumber[i]=set;//i hasn't been visited yet; assign set to it
    if(setnumber[i]!=set)
     {//Has been already assigned set before, and this is NOT equal to the set which it SHOULD be assigned
     //from the value passed in function call
         flag=-1;
         return;
     }  
    if(setnumber[i]==1)
      neighbour=2;//if vertex is in set 1 then all it's neighbours must be in set 2
    else    
      neighbour=1;//vice versa
    vertex *temp=adj[i];//to traverse the adjacency list of i
    while(temp!=NULL)
    {
        if(setnumber[temp->data]==0)//the vertex in adjacency list hasn't been visited
        assignset(adj,setnumber,temp->data,neighbour);//assign set to it (Depth First Search)
        if(setnumber[temp->data]!=neighbour)
           {//Has been already assigned set before, and this is NOT equal to the set which it SHOULD be assigned
           //considering that all the neighbours of a vertex must be in set 2 if vertex is in set 1
           //and vice versa
               flag=-1;
               return;
           }
        temp=temp->next;//traverse adjacency list
    }
}
int main()
{
    int numvertex,numedges;
    scanf("%d %d",&numvertex,&numedges);
    if(numvertex<2)//number of vertices is 0 or 1; graph is not bipartite
    {
        flag=-1;
        printf("NO");
        return 0;
    }
    vertex *adj[numvertex], *tail[numvertex];
    int setnumber[numvertex];
    //adj: array of pointers; they point to adjacency lists of the corresponding index.
    //tail: points to last element of adjacency list
    //setnumber: contains the set number of the vertex;
    //if it is in set 1 then setnumber[i] is 1
    //"     "      "  2     "       "      " 2
    //if it hasn't been visited yet then setnumber is 0 by default
    for(int i=0;i<numvertex;i++)
    {
        adj[i]=NULL;
        tail[i]=NULL;
        setnumber[i]=0;
    }//initialization
    input(adj,tail,numvertex,numedges);//scan in all the edges into adjacency list
    for(int i=0;i<numvertex;i++)
    {
        if(setnumber[i]==0)
        assignset(adj,setnumber,i,1);
        //if hasn't been visited (in case of non-connected graph or if i=0)
        //then assignset 1 to it, and assign sets to other vertices for which a path
        //to i exists using DFS (so that bipartite property holds)
        //if bipartite property is violated at any point, flag becomes -1
        //and we exit the loop
        if(flag==-1)
         break;
    }
    if(flag==1)
     {//Graph is bipartite, print the sets for each vertex
        printf("YES");
        for(int i=0;i<numvertex;i++)
        {    
            printf("\n");
            printf("%d",setnumber[i]);
        }
    }
    else//graph is NOT bipartite
     printf("NO");
    return 0;
}
