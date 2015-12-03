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

void printf_inorder(struct node *node,FILE *f)
{
	if(node == 0)
	{
		return;
	}
	printf_inorder(node->left,f);

	printf("%s\n",node->name);
	fprintf(f,"name : %s\n",node->name);
	fprintf(f,"phone : %s\n",node->phone);
	fprintf(f,"email : %s\n",node->email);
	fprintf(f,"memo : %s\n",node->memo);

	printf_inorder(node->right,f);
}
