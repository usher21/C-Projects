@author Mar Ndiaye
@date 12-02-2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "FileHandler.h"
#include "Student.h"
#include "InputHandler.h"

void showMenu(int *choice);
void showSearchMenu(int *choice);
void showNoteMenu(int *choice);

int main(void)
{
	char *fileName = "students.save";
	int choice, searchChoice, noteChoice, prevMenu = 0, n;
	Student student;

	if (!exists(fileName))
	{
		printf("Impossible d'évaluer '%s' : Aucun fichier ou dossier crée\n", fileName);
		exit(EXIT_FAILURE);
	} else {
		if (dataExists(fileName))
		{
			n = numberOfLine(fileName);
			Student **students = loadData(fileName);

			/*---------------------------------------*/

			do
			{
				showMenu(&choice);
				
				switch(choice)
				{
					case 1:
						clearScreen();
						do
						{
							readStudentInfos(&student);
							if(saveStudent(student, fileName))
							{
								printf("\n\t\t *** Étudiant enregistré avec succès *** \n");
							} else {
								printf("\n\t\t *** Impossible d'enregistrer l'étudiant *** \n");
							}
							n++;
							errno = 0;
							students = (Student**)realloc(students, sizeof(Student*) * n);
							if (students == NULL)
							{
								fprintf(stderr, "Erreur !!! %s", strerror(errno));
								exit(EXIT_FAILURE);
							}
							students[n - 1] = (Student*)malloc(sizeof(Student));
							if (students[n - 1] == NULL)
							{
								fprintf(stderr, "Erreur !!! %s", strerror(errno));
								exit(EXIT_FAILURE);
							}
							strcpy(students[n - 1]->firstName, student.firstName);
							strcpy(students[n - 1]->lastName, student.lastName);
							strcpy(students[n - 1]->class, student.class);
							strcpy(students[n - 1]->telephone, student.telephone);
							students[n - 1]->devNote = student.devNote;
							students[n - 1]->projectNote = student.projectNote;
							students[n - 1]->examNote = student.examNote;
							students[n - 1]->moyenne = student.moyenne;
						} while (pause());
						break;
					case 2:
						showAllStudent(students, n);
						break;
					case 3:
						sortByAverage(students, n);
						showAllStudent(students, n);
						break;
					case 4:
						char str[30];
						do
						{
							prevMenu = 0;
							showSearchMenu(&searchChoice);
							switch (searchChoice)
							{
								case 1:
									readTelephone(str);
									Student *student1 = searchStudentByTelephone(students, n, str);
									if (student1 == NULL)
									{
										printf("Ce numéro de téléphone ne correspond à aucun étudiant -> \"%s\"\n", str);
									} else {
										showStudent(student1, students, n);
									}
									break;
								case 2:
									readName(str);
									Student *student2 = searchStudentByLastName(students, n, str);
									if (student2 == NULL)
									{
										printf("Ce nom ne correspond à aucun étudiant -> \"%s\"\n", str);
									} else {
										showStudent(student2, students, n);
									}
									break;
								case 3:
									readFirstName(str);
									Student *student3 = searchStudentByFirstName(students, n, str);
									if (student3 == NULL)
									{
										printf("Ce prénom ne correspond à aucun étudiant -> \"%s\"\n", str);
									} else {
										showStudent(student3, students, n);
									}
									break;
								case 4:
									readClass(str);
									Student *student4 = searchStudentByClassName(students, n, str);
									if (student4 == NULL)
									{
										printf("Auncun étudiant n'appartient à cette classe -> \"%s\"\n", str);
									} else {
										showStudent(student4, students, n);
									}
									break;
								case 0:
								 	prevMenu = 1;
									break;
							}
						} while (prevMenu != 1 && pause() && searchChoice != 0);
						break;
					case 5:
						char tel[15];
						do
						{
							clearScreen();
							printf("\nEntrer le numéro téléphone de l'étudiant pour modifier sa moyenne: \n");
							do {
								readTelephone(tel);
								if (!existsPhone(tel))
									printf("\n\t\t *** L'étudiant que vous chercher n'existe pas : Numéro de téléphone inconnu -> \"%s\" ***\n", tel);
							} while (!existsPhone(tel));
							showStudent(searchStudentByTelephone(students, n, tel), students, n);
							do
							{
								showNoteMenu(&noteChoice);
								handleModificationNotes(tel, noteChoice);
								prevMenu = pause();
							} while (prevMenu != 0 && noteChoice != 0);
						} while (prevMenu != 0 && noteChoice != 0);
						break;
				}
			} while (choice != 0);

			/*---------------------------------------*/			
			freeMemory(students, n);
		}
		else
		{
			readStudentInfos(&student);
			if(saveStudent(student, fileName))
			{
				printf("Étudiant enregistré avec succès\n");
			} else {
				printf("Impossible d'enregistrer l'étudiant\n");
			}
		}
	}
	return 0;
}

void showMenu(int *choice) {
	clearScreen();
	int ret;
	do
	{
		printf("\n\t\t\t *** Gestion des étudiants ***\n\n");
		printf("1: Ajouter un étudiant\n");
		printf("2: Afficher tout\n");
		printf("3: Trier et afficher par ordre décroissant de la moyenne\n");
		printf("4: Rechercher selon un critère (Téléphone, nom, prénom ou classe)\n");
		printf("5: Modifier la note d'un étudiant\n");
		printf("0: Quitter\n");
		printf("-----------------------------------------------------------------------\n");
		printf("Votre choix > ");
		ret = scanf("%1d", choice);
		flushBuffer();
		if (ret != 1) {
			*choice = -1;
			clearScreen();
			printf("\n\t!!! Veuillez saisir un nombre !!!\n");
		} else if (*choice < 0 || *choice > 5)
		{
			printf("Erreur !!! entrée invalide\n");
		}
	} while (*choice < 0 || *choice > 5);
}

void showSearchMenu(int *choice) {
	clearScreen();
	int ret;
	do
	{
		printf("\n\t\t *** Rechercher un étudiant selon un critère ***\n\n");
		printf("1: Par son téléphone\n");
		printf("2: Par son nom\n");
		printf("3: Par son prénom\n");
		printf("4: Par sa classe\n");
		printf("0: Retour au menu précédent\n");
		printf("----------------------------\n");
		printf("Votre choix: ");
		ret = scanf("%1d", choice);
		flushBuffer();
		if (ret != 1) {
			*choice = -1;
			clearScreen();
			printf("\n\t!!! Veuillez saisir un nombre !!!\n");
		} else if (*choice < 0 || *choice > 4) {
			clearScreen();
			printf("\n\t!!! Entrée invalide !!! Le choix doit être compris entre 0 et 4\n");
		}
	} while (*choice < 0 || *choice > 4 || ret != 1);
}

void showNoteMenu(int *choice) {
	int ret = 0;
	do
	{
		printf("\n\t\t *** Quelle note voulez-vous modifier *** \n");
		printf("1: Note de devoir\n");
		printf("2: Note de projet\n");
		printf("3: Note d'examen\n");
		printf("0: Retour au menu précédent\n");
		printf("-----------------------\nVotre choix > ");
		ret = scanf("%1d", choice);
		flushBuffer();
		if (ret != 1) {
			*choice = -1;
			clearScreen();
			printf("\n\t!!! Veuillez saisir un nombre !!!\n");
		} else if (*choice < 0 || *choice > 4) {
			clearScreen();
			printf("\n\t!!! Entrée invalide !!! Le choix doit être compris entre 0 et 3\n");
		}
	} while (*choice < 0 || *choice > 3);
}
