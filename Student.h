#ifndef __ETUDIANT__H__
#define __ETUDIANT__H__

	typedef struct
	{
		char firstName[51];
		char lastName[51];
		char telephone[15];
		char class[21];
		double projectNote;
		double examNote;
		double devNote;
		double moyenne;
	} Student;

	typedef enum { DEV_NOTE = 1, PROJECT_NOTE, EXAM_NOTE } NOTE;

	void readStudentInfos(Student *student);

	/*------------------------------------------------------------------*/

	void readName(char *name);
	void readFirstName(char *firstName);
	void readTelephone(char *tel);
	bool existsPhone(char *tel);
	void readClass(char *class);
	double readNote(char *message);
	void semiColon(char *note);

	/*------------------------------------------------------------------*/

	int *longerString(Student **data, int lines);
	void showHeader(int length, int *lengths);
	void showSpecialChar(int length);
	void showAllStudent(Student **data, int lines);
	void showNumberOfPages(int n, int *page);
	void showStudentPerPage(Student **student, int begin, int end, int *lengths, int length);
	
	void sortByAverage(Student **data, int lines);
	void handleModificationNotes(char *tel, int choice);
	void modifyStudentNote(char *tel, double newNote, NOTE note);

	Student *searchStudentByFirstName(Student **students, int lines, char *str);
	Student *searchStudentByLastName(Student **students, int lines, char *str);
	Student *searchStudentByClassName(Student **students, int lines, char *str);
	Student *searchStudentByTelephone(Student **students, int lines, char *str);

	void showStudent(Student *student, Student **students, int lines);

	/*------------------------------------------------------------------*/
	
#endif
