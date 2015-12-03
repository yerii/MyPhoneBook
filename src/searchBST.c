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
struct node *root = 0;
struct node * searchBST(char *name)
{
	struct node *cur_node = root;
	while(1)
	{
		if(cur_node == 0)
		{
			printf("%s`s Information is not exist...\n",name);
			return ;
		}

		if(strcmp(cur_node->name,name)>0)
		{
			cur_node = cur_node -> left;
		}

		else if(strcmp(cur_node->name,name)<0)
		{
			cur_node = cur_node -> right;
		}
		else
		{
			printf("%s`s phone number is %s",name,cur_node->phone);
			printf("%s`s email is %s",name,cur_node->email);
			printf("%s`s memo is %s",name,cur_node->memo);
			return cur_node;
		}
	}
}
