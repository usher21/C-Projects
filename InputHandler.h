#ifndef __INPUT__HANDLER__H__
#define __INPUT__HANDLER__H__

	char *read_input(char *str, size_t size, FILE *file);
	void flushBuffer(void);
	int pause(void);
	void wait(void);
	void clearScreen(void);
	

#endif