// PROJECT_PHONEBOOK
// Developed by 201201716 WONKYUNGHO
// Date : ~ 131101
// I will use fopen_s function instead of fopen.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<wchar.h>
#include<memory.h>
#include<locale.h>
FILE *fp_load, *fp_save;
int overlapflag; // 동명이인있는지 확인하는거!
int quitflg;
int CCMPflag; // 초성 상으로 검색할때의 플래그
int cont;
int shakeflag;

void Load(void);
void Menu(void);
struct node *Search(struct node *, wchar_t *, int);
void Showall(void);
void Modify(struct node *, wchar_t *);
void Add(void);
void Delete(struct node *del, wchar_t *find);
void addToBST(wchar_t *, wchar_t *, wchar_t *, wchar_t *);
void InorderTraversal(struct node *);
void searchmenu();
void connectBST(struct node *);
struct node *findoverlap(int overlap);
struct node *removeNode(struct node *, wchar_t *, int);
struct node *findLeast(struct node *node);
void addToSLL(struct node *);
void destorySLL(void);
struct node *findobject(wchar_t *, int);
void DeleteDLL(struct node *);
void CoverWrite(void);

int power(int t, int s)
{
	// s제곱 함수
	int result = 1, i;
	for (i = 0; i<s; i++)
	{
		result = result * t;
	}
	return result;
}
struct working
{
	struct node *connect;
	struct working *next;
};
struct working *first = NULL;
// BST
struct node
{
	wchar_t *Name;
	wchar_t *Tel;
	wchar_t *Email;
	wchar_t *Note;
	struct node *left;
	struct node *right;
	int masked; // 재정렬때 사용
	int overlapflag; // 동명이인있는지 확인하는거!
};
// DLL
struct sorting
{
	struct node *connect; // BST를 가리키는 포인터..
	struct sorting *next;
	struct sorting *prev;
};
struct sorting *head = NULL; // BST를 참조할 DLL
struct node *root = NULL;
// Delete, Modify 시 전체 트리를 다시 파일포인터에 써야함. (DLL)
void Load()
{
	int i, cnt = 0, k, j = 0, overlap = 0;
	int dataflag = 0; // 파일에서 읽어올때 각각의 항목이 있는지 체크할 플래그.1, 2, 3,4
	int nameflg = 0, telflg = 0, emailflg = 0, noteflg = 0;
	char *filename = (char *)malloc(80);
	wchar_t *buf[4000]; // 저장할 놈 최소 4000/5(공백포함) = 800
	wchar_t *name[800], *tel[800], *email[800], *note[800];
	wchar_t *none = L"none";
	int person_idx = 0; // 각각의 사람!
	int peoplecnt = 0;

	printf("Input load filename(.txt): ");
	// get_s(char *filename, int MAXIMUM_size)
	gets_s(filename, 80);
	fopen_s(&fp_save, "phonebook.txt", "wt");
	while (1)
	{
		fopen_s(&fp_load, filename, "rt");
		if (fp_load == NULL)
		{
			printf("error! Plese input correct filename. : ");
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

	// confirm file contents.
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
			for (k = j + 1; k < wcslen(buf[i]); k++)
			{
				buf[i][overlap] = buf[i][k];
				overlap++;
			}
			buf[i][overlap-1]=0; // 줄바꿈까지 지워줌.
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
			if (emailflg + noteflg + nameflg + telflg == 0)
			{
				break;
			}

			if (nameflg == 0)
			{
				name[person_idx] = L"none";
			}
			if (telflg == 0)
			{
				tel[person_idx] = L"none";
			}
			if (emailflg == 0)
			{
				email[person_idx] = L"none";
			}
			if (noteflg == 0)
			{
				note[person_idx] = L"none";
			}
			nameflg = telflg = emailflg = noteflg = 0;
			addToBST(name[person_idx], tel[person_idx], email[person_idx], note[person_idx]);
			// 파일에 저장
			if (wcscmp(name[person_idx], L"none") != 0) { fwprintf(fp_save, L"Name : %s\n", name[person_idx]); }
			if (wcscmp(tel[person_idx], L"none") != 0) { fwprintf(fp_save, L"Tel : %s\n", tel[person_idx]); }
			if (wcscmp(email[person_idx], L"none") != 0) { fwprintf(fp_save, L"Email : %s\n", email[person_idx]); }
			if (wcscmp(note[person_idx], L"none") != 0) { fwprintf(fp_save, L"Note : %s\n", note[person_idx]); }
			fwprintf(fp_save, L"\n");
			person_idx++;
		}

	}
	printf("Load successfully! input any key..");
	getchar();
}
int main(void)
{
	setlocale(LC_ALL, "korean");
	Menu();

	fclose(fp_load);
	fclose(fp_save);
	return 0;
}

void Menu(void)
{
	int k, n = 4;
	wchar_t *keyword;
	Load();
	while (1)
	{
		system("cls");
		printf("##   Main fuction : Search(1), Add(2), Showall(3)\n");
		printf("##   If you want to exit program, input 'quit' \n");

		keyword = (wchar_t *)malloc(60);
		printf("##   Plese select function! : ");
		_getws_s(keyword, 30);
		if (wcscmp(keyword, L"quit") == 0)
		{
			return;
		}
		else
		{
			(long int)keyword = wcstol(keyword, NULL, 10);
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
// if file is empty, return -1; 
struct node *findoverlap(int overlap)
{
	struct node *temp = root; // 전체 다 뒤지네..ㅠ
	if (temp == NULL)
	{
		return;
	}
	while (1)
	{
		if (overlap == temp->overlapflag)
		{
			return temp; // case1이 되면 다시 void형으로..
		}
		else
		{
			struct node *temp2;
			temp2 = temp;
			while (temp2 != NULL)
			{
				if (overlap == temp->overlapflag)
				{
					return temp; // case1이 되면 다시 void형으로..
				}
				temp2 = temp2->left;
			}
			temp2 = temp;
			while (temp2 != NULL)
			{
				if (overlap == temp->overlapflag)
				{
					return temp; // case1이 되면 다시 void형으로..
				}
				temp2 = temp2->right;
			}
		}

	}

}
void searchmenu()
{
	wchar_t *find;
	overlapflag = 0;
	system("cls");
	printf("##   Here is Search fuction!\n");
	find = (wchar_t *)malloc(200);
	printf("##   Input name : ");
	_getws_s(find, 100);
	quitflg = 0;
	Search(root, find, 0);
	CCMPflag = 0; cont = 0;
}
struct node *Search(struct node * node, wchar_t *find, int overlap) //overlap ->중복된 놈을 찾을 녀석
{
	struct node *temp = node;
	char key;
	int shortest;
	/*  초성을 처리하기 위한 파트  */
	/*  초성은 0~18까지이고, chosung의 index는 입력한 초성의 코드!*/
	int chosung_input[6] = { 0 }; // 입력받은 초성 , 이름이 6글자까지 있다고 가정
	int chosung_cmp[6] = { -999 };  // 비교할 초성..(원래 저장되잇는것들)
	int absolute_code, jungsung, jongsung; // choung_cmp구하기 전 단계
	unsigned int i, k, idx_chosung, matchcount, ischosung;
	wchar_t *mask_find; // 초성으로 쓸 find의 mask
	wchar_t chosung[19] = { L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', L'ㄸ',
		L'ㄹ', L'ㅁ', L'ㅂ',
		L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ',
		L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ', L'ㅌ',
		L'ㅍ', L'ㅎ' };
	CCMPflag = 0;
	/*  빈 경우에는 바로 나가줘야지  */
	if (node == NULL)
	{
		return;
	}
	ischosung = 0; // 내가 입력한게 이름인지 초성인지는 구분을 ㅎㅎ
	mask_find = (wchar_t *)malloc(sizeof(wchar_t) * 100);
	wcscpy_s(mask_find, 100, find);
	for (i = 0; i <6; i++)
	{
		for (idx_chosung = 0; idx_chosung < 19; idx_chosung++)
		{
			if (mask_find[i] == chosung[idx_chosung])
			{
				ischosung++;
				mask_find[i] = idx_chosung;
				//		wprintf(L"%c\n", find[i]);
			}
		}
	}
	if (ischosung == 0)
	{
		/* 입력한게 초성이 아님 ! */
		CCMPflag = -999;
	}
	//	printf("%d %d %d\n", mask_find[0], mask_find[1], mask_find[2]); 	// 초성이 잘 따졋나 테스트
	/*  이 순간, mask_find는 입력한 초성의 고유 코드를 가지고 있음  */

	while (1)
	{
		/*  node(temp)->Name의 초성을 따야지!   */
		for (k = 0; k<wcslen(temp->Name); k++)
		{
			absolute_code = temp->Name[k] - 0xAC00;
			jongsung = absolute_code % 28;
			jungsung = ((absolute_code - jongsung) / 28) % 21;
			chosung_cmp[k] = ((absolute_code - jongsung) / 28) / 21;
		}
		//			printf("%d %d %d\n", chosung_cmp[0], chosung_cmp[1], chosung_cmp[2]);
		/*  여기까지 초성을 따고 비교를 시작하지  */
		matchcount = 0;
		if (wcslen(temp->Name) > wcslen(find))
		{
			shortest = wcslen(find);
		}
		else
		{
			shortest = wcslen(temp->Name);
		}
		for (i = 0; i<shortest; i++)
		{
			if (chosung_cmp[i] == mask_find[i])
			{
				matchcount++;
			}
		}
		/*  초성을 비교해서 모두 같다면 CCMflag ON!  */
		if (matchcount == wcslen(temp->Name))
		{
			CCMPflag = 1; // 세글자 다 같음
		}
		if (CCMPflag != -999 && chosung_cmp[0] > mask_find[0])
		{
			CCMPflag = -1; // 왼쪽으로
		}
		if (CCMPflag != -999 && chosung_cmp[0] < mask_find[0])
		{
			CCMPflag = 2; // 오른쪽
		}
		else if (CCMPflag != -999 && chosung_cmp[0] == mask_find[0] && CCMPflag != 1)
		{
			// 성씨 같으면 다 뒤져야 함
			cont = 1;
			Search(temp->right, find, 0);
			Search(temp->left, find, 0);
		}
		//			printf("CCMPflag = %d\n", CCMPflag);
		/************           본격적으로 시작!            ************/
		if ((CCMPflag == 1 || wcscmp(find, temp->Name) == 0) || (find[0] == temp->Name[0] && wcslen(find) < 2))
		{
			if (overlap != 0)
			{
				if (temp->overlapflag == overlap)
				{
					return temp;
				}
				else
				{
					struct node * temp2 = findoverlap(overlap);
					return temp2;
				}
			}
			overlapflag++;
			temp->overlapflag = overlapflag;
			// 검색결과가 두명이상이면 사용할거~
			addToSLL(temp);

			if (wcscmp(temp->Name, L"none") != 0) { wprintf(L"Name : %s\n", temp->Name); }
			if (wcscmp(temp->Tel, L"none") != 0) { wprintf(L"Tel : %s\n", temp->Tel); }
			if (wcscmp(temp->Email, L"none") != 0) { wprintf(L"Email : %s\n", temp->Email); }
			if (wcscmp(temp->Note, L"none") != 0) { wprintf(L"Note : %s\n", temp->Note); }
			wprintf(L"overlap : %d\n\n", temp->overlapflag);

			// 동명이인이 있나 확인
			Search(temp->right, find, 0);
			Search(temp->left, find, 0);

			if (quitflg == 1)
			{
				return;
			}
			printf("##   Detail function: Modify(1), Delte(2)\n");
			printf("##   If you want to go before menu, input 'N or n'\n");
			printf("##   What Do you want to do?(1 / 2) : ");
			scanf_s(" %c", &key);
			switch (key)
			{
			case '1':
				Modify(temp, temp->Name); // case1: 여기다 temp를 보내주는건어떠려나
				quitflg = 1;
				break;
			case '2':
				Delete(temp, temp->Name);
				quitflg = 1;
				break;
			default:
				quitflg = 1;
				return temp; // case1이 되면 다시 void형으로..
			}
			return temp; // case1이 되면 다시 void형으로..
		}
		else
		{
			// 이름으로 찾기
			if (CCMPflag != 2 && ((CCMPflag == -1) || wcscmp(find, temp->Name) < 0) || (find[0] < temp->Name[0] && wcslen(find) < 2))
			{
				// 찾으려는게 왼쪽
				if (temp->left == NULL)
				{
					// 찾는게 BST에 없는거
					if (overlapflag == 0 && cont == 0)
					{
						printf("##   This Name is not included in phonebook.\n");
						getchar();
					}
					return temp;
				}
				else
				{
					temp = temp->left;
				}

			}
			else if (CCMPflag != -1 && (CCMPflag == 2 || wcscmp(find, temp->Name) >= 0) || (find[0] >= temp->Name[0] && wcslen(find) < 2))
			{
				// 찾으려는게 오른쪽
				if (temp->right == NULL)
				{
					if (overlapflag == 0 && cont == 0)
					{
						printf("##   This Name is not included in phonebook.\n");
						getchar();
					}
					return temp;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
	}
}

void Showall()
{
	// 가나다 순으로 보여주기
	system("cls");
	printf("##   Here is Showall fuction\n");
	//	InorderTraversal(root);
	{
		struct sorting *temp = head;
		while (temp != NULL)
		{
			if (wcscmp(temp->connect->Name, L"none") != 0) { wprintf(L"Name:%s\n", temp->connect->Name); }
			if (wcscmp(temp->connect->Tel, L"none") != 0) { wprintf(L"Tel:%s\n", temp->connect->Tel); }
			if (wcscmp(temp->connect->Email, L"none") != 0) { wprintf(L"Email:%s\n", temp->connect->Email); }
			if (wcscmp(temp->connect->Note, L"none") != 0) { wprintf(L"Note:%s\n", temp->connect->Note); }
			wprintf(L"\n");
			temp = temp->next;
		}
	}
	printf("현재 노드의 총 개수 : %d\n", shakeflag);
	printf("If you want to go last step, input any key\n");
	getchar();

}

void Add(void)
{
	wchar_t *name, *tel, *email, *note;
	char cmd;

	system("cls");
	printf("##   Here is Add fuction\n");
	printf("##   If you don't want to add information, input 'none'.\n");
	while (1)
	{
		printf("##   Please input personal informaion (name) : ");
		name = (wchar_t *)malloc(200);
		_getws_s(name, 100);
		if (wcscmp(name, L"none") == 0)
		{
			wcscpy_s(name, 100, L"none");
		}
		printf("##   Please input personal informaion (tel) : ");
		tel = (wchar_t *)malloc(200);
		_getws_s(tel, 100);
		if (wcscmp(tel, L"none") == 0)
		{
			wcscpy_s(tel, 100, L"none");
		}

		printf("##   Please input personal informaion (email) : ");
		email = (wchar_t *)malloc(300);
		_getws_s(email, 150);
		if (wcscmp(email, L"none") == 0)
		{
			wcscpy_s(email, 150, L"none");
		}

		printf("##   Please input personal informaion (note) : ");
		note = (wchar_t *)malloc(1000);
		_getws_s(note, 500);
		if (wcscmp(note, L"none") == 0)
		{
			wcscpy_s(note, 500, L"none");
		}

		printf("\n");
		addToBST(name, tel, email, note);
		if (wcscmp(name, L"none") != 0) { fwprintf(fp_save, L"Name : %s\n", name); }
		if (wcscmp(tel, L"none") != 0) { fwprintf(fp_save, L"Tel : %s\n", tel); }
		if (wcscmp(email, L"none") != 0) { fwprintf(fp_save, L"Email : %s\n", email); }
		if (wcscmp(note, L"none") != 0) { fwprintf(fp_save, L"Note : %s\n", note); }
		fwprintf(fp_save, L"\n");
		printf("## Do you want to continue Add? (Y/N): ");
		scanf_s("%c", &cmd);
		fflush(stdin);
		switch (cmd)
		{
		case 'Y':
		case 'y':
			break;
		case 'N':
		case 'n':
			return;
		}
	}

}
void addToBST(wchar_t *name, wchar_t *tel, wchar_t *email, wchar_t *note)
{
	// This is add to bst fnction.
	struct node *fresh = (struct node *)malloc(sizeof(struct node));
	fresh->left = fresh->right = NULL;
	// save personal information to node
	fresh->Name = (wchar_t *)malloc(200);  wcscpy_s(fresh->Name, 100, name);
	fresh->Tel = (wchar_t *)malloc(200);  wcscpy_s(fresh->Tel, 100, tel);
	fresh->Email = (wchar_t *)malloc(300); wcscpy_s(fresh->Email, 150, email);
	fresh->Note = (wchar_t *)malloc(1000);  wcscpy_s(fresh->Note, 500, note);
	// 흔들 타이밍을 위해 증가..
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
		while (1)
		{
			// 이름으로 순서구분.
			// 새로 넣는 것이 temp랑 같거나 앞에있으면 밑으로 감.. (동명이인은 먼저 온 순서!)
			if (wcscmp(fresh->Name, temp->Name) < 0)
			{
				if (temp->left == NULL)
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
					temp->right = fresh;
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

void Modify(struct node *temp, wchar_t *find)
{
	struct node *modi, *fresh;
	wchar_t *key;
	wchar_t *mod;
	modi = temp;
	printf("##   Here is Modify function!\n");

	if (overlapflag > 1)
	{
		//동명이인이 있는 경우 & 여러명이 나온 경우
		int select;
		printf("Who want to modify?(input overlapflag) : ");
		scanf_s("%d", &select);
		fflush(stdin);
		modi = findobject(NULL, select);
		destorySLL();
	}

	if (wcscmp(modi->Name, L"none") != 0) { wprintf(L"Name : %s\n", modi->Name); }
	if (wcscmp(modi->Tel, L"none") != 0) { wprintf(L"Tel : %s\n", modi->Tel); }
	if (wcscmp(modi->Email, L"none") != 0) { wprintf(L"Email : %s\n", modi->Email); }
	if (wcscmp(modi->Note, L"none") != 0) { wprintf(L"Note : %s\n", modi->Note); }

	printf("What do you want to modify? ( name(1), tel(2), email(3), note(4) ) : ");
	if (overlapflag < 2)
	{
		getchar();
	}
	key = (wchar_t *)malloc(60);
	_getws_s(key, 30);
	if (wcscmp(key, L"quit") == 0) { return; }
	else
	{
		key = wcstol(key, NULL, 10);
		switch ((int)key)
		{
		case 1:
			// 이름을 바꾸는 경우 - 기존의 것을 삭제한 후 새로 추가.
			fresh = (struct node *)malloc(sizeof(struct node));
			fresh->Tel = (wchar_t *)malloc(200); fresh->Email = (wchar_t *)malloc(300);
			fresh->Note = (wchar_t *)malloc(1000);
			wcscpy_s(fresh->Tel, 100, modi->Tel);
			wcscpy_s(fresh->Email, 150, modi->Email);
			wcscpy_s(fresh->Note, 500, modi->Note);
			printf("input new name : ");
			mod = (wchar_t *)malloc(200);
			_getws_s(mod, 100);
			root = removeNode(root, modi->Name, modi->overlapflag);
			shakeflag--;
			addToBST(mod, fresh->Tel, fresh->Email, fresh->Note);
			CoverWrite();
			break;
		case 2:
			// 전화번호를 바꾸는경우
			printf("input new phone number : ");
			mod = (wchar_t *)malloc(200);
			_getws_s(mod, 100);
			wcscpy_s(modi->Tel, 100, mod);
			CoverWrite();
			break;
		case 3:
			// 이메일을 바꾸는 경우
			printf("input new email : ");
			mod = (wchar_t *)malloc(300);
			_getws_s(mod, 150);
			wcscpy_s(modi->Email, 150, mod);
			CoverWrite();
			break;
		case 4:
			// 노트를 바꾸는 경우
			printf("input new note : ");
			mod = (wchar_t *)malloc(1000);
			_getws_s(mod, 500);
			wcscpy_s(modi->Note, 500, mod);
			CoverWrite();
			break;
		}
	}

	// case 1: 다른정보를 수정하려고 하면 그대로.
	// case 2: 이름을 수정하면 해당 노드를 삭제하고 재추가.
	// case 3: 동명이인을 중 누구를 수정?
}
void Delete(struct node *del, wchar_t *find)
{
	// 동명이인중 누구를 삭제?
	struct node *temp = del;
	struct working *decision = first;
	int cnt = 0;

	printf("## Here is Delete function\n");
	if (overlapflag > 1)
	{
		//동명이인이 있는 경우
		int select;
		while (1)
		{
			printf("##   Who want to delete?(input overlapflag) : ");
			scanf_s("%d", &select);
			fflush(stdin);

			//select가 이상한 값인지 아닌지 확인
			while (decision != NULL)
			{
				if (decision->connect->overlapflag == select)
				{
					cnt++;
				}
				decision = decision->next;
			}
			decision = first;
			if (cnt == 0)
			{
				printf("Try again! This overlap is not included in List\n");
			}
			else
			{
				break;
			}
		}
		temp = findobject(NULL, select);
		destorySLL();
		//	wprintf(L"지울 놈 : %s %s\n", temp->Name, temp->Tel);
		root = removeNode(root, temp->Name, select);
		shakeflag--;
	}
	else
	{
		root = removeNode(root, temp->Name, 0);
		shakeflag--;
	}

	printf("##   Delete sucessfully!\n");
	CoverWrite();
	getchar();

}
struct node *removeNode(struct node *node, wchar_t *key, int overlap)
{
	if (node == NULL)
	{
		return;
	}
	if ((wcscmp(key, node->Name) == 0 && (node->overlapflag == overlap || overlap == 0)))
	{
		//		printf("%d %d\n", node->overlapflag, overlap);
		//		wprintf(L"%s %s\n", node->Name, node->Tel);
		// found match
		if (node->left == NULL && node->right == NULL) // 자식이 없음
		{
			//수정
			DeleteDLL(node);
			free(node);
			return 0;
		}
		else if (node->left == NULL) // 오른쪽 자식은 남아있음.
		{
			struct node *ret = node->right;
			DeleteDLL(node);
			free(node);
			return ret;
		}
		else if (node->right == NULL) // 왼쪽 자식은 남아있음.
		{
			struct node *ret = node->left;
			DeleteDLL(node);
			free(node);
			return ret;
		}
		else // 양쪽 모두 자식이 있음..
		{
			struct node *toReplace = findLeast(node->right);
			//		DeleteDLL(node);
			wcscpy_s(node->Name, 20, toReplace->Name);
			wcscpy_s(node->Tel, 20, toReplace->Tel);
			wcscpy_s(node->Email, 20, toReplace->Email);
			wcscpy_s(node->Note, 20, toReplace->Note);
			node->right = removeNode(node->right, toReplace->Name, 0);
			return node;
		}
	}
	else if (wcscmp(key, node->Name) < 0)
	{
		// 지워지니까 부모로!
		node->left = removeNode(node->left, key, overlap);
		return node;
	}
	else // key>node->i
	{
		node->right = removeNode(node->right, key, overlap);
		return node;
	}
}
struct node *findLeast(struct node *node)
{
	// 가장 작은 값을 가진 놈을 찾음. 기준에서..
	struct node *cur = node;
	while (cur->left != NULL)
	{
		cur = cur->left;
	}
	return cur;
}

// 지울때나 이름을 수정할땐 어떻게 할까?
void connectBST(struct node *node)
{
	struct sorting *fresh;
	fresh = (struct sorting *)malloc(sizeof(struct sorting));
	fresh->next = 0;
	fresh->prev = 0;
	fresh->connect = (struct node *)malloc(sizeof(struct node)); // BST를 가르쳐 줄 놈.
																 //	struct node *connectDLL = node;
	fresh->connect = node; // BST가르키기
						   // BST에 추가하면서 그때그때 넣어줌 - 이름수정과 삭제때 고려안함 (지금은)
						   // BST를 탐색하면서 순서대로 주소를 갖다 씀. (x)
						   /*  DLL을 붙여나갈때 Sorting 시키면서 붙여나가는 걸로 ㅎㅎ */
	if (head == NULL)
	{
		//DLL이 비어 있을 때
		head = fresh;
		return;
	}
	else
	{
		// 붙일 때마다 이미 들어와 있는 값과 비교해서 크기 순으로 맞춰나가자

		struct sorting *temp = head;
		while (1)
		{
			//		wprintf(L"temp: %s %s %s %s\n", temp->connect->Name, temp->connect->Tel, temp->connect->Email, temp->connect->Note);
			if (wcscmp(fresh->connect->Name, temp->connect->Name) < 0)
			{
				if (temp == head)
				{
					temp->prev = fresh;
					fresh->next = temp;
					head = head->prev;
					//				wprintf(L"head: %s %s %s %s\n", head->connect->Name, head->connect->Tel, head->connect->Email, head->connect->Note);
					return;
				}
				else
				{
					fresh->next = temp;
					fresh->prev = temp->prev;
					temp->prev->next = fresh;
					temp->prev = fresh;
					return;
				}
			}
			else if (temp->next == NULL)
			{
				temp->next = fresh;
				fresh->prev = temp;
				return;
			}
			temp = temp->next;
		}
	}
}

void DeleteDLL(struct node *del)
{
	struct sorting *cur = head;
	// 지울 노드를 찾음
	while (1)
	{
		if (cur == NULL)
		{
			// place가 DLL에 없는 경우
			return;
		}
		if (cur->connect != del)
		{
			cur = cur->next;
		}
		else
		{
			break;
		}
	}
	//	wprintf(L"%s %s\n", cur->connect->Name, cur->connect->Tel);
	// cur는 지울 노드를 가리키고 있음.
	// 1. cur가 head일 경우.
	if (cur == head)
	{
		head = head->next;
		if (head->next != NULL)
		{
			head->next->prev = NULL;
		}
		free(cur);
		return;
	}
	else
	{
		cur->prev->next = cur->next;
		if (cur->next != NULL)
		{
			cur->next->prev = cur->prev;
		}
		free(cur);
		return;
	}
}

void addToSLL(struct node *node)
{
	struct working *fresh;
	fresh = (struct working *)malloc(sizeof(struct working));
	fresh->connect = (struct node *)malloc(sizeof(struct node));
	fresh->next = NULL;
	fresh->connect = node;
	if (first == NULL)
	{
		first = fresh;
		return;
	}
	else
	{
		struct working *temp = first;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = fresh;
	}

	{
		struct working *temp = first;
		while (temp != NULL)
		{
			//		wprintf(L"SLL--------------------%s, overlap:%d\n", temp->connect->Name, temp->connect->overlapflag);
			temp = temp->next;
		}
	}

}
void destorySLL(void)
{
	// 검색만 하고 바로 제거 ㅋ
	struct working *del;
	while (first != NULL)
	{
		del = first;
		first = first->next;
		free(del);
	}
}
//SLL - 초성 검색, 성씨검색등으로 나온 놈 처리
struct node *findobject(wchar_t *keyword, int select)
{
	struct working *work = first;
	while (work != NULL)
	{
		if (keyword == NULL)
		{
			if (work->connect->overlapflag == select)
			{
				return work->connect;
			}
		}
		else
		{
			if (wcscmp(work->connect->Name, keyword) == 0 || (keyword[0] == work->connect->Name[0] && wcslen(keyword) < 2))
			{
				if (work->connect->overlapflag == select)
				{
					//		wprintf(L"find--------------------%s, overlap:%d\n", work->connect->Name, work->connect->overlapflag);
					return work->connect;
				}
			}
		}
		work = work->next;
	}
}

void CoverWrite(void) // 수정, 삭제가 일어낫을때 처음부터 다시 써줄 함수
{
	struct sorting *temp = head;
	fclose(fp_save);
	fopen_s(&fp_save, "phonebook.txt", "wt");
	while (temp != NULL)
	{
		if (wcscmp(temp->connect->Name, L"none") != 0) { fwprintf(fp_save, L"Name : %s\n", temp->connect->Name); }
		if (wcscmp(temp->connect->Tel, L"none") != 0) { fwprintf(fp_save, L"Tel : %s\n", temp->connect->Tel); }
		if (wcscmp(temp->connect->Email, L"none") != 0) { fwprintf(fp_save, L"Email : %s\n", temp->connect->Email); }
		if (wcscmp(temp->connect->Note, L"none") != 0) { fwprintf(fp_save, L"Note : %s\n", temp->connect->Note); }
		fwprintf(fp_save, L"\n");
		temp = temp->next;
	}
} // 수정이나 삭제햇을때 덮어쓰기



