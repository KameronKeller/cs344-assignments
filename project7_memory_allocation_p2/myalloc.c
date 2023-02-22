/*
Author: Kameron Keller
Course: CS 344 OS I, Winter 2023
Assignment: Project 7
*/

#include <stdio.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block *head = NULL;  // Head of the list, empty

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

void myfree(void *p) {

}

void print_data(void) {
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int is_available(struct block *node) {
	return node->in_use ? 0 : 1;
}

int is_large_enough(int requested_space, struct block *node) {
	return requested_space <= node->size;
}

int is_splittable(struct block *node, int requested_space) {
	int available_space = node->size;
	int padded_requested_space = PADDED_SIZE(requested_space);
	int padded_struct_block_size = PADDED_SIZE(sizeof(struct block));
	int required_space = padded_requested_space + padded_struct_block_size + 16;
	
	return available_space >= required_space ? 1 : 0;
}

int last_node(struct block *node) {
	return node->next == NULL;
}

void mark_in_use(struct block **node) {
	(*node)->in_use = 1;
}

void *pointer_offset(struct block *node) {
	int padded_block_size = PADDED_SIZE(sizeof(struct block));
	return PTR_OFFSET(node, padded_block_size);
}

void split_space(struct block *node, int size) {
		// new node
		// connect node
}

struct block *get_sufficient_block(int requested_space, struct block *node) {
	if (is_available(node) && is_large_enough(requested_space, node)) {
		if (is_splittable(node, requested_space)) {
			split_space(node, requested_space);
		}
		return node;
	} else if (last_node(node)) {
		return NULL;
	} else {
		return get_sufficient_block(requested_space, node->next);
	}
}

void setup_initial_memory(int num_bytes, struct block **head) {
    *head = mmap(NULL, num_bytes, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    (*head)->next = NULL;
    (*head)->size = num_bytes - PADDED_SIZE(sizeof(struct block));
    (*head)->in_use = 0;
}

void *myalloc(int requested_space) {
	if (head == NULL) {
		setup_initial_memory(1024, &head);
	}

	struct block *available_block = get_sufficient_block(requested_space, head);


	if (available_block == NULL) { // if no available block
		return NULL;
	} else {
		mark_in_use(&available_block);
		return pointer_offset(available_block);
	}
}

void test_methods() { // simple method to test other helper functions. Delete if no longer needed for testing.
	// Create sample nodes
	struct block n3 = { NULL, 1000, 0 };
	struct block n2 = { &n3, 5, 0 };
	struct block n1 = { &n2, 10, 0 };

	struct block *available = get_sufficient_block(20, &n1);

	printf("=== Start method tests ===\n");
	printf("available? %d\n", is_available(&n1));
	printf("found? %d\n", available == NULL);
	printf("found: %d\n", available->size);
	printf("=== End method tests ===\n\n");
}


int main(void) {
	// test_methods(); // Function for testing various helper functions, uncomment to use or delete if unneeded

    void *p;

    p = myalloc(512);
    print_data();

    // myfree(p);
    // print_data();
}


