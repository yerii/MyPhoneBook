
#include <stdio.h>

struct node
{
	struct node *left;
	struct node *right;
	char name[20];
	char phone[20];
	char memo[50];
};

struct node *root = 0;
struct node *createNewNode(char *name, char *phone, char *memo)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->left = 0;
	new_node->right = 0;
	strcpy(new_node->name,name);
	strcpy(new_node->phone,phone);
	strcpy(new_node->memo,memo);
	return new_node;
}
int main(void)
{
	int menuNum;
	char name[20];
	char phone[20];
	char memo[50];

	printf("select the menu.\n");
	printf("1. ");//menu
	scanf("%d",&menuNum);

}

