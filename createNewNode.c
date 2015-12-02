struct node *createNewNode(char *name, char *phone, char *email, char *memo)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->left=0;
	new_node->right=0;
	strcpy(new_node->name,name);
	strcpy(new_node->phone,phone);
	strcpy(new_node->email,email);
	strcpy(new_node->memo, memo);
	return new_node;
}

