#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct frame{
	item data;
	struct frame *next;
} frame;

typedef struct queue{
	frame *head;
	frame *tail;
	int size;
}queue;

void initialize_queue(queue *que);
void enqueue(queue *que, item x);
void print_queue(queue que);
item dequeue(queue *que);
void free_queue(queue *que);

int main(){
	queue que;
	initialize_queue(&que);
	enqueue(&que, 3);
	enqueue(&que, 4);
	print_queue(que);

	dequeue(&que);
	print_queue(que);
	dequeue(&que);
	print_queue(que);
	dequeue(&que);
	print_queue(que);
	free_queue(&que);
}

void initialize_queue(queue *que){
	que->head=NULL;
	que->tail=NULL;
	que->size=0;
}

void enqueue(queue *que, item x){
	frame *new_tail=malloc(sizeof(frame));
	new_tail->data=x;
	new_tail->next=NULL;
	if(que->tail!=NULL)
		que->tail->next=new_tail;
	else
		que->head=new_tail;
	que->tail=new_tail;
	que->size++;
}

void print_queue(queue que){
	frame *current=que.head;
	if(current==NULL){
		printf("Queue is empty.\n");
		return;
	}
	for(int i=0; i<que.size; i++){
		printf("%d ", current->data);
		current=current->next;
	}
	printf("\n");
}

item dequeue(queue *que){
	frame *old_head=que->head;
	if(old_head==NULL){
		printf("Dequeue failed: queue is empty.\n");
		return -1;
	}
	item r=que->head->data;
	que->head=que->head->next;
	if(que->head==NULL)
		que->tail=NULL;
	free(old_head);
	que->size--;
	return r;
}

void free_queue(queue *que){
	frame *current=que->head;
	for(int i=0; i<que->size; i++){
		frame *next=current->next;
		free(current);
		current=next;
	}
	que->head=NULL;
	que->tail=NULL;
	que->size=0;
}
