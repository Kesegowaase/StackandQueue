#include <stdlib.h>
#include <stdio.h>

int smallest = 100;
struct customer{
	
	int id,first_min,time_spent;
	struct customer *next;
	
};

struct workers{
	int id,customer_id,customer_first,customer_total,total_work,waiting_time;
	struct workers *next;
};

struct customer * customer_queue(struct customer *head,int id,int first_time,int second_time){
	if(head == NULL){
        head = (struct customer *)malloc(sizeof(struct customer));
        head -> id = id;
        head -> first_min = first_time;
        head -> time_spent = second_time;
        head -> next = NULL;
        return head;
    }
    struct customer *iter = head;
    while(iter -> next != NULL)
        iter = iter -> next;
    
    struct customer *temp = (struct customer *)malloc(sizeof(struct customer));
    temp -> id = id;
    temp -> first_min = first_time;
    temp -> time_spent = second_time;
    temp -> next = NULL;
    iter -> next = temp;
    return head;
}

struct workers * workers_stack(struct workers *head,int id){
    
    if(head == NULL){
        head = (struct workers*)malloc(sizeof(struct workers));
        head -> id = id;
        head -> customer_id = 0;
        head -> customer_total = 0;
        head -> total_work = 0;
        head -> waiting_time = 0;
        head -> next = NULL;
        return head;
    }
    struct workers *temp = (struct workers*)malloc(sizeof(struct workers));
    temp -> id = id;
    temp -> customer_id = 0;
    temp -> customer_total = 0;
    temp -> total_work = 0;
    temp -> waiting_time = 0;
    temp -> next = head;
    return temp;
}

int sml(int number){
    
    if(number< smallest)
        return number;
    else
        return smallest;
    
}

struct workers* combine(struct workers *w_root,struct customer *c_root){
    struct workers *w_temp = w_root;
    struct customer *c_temp = c_root;
    for(int i=0;i<6;i++){
        if(w_temp -> customer_total == 0 || w_temp -> customer_total <= c_temp -> first_min){
            w_temp -> customer_id = c_temp -> id;
            w_temp -> customer_first = c_temp -> first_min;
            w_temp -> customer_total = (c_temp -> first_min) + (c_temp -> time_spent);
            w_temp -> total_work += c_temp -> time_spent;
            w_temp -> waiting_time = 0;
            printf("%d %d %d %d %d\n",w_temp -> customer_id,w_temp -> id,w_temp -> customer_first,w_temp -> customer_total,w_temp -> waiting_time);
            return w_root;
        }
            w_temp = w_temp -> next;
    }
    w_temp = w_root;
    for(int j = 0;j<6;j++){
        smallest = sml(w_temp -> customer_total);
        w_temp = w_temp -> next;
    }
    w_temp = w_root;
    
    for(int k = 0;k<6;k++){
        if(w_temp -> customer_total == smallest){
            w_temp -> customer_id = c_temp -> id;
            w_temp -> customer_first = smallest;
            w_temp -> customer_total = smallest + (c_temp -> time_spent);
            w_temp -> total_work += c_temp -> time_spent;
            w_temp -> waiting_time = smallest - c_temp -> first_min;
            printf("%d %d %d %d %d\n",w_temp -> customer_id,w_temp -> id,w_temp -> customer_first,w_temp -> customer_total,w_temp -> waiting_time);
            smallest = 100;
            return w_root;
        }
        w_temp = w_temp -> next;
    }
    
    
}

void shows_total(struct workers *head){
    struct workers *iter = head;
    while(iter != NULL){
        printf("%d %d\n",iter -> id,iter -> total_work);
        iter = iter -> next;
    }
    
}

void shows_queue(struct customer *head){
	struct customer *iter = head;
	while(iter != NULL){
		printf("%d\t%d\t%d\n",iter -> id,iter -> first_min,iter -> time_spent);
		iter = iter -> next;
	}
	
}
void shows_stack(struct workers *head){
    struct workers *iter = head;
    while(iter != NULL){
        printf("%d\n",iter -> id);
        iter = iter -> next;
    }
}



int main(){
    struct workers *w_root = NULL;
    struct customer *c_root = NULL;
	int id,first_time,second_time;
	int counter = 0 ;
	while(1){
		scanf("%d",&id);
		if(id == -1)
			break;
		scanf("%d",&first_time);
		scanf("%d",&second_time);
        counter++;
        c_root = customer_queue(c_root,id,first_time,second_time);
	}
	for(int i=1;i<7;i++){
        w_root = workers_stack(w_root,i);
    }

	for(int i = 0;i< counter;i++){
        w_root = combine(w_root,c_root);
        c_root = c_root -> next;
    }
    
    printf("\n");
    shows_total(w_root);
    
}
