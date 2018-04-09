/*
 ============================================================================
 Name        : Files.c
 Author      : piotr
 Version     :
 Copyright   : Copyleft @2018
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_structures.h"

int main(void) {

	const int N=46;
	FILE * text;
	FILE * numbers;

	sllist * test = mkList();

	if ((text=fopen("/home/zach/eclipse-workspace/Student_struct_PWP/src/classlist.txt", "r")) == NULL) {
		puts("Can't read classlist file.");
		exit(1);
	}
//  When writing (creating) gpa.dat file (via stream numbers):
//	numbers=fopen("/home/piotr/gpa.dat", "wb");
	//When reading the gpa.dat file:
	numbers=fopen("/home/zach/eclipse-workspace/Student_struct_PWP/src/gpa.dat", "rb");
	if (numbers == NULL) {
		puts("Problems with gpa.dat file.");
		exit(2);
	}



	// My binary file consists of these:
	struct gpa {
		int snum;
		double gpa;
	};

	// Allocating an array (scores) with N gpa-size elements.
	struct gpa * scores=(struct gpa *)calloc(N, sizeof(struct gpa));

// When setting up gpa-s in scores and writing the gpa.dat file
//	for(int i=0; i < N; i++) {
//		scores[i].snum=1001+i;
//		scores[i].gpa= 2.2+2*(double)rand()/RAND_MAX;
//	}
//
//	fwrite(scores,sizeof(struct gpa), N, numbers);   // Writting...  (all at once)

	// Reading the gpa.dat file (stream: numbers):
	fread(scores,sizeof(struct gpa), N, numbers);
	// The whole scores array is initialized instantly; so, print it out:
	for(int i=0; i < N; i++) {
		printf("sn=%07d gpa=%lf\n", scores[i].snum, scores[i].gpa);
	}

	// Reading classlist - a text file of lines (stream: text):
	//char line[80];
	// 1.5 loop - note EOF problem
	//fgets(line, 80, text);

	int i = 0;
	char a[80];
	char b[80];
	fscanf(text, "%s %s", a, b);

	insert(test, mksP(scores[i].snum,a,b, scores[i].gpa));
	printf("%s %s", a, b);
	i++;
	//struct student * s;
	while (!feof(text)) {
		// puts(line);
		//printf("%s", line);
		fscanf(text, "%s %s", a, b);

		insert(test, mksP(scores[i].snum,a,b, scores[i].gpa));
		printf("%s %s", a, b);
		i++;
		//fgets(line, 80, text);
	}
	puts("\n\nPrintall\n");
	printAll(test);
	puts("\n\nFindbyId\n");
	findByID(test,1046);
	findByID(test,2041);
	puts("\n\nfindHonors\n");
	findHonors(test);

	puts("\nAnything else?"); /* prints Anything else? */
	return EXIT_SUCCESS;
}
