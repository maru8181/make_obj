#include "main.h"

void write_data(FILE *fp, unsigned int first_address, unsigned int last_address){
	unsigned char randomByteData;
	unsigned char randomData[0x10];

	for (unsigned int i = first_address; i < last_address; i = i + 0x10) {

		for(char i=0; i<0x10; i++) {
			randomByteData = rand() % 0x100;
			randomData[i] = randomByteData;
		}

		for (char j=0; j<0x10; j++){
			fprintf(fp, "%02x", randomData[j]);
		}
		fputc('\n', fp);
	}
}
