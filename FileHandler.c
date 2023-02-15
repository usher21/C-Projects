#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ------------------------------------------------------------------

#include "FileHandler.h"
#include "InputHandler.h"

// ------------------------------------------------------------------

bool exists(char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (!file)
	{
		return false;
	}

	fclose(file);
	return true;
}

// ------------------------------------------------------------------

bool dataExists(char *fileName) {
	FILE *file = fopen(fileName, "r");
	char data[255]; 
	if(read_input(data, sizeof(data), file)) {
		return true;
	}
	return false;
}

// ------------------------------------------------------------------

int numberOfLine(char *fileName) {
	FILE *file = fopen(fileName, "r");
	char data[255];
	int n = 0;
	while(read_input(data, sizeof(data), file)) {
		n++;
	}
	fclose(file);
	return n;
}

// ------------------------------------------------------------------

Student **loadData(char *fileName) {
	FILE *file = fopen(fileName, "r");
	errno = 0;
	if (file == NULL)
	{
		fprintf(stderr, "Erreur !! %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	int n = numberOfLine(fileName), i = 0;
	Student **data;
	data = (Student**)malloc(sizeof(Student*) * n);
	if (data == NULL)
	{
		printf("Mémoire insuffisant\n");
		exit(EXIT_FAILURE);
	}

	do
	{
		data[i] = (Student*)malloc(sizeof(Student));
		if (data[i] == NULL)
		{
			printf("Mémoire insuffisant\n");
			exit(EXIT_FAILURE);
		}
		fscanf(file, "%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%lf|%lf|%lf|%lf\n", data[i]->firstName, data[i]->lastName, data[i]->telephone ,data[i]->class, &data[i]->projectNote, &data[i]->examNote, &data[i]->devNote, &data[i]->moyenne);
		i++;
	} while (!feof(file) && i < n);

	fclose(file);

	return data;
}

// ------------------------------------------------------------------

void addStudentToArray(Student **students, Student student, int lines) {
	strcpy(students[lines - 1]->firstName, student.firstName);
	strcpy(students[lines - 1]->lastName, student.lastName);
	strcpy(students[lines - 1]->class, student.class);
	strcpy(students[lines - 1]->telephone, student.telephone);
	students[lines - 1]->devNote = student.devNote;
	students[lines - 1]->projectNote = student.projectNote;
	students[lines - 1]->examNote = student.examNote;
	students[lines - 1]->moyenne = student.moyenne;
}

// ------------------------------------------------------------------

void reallocateMemory(Student **students, int lines)
{
	printf("Dans le reallocate: %d\n", lines);
	errno = 0;
	students = (Student**)realloc(students, sizeof(Student*) * lines);
	if (students == NULL)
	{
		fprintf(stderr, "Erreur !!! %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Dans le reallocate: %d\n", lines);
	students[lines - 1] = (Student*)malloc(sizeof(Student));
	if (students[lines - 1] == NULL)
	{
		fprintf(stderr, "Erreur !!! %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Dans le reallocate: %d\n", lines);
}

// ------------------------------------------------------------------

bool saveStudent(Student student, char *fileName) {
	FILE *file = fopen(fileName, "a");
	if (!file)
	{
		printf("Impossible d'évaluer %s : fichier introuvable\n", fileName);
		exit(EXIT_FAILURE);
	}

	int success = fprintf (file, "%s|%s|%s|%s|%.2f|%.2f|%.2f|%.2f\n", student.firstName, student.lastName, student.telephone ,student.class, student.projectNote, student.examNote, student.devNote, student.moyenne);

	fclose(file);

	return success >= 1;
}

// ------------------------------------------------------------------

void freeMemory(Student **students, int lines) {
	for (int i = 0; i < lines; ++i)
	{
		free(students[i]);
	}
	free(students);
}

// ------------------------------------------------------------------