/* from https://en.wikipedia.org/wiki/Gray_code
	
  It converts a number to/from gray code to normal number.
  It takes..
	1. (-gb) gray code in binary form
	2. (-gd) gray code in decimal form
	3. (-nb) normal number in binary form
	4. (-nd) normal number in decimal form

  ToDo:
  - err checking in binStrToInt
  - boundary check in intToBinStr, maybe.

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	INT_BIT_COUNT	64
#define	INPUT_GRAY	1<<3
#define	INPUT_NORM	1<<2
#define	INPUT_DEC	1<<1
#define	INPUT_BIN	1<<0

unsigned int binStrToInt(const char *binStr){
	unsigned int ret, i;
	char n;
	for(i=0, ret=0; (n=binStr[i])!='\0'; i++){
		ret = ret << 1;
		if(n=='1')
			ret = ret | 1;
	}
	return ret;
}

void intToBinStr(char* ret, unsigned int n){
	int i,j,m;
	char buf[INT_BIT_COUNT];
	for(i=0; n>0; i++){
		if ((n&1)==1) buf[i]='1';
		else buf[i]='0';
		n = n>>1;
	}
	for(n=0,i--;i>-1;i--,n++)
		ret[n]=buf[i];
	ret[n]='\0';
}

/* THESE TWO FUNCTIONS ARE DIRECTLY FROM WIKIPEDIA */
unsigned int binToGray(unsigned int num){
	return (num>>1)^num;
}

unsigned int grayToBinary(unsigned int num){
	unsigned int mask;
	for (mask=num>>1; mask!=0; mask=mask>>1)
		num=num^mask;
	return num;
}
/*                                               */

void usage(char *n){
	printf("usage: \t%s [-ngdb] [number]\n",n);
	printf("\toptions ng and db are mutually exclusive.\n");
	exit(1);
}

int main(int argc, char *argv[]){
	unsigned int dec_in,dec_out;
	char bstr_in[INT_BIT_COUNT],bstr_out[INT_BIT_COUNT];
	char m,option=0;
	while((m=getopt(argc,argv,"ngdb"))>1)
		switch(m){
		case 'n':
			if(option & INPUT_GRAY)
				usage(argv[0]);
			option |= INPUT_NORM;
			break;
		case 'g':
			if(option & INPUT_NORM)
				usage(argv[0]);
			option |= INPUT_GRAY;
			break;
		case 'd':
			if(option & INPUT_BIN)
				usage(argv[0]);
			option |= INPUT_DEC;
			break;
		case 'b':
			if(option & INPUT_DEC)
				usage(argv[0]);
			option |= INPUT_BIN;
			break;
		default:
			usage(argv[0]);
		}

	if(option&INPUT_DEC){
		dec_in = (unsigned int)atoi(argv[optind]);
	} else if(option&INPUT_BIN){
		dec_in = binStrToInt(argv[optind]);
	}
	intToBinStr(bstr_in,dec_in);

	printf("Norm_dec, Norm_bin, Gray_dec, Gray_bin\n");
	if(option&INPUT_GRAY){
		dec_out = grayToBinary(dec_in);
		intToBinStr(bstr_out,dec_out);
		printf("%d, %s, %d, %s\n",
			dec_out,bstr_out,dec_in,bstr_in);
	}else if(option&INPUT_NORM){
		dec_out = binToGray(dec_in);
		intToBinStr(bstr_out,dec_out);
		printf("%d, %s, %d, %s\n",
			dec_in,bstr_in,dec_out,bstr_out);
	}
	return 0;
}
