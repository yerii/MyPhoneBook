struct node *removeNode(struct node *node, char *buf)
{
	if(node == 0))
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
