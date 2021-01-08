#include<stdio.h>
#include<stdlib.h>


typedef struct BST
{
	int data;
	struct BST *left;
	struct BST *right;
}node;



node *create();
void insert(node*,node *);
void preorder(node *);
void postorder(node *);
int BST(node *);
int BSTutil(node *, int min, int max);


int BST(node *root)
{
	return (BSTutil(root,INT_MIN,INT_MAX));
}

int BSTutil(node* root, int min, int max)
{
	if(root == NULL)
	  return 1;
	  
	 if(root->data < min || root->data > max)
	  return 0;
	  
	  return BSTutil(root->left,min,root->data-1) && BSTutil(root->right,root->data+1,max);
	
}

node *create()
{
	node *temp;
	printf("enter the data\n");
	temp = (node*)malloc(sizeof(node));
	scanf("%d", &temp->data);
	temp->left = temp->right = NULL;
	return temp;
	
}

void insert(node* root, node *temp)
{
	if(temp->data < root->data)
	{
		   if(root->left!= NULL)
		   {
		   	  insert(root->left,temp);
		   }
		   else
		   {
		   	  root->left = temp;
		   }
	
	}
	
	if(temp->data > root->data)
	{
		  if(root->right != NULL)
		  {
		  	 insert(root->right, temp);
		  }
		  else
		  {
		  	 root->right= temp;
		  }
	}
}

void preorder(node * root)
{
	if(root == NULL)
	{
		 printf("No Elements found in BST Tree\n");
		 return;
	}
	
	printf("%d==>", root->data);
	if(root->left != NULL)
	{
		 preorder(root->left);
	}
	
	if(root->right != NULL)
	{
		 preorder(root->right);
	}
}

void postorder(node *root)
{
   if(root==NULL)
   {
   	 printf("No elements in BST Tree\n");
   	 return;
   }
   
   if(root->left!= NULL)
   {
   	  postorder(root->left);
   }
   
   if(root->right != NULL)
   {
   	  postorder(root->right);
   }
   
   printf("%d==>", root->data);	
	   
}

void inorder(node * root)
{
   if(root == NULL)
   {
       printf("No elements in BST Tree\n");
	   return ;	
   }	
   
   if(root->left != NULL)
   {
   	   inorder(root->left);
   }
   
   printf("%d==>", root->data);
   
   if(root->right != NULL)
   {
   	   inorder(root->right);
   }
	
}


int main()
{
	char ch;
	node*root=NULL,*temp;
	
	do
	{
		  temp = create();
		  if(root == NULL)
		  {
		  	   root = temp;
		  }
		  else
		  {
		  	  insert(root, temp);
		  }
		  printf("do u want to continue(y/n):?\n");
		  getchar();
		  scanf("%c", &ch);
		  
	}while(ch=='y' || ch == 'Y');
	
	printf("\n");
	preorder(root);
	printf("\n");
	
	postorder(root);
	
	printf("\n");
	inorder(root);

    printf("\n");
    if(BST(root))
    {
    	 printf("is BST\n");
	}
	else
	{
		  printf("Not BST\n");
	}
}

