#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<wchar.h>
#include<memory.h>
#include<locale.h>

FILE *fp_load, *fp_save;
int overlapflag;
int shakeflag;

struct node *findobject(wchar_t *,int);
struct node *root = NULL;
struct sorting *head = NULL;
struct working
{
	struct node *connect;
	struct working *next;
};
struct working *first = NULL;
struct node *removeNode(struct node *,wchar_t *,int);
struct node
{
	wchar_t *Name;
	wchar_t *Tel;
	wchar_t *Email;
	wchar_t *Note;
	struct node *left;
	struct node *right;
	int masked;
	int overlapflag;
};

struct sorting
{
	struct node *connect;
	struct sorting *next;
	struct sorting *prev;
};
void addToBST(wchar_t *name, wchar_t *tel, wchar_t *email, wchar_t *note)
{
	struct node *fresh = (struct node *)malloc(sizeof(struct node));
	fresh->left = fresh->right = NULL;
	fresh->Name = (wchar_t *)malloc(200);
	wcscpy_s(fresh->Name,100,name);
	fresh->Tel = (wchar_t *)malloc(200);
	wcscpy_s(fresh->Tel,100,tel);
	fresh->Email = (wchar_t *)malloc(300);
	wcscpy_s(fresh->Email,150,email);
	fresh->Note = (wchar_t *)malloc(1000);
	wcscpy_s(fresh->Note,500,note);

	shakeflag++;
	if(root == NULL)
	{
		root = fresh;
		connetBST(fresh);
		return ;
	}
	else
	{
		struct node *temp = root;
		while(1)
		{
			if(wcscmp(fresh->Name,temp->Name) < 0)
			{
				if(temp->left == NULL)
				{
					temp->left = fresh;
					connectBST(fresh);
					return ;
				}
				else
				{
					temp = temp->left;
				}
			}
			else
			{
				if(temp->right == NULL)
				{
					temp->right = fresh;
					connectBST(fresh);
					return ;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
	}
}

void CoverWrite(void)
{
        struct sorting *temp = head;
        fclose(fp_save);
        fopen_s(&fp_save,"phonebook.txt","wt");
        while(temp != NULL)
        {
                if(wcscmp(temp->connect->Name,L"none")!=0)
                {
                        fwprintf(fp_save,L"Name : %s\n",temp->connect->Name);
                }
		if(wcscmp(temp->connect->Tel,L"none")!=0)
                {
                        fwprintf(fp_save,L"Tel : %s\n",temp->connect->Tel);
                }
                if(wcscmp(temp->connect->Email,L"none")!=0)
                {
                        fwprintf(fp_save,L"Email : %s\n",temp->connect->Email);
                }
		if(wcscmp(temp->connect->Note,L"none")!=0)
		{
			fwprintf(fp_save,L"Note : %s\n",temp->connect->Note);
		}
		fwprintf(fp_save,L"\n");
		temp = temp->next;
	}
}

void modify(struct node *temp, wchar_t *find)
{
	struct node *modi, *fresh;
	wchar_t *key;
	wchar_t *mod;
	modi = temp;
	printf("## Here is modify function!\n");

	if(overlapflag>1)
	{
		int select;
		printf("who want to modify?(input overlapflag) : ");
		scanf_s("%d",&select);
		fflush(stdin);
		modi = findobject(NULL,select);
		destroySLL();
	}

	if(wcscmp(modi->Name,L"none") != 0)
	{
		wprintf(L"Name : %s\n",modi->Name);
	}
	if(wcscmp(modi->Tel,L"none") != 0)
	{
		wprintf(L"Tel : %s\n",modi->Tel);
	}
	if(wcscmp(modi->Email,L"none") != 0)
	{
		wprintf(L"Email : %s\n",modi->Email);
	}
	if(wcscmp(modi->Note,L"none") != 0)
	{
		wprintf(L"Note : %s\n",modi->Note);
	}

	printf("What do you want to modify? (name(1), tel(2), email(3), note(4) :)");
	if(overlapflag < 2)
	{
		getchar();
	}
	key = (wchar_t *)malloc(60);
	_getws_s(key,30);
	if(wcscmp(key,L"quit") == 0)
	{
		return ;
	}
	else
	{
		key = wcstol(key, NULL, 10);
		switch((int)key)
		{
			case 1:
			fresh = (struct node*)malloc(sizeof(struct node));
			fresh->Tel = (wchar_t *)malloc(200);
			fresh->Email = (wchar_t *)malloc(300);
			fresh->Note = (wchar_t *)malloc(1000);
			wcscpy_s(fresh->Tel,100,modi->Tel);
			wcscpy_s(fresh->Email,150,modi->Email);
			wcscpy_s(fresh->Note,500,modi->Note);
			printf("input new name : ");
			mod = (wchar_t *)malloc(200);
			_getws_s(mod,100);
			root = removeNode(root, modi->Name, modi->overlapflag);
			shakeflag--;
			addToBST(mod, fresh->Tel, fresh->Email, fresh->Note);
			CoverWrite();
			break;
		case 2:
			printf("input new phone number : ");
			mod = (wchar_t *)malloc(200);
			_getws_s(mod,100);
			wcscpy_s(modi->Tel,100,mod);
			CoverWrite();
			break;
		case 3:
			printf("input new email : ");
			mod = (wchar_t *)malloc(300);
			_getws_s(mod,150);
			wcscpy_s(modi->Email,150,mod);
			CoverWrite();
			break;
		case 4:
			printf("input new note : ");
			mod = (wchar_t *)malloc(1000);
			_getws_s(mod,500);
			wcscpy_s(modi->Note,500,mod);
			CoverWrite();
			break;
		}
	}
}

void destroy(void)
{
	struct working *del;
	while(first != NULL)
	{
		del = first;
		first = first->next;
		free(del);
	}
}

void connectBST(struct node *node)
{
	struct sorting *fresh;
	fresh = (struct sorting *)malloc(sizeof(struct sorting));
	fresh->next = 0;
	fresh->prev = 0;
	fresh->connect = (struct node *)malloc(sizeof(struct node));

	fresh->connect = node;

	if(head == NULL)
	{
		head = fresh;
		return ;
	}
	else
	{
		struct sorting *temp = head;
		while(1)
		{
			if(wcscmp(fresh->connect->Name, temp->connect->Name)<0)
			{
				if(temp==head)
				{
					temp->prev = fresh;
					fresh->next = temp;
					head = head->prev;
					return;
				}
				else
				{
					fresh->next = temp;
					fresh->prev = temp->prev;
					temp->prev->next = fresh;
					temp->prev = fresh;
					return ;
				}
			}
			else if(temp->next == NULL)
			{
				temp->next = fresh;
				fresh->prev = temp;
				return ;
			}
			temp = temp->next;
		}
	}
}

