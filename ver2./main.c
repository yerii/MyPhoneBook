#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node *root=0;
int main(void)
{


   char buf_name[30];
   char buf_tel[30];
   char buf_mail[30];
   char buf_note[30];
   char buf[30];
   int i;
   int choice;
   FILE *fp=fopen("addressbook.txt","r");


   while(getc!=-1)
   {
      while((i=fgetc(fp))!=':')
      {
         if(i == -1)
         {
            break;
         }
      }
      if(i == -1)
      {
         break;
      }

      fgets(buf_name,sizeof(buf_name),fp);
      buf_name[strlen(buf_name)-1]='\0';

      while((i=fgetc(fp))!=':')
      {

      }


      fgets(buf_tel,sizeof(buf_tel),fp);
      buf_tel[strlen(buf_tel)-1]='\0';

      while((i=fgetc(fp))!=':')
      {

      }


      fgets(buf_mail,sizeof(buf_mail),fp);
      buf_mail[strlen(buf_mail)-1]='\0';

      while((i=fgetc(fp))!=':')
      {

      }


      fgets(buf_note,sizeof(buf_note),fp);
      buf_note[strlen(buf_note)-1]='\0';      

      Fadd(buf_name,buf_tel,buf_mail,buf_note);


   }
   while(1)
   {

      basic();
      printf("기능을 선택해주세요 : ");
      fflush(stdin);
      scanf("%d",&choice);

      if(choice==1)
      {
         system("cls");
         printf("주소록을 불러왔습니다.\n");
      }
      else if(choice==2)//검색
      { 
         system("cls");
         basic();
         while(1)
         {
            printf("찾고싶은 사람의 이름을 입력해주세요 :");
            scanf("%s",&buf);

            if(strcasecmp(buf,"menu")==0)
            {
               printf("\n");
               break;
            }
            Fsearch(buf);
         }
      }
      else if(choice==3)//추가
      {
         system("cls");
         basic();
         while(1)
         {
            printf("추가할 이름을 입력해주세요 :");
            scanf("%s",buf_name);
            if(strcasecmp(buf_name,"menu")==0)
            {
               printf("\n");
               break;
            }
            printf("추가할 번호를 입력해주세요 :");
            scanf("%s",buf_tel);
            if(strcasecmp(buf_tel,"menu")==0)
            {
               printf("\n");
               break;
            }
            printf("추가할 메일을 입력해주세요 :");
            scanf("%s",buf_mail);
            if(strcasecmp(buf_mail,"menu")==0)
            {
               printf("\n");
               break;
            }
            printf("추가할 노트를 입력해주세요 :");
            scanf("%s",buf_note);
            printf("\n");

            Fadd(buf_name,buf_tel,buf_mail,buf_note);

            if(strcasecmp(buf_note,"menu")==0)
            {
               printf("\n");
               break;
            }
         }
      }
      else if(choice==4)//삭제
      {
         system("cls");
         basic();
         while(1)
         {
            printf("삭제할 이름을 입력해주세요 :");
            scanf("%s",&buf);
            if(strcasecmp(buf,"menu")==0)
            {
               printf("\n");
               break;
            }
            removeBST(root,buf);
         }

      }
      else if(choice==5) //보기
      {
         system("cls");
         basic();
         printDLL();
      }
      else if(choice==6)
      {
         writeDLL();
         printf("\n-----------종료하겠습니다------------\n");
         return 0;
      }
   }
   fclose(fp);
   return 0;

}
