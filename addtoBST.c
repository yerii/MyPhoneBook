void addToBST(char *name, char *phone, char *email, char *memo)
{	struct node *new_node = createNewNode(name,phone, email,memo);
	if(root==0)
	{
		root = new_node;
		return;
	}
	else
	{	struct node *cur_node=root;
		while(1)
		{if(strcmp(cur_node->name, new_node->name)>0)
		{if(cur_node->left==0)
			{cur_node->left=new_node;
				return;
			}cur_node=cur_node->left;
		}
		else if(strcmp(cur_node->name,new-node->name)<0)
		{if(cur_node->right==0)
			{cur_node->right = new_node;
				return;}
			cur_node = cur_node->left;
		}
		else if(strcmp(cur_node->name, new_node->name)<0)
		{
			if(cur_node->right==0)
			{cur_node->right=new_node;
				return;}
			cur_node=cur_node->right;
		}
		else
		{printf("same name");}
	}
	}
}
