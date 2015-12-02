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
