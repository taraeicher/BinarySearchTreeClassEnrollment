/*Program Description: Manipulate a binary search tree. Key is a string defined in corresponding header file.
*						Contains file I/O used for printing and capturing key data.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 11/23/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "bin_search_tree.h"

//Sets the key a to the value of the key b.

void key_setequal(Key a, Key b)
{
	strcpy(a,b);
}
 
//Returns true (1) if the two keys are equal, or false (0) otherwise.
 
int key_isequal(Key a, Key b) 
{
	if(!strcmp(a,b))	//if difference between keys is zero
		return 1;
	else return 0;
}

//Returns true (1) if a comes before b in the order used for sorting.

int key_lessthan(Key a, Key b)
{
	if(strcmp(a,b)==-1)	//if b is greater than a
		return 1;
	else return 0;
}

//Initialize tree.

void tree_init(Tree *t)
{
	*t=NULL;	
}

//makes a new Node (with malloc), sets its key to k, its parent to parent, and its left and right children to NULL.

Node *tree_makenode(Key k, Node *parent)
{
	Node *node;		//return value
	
	//Set values based on user input.
	//Make sure the variable can be allocated first.
	
	if ((node = malloc(sizeof(Node))))
	{
		strcpy(node->key,k);
		node->parent=parent;
		node->leftchild=NULL;
		node->rightchild=NULL;
	}

	return node;
}

//Return a pointer to the root of the tree.

Node *tree_root(Tree t)
{
	return t;
}

//Return a pointer to the parent of a given node.

Node *tree_parent(Node *n, Tree t)
{
	return n->parent;
}

//Return a pointer to the left child of a given node.

Node *tree_leftchild(Node *n, Tree t)
{
	return n->leftchild;
}

//Return a pointer to the right child of a given node.

Node *tree_rightchild(Node *n, Tree t)
{
	return n->rightchild;
}

//Find and return the node that matches a given key.

Node *tree_search(Key k, Tree t)
{
	Node *match=NULL;   	//return value
	Node *node=t;		//dynamic pointer for traversal
	int unraveling=0;	//Set to 1 when the recursion process begins to unravel.

	//Search nodes in preorder to find key match.

	while(node&&!match&&!unraveling)
	{
		//If the key matches the node key, return the position of the node.
		//Otherwise, search the left subtree if the key is less than the node key.
		//Otherwise, the key is greater than the node key, so search the right subtree.

		int same=strcmp(node->key,k);

		if(same==0)
			match=node;
		else if(same>0)
		{
			match=tree_search(k,node->leftchild);

			//If the basis case (null child) has been reached, unraveling will start.
			//Do not re-enter while loop or an infinite loop will result.

			if(!match) unraveling=1;
		}
		else
		{
			match=tree_search(k,node->rightchild);

			//If the basis case (null child) has been reached, unraveling will start.
			//Do not re-enter while loop or an infinite loop will result.

			if(!match) unraveling=1;
		}

	}

	//Return a pointer to the match, even if null.

	return match;
}

//Return the number of children of a given node.

int tree_num_children(Node *n)
{
	int children=0;
	if (n->leftchild!=NULL) children++;
	if (n->rightchild!=NULL) children++;
	return children; 
}

//Insert a new node into the tree in sorted order.

void tree_insert(Tree *t, Key k)
{	
	//Make sure the key is valid first.

	if(k[0]!=(char)'?')
	{
		//If there are no nodes, create the first.

		if(tree_root(*t)==NULL)
			*t=tree_makenode(k,NULL);
	
		//Otherwise, insert the node into a suitable position or exit if a node with the key already exists.

		else
		{
			Tree sub=*t;			//subtree for checking
			Tree subParent=NULL;	//parent of subtree, used for final placement of node
			int right=0;			//holds whether the current subtree is a right or left subtree of its parent

			//Keep searching as long as key does not match the current node and the current node is not null.

			while(sub&&!key_isequal(k,sub->key))
			{
				//Hold place of current sub.
				
				subParent=sub;
				
				//If the key value is greater than the current node key, look at the right child.
				//Otherwise, look at the left child.
				//Case of equality is handled in the "while" statement.

				if(key_lessthan(k,sub->key))
				{
					sub=sub->leftchild;
					right=0;
				}
				else
				{
					sub=sub->rightchild;
					right=1;
				}
			}

			//If the loop finished because a null node was reached, insert a new node with the key here.

			if(!sub)
			{
				Tree new=tree_makenode(k,subParent);

				//Set the new node as either a right or left child of its parent based on "right" value.

				if(right)
					subParent->rightchild=new;
				else
					subParent->leftchild=new;
			
			}
		}
	}		
}

//Delete node with a given key.

void tree_delete(Tree t, Key k)
{	
	Node *node=tree_search(k,t);
	Node *replacement=NULL;

	//If there is a node to delete, replace and delete it.	

	if(node)
	{
		//If a left child exists, replace node with left child's rightmost descendant and subtree.

		if(node->leftchild)
		{
			replacement=node->leftchild;

			//Find left child's rightmost descendant.

			while(replacement->rightchild)
				replacement=replacement->rightchild;

			//Find left child's rightmost descendant's leftmost leaf.

			if(replacement!=node->leftchild)
			{
				Node *replacementLeftmostLeaf=replacement;
				while(replacementLeftmostLeaf->leftchild)
					replacementLeftmostLeaf=replacementLeftmostLeaf->leftchild;

				//Make left child of node descend from left child's rightmost descendant's leftmost leaf.

				node->leftchild->parent=replacementLeftmostLeaf;
				replacementLeftmostLeaf->leftchild=node->leftchild;
			}

			//Remove left child's rightmost descendant and subtree from former position.
			//Place it in position of node.

			replacement->rightchild=node->rightchild;
			if (node->rightchild)
				node->rightchild->parent=replacement;
			replacement->parent->rightchild=NULL;
				
			//Reset the parent.
				
			replacement->parent=node->parent;
		}

		//If there is no left child, replace it with its right child.
		//Reset the parent.

		else if(node->rightchild)
		{
			replacement=node->rightchild;
			replacement->parent=node->parent;
		}

		//Make node's parent point to node's replacement as a child.

		if(node->parent)
		{
			if(node->parent->leftchild==node)
				node->parent->leftchild=replacement;
			else
				node->parent->rightchild=replacement;
		}
	
		//Free the space.

		free(node);
	}
}

//Print the contents of the list to a given file in preorder.

void tree_preorder(Node *n, FILE *fp)
{
	//If node is not null, print the key and traverse recursively.

	if(n)
	{
		fprintf(fp,"%s\n",n->key);
		Node *left=NULL;			//placeholder for left child
		Node *right=NULL;			//placeholder for right child

		//If there is a left child, traverse it.
		//Do the same for a right child.
		
		if((left=tree_leftchild(n,n)))
			tree_preorder(left,fp);
		if((right=tree_rightchild(n,n)))
			tree_preorder(right,fp);
	}
}

//Print the contents of the list to a given file in postorder.

void tree_postorder(Node *n, FILE *fp)
{
	//If node is not null, traverse recursively and print the keys.

	if(n)
	{
		Node *left=NULL;			//placeholder for left child
		Node *right=NULL;			//placeholder for right child

		//If there is a left child, traverse it.
		//Do the same for a right child.
		//If there are no children, print the key.
		
		if((left=tree_leftchild(n,n)))
			tree_postorder(left,fp);
		if((right=tree_rightchild(n,n)))
			tree_postorder(right,fp);
		if(tree_num_children(n)==0)
			fprintf(fp,"%s\n",n->key);
	}
}

//Print the contents of the list to a given file in inorder.

void tree_inorder(Node *n, FILE *fp)
{
	//If node is not null, traverse recursively and print the keys.

	if(n)
	{
		Node *left=tree_leftchild(n,n);				//placeholder for left child
		Node *right=tree_rightchild(n,n);			//placeholder for right child

		//If there is a left child, traverse it.
		//Print the original node key.
		//If there is a right child, traverse it.
		
		if(left)
			tree_inorder(left,fp);
		fprintf(fp,"%s\n",n->key);
		if(right)
			tree_inorder(right,fp);
	}
}

//Determine whether the tree is empty.

int tree_empty(Tree t)
{
	//If front of queue is null, queue is empty.	

	if(tree_root(t)==NULL)
		return 1;
	return 0;
}

//Find the height of the tree.

int tree_height(Tree t)
{
	int height=-1;		//height of tree
	int hleft=0;		//heights of left and right subtrees
	int hright=0;		
	
	//If t is not null, find height recursively.
	
	if(t)
	{
		height++;
		hleft=tree_height(tree_leftchild(t,t));
		hright=tree_height(tree_rightchild(t,t));
		if(hleft>=hright)
			height+=hleft+1;
		else height+=hright+1;
	}
	return height;
}

//Delete all nodes in the tree.

void tree_makenull(Tree t)
{
	//Delete the node and its children.

	if(!tree_empty(t))
	{
		tree_delete(t,t->key);
		tree_delete(t->leftchild,t->leftchild->key);
		tree_delete(t->rightchild,t->rightchild->key);
	}		
}

//Populate empty list.

int populate(FILE *fp, Tree *t)
{
	int fileDone=feof(fp);				//Has EOF been reached?

	//If file is not empty, begin populating array.		

	while(!fileDone)
	{
		char *key=getKey(fp);			//Get the key.

		//If end of file, exit.
		//Otherwise, create a Node and populate key field. Free the space allocated for the key.
	
		if(*key=='!')
			fileDone=1;
		else tree_insert(t,key);
		free(key);
	}

	//Close the file. Return with 0 if the file could not be closed.

	if(!(fclose(fp)==0))
		return 2;

	//Return with a 1 if all went well.

	return 1;
}

//Construct the key from file data.

char *getKey(FILE *fp)
{
	//Get class.

	char class[7]={0};			//class string
	int ok=getString(class,7,':',fp); 	//Check for proper formatting.
	char *errVal=malloc(sizeof(char));
	char *endVal=malloc(sizeof(char));
	*errVal='?';				//Return pointer to question mark if input format is invalid.
	*endVal='!';				//Return pointer to exclamation point if end of file is reached.

	//Return '?' if not properly formatted.
	//Return '!' if end of file has been reached.

	if(!ok)
		return errVal;
	else if(ok==-1)
		return endVal;
		
	//Get first name.

	char first[31]={0};			//first name string
	ok=getString(first,31,':',fp); 	//Check for proper formatting.

	//Return '?' if not properly formatted.
	//Return '!' if end of file has been reached.

	if(!ok)
		return errVal;
	else if(ok==-1)
		return endVal;

	//Get middle name.

	char middle[31]={0};				//middle name string
	ok=getString(middle,31,':',fp); 	//Check for proper formatting.

	//Return '?' if not properly formatted.
	//Return '!' if end of file has been reached.

	if(!ok)
		return errVal;
	else if(ok==-1)
		return endVal;

	//Get last name.

	char last[31]={0};			//last name string
	ok=getString(last,31,'\n',fp); 	//Check for proper formatting.

	//Return '?' if not properly formatted.
	//Return '!' if end of file has been reached.

	if(!ok)
		return errVal;
	else if(ok==-1)
		return endVal;


	//If all went well, create a key in format "Last, First M" and return a pointer to it.

	int i=0; 	//counter
	int j=0;	//second counter	
	char *keyAddress=malloc(sizeof(Key));	//pointer to key string

	for(;i<strlen(last);i++)
		*(keyAddress+i)=last[i];
	*(keyAddress+(i))=',';
	*(keyAddress+(++i))=' ';
	++i;
	for(;j<strlen(first);i++,j++)
		*(keyAddress+i)=first[j];
	*(keyAddress+(i))=' ';
	*(keyAddress+(++i))=middle[0];
	*(keyAddress+(++i))=0;
	
	//Free the allocated ending and error values.
	
	free(errVal);
	free(endVal);
	
	return keyAddress;
}

//Print tree contents to a file using a specified order.

int printToFile(Tree t, FILE *fp, int order)
{
	//Handle order of traversal.

	switch(order)
	{
		case -1:	tree_postorder(t,fp);
					break;
		case 0:		tree_inorder(t,fp);
					break;
		case 1:		tree_postorder(t,fp);
					break;
		default:	break;
	}

	//Close the file. Return with 0 if the file could not be closed.

	if(!(fclose(fp)==0))
		return 0;
	return 1;
}

//Delete the specified records from a file.

int deleteFromFile(FILE *fp, Tree t)
{
	int fileDone=feof(fp);				//Has EOF been reached?

	//If file is not empty, begin populating array.		

	while(!fileDone)
	{
		char *key=getKey(fp);		//Get the key.

		//If end of file, exit.
		//Otherwise, delete the nodes in the tree that contain the given key. Free the space allocated for the key.
	
		if(*key=='!')
			fileDone=1;
		else tree_delete(t,key);
		free(key);
	}

	//Close the file. Return with 0 if the file could not be closed.

	if(!(fclose(fp)==0))
		return 2;

	//Return with a 1 if all went well.

	return 1;
}
