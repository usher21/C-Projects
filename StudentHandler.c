#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>

#include "Student.h"
#include "InputHandler.h"
#include "TelephoneHandler.h"
#include "FileHandler.h"

/*---------------------------------------------------------------------------------------------------------*/

void readStudentInfos(Student *student)
{
	printf("\n\t\t *** Entrer les informations d'un étudiant *** \n");
	readName(student->lastName);
	readFirstName(student->firstName);
	do {
		readTelephone(student->telephone);
		if (existsPhone(student->telephone))
			printf("\n\t\t *** Ce numéro de téléphone existe déjà -> \"%s\"\n", student->telephone);
	} while (existsPhone(student->telephone));
	readClass(student->class);
	student->devNote = readNote("Note de devoir");
	student->projectNote = readNote("Note de projet");
	student->examNote = readNote("Note d'examen");
	student->moyenne = (student->devNote + student->projectNote + student->examNote) / 3;
}

/*---------------------------------------------------------------------------------------------------------*/

void readFirstName(char *name) {
	do {
	    printf("\nPrénom > ");
	    read_input(name, 51, stdin);

	    if (strlen(name) < 3)
	        printf("Attention ! Le prénom doit contenir 3 caractères au minimum\n");
	    else if (strlen(name) >= 50)
	        printf("Attention ! Le prénom ne doit pas dépasser 50 caractères\n");

	} while (strlen(name) < 3 || strlen(name) >= 50);
}

/*---------------------------------------------------------------------------------------------------------*/

void readName(char *firstName) {
	do {
	    printf("\nNom > ");
	    read_input(firstName, 51, stdin);

	    if (strlen(firstName) < 2)
	        printf("Attention ! Le nom doit contenir 2 caractères au minimum\n");
	    else if (strlen(firstName) >= 50)
	        printf("Attention ! Le nom ne doit pas dépasser 50 caractères\n");

	} while (strlen(firstName) < 2 || strlen(firstName) >= 50);
}

/*---------------------------------------------------------------------------------------------------------*/

void readTelephone(char *tel) {
	bool success = true;
    do {
        printf("\nTéléphone > ");
        read_input(tel, 15, stdin);
        deleteSpaces(tel);
		
		if (isValidNum(tel) == false) {
			printf("\n\t!!! Le numéro de téléphone indiqué n'est pas valide !!!\n");
			success = false;
		}
		else {
			success = true;
		}
    } while (success == false);
}

/*---------------------------------------------------------------------------------------------------------*/

void readClass(char *class) {
	do {
	    printf("\nClasse > ");
	    read_input(class, 21, stdin);

	    if (strlen(class) > 20)
	        printf("\nAttention ! Le nom de la classe ne doit pas dépasser 20 caractères\n");
	} while (strlen(class) > 20);
}

/*---------------------------------------------------------------------------------------------------------*/

double readNote(char *message) {
	char note[6];
	double noteDouble;	
	do
	{
		printf("\n%s > ", message);
		read_input(note, 6, stdin);
		semiColon(note);
		if (strtod(note, NULL) < 0 || strtod(note, NULL) > 20)
		{
			printf("\n\t === La note doit être compris entre 0 et 20 ===\n");
		}
	} while (strtod(note, NULL) < 0 || strtod(note, NULL) > 20);

	noteDouble = strtod(note, NULL);
	return noteDouble;
}

/*---------------------------------------------------------------------------------------------------------*/

void semiColon(char *note) {
	for (int i = 0; i < 6; i++)
	{
		if (note[i] == ';')
		{
			note[i] = '.';
		}
	}
}

/*---------------------------------------------------------------------------------------------------------*/

void showStudentPerPage(Student **student, int begin, int end, int *lengths, int length)
{
	for (int i = begin; i < end; i++)
	{
		printf("|%3s%-*s%3s|", " ", lengths[0], student[i]->firstName, " ");
		printf("%3s%-*s%3s|", " ", lengths[1], student[i]->lastName, " ");
		printf("%3s%-*s%3s|", " ", (int)strlen(student[i]->telephone), student[i]->telephone, " ");
		printf("%1s%-*s%1s|", " ", lengths[2], student[i]->class, " ");
		student[i]->projectNote < 10 ? printf("%3s%-5.2lf%3s|", " ", student[i]->projectNote, " ") : printf("%3s%-4.2lf%3s|", " ", student[i]->projectNote, " ");
		student[i]->examNote < 10 ? printf("%3s%-5.2lf%3s|", " ", student[i]->examNote, " ") : printf("%3s%-4.2lf%3s|", " ", student[i]->examNote, " ");
		student[i]->devNote < 10 ? printf("%3s%-5.2lf%3s|", " ", student[i]->devNote, " ") : printf("%3s%-4.2lf%3s|", " ", student[i]->devNote, " ");
		student[i]->moyenne < 10 ? printf("%3s%-5.2lf%3s|", " ", student[i]->moyenne, " ") : printf("%3s%-4.2lf%3s|", " ", student[i]->moyenne, " ");
		printf("\n");
	} 
}

/*---------------------------------------------------------------------------------------------------------*/

void showAllStudent(Student **data, int lines)
{
	int *lengths = longerString(data, lines);
	int length = lengths[0] + lengths[1] + lengths[2] + 9 + 27 + 44;

	int numberOfPages = ceil((float)lines / (float)10), rows = 10;
	int begin, end, page = 1;
	if (lines > 10)
	{
		while (page != 0)
		{
			printf("\n\n\t\t\t ================================== Page %d ==================================\n\n", page);
			if (page == numberOfPages && lines % 10 != 0)
			{
				begin = (page - 1) * rows;
				end = begin + (lines % 10);
			} else {
				begin = (page - 1) * rows;
				end = page * rows;
			}
			showHeader(length, lengths);
			showSpecialChar(length);
			showStudentPerPage(data, begin, end, lengths, length);
			showSpecialChar(length);
			showNumberOfPages(numberOfPages, &page);
		}
	} else {
		showSpecialChar(length);
		showStudentPerPage(data, 0, lines, lengths, length);
		showSpecialChar(length);
	}
}

/*---------------------------------------------------------------------------------------------------------*/

void showNumberOfPages(int n, int *page) {
	int ret;
	printf("\n\t[0] : Aller au menu précédent\t");
	do
	{
		for (int i = 0; i < n; i++)
			printf("\t[%d]", i+1);

		ret = scanf("%d", page);
		flushBuffer();
		
		if (ret != 1) {
			*page = -1;
			printf("\n\t\tEntrée invalide !!! veuillez saisir un nombre\n\n");
		}
	} while (*page < 0 || *page > n);
}

/*---------------------------------------------------------------------------------------------------------*/

void showSpecialChar(int length) {
	printf(" ");
	for (int i = 0; i < length; ++i)
    {
        printf("%s", "-");
    }
    printf("\n");
}

/*---------------------------------------------------------------------------------------------------------*/

void showHeader(int length, int *lengths) {
	showSpecialChar(length);
	printf("|%3s%-*s%3s|", " ", lengths[0], "Prenom", " ");
	printf("%3s%-*s%3s|", " ", lengths[1], "Nom", " ");
	printf("%3s%-*s%3s|", " ", 9, "Telephone", " ");
	printf("%1s%-*s%1s|", " ", lengths[2], "Classe", " ");
	printf("%2s%-7s%2s|", " ", "Projet", " ");
	printf("%2s%-7s%2s|", " ", "Examen", " ");
	printf("%2s%-7s%2s|", " ", "Devoir", " ");
	printf("%2s%-7s%2s|", " ", "Moyenne", " ");
	printf("\n");
}

/*---------------------------------------------------------------------------------------------------------*/

int *longerString(Student **data, int lines) {
	int l1 = 0, l2 = 0, l3 = 0;
	static int lengths[3];

	for (int i = 0; i < lines; i++)
	{
		if (strlen(data[i]->firstName) > l1)
			l1 = strlen(data[i]->firstName);

		if (strlen(data[i]->lastName) > l2)
			l2 = strlen(data[i]->lastName);
		
		if (strlen(data[i]->class) > l3)
			l3 = strlen(data[i]->class);
	}
	lengths[0] = l1;
	lengths[1] = l2;
	lengths[2] = l3;
	return lengths;
}

/*---------------------------------------------------------------------------------------------------------*/

void sortByAverage(Student **students, int lines) {
	Student *tempStudent;
	for (int i = 0; i < lines - 1; ++i)
	{
		for (int j = i + 1; j < lines; ++j)
		{  
			if (students[i]->moyenne < students[j]->moyenne)
			{
				tempStudent = students[i];
				students[i] = students[j];
				students[j] = tempStudent;
			}
		}
	}
}

/*---------------------------------------------------------------------------------------------------------*/

void showStudent(Student *student, Student **students, int lines) {
	int *lengths = longerString(students, lines);
	int length = lengths[0] + lengths[1] + lengths[2] + 9 + 27 + 44;
	
	showHeader(length, lengths);
	showSpecialChar(length);
	printf("|%3s%-*s%3s|", " ", lengths[0], student->firstName, " ");
	printf("%3s%-*s%3s|", " ", lengths[1], student->lastName, " ");
	printf("%3s%-*s%3s|", " ", (int)strlen(student->telephone), student->telephone, " ");
	printf("%1s%-*s%1s|", " ", lengths[2], student->class, " ");
	printf("%3s%-4.2lf%3s|", " ", student->projectNote, " ");
	printf("%3s%-4.2lf%3s|", " ", student->examNote, " ");
	printf("%3s%-4.2lf%3s|", " ", student->devNote, " ");
	printf("%3s%-4.2lf%3s|", " ", student->moyenne, " ");
	printf("\n");
	showSpecialChar(length);
}

/*---------------------------------------------------------------------------------------------------------*/

Student *searchStudentByFirstName(Student **students, int lines, char *firstName)
{
	Student *student = NULL;
	for (int i = 0; i < lines; i++)
	{
		if (strcmp(students[i]->firstName, firstName) == 0)
		{
			student = students[i];
		}
	}
	return student;
}

/*---------------------------------------------------------------------------------------------------------*/

Student *searchStudentByLastName(Student **students, int lines, char *lastName) {
	Student *student = NULL;
	for (int i = 0; i < lines; i++)
	{
		if (strcmp(students[i]->lastName, lastName) == 0)
		{
			student = students[i];
		}
	}
	return student;
}

/*---------------------------------------------------------------------------------------------------------*/

Student *searchStudentByClassName(Student **students, int lines, char *className) {
	Student *student = NULL;
	for (int i = 0; i < lines; i++)
	{
		if (strcmp(students[i]->class, className) == 0)
		{
			student = students[i];
		}
	}
	return student;
}

/*---------------------------------------------------------------------------------------------------------*/

Student *searchStudentByTelephone(Student **students, int lines, char *tel) {
	Student *student = NULL;
	for (int i = 0; i < lines; i++)
	{
		if (strcmp(students[i]->telephone, tel) == 0)
		{
			student = students[i];
		}
	}
	return student;
}

/*---------------------------------------------------------------------------------------------------------*/

bool existsPhone(char *tel) {
	Student student;
	FILE *file = fopen("students.save", "r");
	errno = 0;
	if (file == NULL)
	{
		fprintf(stderr, "Erreur !! %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	do
	{
		fscanf(file, "%[a-zA-ZéàçÀÇÉ0-9. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%lf|%lf|%lf|%lf\n", student.firstName, student.lastName, student.telephone ,student.class, &student.projectNote, &student.examNote, &student.devNote, &student.moyenne);
		if (strcmp(tel, student.telephone) == 0)
		{
			return true;
		}
	} while (!feof(file));
	fclose(file);

	return false;
}

/*---------------------------------------------------------------------------------------------------------*/

void modifyStudentNote(char *tel, double newNote, NOTE note) {
	FILE *file = fopen("students.save", "r");
	if (!file)
	{
		fprintf(stderr, "Erreur !! %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	FILE *file1 = fopen("stduents.txt", "w");
	Student student;
	double avg;
	
	do
	{
		fscanf(file, "%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%[a-zA-Z0-9éàçÀÇÉ. ]|%lf|%lf|%lf|%lf\n", student.firstName, student.lastName, student.telephone ,student.class, &student.projectNote, &student.examNote, &student.devNote, &student.moyenne);
		if (strcmp(tel, student.telephone) == 0 && note == DEV_NOTE)
		{
			avg = (newNote + student.examNote + student.projectNote) / 3;
			fprintf(file1, "%s|%s|%s|%s|%.2lf|%.2lf|%.2lf|%.2lf\n", student.firstName, student.lastName, student.telephone ,student.class, student.projectNote, student.examNote, newNote, avg);
		} else if (strcmp(tel, student.telephone) == 0 && note == PROJECT_NOTE)
		{
			avg = (newNote + student.examNote + student.devNote) / 3;
			fprintf(file1, "%s|%s|%s|%s|%.2lf|%.2lf|%.2lf|%.2lf\n", student.firstName, student.lastName, student.telephone ,student.class, newNote, student.examNote, student.devNote, avg);
		} else if (strcmp(tel, student.telephone) == 0 && note == EXAM_NOTE)
		{
			avg = (newNote + student.devNote + student.projectNote) / 3;
			fprintf(file1, "%s|%s|%s|%s|%.2lf|%.2lf|%.2lf|%.2lf\n", student.firstName, student.lastName, student.telephone ,student.class, student.projectNote, newNote, student.devNote, avg);
		} else {
			fprintf(file1, "%s|%s|%s|%s|%.2lf|%.2lf|%.2lf|%.2lf\n", student.firstName, student.lastName, student.telephone ,student.class, student.projectNote, student.examNote, student.devNote, student.moyenne);
		}
	} while (!feof(file));
	fclose(file);
	fclose(file1);

	remove("students.save");
	rename("stduents.txt", "students.save");
}

/*---------------------------------------------------------------------------------------------------------*/

void handleModificationNotes(char *tel, int choice)
{
	double note;
	switch (choice)
	{
		case 1:
			note = readNote("Entrer la nouvelle note de devoir");
			modifyStudentNote(tel, note, DEV_NOTE);
			break;

		case 2:
			note = readNote("Entrer la nouvelle note de projet");
			modifyStudentNote(tel, note, PROJECT_NOTE);
			break;

		case 3:
			note = readNote("Entrer la nouvelle note d'examen");
			modifyStudentNote(tel, note, EXAM_NOTE);
			break;
	}
}