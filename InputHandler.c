#include <stdio.h>
#include <string.h>

#include "InputHandler.h"

/*------------------------------------------------------------------------------------------*/

void flushBuffer() {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

/*------------------------------------------------------------------------------------------*/

int pause(void) {
	printf("\nVoulez-vous continuer ? \t");
	int c;
	do
	{
		printf("1: Continuer \t 0: Arrêter > ");
		scanf("%d", &c);
		flushBuffer();
		if (c != 1 && c != 0)
		{
			printf("!!! choix invalide !!!\n");
		}
	} while (c != 1 && c != 0);

	return c;
}

/*------------------------------------------------------------------------------------------*/

char *read_input(char *str, size_t size, FILE *file) {
	char *data = fgets(str, size, file);
    if (data)
    {
        size_t len = strlen(str);

        if(str[len - 1] == '\n')
            str[len - 1] = '\0';
        else
            flushBuffer();

        return data;
    }
    
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------*/

void wait(void) {
	printf("\nAppuyer sur la touche [Entrée] pour continuer ... ");
	flushBuffer();
}

/*---------------------------------------------------------------------------------------------------------*/

void clearScreen(void) {
	printf("\033[H\033[2J");
}

/*---------------------------------------------------------------------------------------------------------*/