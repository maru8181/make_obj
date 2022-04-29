#include "main.h"

void check_sum_calc(unsigned char *data, unsigned char count, unsigned char *sum){
	unsigned int temp;

	for(char i=0; i<count; i++){
		temp += data[i];
	}
	*sum = temp ^ 0xFF;
}

void write_data(FILE *fp, unsigned int first_address, unsigned int last_address){
	unsigned char randomByteData;
	unsigned char randomData[0x10];
	unsigned char dumpData[0x20];
	unsigned char dumpCount;

	for (unsigned int i = first_address; i < last_address; i = i + 0x10) {

		for(char j=0; j<0x10; j++) {
			randomByteData = rand() % 0x100;
			randomData[j] = randomByteData;
		}

		dumpCount = 0x10;
		fputc('S', fp);
		if((i < 0x10000)) {
			fputc('1', fp);
			dumpData[0] = 0x13;
			dumpData[1] = (i >> 8);
			dumpData[2] = i;
			dumpCount += 3;
			for(char j=0; j<0x10; j++){
				dumpData[j+3] = randomData[j];
			}
		}else if((i >= 0x10000) && (i < 0x1000000)) {
			fputc('2', fp);
			dumpData[0] = 0x14;
			dumpData[1] = (i >> 16);
			dumpData[2] = (i >> 8);
			dumpData[3] = i;
			dumpCount += 4;
			for(char j=0; j<0x10; j++){
				dumpData[j+4] = randomData[j];
			}
		}else if((i >= 0x1000000)) {
			fputc('3', fp);
			dumpData[0] = 0x15;
			dumpData[1] = (i >> 24);
			dumpData[2] = (i >> 16);
			dumpData[3] = (i >> 8);
			dumpData[4] = i;
			dumpCount += 5;
			for(char j=0; j<0x10; j++){
				dumpData[j+5] = randomData[j];
			}
		}
		check_sum_calc(dumpData, dumpCount, &dumpData[dumpCount]);
		dumpCount += 1;

		for (char j=0; j<dumpCount; j++){
			fprintf(fp, "%02X", dumpData[j]);
		}

		fputc('\n', fp);
	}
}
