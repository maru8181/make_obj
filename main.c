#include "main.h"

int main(){
	static FILE *fp_r = NULL;
	static FILE *fp_w = NULL;
	static unsigned int addressData[6];
	static unsigned char key[30];
	static char i = 0;
	static unsigned int codeFlashFirstAddress;
	static unsigned int codeFlashLastAddress;
	static unsigned int userBootFirstAddress;
	static unsigned int userBootLastAddress;
	static unsigned int dataFlashFirstAddress;
	static unsigned int dataFlashLastAddress;

	fp_r = fopen("config.txt", "r");
	while (fscanf(fp_r, "%s = %x", key, &addressData[i]) != EOF) {
		i++;
	}
	fclose(fp_r);

	codeFlashFirstAddress = addressData[0];
	codeFlashLastAddress = addressData[1];
	userBootFirstAddress = addressData[2];
	userBootLastAddress = addressData[3];
	dataFlashFirstAddress = addressData[4];
	dataFlashLastAddress = addressData[5];

	fp_w = fopen("TEST.S", "w");
	write_data(fp_w, codeFlashFirstAddress, codeFlashLastAddress);
	write_data(fp_w, userBootFirstAddress, userBootLastAddress);
	write_data(fp_w, dataFlashFirstAddress, dataFlashLastAddress);
	fprintf(fp_w, "S9030000FC\n");
	fclose(fp_w);

	return 0;
}
