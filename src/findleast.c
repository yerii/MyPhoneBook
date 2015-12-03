struct node *findLeast(struct node *node)
{
	strut node *cur = node;
	while(cur->left != 0)
	{
		cur = cur->left;
	}
	return cur;
}
