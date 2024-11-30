// BST

#include<iostream>
#include<limits.h>


using namespace std;


typedef struct BST{
	int data;
	struct BST *left;
	struct BST *right;
}node;

node *create();
void insert(node*,  node*);
void preorder(node*);
void postorder(node*);
void inorder(node*);
int BST(node*);
int BSTutil(node*,int min,int max);


node *create()
{
	 node *temp;
	 //temp = (node*)malloc(sizeof(node));
	 printf("enter the data:\n");
	 temp = new node;
	 cin >> temp->data;
	 temp->left=temp->right = NULL;
	 return temp;
}

int BST(node* root)
{
	return (BSTutil(root,INT_MIN,INT_MAX));
}


int BSTutil(node* root, int min, int max)
{
	if(root == NULL)
	{
		return 1;
	}
	
	if(root->data < min ||  root->data > max)
	{
		return 0;
	}
	
	return BSTutil(root->left,min,root->data-1) && BSTutil(root->right,root->data+1,max);
}

void insert(node* root, node* temp)
{
	if(temp->data < root->data)
	{
		   if(root->left != NULL)
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
		 if(root->right!= NULL)
		 {
		 	 insert(root->right, temp);
		 }
		 else
		 {
		 	root->right = temp;
		 }
	}
}

void preorder(node* root)
{
	if(root == NULL)
	{
		cout << "No ELements in BST Tree" << endl;
	}
	
	cout <<   root->data << "===>";
	
	if(root->left!= NULL)
	{
		  preorder(root->left);
	}
	
	if(root->right!= NULL)
	{
		 preorder(root->right);
	}
}

void postorder(node* root)
{
    if(root == NULL)
	{
	   cout << "No Elements in BST Tree" << endl;	
	}	
	
	if(root->left != NULL)
	{
		postorder(root->left);
	}
	if(root->right != NULL)
	{
		 postorder(root->right);
	}
	
	cout << root->data << "==>";
}

void inorder(node *root)
{
	if(root == NULL)
	{
		cout << "No Elements in BST Tree" << endl;		
	}
	
	if(root->left!= NULL)
	{
		inorder(root->left);
	}
	cout << root->data << "==>";
	if(root->right!= NULL)
	{
		inorder(root->right);
	}
}


int main()
{
	char ch;
	node* root=NULL,*temp;
	
	do
	{
		 temp = create();
		 if(root == NULL)
		 {
		 	 root = temp;
		 }
		 else
		 {
		 	insert(root,temp);
		 }
		 
		 cout << "Do you want to continue(y/n)?:" << endl;
		 getchar();
		 cin >> ch ;
		 
	}while(ch =='y' || ch == 'Y');
	
	cout << endl;
	preorder(root);
	cout << endl;
	postorder(root);
	cout << endl;
	inorder(root);
	cout << endl;
	if(BST(root))
	{
		 cout << "IS BST" << endl;
	}
	else
	{
		cout << "Not BST" << endl;
	}
}
