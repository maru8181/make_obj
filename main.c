#include "main.h"

int main(){
	static FILE *fp_r = NULL;
	static FILE *fp_w = NULL;
	static char i;
	static unsigned int address_data[6];
	static unsigned char key[30];

	fp_r = fopen("config.txt", "r");
	i = 0;
	while (fscanf(fp_r, "%s = %x", key, &address_data[i]) != EOF) {
		i++;
	}
	fclose(fp_r);

	fp_w = fopen("TEST.S", "w");
	fclose(fp_w);

	return 0;
}
