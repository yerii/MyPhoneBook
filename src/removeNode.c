#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
	struct node *left;
	struct node *right;
	char name[20];
	char phone[20];
	char email[20];
	char memo[50];
};

struct node *findLeast(struct node *node)
{
	struct node *cur = node;
	while(cur -> left != 0)
	{
		cur = cur->left;
	}
	return cur;
}

struct node *removeNode(struct node *node, char *buf)
{
	if(node == 0)
	{
		printf("no one.\n");
		return;
	}

	if(strcmp(buf,node->name)==0)
	{
		if(node->left == 0 && node->right==0)
		{
			free(node);
			printf("delete complete.\n");
			return 0;
		}

		else if(node -> left == 0)
		{
			struct node *ret = node->right;
			free(node);
			printf("delete complete.\n");
			return ret;
		}

		else if(node -> right ==0)
		{
			struct node *ret = node->left;
			free(node);
			printf("delete complete.\n");
			return ret;
		}

		else
		{
			struct node *toReplace = findLeast(node->right);
			strcpy(node->name, toReplace->name);
			strcpy(node->phone, toReplace->phone);
			strcpy(node->email, toReplace->email);
			strcpy(node->memo, toReplace->memo);
			node->right=removeNode(node->right, toReplace->name);
			printf("delete complet.\n");
			return node;
		}
	}
	else if(strcmp(buf, node->name)<0)
	{
		node->left = removeNode(node->left, buf);
		return node;
	}
	else 
	{
		node -> right = removeNode(node->right,buf);
		return node;
	}
}
