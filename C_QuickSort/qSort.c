//*****************************************************************************
//  
//  Comment Block
//  2020.08.16 Live Coding testing
//  PlaidCat 2020
//
//  Basic Int quick sort
//
//  everythcing will be stored in heap arrays
// 
//
// Trying VS Code to make this clearer
// 
//  Next time:
//  * Input for Files and basic bash frame work.
//
//
//*****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

//GLOBALS
typedef struct{
    int DEBUG;
    int threads;
    char *file;
} config;

config my_config;

//__ProtoTypes_______
//___Validation and Testing__________
int testSorter();
int isSorted(unsigned int *arr, unsigned long arrSize);
unsigned int *loadBadArr();
int parse_input(int argc, char *argv[]);

//__Ingestion__


//__Information____
void printArray(unsigned int *arr, unsigned int arrSize);

//__Memory Management_____
unsigned int *createRandomArray(unsigned int size);
unsigned int *load_file(char *file, unsigned int *size);
void freeArray(unsigned int *arr);

//__Quick Sort___
//This is recursive
void qSort(unsigned int *arr, unsigned long start, unsigned long end);
unsigned long qPartition(unsigned int *arr, unsigned long start, unsigned long end, unsigned long index);

//___MAIN____
int main(int argc, char *argv[]) {
    int res;
    unsigned int *arr = NULL;
    unsigned int size = 0;
    struct timespec load_start={0,0}, load_end={0,0};
    struct timespec qSort_start={0,0}, qSort_end={0,0}; 

    my_config.file = NULL;
    my_config.DEBUG = 0;
    my_config.threads = 1;

    res = parse_input(argc, argv);
    if (res){
        fprintf(stderr, "Failed to Parse ... Exiting\n");
        exit(1);
    }
    
    if (my_config.DEBUG) {
        res = testSorter();
        if (res == 0)
            return -1;       
    }

    if (my_config.file == NULL) {
        size = 20000;
        arr = createRandomArray(size);
        //arr = loadBadArr();
        printArray(arr, size);
        qSort(arr, 0,  size-1);
        printArray(arr, size);
    }else {
        clock_gettime(CLOCK_MONOTONIC_RAW, &load_start);
        arr = load_file(my_config.file, &size);
        if (arr == NULL){
            fprintf(stderr, "Failed to load array from file: %\n ... Exiting\n", my_config.file);
            return -1;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &load_end);
                
        clock_gettime(CLOCK_MONOTONIC_RAW, &qSort_start);
        qSort(arr, 0, size-1);
        clock_gettime(CLOCK_MONOTONIC_RAW, &qSort_end);

        if(load_end.tv_nsec < load_start.tv_nsec){
            load_end.tv_nsec += 1000000000;
            load_end.tv_sec--;
        }
        if(qSort_end.tv_nsec < qSort_start.tv_nsec){
            qSort_end.tv_nsec += 1000000000;
            qSort_end.tv_sec--;
        }

        printf("Loading File Took: %ld.%09ld\n", 
            (long)(load_end.tv_sec - load_start.tv_sec), (load_end.tv_nsec - load_start.tv_nsec));
        printf("QSort took: %ld.%09ld\n",
            (long)(qSort_end.tv_sec - qSort_start.tv_sec), (qSort_end.tv_nsec - qSort_start.tv_nsec));
    }

    res = isSorted(arr, size);
    if (res)
        printf("Huzza its sorted\n");
    else
        printf("ya goofed in your crappy qSort\n");

    freeArray(arr);

    return res;
}

unsigned int *load_file(char *file, unsigned int *size){
    FILE *fp = NULL;
    unsigned int *arr = NULL;
    char *line = NULL;
    size_t n = 0;
    ssize_t count;
    (*size) = 0;
    unsigned int i;


    fp = fopen(file, "r");
    if (fp == NULL){
        *size = 0;
        return NULL;
    }

    count = getline(&line, &n, fp);
    if(count != 1){
        (*size) = (unsigned int)strtoul(line, NULL, 10);
    }

    arr = (unsigned int *)malloc(sizeof(unsigned int) * (*size));

    i = 0;
    while( ((count = getline(&line, &n, fp)) != -1) &&   (i < *size) ){
        arr[i] = (unsigned int)strtoul(line, NULL, 10);
        i ++;
    }
    
    if(line != NULL)
        free(line);
    
    if(fp != NULL)
        fclose(fp);

    return arr;

}

void printArray(unsigned int *arr, unsigned int arrSize){
    unsigned int i;

    printf("Printing array of size %u\n", arrSize);

    //crappy print
    for (i=0; i < arrSize; ++i){
        printf("%u\n", arr[i]);
        
        if ( i % 10)
            fflush(stdin);
    }
    printf("\n");
}

unsigned int *createRandomArray(unsigned int size){
    unsigned int *array;
    unsigned int i;

    array = (unsigned int *)malloc(sizeof(unsigned int) * size);
    
    srand48(time(NULL));
    for (i=0; i < size; ++i){
        array[i] = (lrand48());
    }
    
    return array;
}

void freeArray(unsigned int *arr){
    if (arr == NULL)
        return;

    free(arr);
}

//___QuickSort___
void qSort(unsigned int *arr, unsigned long start, unsigned long end){
    static unsigned long c = 1;

    if ( my_config.DEBUG && (c % 1000000) == 0){
        printf("qSort Iteration %lu\t Sorting Indexes %lu -> %lu\n", c, start, end);
    }

    c = c + 1; 
    if (start < end) {
        unsigned long pivot = qPartition(arr, start, end, start);

        //Sort less than Pivot
        if(pivot >0)
            qSort(arr, start, pivot -1);
        //Sort Greater than Pivot 

        qSort(arr, pivot+1, end);
    }
        
}

unsigned long qPartition(unsigned int *arr, unsigned long start, unsigned long end, unsigned long index){
    unsigned int indexVal = arr[index];
    unsigned int swapper;
    unsigned long i, loc;
    
//    printf("\tworking on Start: %u -- End: %u -- index: %u\n", start, end, index);

    //Stick our pivot at the back of the array
    swapper = arr[index];
    arr[index] = arr[end];
    arr[end] = swapper;

    loc = start;
    for (i=start; i < end; ++i){
        if (arr[i] <= indexVal){
            swapper = arr[i];
            arr[i] = arr[loc];
            arr[loc] = swapper;
            loc++;
        }
    }

    swapper = arr[loc];
    arr[loc] = arr[end];
    arr[end] = swapper;
    
    return loc;
}

//_START_Validation and Testing__________

int testSorter(){
    unsigned int *sortedTestTrue;
    unsigned int *sortedTestFalse;
    
    int size = 3;
    int i, res;
    int results = 1;

    sortedTestTrue = (unsigned int *)malloc(sizeof(unsigned int)*size);
    sortedTestFalse = (unsigned int *)malloc(sizeof(unsigned int)*size);


    for (i=0; i < size; ++i) {
        sortedTestTrue[i] = i;
        sortedTestFalse[i] = size-i;
    }

    printArray(sortedTestTrue, size);
    printArray(sortedTestFalse, size);

    res = isSorted(sortedTestTrue, size);
    if (res != 1){
        printf("sortedTestTrue returned 0 (FALSE)\n");
        results = 0;
    }

    res = isSorted(sortedTestFalse, size);
    if (res == 1){
        printf("sortedTestFalse return 1 (TRUE)\n");
        results = 0;
    }

    free(sortedTestTrue);
    free(sortedTestFalse);

    return results;
}

int isSorted(unsigned int *arr, unsigned long arrSize){
    unsigned long i;

    //Assume if its Null Return
    if (arrSize == 0) return 1;

    if (arrSize == 1) return 1;

    for (i=1; i < arrSize; ++i){
        if (arr[i-1] > arr[i]){
            if(my_config.DEBUG)
                printf("[%lu] arr[%lu]:%u > arr[%lu]:%u\n", i, i-1, arr[i-1], i, arr[i]);
                
            return 0; //Fail Fast
        }
    }

    return 1;
}

//this should be done by a loading file
unsigned int *loadBadArr(){
    unsigned int *arr;
    arr = (unsigned int *)malloc(sizeof(unsigned int)*20);

    arr[0] = 435228497;
    arr[1] = 1775875431;
    arr[2] = 1259489317;
    arr[3] = 1725732112;
    arr[4] = 1728679395;
    arr[5] = 694661385; 
    arr[6] = 2087335988;
    arr[7] = 2020467229;
    arr[8] = 209333757;
    arr[9] = 593059899;
    arr[10] = 2012754115;
    arr[11] = 1383773594;
    arr[12] = 325622910;
    arr[13] = 412598099;
    arr[14] = 813993237;
    arr[15] = 1893121973;
    arr[16] = 1185724710;
    arr[17] = 1817088232;
    arr[18] = 1852268963;
    arr[19] = 2118348116;

    return arr;
}

int parse_input(int argc, char *argv[]){
    int opt;
    int res;
    res = 0; // initialize to fail

    // ':' after option letter designates it will consume the next section as an argument for the option
    while ((opt = getopt(argc, argv, "f:t:d")) != -1) {
        switch(opt){
            case 'f':
                my_config.file = optarg;
                break;
            case 'd':
                my_config.DEBUG = 1;
                break;
            case 't':
                my_config.threads = strtoul(optarg, NULL, 10);
                if (errno){
                    fprintf(stderr, "Input %s throws error:\n\t%s\n\n", optarg, strerror(errno));
                    res = 1;
                }
        }
    }

    for(; optind < argc; ++optind){
        printf("extra arguments: %s\n", argv[optind]);
    }

    return res;
}
//_END___Validation and Testing__________