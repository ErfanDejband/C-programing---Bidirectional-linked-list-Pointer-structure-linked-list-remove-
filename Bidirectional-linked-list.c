#include <stdio.h>
#include <stdlib.h>

typedef struct num_storage
{
    int number;
    struct num_storage *next;
    struct num_storage *prev; // add a link to a previous num_storage
} tNumStorage;

typedef struct num_stor_head
{
    int counts;
    struct num_storage *head;
    struct num_storage *tail;
    struct num_storage *previous_tail;
} tNumStorHead;


void add_number(tNumStorHead *list, int input);
void get_input(tNumStorHead *list);
void initial_list(tNumStorHead *list);
void print_list(tNumStorHead *list);


int main (void)
{
    int i;
    tNumStorHead *list;
    list = (tNumStorHead *) malloc (sizeof(tNumStorHead));
    initial_list(list);
    get_input(list);
}

void initial_list(tNumStorHead *list)
{
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void print_list(tNumStorHead *list)
{
    
    tNumStorage *node_ptr;
    printf("\n");
    printf("  list->counts: %d\n", list->counts);
    node_ptr=list->head;
    printf("  from head --> ");
    while (node_ptr != NULL)
    {
        printf("%d ", node_ptr->number);
        node_ptr = node_ptr->next;
    }
    node_ptr=list->tail;
    printf("\n  from tail --> ");
    while (node_ptr != NULL)
    {
        printf("%d ", node_ptr->number);
        node_ptr = node_ptr->prev;
    }
    printf("\n\n");
    
}

void add_number(tNumStorHead *list, int input)
{
    //boundery part and create conections
    int target_location;
    int possition;
    tNumStorage *Uinput;
    Uinput = (tNumStorage *) malloc (sizeof(tNumStorage));
    Uinput->number=input; // give number
    if (list->counts == 0) // create only a head
    {
        list->head = Uinput;
        list->tail = Uinput;
        list->head->next=NULL;
        list->head->prev=NULL;
    }
    else if(list->counts == 1 ) // previous tail will be head because there is only two storage
    {
        printf("Specify a target location: ");
        scanf("%d", &target_location);
        if(target_location>list->counts){
            printf("there is NOT such location last location is -%d-\n",list->counts);
            get_input(list);}
        if(target_location<1){
            printf("First target location is _1_\n");
            get_input(list);}
        printf("1.Befor or 2.After the location %d: ",target_location);
        scanf("%d", &possition);
        if(possition>2){
            printf("No such choose !\n");
            get_input(list);
        }

        if(possition==1){
            list->head->prev = Uinput;
            Uinput->prev = NULL;
            list->head=list->head->prev;
            list->previous_tail=list->head;
            Uinput->next=list->tail;
            // list->tail->next = NULL;
        }else{
            list->head->next = Uinput;
            list->tail=Uinput;
            list->previous_tail=list->head;
            list->tail->next = NULL;
            list->tail->prev = list->previous_tail;
        }
    }
    //previous tail will be tail before updating
    else{
        printf("Specify a target location: ");
        scanf("%d", &target_location);
        if(target_location>list->counts){
            printf("there is NOT such location last location is -%d-\n",list->counts);
            get_input(list);}
        if(target_location<1){
            printf("First target location is _1_\n");
            get_input(list);}
        printf("1.Befor or 2.After the location %d: ",target_location);
        scanf("%d", &possition);
        if(possition>2){
            printf("No such choose !\n ");
            get_input(list);}
        else
        {

            tNumStorage *temp_p;
            temp_p = (tNumStorage *) malloc (sizeof(tNumStorage));
            // tNumStorage *temp_p2;
            // temp_p2 = (tNumStorage *) malloc (sizeof(tNumStorage));
            temp_p=list->head;
            int point_to_location=1;
            while (point_to_location!=target_location)
            {
                point_to_location=point_to_location+1;
                temp_p=temp_p->next;
            }
            printf("\npoint_to_location = %d \n",point_to_location);
            printf("temp_p->number = %d\n",temp_p->number);
            if (possition==1)
            {
                
                Uinput->next=temp_p;
                Uinput->prev=temp_p->prev;
                if(point_to_location==1)
                {
                    list->head= Uinput;
                }else if(point_to_location==list->counts){
                    // temp_p2=temp_p->prev;
                    // temp_p2->next=Uinput;
                    (temp_p->prev)->next=Uinput;

                    list->previous_tail=temp_p->prev;
                }else{
                    // temp_p2=temp_p->prev;
                    // temp_p2->next=Uinput;
                    (temp_p->prev)->next=Uinput;
                }
                temp_p->prev=Uinput;
            }
            else
            {
                Uinput->prev=temp_p;
                Uinput->next=temp_p->next;
                if(point_to_location==list->counts){
                    list->tail=Uinput;
                    list->previous_tail=list->tail->prev;
                }else if(point_to_location==(list->counts)-1){
                    // temp_p2=temp_p->next;
                    // temp_p2->prev=Uinput;
                    (temp_p->next)->prev=Uinput;
                    list->previous_tail=list->tail->prev;
                }else{
                    // temp_p2=temp_p->prev;
                    // temp_p2->next=Uinput;
                    (temp_p->next)->prev=Uinput;
                }
                temp_p->next=Uinput;
            }
            // free(temp_p);
        }
    }
    list->counts = list->counts+1;
}

void delete_last(tNumStorHead *list){ // ne function to delet
    if(list->counts==0){ // if there is nothing or it is beging of the program
        printf("\nThere is Nothing to delete ~('o')~");
    }
    // if there is only head and we dont have tail and previous tail yet
    else if(list->counts==1){ 
        int target_location;
        printf("Specify a target location: ");
        scanf("%d", &target_location);
        if(target_location>list->counts){
            printf("there is NOT such location last location is -%d-\n",list->counts);
            get_input(list);}
        if(target_location<1){
            printf("First target location is _1_\n");
            get_input(list);}
        list->counts = list->counts-1;
        initial_list(list);
    }
    else{
        int target_location;
        printf("Specify a target location: ");
        scanf("%d", &target_location);
        if(target_location>list->counts){
            printf("there is NOT such location last location is -%d-\n",list->counts);
            get_input(list);}
        if(target_location<1){
            printf("First target location is _1_\n");
            get_input(list);}
        tNumStorage *temp_p;
        temp_p = (tNumStorage *) malloc (sizeof(tNumStorage));
        temp_p=list->head;
        int point_to_location=1;
        while (point_to_location!=target_location)
        {
            point_to_location=point_to_location+1;
            temp_p=temp_p->next;
        }
        if (point_to_location==1)
        {
            list->head=list->head->next;
            list->head->prev=NULL;
            temp_p->next=NULL;
        }else if (point_to_location==list->counts)
        {
            list->tail=list->tail->prev;
            list->previous_tail=list->previous_tail->prev;
            temp_p->prev=NULL;
            list->tail->next=NULL;
        }else if (point_to_location==(list->counts-1))
        {
            list->previous_tail=list->previous_tail->prev;
            (temp_p->prev)->next=temp_p->next;
            (temp_p->next)->prev=temp_p->prev;
            temp_p->next=NULL;
            temp_p->prev=NULL;
        }else
        {
            (temp_p->prev)->next=temp_p->next;
            (temp_p->next)->prev=temp_p->prev;
            temp_p->next=NULL;
            temp_p->prev=NULL;
        }
        free(temp_p);
        list->counts = list->counts-1;
    }
    

}
void get_input(tNumStorHead *list)
{   
    int addordel=0;
    int addnum;
    while(addordel!=-1)
    { 
        printf("1. Add number or 2. Delet a number: ");
        scanf("%d", &addordel);
        if(addordel==1){
            printf("Add your number: ");
            scanf("%d", &addnum);
            
            add_number(list,addnum);
            print_list(list);
            }
        else if(addordel==2){
            delete_last(list);
            print_list(list);
            }
        else if(addordel != -1)
        {printf("!!No such choose !\n");}
        
        
    }
    printf("\nbye (^_^) bye \n\n\n");
}
