//*****************************************************************************
//  
//  Comment Block
//  2020.08.16 Live Coding testing
//  PlaidCat 2020
// 
//  Generate File of X amount or X size
//
//  can only make a file with this many elements: 4294967295 * sizeof()
//  UINT_MAX
//
//*****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

typedef struct {
    unsigned long size;
    char *file;
    FILE *fp;
}generator;

int parse_input(int argc, char *argv[], generator *my_array){
    int opt;
    int res;
    res = 0;

    while ((opt = getopt(argc, argv, ":s:f:")) != -1 ){
        switch(opt){
            case 's':
                errno = 0;
                printf("Number Of Elements: %s\n", optarg);
                my_array->size = strtoul(optarg, NULL, 10);
                if (errno){
                    fprintf(stderr, "Input %s throws error:\n\t%s\n\n", optarg, strerror(errno));
                    res = 1;
                    break;
                }
                break;
            case 'f':
                printf("output file: %s\n", optarg);
                my_array->file = optarg;
                my_array->fp = fopen(my_array->file, "w");
                if (my_array->fp == NULL) {
                    fprintf(stderr, "File Pointers still NULL\n\t%s\n", strerror(errno));
                    res = 1;
                    break;
                }

                break;
        }
    }

    for(; optind < argc; ++optind){
        printf("extra arguments: %s\n", argv[optind]);
    }

    return res;
}

int GenFile(generator *my_array){
    unsigned long i;
    int res;

    i = 0;
    res = 0;

    fprintf(my_array->fp, "%lu\n", my_array->size);

    srand48(time(NULL));

    for (; i < my_array->size; ++i){
        fprintf(my_array->fp, "%u\n", (unsigned int)lrand48());
        if ((i % 100) == 0)
            fflush(my_array->fp);
    }

    return res;
}

int main(int argc, char *argv[]) {
    int res;
    generator my_array;

    my_array.size = 0;
    my_array.file = NULL;
    my_array.fp = NULL;
    res = 0;

    printf("MAX Elements: %lu\nElement Size: %ld\nMax Total File Size: %llu\n", 
            ULONG_MAX, sizeof(unsigned int), ULONG_MAX * (unsigned long long)sizeof(unsigned int));

    res = parse_input(argc,argv, &my_array);
    if (res){
        printf("Failed To Parse ... Exiting\n");
        if (my_array.fp != NULL){
            printf("Closing open file: %s\n", my_array.file);
            fclose(my_array.fp);
        }
        exit(1);
    }

    printf("size %lu for outfile %s\n", my_array.size, my_array.file);
    
    res = GenFile(&my_array);
    if (res){
        printf("Failed to Gen File\n");
        res = 1;
    }

    if (my_array.fp != NULL){
        fclose(my_array.fp);
    }

    return res;
}