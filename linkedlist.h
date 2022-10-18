#include <stdio.h>
#include <stdlib.h>

typedef struct _payload_struct{
	int x;
	int y;
} payload_struct;
typedef struct _node{
	payload_struct payload;
  int key;
  struct _node* next;
} node;

typedef struct linked_list{
  node* HEAD;
  node* CURRENT;
  node* BACK;
}ll;

/*
void delete(ll* list, int key);
int length(ll* list);
void reverse(ll* list);
void append(ll* list, int x, int y);
void printlist(ll* list);
void push(ll* list, int x, int y);
int irerate_list(ll* list);
ll* new_list();
*/

void remove_first(ll* list){
	node* tmp_node;
	tmp_node = list->HEAD;
	list->HEAD = list->HEAD->next;
	free(tmp_node);
}

void delete(ll* list, int key){
  node* lag = list->HEAD;
  node* p = list->HEAD;
  while (p->key != key) {
    if(p->next==NULL){
      return;
    }
    lag = p;
    p = p->next;
  }
  lag->next = p->next;
  free(p);
}

int length(ll* list){
  node* p = list->HEAD;
  int i = 0;
  while(p != NULL){
    p = p->next;
    i++;
  }
  return i;
}

void reverse(ll* list){
  node* plag = NULL;
  node* p = list->HEAD;
  node* tmp;

  //while(p->next != NULL){
  while(p != NULL){
    tmp = p->next;
    p->next = plag;
    plag = p;
    p = tmp;
  }
  tmp = list->HEAD;
  list->HEAD = list->BACK;
  list->BACK = tmp;
}

void append(ll* list, payload_struct payload){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->payload = payload;
  if(list->HEAD==NULL){
    list->HEAD = new_node;
    list->BACK = new_node;
    return;
  } 
  list->BACK->next = new_node;
  list->BACK = new_node;
  new_node->next = NULL;
}


void printlist(ll* list){
  node* p = list->HEAD;
  int i = 0;
  while(p!=NULL) {
    printf("Link %d x:%i y:%i\n",i+1,p->payload.x,p->payload.y); 
    p = p->next;
    i++;
  }
}


void push(ll* list, payload_struct payload){
  node* new_node = (node*)malloc(sizeof(node));
  new_node->payload = payload;
  new_node->next = list->HEAD;
  list->HEAD = new_node;
  if(list->BACK == NULL){
  	list->BACK = new_node;
  }
}

ll* new_list(){
  ll* list = (ll*)malloc(sizeof(ll));
  list->HEAD = NULL;
  list->BACK = NULL;
  list->CURRENT = NULL;
  return list;
}

payload_struct iterate_list(ll* list) {
  if(list->CURRENT == NULL){
    list->CURRENT = list->HEAD;
  }
  payload_struct tmp;
  if(list!=NULL) {
    tmp = list->CURRENT->payload;
    if(list->CURRENT->next != NULL){
      list->CURRENT = list->CURRENT->next;
    }else{
      list->CURRENT = list->HEAD;
    }
    return tmp;
  }
}

