#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
struct node{
node *previous;
int data;
int id;
node *next;
};

node* deletion(node *start);
void insertionAtEnd(node**,int,int);
int round_robin(node **head,int quanta,int *save,int *gantt);
void display(node*);

int main(){
node *start=NULL;
int n,save=0;
cin>>n;
int *gantt=(int*)malloc(sizeof(int)*100*2);
int i=0;
while(n!=-1){
    insertionAtEnd(&start,n,i++);
    cin>>n;
}
cout<<"Before Scheduling \n";
display(start);
int g,cpu=100,value,k=0;
while(start){
g=round_robin(&start,10,&save,gantt);
if(gantt[g-1]%9==0){
    k++;
    srand(time(0));
    value=(rand()%(50-value+1)+1);
insertionAtEnd(&start,value,i++);
cout<<"\nBefore Scheduling \n";
display(start);
}
if(gantt[g-1]>=cpu)break;
cout<<"\nAfter Scheduling \n";
display(start);
cout<<"\nrand "<<value<<"\ng "<<g;
}
cout<<"\nSave Time = "<<save;
cout<<"\nGantt Chart\n";
for(int i=0;i<g;i++){
    cout<<*(gantt+i)<<" "<<*(gantt+100+i)<<"\n";
}
return 0;
}

void insertionAtEnd(node **start,int time,int d){
    node *n=new node;
    n->data=time;
    n->id=d;
    n->next=(*start);
   if((*start)==NULL){
    n->previous=n;
    n->next=n;
    (*start)= n;
   }else{
       node *temp=(*start);
      while(temp->next!=(*start)){
        temp=temp->next;
      }
      temp->next=n;
      n->previous=temp;
      (*start)->previous=n;
   }
}
int round_robin(node **start,int quanta,int *save,int *gantt){
     static int counter=0;
    static int g=0;
 if((*start)->data>quanta){
    (*start)->data=(*start)->data-quanta;
     *(gantt+(g))=(*start)->id;
    (*start)=(*start)->next;
    counter=counter+quanta;
 }else{
    *save=*save+(quanta-(*start)->data);
    counter=counter+(*start)->data;
     *(gantt+(g))=(*start)->id;
     (*start)=deletion(*start);
     }
     cout<<"\ncounter="<<counter;
      *(gantt+(1*100)+g)=counter;
      g++;
      return g;
}
void display(node *start){
node *ptr=start;
while(ptr&&ptr->next!=start){
    cout<<ptr->data<<" ";
    ptr=ptr->next;
}
if(ptr)
cout<<ptr->data;
}
node* deletion(node *start){
    if(start->next==start)return NULL;

node *last=start->previous;
start=start->next;
start->previous=last;
last->next=start;
return start;
}
