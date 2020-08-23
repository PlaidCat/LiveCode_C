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
//  * C lookup for defs
//
//
//*****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//__ProtoTypes_______
//___Validation and Testing__________
int testSorter();
int isSorted(unsigned int *arr, int arrSize);
unsigned int *loadBadArr();

//__Information____
void printArray(unsigned int *arr, unsigned int arrSize);

//__Memory Management_____
unsigned int *createRandomArray(unsigned int size);
void freeArray(unsigned int *arr);

//__Quick Sort___
//This is recursive
void qSort(unsigned int *arr, unsigned int start, unsigned int end);
unsigned int qPartition(unsigned int *arr, unsigned int start, unsigned int end, unsigned int index);

//___MAIN____
int main(int argc, char *argv[]) {
    int res;
    unsigned int *arr;
    unsigned int size = 20000;
    
    res = testSorter();
    if (res == 0)
        return -1;

    arr = createRandomArray(size);
    //arr = loadBadArr();
    printArray(arr, size);
    qSort(arr, 0,  size-1);
    printArray(arr, size);

    res = isSorted(arr, size);
    if (res)
        printf("Huzza its sorted\n");
    else
        printf("ya goofed in your crappy qSort\n");

    freeArray(arr);

    return res;
}

void printArray(unsigned int *arr, unsigned int arrSize){
    unsigned int i;

    printf("Printing array of size %u\n", arrSize);

    //crappy print
    for (i=0; i < arrSize; ++i){
        printf("%u ", arr[i]);
        
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
void qSort(unsigned int *arr, unsigned int start, unsigned int end){
    static int c = 1;
//    printf("qSort Iteration %d\t Sorting Indexes %u -> %u\n", c, start, end);

    c = c + 1;
    if (start < end) {
        unsigned int pivot = qPartition(arr, start, end, start);

        //Sort less than Pivot
        if(pivot >0)
            qSort(arr, start, pivot -1);
        //Sort Greater than Pivot 
        if(pivot >0)
            qSort(arr, pivot+1, end);
    }
        
}

unsigned int qPartition(unsigned int *arr, unsigned int start, unsigned int end, unsigned int index){
    unsigned int indexVal = arr[index];
    unsigned int swapper;
    unsigned int i, loc;
    
//    printf("\tworking on Start: %u -- End: %u -- index: %u\n", start, end, index);

    //Stick our pivot at the back of the array
    swapper = arr[index];
    arr[index] = arr[end];
    arr[end] = swapper;

    loc = start;
    for (i=start; i < end; ++i){
        if (arr[i] <= indexVal){
//            printf("\tswapping [%u]%u and [%u]%u because the pivot %u\n", i, arr[i], loc, arr[loc], indexVal);
            swapper = arr[i];
            arr[i] = arr[loc];
            arr[loc] = swapper;
            loc++;
        }
    }

    swapper = arr[loc];
    arr[loc] = arr[end];
    arr[end] = swapper;
    
//    printf("\tLoc/Pivot Returned: %u\n", loc);
    
    return loc;
}

//___Validation and Testing__________
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

int isSorted(unsigned int *arr, int arrSize){
    int i;

    //Assume if its Null Return
    if (arrSize == 0) return 1;

    if (arrSize == 1) return 1;

    for (i=1; i < arrSize; ++i){
        if (arr[i-1] > arr[i])
            return 0; //Fail Fast
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
