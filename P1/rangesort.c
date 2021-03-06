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

int compareTo(const void *a, const void *b){
    return ( *(rec_t*)a.key - *(rec_t*)b.key );
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
        fprintf(stderr, "Error: Cannot open file %s", argv[0]);
        exit(1);
    }
    /* obtain the file size*/
    struct stat fileStat;
    fstat(fd, &fileStat);
    int fileSize = fileStat.st_size;
    /* calculate number of elements in the array*/
    int numOfElements = fileSize/sizeof(rec_t);
    struct rec_t recs[numOfElements];
    rec_t recPointer;
    int i = 0;
    
    while ( read(fd, &recPointer, sizeof(rec_t))) != 0 ){
        if (recPointer.key >= lowValue && recPointer.key <= highValue) {
            recs[i] = recPointer;
            i++;
        }
    }
    qsort(values, numOfElements, sizeof(rec_t), compareTo);
    
	return 0;
}
