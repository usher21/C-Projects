#ifndef __FILE__HANDLER__H__
#define __FILE__HANDLER__H__
	
	#include <stdbool.h>
	#include "Student.h"

	bool exists(char *fileName);
	bool dataExists(char *fileName);
	int numberOfLine(char *fileName);
	Student **loadData(char *fileName);
	bool saveStudent(Student student, char *fileName);
	void reallocateMemory(Student **students, int lines);
	void freeMemory(Student **students, int lines);
	void addStudentToArray(Student **students, Student student, int lines) ;

#endif