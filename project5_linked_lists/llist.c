#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void llist_insert_head(struct node **head, struct node *n) {

	struct node *temp = malloc(sizeof(struct node));
	temp->value = (*head)->value;
	temp->next = (*head)->next;
	(*head)->value = n->value;
	(*head)->next = n;
	n->value = temp->value;
	n->next = temp->next;

	free(temp);

}

// struct node *llist_delete_head(struct node **head) {

// }

// void llist_insert_tail(struct node **head, struct node *n) {

// }

void llist_print(struct node *head) {
	struct node *current = head;
	printf("%d", head->value);
	while (current->next != NULL) {
		current = current->next;
		printf(" -> %d", current->value);
	}
	printf("\n");
}

// void llist_free(struct node **head) {

// }


struct node *node_alloc(int value) {
	struct node *new_node = malloc(sizeof(struct node));

	if (new_node != NULL) {
		new_node->value = value;
		new_node->next = NULL;
	}

	// struct node new_node = {value, NULL};
	// return &(struct node){value, NULL};
	return new_node;
}

void node_free(struct node *n) {
	free(n);
}


int is_ih(char *arg) {
	return strcmp(arg, "ih") == 0 ? 1 : 0; // return true (1) if string matches
}

int is_it(char *arg) {
	return strcmp(arg, "it") == 0 ? 1 : 0; // return true (1) if string matches
}

int is_dh(char *arg) {
	return strcmp(arg, "dh") == 0 ? 1 : 0; // return true (1) if string matches
}

int is_f(char *arg) {
	return strcmp(arg, "f") == 0 ? 1 : 0; // return true (1) if string matches
}

int is_p(char *arg) {
	return strcmp(arg, "p") == 0 ? 1 : 0; // return true (1) if string matches
}


int main(int argc, char *argv[]) {
	const char *USAGE_STATEMENT = "Usage: [ih integer_value] [it integer_value] [dh] [f] [p]";

	if (argc < 2) {
		printf("%s\n", USAGE_STATEMENT);
		exit(1);
	}

	struct node *head = node_alloc(5050);
	struct node *next_node = node_alloc(1234);
	head->next = next_node;


	for (int i = 1; i < argc; i++) {

		if (is_ih(argv[i])) {
			char *new_head_string_value = argv[i + 1];
			int new_head_value = atoi(new_head_string_value);

			struct node *n = node_alloc(new_head_value);
			llist_insert_head(&head, n);
			i++; // ih it takes two arguments, so increment to skip value arg on next loop
		} else if (is_it(argv[i])) {
			// llist_insert_tail(struct node **head, struct node *n);
			i++; // it takes two arguments, so increment to skip arg on next loop
		} else if (is_dh(argv[i])) {
			// llist_delete_head();
		} else if (is_f(argv[i])) {
			// llist_free();
		} else if (is_p(argv[i])) {
			llist_print(head);
		} else {
			printf("%s\n", USAGE_STATEMENT);
			exit(1);
		}

	}





	return 0;
}
