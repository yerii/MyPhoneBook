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
void inorder(struct node *node)
{
	if(node==0)
	{
		return;
	}
	inorder(node->left);
	displayNodeInfo(node);
	//inorder(node->right);
}
