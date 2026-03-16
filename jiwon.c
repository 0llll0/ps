#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class{
	int code;
	char name[30];
	int unit;
	int grading;
};

char kname[2][10] = {"A+~F", "P/F"};

int loadData(struct st_class* c[]);
void printAllClasses(struct st_class* c[], int csize);
void findClasses(char* name, struct st_class* c[], int csize);
void saveAllClasses(struct st_class* c[], int csize);

int addNewClass(struct st_class* c[], int csize);
void editClass(struct st_class* c[], int csize);

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize);
void printMyClasses(int my[], int msize, struct st_class* c[], int csize);
void saveMyClass(int my[], int msize, struct st_class* c[], int csize);

int main(void) {
	int no;
	struct st_class* classes[50];

	int myclass[10];
	int mycount = 0;

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while(1){
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if(no == 1){
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if(no == 2){
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if(no == 3){
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if(no == 4){
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if(no == 5){
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if(no == 6){
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if(no == 7){
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else break;
	}
	return 0;
}

int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

int addNewClass(struct st_class* c[], int csize){
	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));
	int duplicated;

	while(1){
		duplicated = 0;
		printf(">> code number > ");
		scanf("%d", &(p->code));

		for(int i = 0; i < csize; i++){
			if(c[i]->code == p->code){
				duplicated = 1;
				break;
			}
		}

		if(duplicated == 0) break;
		printf("> Duplicated code. Try again.\n");
	}

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize + 1;
}

void editClass(struct st_class* c[], int csize){
	struct st_class* p = NULL;
	int code;

	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	for(int i = 0; i < csize; i++){
		if(c[i]->code == code){
			p = c[i];
			break;
		}
	}

	if(p == NULL){
		printf("> No such class.\n");
		return;
	}

	printf("> Current: [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");
}

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
	int code;
	int exists;
	int duplicated;

	if(msize >= 10){
		printf("> You cannot apply more classes.\n");
		return msize;
	}

	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	exists = 0;
	for(int i = 0; i < csize; i++){
		if(c[i]->code == code){
			exists = 1;
			break;
		}
	}

	if(exists == 0){
		printf("> No such class.\n");
		return msize;
	}

	duplicated = 0;
	for(int i = 0; i < msize; i++){
		if(my[i] == code){
			duplicated = 1;
			break;
		}
	}

	if(duplicated == 1){
		printf("> Already applied.\n");
		return msize;
	}

	my[msize] = code;
	msize++;

	return msize;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
	int total = 0;
	int count = 0;

	for(int i = 0; i < msize; i++){
		for(int j = 0; j < csize; j++){
			if(my[i] == c[j]->code){
				printf("%d. [%d] %s [credit %d - %s]\n", count + 1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
				total += c[j]->unit;
				count++;
				break;
			}
		}
	}

	printf("Total credits : %d\n", total);
}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){
	FILE* file;
	int total = 0;
	int credit1 = 0;
	int credit2 = 0;
	int count = 0;

	file = fopen("my_classes.txt", "w");
	if(file == NULL) return;

	for(int i = 0; i < msize; i++){
		for(int j = 0; j < csize; j++){
			if(my[i] == c[j]->code){
				fprintf(file, "%d. [%d] %s [credit %d - %s]\n", count + 1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
				total += c[j]->unit;

				if(c[j]->grading == 1) credit1 += c[j]->unit;
				else if(c[j]->grading == 2) credit2 += c[j]->unit;

				count++;
				break;
			}
		}
	}

	fprintf(file, "Total classes : %d\n", msize);
	fprintf(file, "Total credits : %d\n", total);
	fprintf(file, "A+~F credits : %d\n", credit1);
	fprintf(file, "P/F credits : %d\n", credit2);

	fclose(file);
}