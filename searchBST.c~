struct node * searchBST(char *name)
{
	struct node *cur_node = root;
	while(1)
	{
		if(cur_node == 0)
		{
			printf("Information is not exist...\n",name);
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
			printf("");//every information....
			return cur_node;
		}
	}
}
