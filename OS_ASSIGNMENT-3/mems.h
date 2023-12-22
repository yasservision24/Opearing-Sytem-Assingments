


#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define PAGE_SIZE 4096





typedef struct mems_node {
    void *start;
    size_t size;
    size_t strt_virtual_address;
    size_t end_virtual_address;
    size_t ret_address;
    struct mems_node *next;
    struct mems_node *prev;
    struct mems_sub_node *sub_head;

} mems_node;

typedef struct mems_sub_node {
    void *start;
    size_t size;
    int type;
    size_t strt_virtual_address;
    size_t end_virtual_address;
    struct mems_sub_node *next;
    struct mems_sub_node *prev;
} mems_sub_node;

mems_node *head = NULL;
mems_node *tail = NULL;

void *start_address = NULL;
void *virtual_address=NULL;
int num_mapped_pages = 0;




void mems_init() {
    head=NULL;
    tail = NULL;



}




void *mems_malloc(size_t size) {



    mems_node *temp = head;
    mems_sub_node *sub_temp = NULL;
    void *ret_address = NULL;

    while (temp != NULL) {
        sub_temp = temp->sub_head;

        while (sub_temp!=NULL) {

            if (sub_temp->type == 0 && sub_temp->size >= size && sub_temp->next==NULL) {



                sub_temp->type = 1;

                sub_temp->strt_virtual_address=sub_temp->prev->end_virtual_address+1;
                sub_temp->end_virtual_address=sub_temp->strt_virtual_address+size-1;
                ret_address=sub_temp->start;
                //virtual_address=(sub_temp->strt_virtual_address);
                virtual_address = (void*)(uintptr_t)(sub_temp->strt_virtual_address);


                mems_sub_node *just_sub_node = (mems_sub_node *)mmap(NULL, sizeof(mems_sub_node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                sub_temp->next=just_sub_node;
                just_sub_node->start = sub_temp->start+size;
                just_sub_node->size = (sub_temp->size)-size;
                just_sub_node->type = 0;
                just_sub_node->prev = sub_temp;
                just_sub_node->next = NULL;
                just_sub_node->strt_virtual_address=sub_temp->end_virtual_address+1;
                just_sub_node->end_virtual_address=just_sub_node->strt_virtual_address+just_sub_node->size-1;



                sub_temp->size=size;
                sub_temp->next=just_sub_node;
                break;
            }
            else if(sub_temp->type == 0 && sub_temp->size >= size && sub_temp->next!=NULL){

                    sub_temp->type = 1;

                    sub_temp->strt_virtual_address=sub_temp->prev->end_virtual_address+1;
                    sub_temp->end_virtual_address=sub_temp->strt_virtual_address+size-1;
                    ret_address=sub_temp->start;
                    //virtual_address=sub_temp->strt_virtual_address;
                    virtual_address = (void*)(uintptr_t)(sub_temp->strt_virtual_address);


                    mems_sub_node *just_sub_node = (mems_sub_node *)mmap(NULL, sizeof(mems_sub_node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                    sub_temp->next=just_sub_node;
                    just_sub_node->start = sub_temp->start+size;
                    just_sub_node->size = (sub_temp->size)-size;
                    just_sub_node->type = 0;
                    just_sub_node->prev = sub_temp;
                    just_sub_node->next = sub_temp->next;
                    just_sub_node->strt_virtual_address=sub_temp->end_virtual_address+1;
                    just_sub_node->end_virtual_address=just_sub_node->strt_virtual_address+just_sub_node->size-1;//sub_temp->next->strt_virtual_address-1;

            }








            sub_temp = sub_temp->next;
        }
        if (ret_address != NULL) {
            break;
        }
        temp = temp->next;

    }

    if (ret_address == NULL) {

        size_t alloc_size = size;
        size_t num_pages = (alloc_size / PAGE_SIZE) + 1;


        mems_node *new_node = (mems_node *) mmap(NULL, num_pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        new_node->start = mmap(NULL, num_pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        new_node->next = NULL;
        new_node->prev = NULL;

        new_node->size=(num_pages * PAGE_SIZE);



        if (head == NULL) {
        head = new_node;
        tail = new_node;
        new_node->strt_virtual_address=1000;
        new_node->end_virtual_address=new_node->strt_virtual_address+num_pages*PAGE_SIZE-1;

        } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
        new_node->strt_virtual_address=new_node->prev->end_virtual_address+1;
        new_node->end_virtual_address=new_node->strt_virtual_address+(num_pages * PAGE_SIZE)-1;
        }
        //new_node->end_virtual_address=new_node->strt_virtual_address+(num_pages * PAGE_SIZE)-1;







        mems_sub_node *sub_new_node = (mems_sub_node *)mmap(NULL, sizeof(mems_sub_node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        new_node->sub_head = sub_new_node;



        mems_sub_node *sub_new_node2=(mems_sub_node *)mmap(NULL, sizeof(mems_sub_node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        sub_new_node->prev=new_node;
        sub_new_node->start = new_node->start;
        sub_new_node->size = size;
        sub_new_node->type = 1;
        sub_new_node->next = sub_new_node2;
        sub_new_node->strt_virtual_address=new_node->strt_virtual_address;

        sub_new_node->end_virtual_address=sub_new_node->strt_virtual_address+size-1;



        sub_new_node2->next=NULL;
        sub_new_node2->prev=sub_new_node;
        sub_new_node2->start=(new_node->start)+size;
        sub_new_node2->type=0;
        sub_new_node2->size=(num_pages * PAGE_SIZE-size);
        sub_new_node2->strt_virtual_address=sub_new_node->end_virtual_address+1;
        sub_new_node2->end_virtual_address=PAGE_SIZE*(num_pages)-1;



        ret_address = sub_new_node->start;
        new_node->ret_address = (size_t)ret_address;

        virtual_address=(void*)(uintptr_t)(sub_new_node->strt_virtual_address);
        num_mapped_pages=num_mapped_pages+num_pages;


    }

    //printf("Return address as integer: %ld  ", (long)ret_address);
    return (void*)virtual_address;
}

#define MAX_CHAINS 100



void mems_print_stats() {

    size_t total_unused_memory = 0;
    int num_segments[MAX_CHAINS] = {0}; // initialize array to 0

    // Traverse the main chain and print details about each node
    mems_node *node = head;
    int chain_index = 0;
    while (node != NULL) {
        printf("[%ld-%ld]", node->strt_virtual_address, node->end_virtual_address);

        // Traverse the sub-chain and print details about each segment
        mems_sub_node *segment = node->sub_head;
        while (segment != NULL) {
            if (segment->type == 0) {
                printf("<-> H[%ld-%ld]", segment->strt_virtual_address, segment->end_virtual_address);
                total_unused_memory += segment->size;
                num_segments[chain_index]++;
            } else {
                printf("<->P[%ld-%ld]", segment->strt_virtual_address, segment->end_virtual_address);
                num_segments[chain_index]++;
            }

            segment = segment->next;
        }

        node = node->next;
        printf(" <-> NULL\n");
        chain_index++;
    }


    printf("Total number of mapped pages: %d\n", num_mapped_pages);
    printf("Total unused memory: %zu bytes\n", total_unused_memory);

    // Print the number of segments in each chain
    printf("\nNumber of segments in each chain:\n");
    for (int i = 0; i < chain_index; i++) {
        printf("Chain %d: %d segments\n", i, num_segments[i]);
    }
}


void *mems_get(void *v_ptr) {
    // Traverse the main chain and find the node that contains the v_ptr
    mems_node *node = head;
    while (node != NULL && (size_t)(v_ptr)>= node->strt_virtual_address) {
        node = node->next;
    }
    node = node->prev;

    // Calculate the offset from the start of the node
    size_t offset = (size_t)v_ptr - node->strt_virtual_address;

    // Calculate the physical address by adding the offset to the returned address
    void *physical_address = (void *)(node->ret_address + offset);

    return physical_address;
}



void mems_free(void* ptr) {
    // Traverse the main chain and find the node that contains the virtual address ptr
    mems_node *node = head;
    while (node != NULL && (size_t)(ptr)>= node->strt_virtual_address) {
        node = node->next;
    }
    node = node->prev;

    // Traverse the sub-chain of the found node and find the sub-node that contains the virtual address ptr
    mems_sub_node *sub_node = node->sub_head;
    while (sub_node != NULL && (size_t)(ptr) >= sub_node->strt_virtual_address) {
        sub_node = sub_node->next;
    }
    sub_node = sub_node->prev;

    // Mark the type of the found sub-node as 0 (HOLE)
    sub_node->type = 0;
    sub_node->end_virtual_address=sub_node->strt_virtual_address+sub_node->size-1;

    // Merge adjacent HOLE sub-nodes in both directions
    while (sub_node->prev != NULL && sub_node->prev->type == 0) {
        sub_node->prev->size += sub_node->size;
        sub_node->prev->end_virtual_address = sub_node->end_virtual_address;
        sub_node->prev->next = sub_node->next;
        if (sub_node->next != NULL) {
            sub_node->next->prev = sub_node->prev;
        }
        sub_node = sub_node->prev;
    }

    while (sub_node->next != NULL && sub_node->next->type == 0) {
        sub_node->size += sub_node->next->size;
        sub_node->end_virtual_address = sub_node->next->end_virtual_address;

        sub_node->next = sub_node->next->next;
        if (sub_node->next != NULL) {
            sub_node->next->prev = sub_node;
        }
    }
}



void mems_finish() {
    // Traverse the main chain and unmap each node
    mems_node *node = head;
    while (node != NULL) {
        munmap((void*)(uintptr_t)(node->ret_address), node->size);

        node = node->next;
    }
}



