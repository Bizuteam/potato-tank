#include "bullet.hpp"

void list_add(ListBullet *head, BulletStruct b, int i) {
	ListBullet *current = head;
	while(current->next != NULL) {
		current = current->next;
	}

	// current->next = malloc(sizeof(ListBullet));
	current->next->bullet = b;
	current->next->id = i;
	current->next->next = NULL;
}

int list_remove_head(ListBullet **head) {
	int retval = -1;
	ListBullet *nextNode = NULL;

	if(*head == NULL) {
		return -1;
	}

	nextNode = (*head)->next;
	retval = (*head)->id;
	free(*head);
	*head = nextNode;

	return retval;
}

int list_remove_id(ListBullet **head, int id) {
	int i = 0, retval = -1;

	ListBullet *current = *head;
	ListBullet *tempNode = NULL;

	if(id == 0) {
		return list_remove_head(head);
	}

	for (i = 0; i < id-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    tempNode = current->next;
    retval = tempNode->id;
    current->next = tempNode->next;
    free(tempNode);

    return retval;
}

void array_init(BulletArray *a, size_t initialSize) {
	a->array = (BulletStruct *) malloc(initialSize * sizeof(BulletStruct));
	a->used = 0;
	a->size = initialSize;
}

void array_insert(BulletArray *a, BulletStruct b) {
	if(a->used == a->size) {
		a->size *= 2;
	}
}
