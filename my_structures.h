/*
 * my_structures.h
 *
 *  Created on: Mar 2, 2018
 *      Author: zach
 */

#ifndef MY_STRUCTURES_H_
#define MY_STRUCTURES_H_

struct student{
	int Student_Number;
	char last_Name[50];
	char first_Name[50];
	double GPA;
};

struct node{
	struct student* st;
	struct node* next;
};

struct sllist{
	struct node* first;
	struct node* last;
};

typedef struct student student;
typedef struct node node;
typedef struct sllist sllist;

void psd(struct student *);
struct student mks(int, char[], char[], float);
struct student * mksP(int, char[], char[], float);
sllist * mklist();
void destroy(sllist);
int insert(struct sllist*, struct student *);
int append(struct sllist*, struct student *);
struct student * first(struct sllist);
struct student * last(struct sllist);
void printAll(struct sllist * );
void findByID(struct sllist *, int);
void findHonors(struct sllist *);
//FILE * openFile(char[]);
//char * readFileLine(FILE *);
//FILE * openBFile (char[]);
//void closeFile (FILE *);
//void writeFileLine(FILE *, char[]);
//char * readFileB(FILE *);

#endif /* MY_STRUCTURES_H_ */
