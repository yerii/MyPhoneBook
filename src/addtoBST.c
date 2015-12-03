#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	struct node *left;
	struct node *right;
	char name[20];
	char phone[20];
	char email[20];
	char memo[50];
};
struct node *root=0;
struct node *createNewNode(char *name, char *phone, char *email, char *memo)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->left=0;
	new_node->right=0;
	strcpy(new_node->name,name);
	strcpy(new_node->phone,phone);
	strcpy(new_node->email,email);
	strcpy(new_node->memo,memo);
}

void addToBST(char *name, char *phone, char *email, char *memo)
{
	struct node *new_node = createNewNode(name,phone, email,memo);

	if(root==0)
	{
		root = new_node;
		return;
	}
	else
	{
		struct node *cur_node=root;
		while(1)
		{
		if(strcmp(cur_node->name, new_node->name)>0)
		{
			if(cur_node->left==0)
			{
				cur_node->left=new_node;
				return;
			}
			cur_node=cur_node->left;
		}
		else if(strcmp(cur_node->name,new_node->name)<0)
		{
			if(cur_node->right==0)
			{
				cur_node->right = new_node;
				return;
			}
			cur_node = cur_node->right;
		}
		else
		{
			printf("same name");
		}
	}
	}
}

