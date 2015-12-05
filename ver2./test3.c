#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <test3.h>
struct node
{
   char *name;
   char *tel;
   char *mail;
   char *note;
   struct node *left;
   struct node *right;
   struct node *next;
};
struct DLL
{
   struct node *bst;
   struct DLL *prev;
   struct DLL *next;
};
struct node *root = 0;
struct DLL *head = 0;
void writeDLL()
{
   struct DLL *temp = head;
   FILE *fp = 0;
   fp = fopen("addressbook.txt", "w");
   while(temp != 0)
   {
      fprintf(fp, "Name:%s\n", temp->bst->name);
      fprintf(fp, "Tel:%s\n", temp->bst->tel);
      fprintf(fp, "Email:%s\n", temp->bst->mail);

      fprintf(fp, "Note:%s\n", temp->bst->note);
      fprintf(fp, "\n");
      temp = temp->next;
   }
   
}
void addtoDLL(struct node *bst)
{
   struct DLL *new_DLL = (struct DLL *)malloc(sizeof(struct DLL));


   new_DLL->bst=bst;
   new_DLL->next=0;
   new_DLL->prev=0;

   if(head==0)
   {
      head=new_DLL;
      return;
   }
   else
   {
      struct DLL *cur = head;

      while(1)
      {
         if(strcmp(new_DLL->bst->name, cur->bst->name)<0)
         {
            if(cur == head)
            {
               cur->prev = new_DLL;
               new_DLL->next = cur;
               head = head->prev;
               return;
            }
            else
            {
               new_DLL->next = cur;
               new_DLL->prev = cur->prev;
               cur->prev->next = new_DLL;
               cur->prev = new_DLL;
               return;
            }
         }
         else if(cur->next == NULL)
         {
            cur->next = new_DLL;
            new_DLL->prev = cur;
            return;
         }
         cur = cur->next;
      }
   }
}
void printDLL()
{
   struct DLL *cur=head;
   if(head==0)
   {
      return ;
   }
   
   while(cur!=0)
   {
      printf("Name:%s\nTel:%s\nMail:%s\nNote:%s\n\n",cur->bst->name,cur->bst->tel,cur->bst->mail,cur->bst->note);
      cur=cur->next;
      
   }
}
void delFromDLL(int which)
{
   struct DLL *cur=head, *crr=head;

   //1. 지울 노드를 찾는다
   if(head->bst == which)   // 지울 노드가 첫번째 노드인 경우
   {
      head=head->next;
      free(cur);
      return;
   }
   cur=crr->next;
   while(crr->next != 0)
   {
      if(crr->next->bst == which)
      {
         cur=crr->next;
         crr->next = cur->next;

         free(cur);
         return;

      }
      else
      {
         crr=crr->next;
      }
   }
}
struct node *findLeast(struct node *node)
{
   struct node *cur = node;
   while(cur->left != 0)
   {
      cur = cur->left;
   }
   return cur;
}
struct node *removeBST(struct node *node, char *name)
{
   if(node == 0)
   {
      return;
   }
   if (strcmp(name,node->name)==0)
   {
      if(node->left == 0 && node->right == 0)
      {
         free(node);
         return 0;
      }
      else if(node->left==0)
      {//오른쪽 자식만 있는경우
         
         struct node *ret=node->right;
         free(node);
         return ret;
      }
      else if(node->right==0)
      {//왼쪽 자식만 있는경우
         struct node *ret=node->left;
         free(node);
         return ret;
      }
      else
      {//자식이 둘 다 있는 경우
         struct node *toReplace = findLeast(node->right);
         strcpy(node->name,toReplace->name);
         node->right=removeBST(node->right,toReplace->name);
         return node;
      }
   }
   else if (strcmp(name,node->name) < 0)
   {
      node->left = removeBST(node->left,name);
            return node;
   }
   else
   {
      node->right = removeBST(node->right,name);
      return node;
   }
   
}
struct node *createNewNode(char *name, char *tel, char *mail, char *note)
{

   struct node *new_node = (struct node *)malloc(sizeof(struct node));
   char *_name, *_tel,*_mail, *_note;
   new_node->left = 0;
   new_node->right = 0;
   _name = (char *)malloc(strlen(name)+1);
   strcpy(_name,name);
   _tel = (char *)malloc(strlen(tel)+1);
   strcpy(_tel, tel);
   _mail = (char *)malloc(strlen(mail)+1);
   strcpy(_mail, mail);
   _note = (char *)malloc(strlen(note)+1);
   strcpy(_note, note);

   new_node->name = _name;
   new_node->tel = _tel;
   new_node->mail = _mail;
   new_node->note = _note;

   return new_node;

}

void Fadd(char *name, char *tel, char *mail, char *note)
{
   struct node *new_node = createNewNode(name, tel, mail, note);
   addtoDLL(new_node);
   if( root == 0)
   {
      root = new_node;
      return;
   }
   else
   {
      struct node *cur_node = root;
      while(1)
      {
         // strcmp : strin compare strcmp(s1,s2)
         // return 0. s1 == s2  김철수 == 김철수
         // return -1 strcmp(s1, s2) < 0 s1 < s2 : s1==김철수, s2==나철수
         if( strcmp(cur_node->name, new_node->name) < 0)//right
         {
            if(cur_node->right == 0)
            {
               cur_node->right = new_node;
               return;
            }
            else
            {
               cur_node = cur_node->right;
            }
         }
         else if( strcmp(cur_node->name, new_node->name) > 0 )//left
         {
            if(cur_node->left == 0)
            {
               cur_node->left = new_node;
               return;
            }
            else
            {
               cur_node = cur_node->left;
            }
         }
         else // strcmp == 0 동일 이름
         {
            printf("same name\n");
            return;
         }
      }
   }

}
void Fshow(struct node *node)
{
   if(node == 0)
   {
      printf("node is null\n");
      return;
   }
   printf("Name:%s\nTel:%s\nE-mail:%s\nNote:%s\n", node->name,node->tel,node->mail,node->note);
   printf("\n");
}
void inorder(struct node *node)
{
   if(node == 0)
   {
      return;
   }
   inorder(node->left);
   Fshow(node);
   inorder(node->right);
}
void Fsearch(char *name)
{
   struct node *cur_node = root;


   while(1)
   {
      if(cur_node == 0)
      {
         printf("%s(이)라는 이름을 가진 사람이 없습니다...\n",name);
         return;
      }

      if( strcasecmp(cur_node->name, name) < 0)//right
      {
         cur_node = cur_node->right;
      }
      else if( strcasecmp(cur_node->name, name) > 0 )//left
      {
         cur_node = cur_node->left;
      }
      else // strcmp == 0 동일 이름
      {
         printf("Name:%s\nTel:%s\nE-Mail:%s\nNote:%s\n",cur_node->name,cur_node->tel,cur_node->mail, cur_node->note);
         printf("\n");
         return;
      }
   }
}
