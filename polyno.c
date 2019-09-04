#include<stdio.h>
#include<stdlib.h>
typedef struct node{
  int exp,coef;
  struct node* link;
}node;
node* pptr=NULL,*qptr=NULL,*rptr=NULL;
void insert(int exp,int coef,node** pptr);
node* eq(int exp);
void mul();
void add();
void traversal();
int main(void){
  int exp,coef;
  
  printf("Enter the coefficients and exponents of First polynomial ");
  scanf("%d%d",&coef,&exp);
  while(coef!=0){
    insert(exp,coef,&pptr);
    scanf("%d%d",&coef,&exp);
  }

  printf("Enter the coefficients and exponents of Second polynomial ");
  scanf("%d%d",&coef,&exp);
  while(coef!=0){
    insert(exp,coef,&qptr);
    scanf("%d%d",&coef,&exp);
  }
  
  add(pptr,qptr,rptr);
  traversal();
  rptr=NULL;
  mul(pptr,qptr,rptr);
  traversal();
}

void insert(int exp,int coef,node** pptr){
  node* temp=*pptr,*temp1;
  node* newnode=(node*)malloc(sizeof(node));
  newnode->exp=exp;
  newnode->coef=coef;
  newnode->link=NULL;
  if(*pptr==NULL){
    *pptr=newnode;
    return;
  }
  else{
    while(temp!=NULL){
      temp1=temp;
      temp=temp->link;
    }
    temp1->link=newnode;
  }
}
      
void traversal(){
  node* temp=rptr;
  while(temp!=NULL){
    printf("%dx^%d ",temp->coef,temp->exp);
    temp=temp->link;
    if(temp!=NULL)
      printf("+");
  }
  printf("\n");
}

node* eq(int x){
  node* temp=rptr;
  while(temp!=NULL){
    if(temp->exp==x)
      return temp;
    temp=temp->link;
  }
  return NULL;
}

void add(){
  node* temp1=pptr,*temp2=qptr;
  while(temp1!=NULL && temp2!=NULL){
    if(temp1->exp>temp2->exp){
      insert(temp1->exp,temp1->coef,&rptr);
      temp1=temp1->link;
    }
    else if(temp2->exp>temp1->exp){
      insert(temp2->exp,temp2->coef,&rptr);
      temp2=temp2->link;
    }
    else{
      insert(temp1->exp,temp2->coef+temp1->coef,&rptr);
      temp1=temp1->link;
      temp2=temp2->link;
    }
  }
  if(temp1!=NULL){
    while(temp1!=NULL){
      insert(temp1->exp,temp1->coef,&rptr);
      temp1=temp1->link;
    }
  }
  else if(temp2!=NULL){
    while(temp2!=NULL){
      insert(temp2->exp,temp2->coef,&rptr);
      temp2=temp2->link;
    }
  }
}

void mul(){
  node* temp1=pptr,*temp2=rptr,*temp3=rptr,*t;
  if(temp1==NULL || temp2==NULL){
    temp3->exp=0;
    temp3->coef=0;
    temp3->link=NULL;
    return;
  }
  else{
    while(temp1!=NULL){
      temp2=qptr;
      while(temp2!=NULL){
	t=eq((temp1->exp+temp2->exp));
	if(t!=NULL)
	  t->coef=t->coef+(temp1->coef*temp2->coef);
	else
	  insert((temp1->exp+temp2->exp),(temp1->coef*temp2->coef),&rptr);
	temp2=temp2->link;
      }
      temp1=temp1->link;
    }
  }
}
