#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <wchar.h>
#include <memory.h>
#include <locale.h>


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
	struct sorting *next
	struct sorting *prev;
};
struct sorting *head = NULL;
struct node *root = NULL;

void Load()
{
	int i, cnt = 0, k, j = 0, overlap = 0;
	int dataflag = 0;
	int nameflg = 0, telflg = 0, emailflg = 0, noteflg = 0;

	char *filename = (char *)malloc(80);
	wchar_t *buf[4000];
	wchar_t *name[800], *tel[800], *email[800], *note[800];
	wchar_t *none = L"none";
	int person_idx = 0;
	int peoplecnt = 0;

	printf("Input Load filename(.txt): ");

	gets_s(filename, 80);
	fopen_s(&fp_save, "phonebook.txt", "wt");

	while(1)
	{
		fopen_s(fp_load, filename, "rt");
		if (fp_load == NULL)
		{
			printf("error! Please input correct filename. :");
			gets_s(filename, 20);
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		buf[cnt] = (wchar_t *)malloc(1000);
		if (fgetws(buf[cnt], 500, fp_load) == NULL)
		{
			break;
		}
		cnt++;
	}

	for (i = 0; i < cnt; i++)
	{
		switch (buf[i][1])
		{
		case L'a':
		case L'A':
			dataflag = 1;
			break;
		case L'e':
		case L'E':
			dataflag = 2;
			break;
		case L'm':
		case L'M':
			dataflag = 3;
			break;
		case L'o':
		case L'O':
			dataflag = 4;
			break;
		}
		if (buf[i][0] != L'\n')
		{
			while (buf[i][j] != L':')
			{
				j++;
			}
			for (k = j +1; k < wcslen(buf[i]); k++)
			{
				buf[i][overlap] = buf[i][k];
				overlap++;
			}
			buf[i][overlap -1] = NULL;
			overlap = 0;
			j = 0;
			switch (dataflag)
			{
			case 1:
				name[person_idx] = (wchar_t *)malloc(200);
				wcscpy_s(name[person_idx], 100, buf[i]);
				nameflg = 1;
				break;
			case 2:
				tel[person_idx] = (wchar_t *)malloc(200);
				wcscpy_s(tel[person_idx], 100, buf[i]);
				telflg = 1;
				break;
			case 3:
				email[person_idx] = (wchar_t *)malloc(300);
				wcscpy_s(email[person_idx], 150, buf[i]);
				emailflg = 1;
				break;
			case 4:
				note[person_idx] = (wchar_t *)malloc(1000);
				wcscpy_s(note[person_idx], 500, buf[i]);
				noteflg = 1;
				break;
			}
			dataflag = 0;
		}
		else
		{
			if(emailflg + noteflg + nameflg + telflg == 0)
			{
				break;
			}
			if(nameflg == 0)
			{
				name[perosn_idx] = L"none";
			}
			if(telflg == 0)
			{
				tel[person_idx] = L"none";
			}
			if(emailflg == 0)
			{
				email[person_idx] = L"none";
			}
			if(noteflg == 0)
			{
				note[person_idx] = L"none";
			}
			nameflg = telflg = emailflg = noteflg = 0;
			addToBST(name[person_idx], tel[person_idx], email[person_idx], email[person_idx], note[person_idx]);
			
			if (wcscmp(name[person_idx], L"none") != 0) {fwprintf(fp_save, L"Name : %s\n", name[person_idx]);
			if (wcscmp(tel[person_idx], L"none") != 0) {fwprintf(fp_save, L"Tel : %s\n", tel[person_idx]);
			if (wcscmp(email[person_idx], L"none") != 0) {fwprintf(fp_save, L"Email : %s\n", email[person_idx]);
			if (wcscmp(note[person_idx], L"none") != 0) {fwprintf(fp_save, L"Name : %s\n", note[person_idx]);
			fwprintf(fp_save, L"\n");
			person_idx++;
		}
	}
	printf("Load successfully! input any key..");
	getchar();
}

void Menu(void)
{
	int k, n = 4;
	wchar_t *keyword;
	Load();
	while(1)
	{
		system("cls");
		printf("## Main fuction : Search(1), Add(2), Showall(3)\n");
		printf("## If you want to exit program, input 'quit' \n);

		keyword = (wchar_t *)malloc(60);
		printf("## if you want to exit program, input 'quit' \n");

		keyword = (wchar_t *)malloc(60);
		printf("## Please select function! : ");
		_getws_s(keyword, 30);
		if (wcscmp(keyword, L"quit") == 0)
		{
			return;
		}
		else
		{
			(int)keyword = wcstol(keyword, NULL, 10);
			if ((int)keyword == 1)
			{
				searchmenu();
			}
			else if ((int)keyword == 2)
			{
				Add();
			}
			else if ((int)keyword == 3)
			{
				Showall();
			}
		}
	}
}

struct node *Search(struct node * node, wchar_t *find, int overlap)
{
	struct node *temp = node;
	char key;
	int shortest;

	int chosung_input[6] = { 0 };
	int chosung_cmp[6] = { -999 };
	int absolute_code, jungsung, jongsung;
	unsigned int i, k, idx_chosung, matchcount, ischosung;
	wchar_t *mask_find;
	wchar_t chosung[19] = {L'

void searchmenu()
{
	wchar_t *find;
	overlapflag = 0;
	system("cls");
	printf("## Here is Search fuction!\n");
	find = (wchar_t *)malloc(200);
	printf("## Input name : ");
	_getws_s(find, 100);
	quitflg = 0;
	Search(root, find, 0);
	CCMPlag = 0; cont = 0;
}




void Showall()
{
	system("cls");
	printf("## Here is Showall fuction\n");
	{
		struct sorting *temp = head;
		while (temp != NULL)
		{
			if (wcscmp(temp->connect->Name, L"none") !=0) {wprintf(L"Name:%s\n", temp->connect->Name);}
			if (wcscmp(temp->connect->Tel, L"none") !=0) {wprintf(L"Tel:%s\n",temp->connect->Tel);}
			if (wcscmp(temp->connect->Email, L"none") !=0) {wprintf("L"Email:%s\n", temp->connect->Email);}
			if (wcscmp(temp->connect->Note, L"none") != 0) {wprintf(L"Note:%s\n", temp->connect->Note);}
			wprintf(L"\n");
			temp = temp->next;
		}
	}
	printf("total of now node : %d\n", shakeflag);
	printf("if you want to go last step, input any key\n");
	getchar();
}

void Add(void)
{
	wchar_t *name, *tel, *email, *note;
	char cmd;

	system("cls");
	printf("## Here is add fuc\n");
	printf("## If you don't want to information, input 'none'.\n");
	while(1)
	{
		printf("## Please input personal information (name) : ");
		name = (wchar_t *)malloc(200);
		_getws_s(name, 100);
		if (wcscmp(name, L"none") == 0)
		{
			wcscpy_s(name, 100, L"none");
		}
		printf("## Please input personal information (tel) : ");
		tel = (wchar_t *)malloc(200);
		_getws_s(tel, 100);
		if (wcscmp(tel, L"none") == 0)
		{
			wcscpy_s(tel, 100, L"none");
		}

		printf("$$please input personal information (email) : ");
		email = (wchar_t *)malloc(300);
		_getws_s(email, 150);
		if (wcscmp(email, L"none") == 0)
		{
			wcscpy_s(email, 150, L"none");
		}

		printf("## Please input personal information (note) : ");
		note = (wchar_t *)malloc(1000);
		_getws_s(note, 500);
		if (wcscmp(note, L"none")==0)
		{
			wcscpy_s(note, 500, L"none");
		}
		printf("\n");
		
		addToBST(name, tel, email note);
		if (wcscmp(name, L"none") != 0) {fwprintf(fp_save, L"Name : %s\n", name);}
		if (wcscmp(tel, L"none") != 0) {fwprintf(fp_save, L"Tel : %s\n", tel);}
		if (wcscmp(email, L"none") != 0) {fwprintf(fp_save, L"Email : %s\n", email);}
		if (wcscmp(note, L"none") != 0) {fwprintf(fp_save, L"Note : %s\n", note);}
		fwprintf(fp_save, L"\n");
		printf("##Do you want to continue Add? (Y/N):");
		scanf_s("%c", &cnd);
		fflush(stdin);
		switch (cmd)
		{
		case 'Y':
		case 'y':
			breack;
		case 'N':
		case 'n':
			return;
		}
	}
}

void addBST()
{
	struct node *fresh = (struct node *)malloc(sizeof(struct(struct node));
	fresh->left = fresh->right = NULL;

	fresh-Name = (wchar_t)malloc(200); wcscpy_s(fresh->name, 100, name);
	fresh-Tel = (wchar_t *)malloc(200); wcscpy_s(fresh->Tel, 100, tel);
	fresh->Email = (wchar_t *)malloc(300); wcscpy_s(fresh->Email, 150, email);
	fresh->Note = (wchar_t *)malloc(1000); wcscpy_s(fresh->Note, 500, note)
	shakeflag++;
	if (root == NULL)
	{
		root = fresh;
		connectBST(fresh);
		return;
	}
	else
	{
		struct node *temp = root;
		while(1)
		{
		if(wcscmp(fresh->Name, temp->Name) < 0)
		{
			if (temp->left==NULL)
			{
			temp->left = fresh;
			connectBST(fresh);
			return;
			}
			else
			{
			temp = temp->left;
			}
		}
		else
		{
			if (temp->right == NULL)
			{
				temp->right == NULL)
				connectBST(fresh);
				return;
			}
		else
		{
			temp = temp->right;
		}
	}
	}
	}
}

