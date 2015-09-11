#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
/* prompt user the usage if there is too many arguments passed */
void usage(char *prog) 
{
    fprintf(stderr, "print Usage: rangesort -i inputfile -o outputfile -l lowvalue -h highvalue", prog);
    exit(1);
}

void invalidRange (){
	fprintf(stderr, "Invalid range value");
    exit(1);
}

int main (int argc, char* argv[]){
	int c;
	int highValue;
	int lowValue;
	char *outFile;
	char *inFile;
	
    while ((c = getopt(argc, argv, "i:o:l:h:")) != -1) {
	switch (c) {
	case 'i':
	    inFile     = strdup(optarg);
	    break;
	case 'o':
	    outFile = strdup(optarg);
	    break;
	case 'l':
	    highValue = atoi(optarg);
	    break;
	case 'h':
	    lowValue   = atoi(optarg);
	    break;	    
	default:
	    usage(argv[0]);
	}
}
/* Check if the range is valid */
	if (highValue <= lowValue){
		invalidRange();
	}
	
	printf("The high val is %d\n", highValue);
	printf("The low val is %d\n", lowValue);
	printf("The input file is %s\n", inFile);
	printf("The output file is %S\n", outFile);
	

/* open input file */
    int fd = open(inFile, O_RDONLY);
    if (fd < 0) {
	perror("open");
	exit(1);
    }
	
	return 0;
}
