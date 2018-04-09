/*
 * aux.c
 *
 *  Created on: Mar 2, 2018
 *      Author: zach
 */
#include "my_structures.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct student stuType;

void psd(struct student * s) {
	printf("\nStudent: %s %s. ID: %i. GPA: %1.1f.\n", s->first_Name,
			s->last_Name, s->Student_Number, s->GPA);
}

struct sllist* mkList() {
	struct sllist * p = (struct sllist *) malloc(sizeof(struct sllist));
	// PWP: If malloc fails, you must return here.
	p->first = NULL;
	p->last = NULL;
	return p;
}

void destroy(struct sllist list) {
// PWP: using a sslist pointer as an argument is strongly advised... 
// PWP: The "destroyed" (=emptied) list should have first and last set to NULL - and you can't do this as it is.
	node * next_node = list.first->next; // PWP: And what if list is empty? (list.first == NULL)
	node a;
	free(list.first);
	while (next_node->next) { // PWP: I have bad feelings about this...
		// PWP: it seems to me that the last node will not be freed.
		a = *next_node->next; // PWP: This may be expensive, as you are rewriting the node 
		free(next_node);
		*next_node = a;
	}
}

int insert(struct sllist * slist, struct student * stu) {
	/*
	 * For whatever reason this function still creates that "Recursive" pointer
	 */

	// PWP: node zero = { NULL, NULL }; // Should make a = 0x0, 0x0
	// PWP: node newNext; // c
	node * newNext; // PWP: This seems to be better... (see below, look for burried dogs...)
	if (slist->first != 0) { // PWP: OK, but !=NULL will be better (you are using NULL anywhere else)
		// PWP: newNext = *slist->first; // slist -> first b
		newNext = slist->first; // slist -> first b
	} else {
		// PWP: newNext = zero; // 0x0
		newNext = NULL;
	}
	//struct node * p = (struct node *) malloc(sizeof(struct node));
	struct node * p = (struct node *) calloc(1, sizeof(struct node*));
	// PWP: check if the calloc worked, return 0, if it failed.
	if (p == NULL) {
		return 0;
	}
	p->st = stu;
	// PWP: Da liegt der hund begraben! 
	// PWP: p->next = &newNext;  
	// PWP: You were storing in the new node's next pointer an address of a temp variable!!!
	// PWP: (invalid as soon as the call ends!)
	p->next = newNext;
	slist->first = p;
	if (!slist->last) {
		slist->last = p;
	}
	return 1;
}

// PWP: Not looking here; looks like the same problem....
int append(struct sllist * slist, struct student * stu) {
	node zero = { 0 };

	struct node * p = (struct node *) malloc(sizeof(struct node));
	p->st = stu;
	p->next = &zero;
	if (slist->first) {
		node Last_Node;
		Last_Node = *slist->last;
		Last_Node.next = p;
	} else {

		slist->first = p;
	}

	slist->last = p;
	return 1;
}

struct student * first(struct sllist slist) {
	// PWP: And if first is NULL?
	student * imidiot = slist.first->st;
	return imidiot;
}
struct student * last(struct sllist slist) {
	// PWP: And if last is NULL?
	student * imidiot = slist.last->st;
	return imidiot;
}

struct student mks(int Snum, char last[], char first[], float GPA) {
	struct student newStudent = { .Student_Number = Snum, .GPA = GPA };
	strcpy(newStudent.last_Name, last);
	strcpy(newStudent.first_Name, first);

	return newStudent;
}

struct student * mksP(int Snum, char last[], char first[], float GPA1) {
	struct student * p = (struct student *) malloc(sizeof(struct student));

	strcpy(p->last_Name, last);
	strcpy(p->first_Name, first);
	p->GPA = GPA1;
	p->Student_Number = Snum;

	return p;

}

void printAll(struct sllist * slist) {
	struct node * first = slist->first;
	psd(first->st);

	struct node * next = slist->first->next;
	while (next != NULL) {
		psd(next->st);
		next = next->next;
	}
}

void findByID(struct sllist * slist, int id) {

	struct node * first = slist->first;
	int sid = first->st->Student_Number;
	struct node * sprev = NULL;
	struct node * snext = first->next;

	while (sid != id && snext != NULL) {
		sprev = snext;
		sid = snext->st->Student_Number;
		snext = snext->next;
	}
	if (snext == NULL){
		printf("Student with ID %i not found", id);
	}
	if (snext != NULL){
		psd(sprev->st);
	}


}

void findHonors(struct sllist * slist) {

	struct node * first = slist->first;
	float sgpa = first->st->GPA;
	struct node * sprev = NULL;
	struct node * snext = first->next;

	char str[1024*12];
	char buffer[256];
	FILE *fp = fopen("honors.txt", "w");

	while (snext != NULL) {
		sprev = snext;
		if (sprev->st->GPA >= 3.5){
			//psd(sprev->st);
			snprintf(buffer, sizeof(buffer), "\nStudent: %s %s. ID: %i. GPA: %1.1f.\n", sprev->st->first_Name,
					sprev->st->last_Name, sprev->st->Student_Number, sprev->st->GPA);
			strncat(str, buffer, sizeof(buffer));
		}
		sgpa = snext->st->GPA;
		snext = snext->next;
	}
	printf(str);
	if (snext == NULL){
		//printf("Student with ID %i not found", id);
	}
	if (snext != NULL){
	//	psd(sprev->st);
	}
	fputs(str, fp);
	fclose(fp);

}

