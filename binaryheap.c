#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int * keys;
    int length;
} BinaryHeap;

int greater(int k, int j, int * arr){
    if(arr[j] < arr[k]){
        return k;
    } else return j;
}

void exch(int arr[], int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void swim(BinaryHeap * heap){
    int i = heap->length;

    while(i >= 1 && heap->keys[i/2] < heap->keys[i]){
        exch(heap->keys, i, i/2);
        i=i/2;
    }
}

void sink(BinaryHeap * heap, int i){

    int * arr = heap->keys;

    while(i < heap->length){
        if(i == 0 && arr[i] < arr[1]) {exch(arr, i, 1); i = 1;}
        else if(i == 0 && arr[i] < arr[2]) {exch(arr, i, 2); i = 2;}

        else if(arr[i] < arr[i * 2]) {exch(arr, i, i * 2); i = i*2;}
        else if(arr[i] < arr[i * 2 + 1]) {exch(arr, i, i * 2 + 1); i = i*2+1;}
        else return;


    }

}

void insert(int k, BinaryHeap * binaryHeap){

    binaryHeap->length = binaryHeap->length+1;

    int length = binaryHeap->length;
    int * arr = binaryHeap->keys;

    arr[length] = k;
    swim(binaryHeap);
}

int deleteMax(BinaryHeap * heap){

    int copy = heap->keys[0];
    exch(heap->keys, 0, heap->length);

    printf("deleting %d ...\n", heap->keys[heap->length]);

    heap->keys[heap->length] = 0x00;
    heap->length--;

    sink(heap, 0);

    return copy;
}

int * heapsort(BinaryHeap * heap){

    int * arr = (int *) calloc(heap->length, sizeof(int));

    for(int i = heap->length-1; i >= 0; i--){
        arr[i] = deleteMax(heap);
    }

    return arr;
}


void printbh(BinaryHeap * heap){

    for(int i = 0; i < heap->length; i++){
        printf("heap->keys[%d] = %d\n", i+1, heap->keys[i]);
    }

}




int main(){
    int size = 10;

    BinaryHeap * heap = (BinaryHeap*) malloc(sizeof(BinaryHeap) + sizeof(int) * size);

    memset(heap, 0x00, size);

    heap->keys = (int*) malloc(size * sizeof(int));
    heap->length = 0;

    insert(1, heap);
    insert(5, heap);
    insert(9, heap);
    insert(3, heap);
    insert(4, heap);
    insert(10, heap);
    insert(8, heap);
    insert(50, heap);

    printbh(heap);

    int * arr = heapsort(heap);



    for(int i = 0; i < size; i++){
        printf("[%d]\v", arr[i]);
    }

    printf("\n");
    free(arr);
    free(heap);
    return 0;
}


