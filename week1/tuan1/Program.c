#include<stdio.h>
#include "Linklist.h"
int main(){
  int key;
  FILE * fptr;
  char name[20];
  char pass[20];
  int status;
  int kiem_tra_dang_nhap = 0 ;
   int i,count = 0;
    struct node *ptr;

        fptr = fopen("account.txt","r");
      if(fptr == NULL){
	printf("khong mo duoc file \n ");
	return 1;
      }   
	while( fscanf(fptr,"%s %s %d ",name,pass,&status) != EOF){
	  insertFirst(name,pass,status);
	}
	  fclose(fptr);
	  
  do{
    printf("USER MANAGEMENT PROGRAM \n");
    printf("________________________\n");
    printf("1.Register \n");
    printf("2.Sing in \n");
    printf("3.Search \n");
    printf("4.sign out \n");
      printf("Your choice (1-4, other to quit) : ");
   
   
    scanf("%d",&key);
    switch(key){
    case 1 :
	printf("tao tai khoan \n");
	printf("nhap ten : ");
	scanf("%s",name);
	if(find(name) != NULL){
	  printf("tai khoan da ton tai \n");
	}
	else{
	  printf("nhap mat khau : ");
	  scanf("%s",pass);
	  
	  fptr = fopen("account.txt","a");
	  if(fptr == NULL){
	    printf("khong mo duoc file \n ");
	    return 1;
	  }
	   fprintf(fptr,"%s %s %d \n",name,pass,1);
	   insertFirst(name,pass,1);
	   fclose(fptr);
	}
	
     
      break;
    case 2 :
     
      printf("Dang Nhap\n");
      printf("**************\n");
      printf("ten tai khoan : ");
      scanf("%s",name);
      if(find(name) == NULL){
	
	printf("tai khoan chua ton tai\n");

      }else{

	for(i = 0 ; i<3; i++){

	  printf("nhap mat khau : ");
	  scanf("%s",pass);

	  if(find2(pass) == NULL){
	    printf("mat khau sai\n");
	    count++;
	  }
	  
	  else{
	    break;
	  }
	}
	if(count == 3){
	  printf("tai khoan bi khoan \n");
	  ptr = find(name);
	  if(ptr != NULL){
	    ptr-> status = 0;
	  }
	  fptr = fopen("account.txt","w");

	  if(fptr == NULL){
	    printf("khong mo duoc file \n ");
	    return 1;
	  }
	   ptr = head;

	  while(ptr != NULL)
	{        
	  fprintf(fptr,"%s %s %d \n",ptr->name,ptr->pass,ptr->status);
      ptr = ptr->next;
   }
	  
	  fclose(fptr);
	}
	else{
	  printf("dang nhap thanh cong \n");
	  kiem_tra_dang_nhap = 1;
	}
      }
      break;
    case 3 :
       
      printf("nhap ten tai khoan can tim kiem : ");
      scanf("%s",name);
      ptr = find(name);
      if(ptr != NULL){
	printf("ten tai khoan: %s \n ",ptr->name);
	if(ptr-> status == 1){
	   printf("trang thai tai khoan : active \n");
	}
	if(ptr->status == 0 ){
	  printf("trang thai tai khoan : blocked \n ");
	}
      }
      else{
	printf("tai khoan chua ton tai \n");}
      break;
    case 4 :
      printf("ten tai khoan : ");

      scanf("%s",name);
      
      if(find(name) == NULL){

	printf("tai khoan chua ton tai\n");

      }else
	{
	  if(kiem_tra_dang_nhap == 0){
	    printf("tai khoan chua dang nhap( vui long quay laij buoc 2) \n");
	    break;
	  }
	  if(kiem_tra_dang_nhap == 1){
	    printf("Goodbye HUST\n");
	    key = 5 ;
	    break;
	  }
	}
      break;
    }
  }while(key < 5 );
}
