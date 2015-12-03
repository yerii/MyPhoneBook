#include <stdio.h>
struct node
{
	struct node *left;
	struct node *right;
	char name[20];
	char phone[20];
	char email[20];
	char memo[50];
};

void displayNodeInfo(struct node *node)
{
	if(node==0)
	{
		printf("Node is Null");
		return;
	}
	printf("name : %s\nphone : %s\nemail : %s\nmemo : %s\n",node->name,node->phone,node->email,node->memo);
}

