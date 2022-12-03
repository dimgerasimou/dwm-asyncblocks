#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "colorscheme.h"

FILE* opencmd(char* cmd) {
	FILE* pointer;
	pointer = popen(cmd, "r");
	if (pointer == NULL){
		fprintf(stderr, "Couldn't execute: %s", cmd);
		exit(EXIT_FAILURE);
	}
	return pointer;
}

int main() {
	char micmuted = 0;
	char volmuted = 0;
	char temp[16];
	char volicon[5];
	unsigned short vol;

	FILE* fp;

	fp = opencmd("/bin/pamixer --get-mute");
	fscanf(fp, "%s", temp);
	if (!strcmp(temp, "true")) {
		volmuted = 1;
		strcpy(volicon, "🔇");
	}
	pclose(fp);
	
	if (!volmuted) {
		fp = opencmd("/bin/pamixer --get-volume");
		fscanf(fp, "%d", &vol);
		pclose(fp);
		
		if (vol == 0)
			strcpy(volicon, "🔇");
		else if (vol > 70)
			strcpy(volicon, "🔊");
		else if (vol < 30)
			strcpy(volicon, "🔈");
		else
			strcpy(volicon, "🔉");
	}


	if (volmuted)
		printf(SFG SBG" %s ^d^\n", volicon);
	else
		printf(SFG SBG" %s "NBG NFG" %d%% ^d^\n", volicon, vol);
	return 0;
}