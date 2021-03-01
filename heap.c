#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN  10
#define PRINTSPACES 2

//---------Positioning functions-----------------------
int parent (int index) { return (index+1)/2 -1; }     //
int left   (int index) { return (index+1)*2 -1; }     //
int right  (int index) { return (index+1)*2   ; }     //
//------------------------------------------------------


//----------Auxiliar functions--------------------------
void swap(int *a, int *b);                            //
int yesNo(void);                                      //
int getint(void);                                     //
//------------------------------------------------------


//Print the options and return the index of the chosen one
int menu(void);


//Generate a new heap as an array of integers
void newHeap(int* heap);


//----------Non-editing functions-----------------------
//-----These functions don't modify the heap-----     //
                                                      //
//Print the heap formatted as a binary tree           //
void printHeap(int* heap, int heapsize, int height);  //
                                                      //
//Check if the heap is maxHeap/minHeap                //
//if type == 0 -> isMinHeap                           //
//else         -> isMaxHeap                           //
void checkHeap  (int* heap, int heapsize, int type);  //
  int isMaxHeap (int* heap, int heapsize);            //
  int isMinHeap (int* heap, int heapsize);            //
//------------------------------------------------------


//----------Editing functions------------------------------
//-----These functions do modify the heap-----           //
                                                         //
//if type == 0 -> buildMinHeap/minHeapify                //
//else         -> buildMaxHeap/maxHeapify                //
void buildHeap     (int* heap, int heapsize, int type);  //
  void maxHeapify  (int* heap, int heapsize, int index); //
  void minHeapify  (int* heap, int heapsize, int index); //
//---------------------------------------------------------


//----------Priority Queue functions---------------------------------------
//These functions only work if the heap is a max/min Heap                //
                                                                         //
//Return the max/min                                                     //
int heapMax             (int* heap, int heapsize);                       //
int heapMin             (int* heap, int heapsize);                       //
                                                                         //
//Return and remove the max/min                                          //
int heapExtractMax      (int* heap, int*heapsize);                       //
int heapExtractMin      (int* heap, int*heapsize);                       //
                                                                         //
//If value>heap[index] -> heap(index) = value                            //
void maxHeapIncreaseKey (int* heap, int heapsize, int index, int value); //
void minHeapIncreaseKey (int* heap, int heapsize, int index, int value); //
                                                                         //
//Insert a new node into the heapMin                                     //
void maxHeapInsert      (int**heap, int*heapsize, int value);            //
void minHeapInsert      (int**heap, int*heapsize, int value);            //
//-------------------------------------------------------------------------


int main(void){

  srand(time(NULL));

  int* heap = malloc(sizeof(int)*LEN);
  if (heap==NULL){
    printf("Error. Out of memory.\n");
  }

  int heapsize = LEN;
  newHeap(heap);

  int option = 0;

  while((option = menu())){

    switch (option) {

      // 1 - Generate a new Heap
      case 1:
        newHeap(heap);
        break;

      // 2 - Print the heap
      case 2:
        printHeap(heap, heapsize, 0);
        break;

      // 3 - Build a Max Heap
      case 3:
        buildHeap(heap, heapsize, 1);
        break;

      // 4 - Build a Min Heap
      case 4:
        buildHeap(heap, heapsize, 0);
        break;

      // 5 - Check if the heap is a Max Heap
      case 5:
        checkHeap(heap, heapsize, 1);
        break;

      // 6 - Check if the heap is a Min Heap
      case 6:
        checkHeap(heap, heapsize, 0);
        break;

      case 7:
        heapMax(heap, heapsize);
        break;

      case 8:
        heapMin(heap, heapsize);
        break;

      case 9:
        heapExtractMax(heap, &heapsize);
        break;

      case 10:
        heapExtractMin(heap, &heapsize);
        break;

      case 11:
        printf("Index of node to be modified: ");
        int index = getint();
        printf("New key value: ");
        int value = getint();
        maxHeapIncreaseKey(heap, heapsize, index, value);
        break;

      case 12:
        printf("Index of node to be modified: ");
        index = getint();
        printf("New key value: ");
        value = getint();
        minHeapIncreaseKey(heap, heapsize, index, value);
        break;

      case 13:
        printf("New node value: ");
        value = getint();
        maxHeapInsert(&heap, &heapsize, value);
        break;

      case 14:
        printf("New node value: ");
        value = getint();
        minHeapInsert(&heap, &heapsize, value);
        break;

      default:
        free(heap);
        exit(1);
    }
  }

  free(heap);
  return 0;

}

void swap(int *a, int *b){

  //Swap two elements of an int array

  int temp = *a;
  *a = *b;
  *b = temp;

}

int yesNo   (void){

  //Return 1 (true) if the key 'y' is pressed, 0 (false) otherwise

  printf("Step by Step? (y/n)\n");

  if (getchar() == 'y'){
    scanf("%*[^\n]");
    scanf("%*c");

    return 1;

  }

  scanf("%*[^\n]");
  scanf("%*c");

  return 0;

}

int getint  (void){

  int n = 0;

  while(scanf("%d", &n)<1 || n<0){
    printf("Invalid choice. Try again.\n");
    scanf("%*[^\n]");
    scanf("%*c");
  }

  scanf("%*[^\n]");
  scanf("%*c");

  return n;

}

int menu    (void){

  printf("\n\n\n------------------------------\n\n");

  printf("Press the corresponding key:\n"
         "1  - Generate a new Heap\n"
         "2  - Print the heap\n"
         "3  - Build a Max Heap\n"
         "4  - Build a Min Heap\n"
         "5  - Check if the heap is a Max Heap\n"
         "6  - Check if the heap is a Min Heap\n"
         "7  - Print the Max (if the heap is a Max Heap)\n"
         "8  - Print the Min (if the heap is a Min Heap)\n"
         "9  - Extract the Max (if the heap is a Max Heap)\n"
         "10 - Extract the Min (if the heap is a Min Heap)\n"
         "11 - Increase the key of a Max heap node\n"
         "12 - Increase the key of a Min heap node\n"
         "13 - Insert a new node in a Max heap\n"
         "14 - Insert a new node in a Min heap\n"
         "0  - Exit\n\n"
       );

  int n = 0;

  while(scanf("%d", &n)<1 || n<0 || n>14){
    printf("Invalid choice. Try again.\n");
    scanf("%*[^\n]");
    scanf("%*c");
  }

  scanf("%*[^\n]");
  scanf("%*c");

  return n;

}

void newHeap            (int* heap){

  for (int i = 0; i<LEN; i++){
    heap[i] = rand() % 100;
    printf("%d ", heap[i]);
  }
  printf("\n\n\n\n");

  printHeap(heap, LEN, 0);

}

void printHeap          (int* heap, int heapsize, int height){

  if (heapsize<=1){

    //print root
    for (int i = 0; i<(pow(2, height)-1) * PRINTSPACES; i++){ printf(" "); }
    printf("%2d\n", heap[0]);

    return;

  }

  //Find index of first element with max height (bottom-left of the heap)
  int index = 1;
  while (index<heapsize){
    index*=2;
  }
  index = index/2 -1;

  printHeap(heap, index, height+1);

  //---------PRINTING SLASHES ABOVE NODES--------
  int tempIndex = index;
  int slash = 0;
  for (int i = 0; i<(pow(2, height)-1) * PRINTSPACES; i++){ printf(" "); }

  while(tempIndex<heapsize){
    if (slash % 2 == 0) {
      printf(" /");
    } else {
      printf("\\ ");
    }
    slash++;
    tempIndex++;
    //separating spaces
    if (tempIndex<heapsize){
      for (int i = 0; i<(pow(2, height+1)-1) * PRINTSPACES; i++){ printf(" ");}
    }
  }
  printf("\n");
  //---------------------------------------------


  //leading spaces
  for (int i = 0; i<(pow(2, height)-1) * PRINTSPACES; i++){ printf(" "); }

  while(index<heapsize){
    printf("%2d", heap[index++]);
    //separating spaces
    if (index<heapsize){
      for (int i = 0; i<(pow(2, height+1)-1) * PRINTSPACES; i++){ printf(" ");}
    }
  }
  printf("\n");
  if (height==0){ printf("\n\n\n");}

}

void checkHeap          (int* heap, int heapsize, int type){

  if (type){
    if (isMaxHeap(heap, heapsize)){
      printf("It's a Max Heap!!! :D\n\n\n\n");
    } else {
      printf("It's not a Max Heap... :(\n\n\n\n");
    }

  } else {
    if (isMinHeap(heap, heapsize)){
      printf("It's a Min Heap!!! :D\n\n\n\n");
    } else {
      printf("It's not a Min Heap... :(\n\n\n\n");
    }
  }

}

int isMaxHeap           (int* heap, int heapsize){

  int lastParent = heapsize/2-1;

  //Checking every parent except the last one
  //(because it could have only one child -> need extra control to prevent seg-fault)
  for (int i = 0; i<lastParent; i++){
    if (heap[i]<heap[left(i)] || heap[i]<heap[right(i)]){ return 0;}
  }

  //Checking last parent
  if (heap[lastParent]<heap[left(lastParent)]){ return 0;}
  int lastChild = right(lastParent);

  //Extra control to check if the right child exists
  if (lastChild<heapsize && heap[lastParent]<heap[lastChild]){ return 0;}

  return 1;

}

int isMinHeap           (int* heap, int heapsize){

  int lastParent = heapsize/2-1;

  //Comments are the same of isMaxHeap (this function only differs for "<" and ">")
  for (int i = 0; i<lastParent; i++){
    if (heap[i]>heap[left(i)] || heap[i]>heap[right(i)]){ return 0;}
  }

  if (heap[lastParent]>heap[left(lastParent)]){ return 0;}
  int lastChild = right(lastParent);
  if (lastChild<heapsize && heap[lastParent]>heap[lastChild]){ return 0;}

  return 1;

}

void buildHeap          (int* heap, int heapsize, int type){

  //StepByStep option (print the heap after each iteration)
  int sbs = yesNo();

  //Apply heapify to every parent node
  if (type){
    for (int i = heapsize/2-1; i>=0; i--){
      maxHeapify(heap, heapsize, i);
      if (sbs){ printHeap(heap, heapsize, 0);}
    }

  } else {
    for (int i = heapsize/2; i>=0; i--){
      minHeapify(heap, heapsize, i);
      if (sbs){ printHeap(heap, heapsize, 0);}
    }
  }

  printHeap(heap, heapsize, 0);

}

void maxHeapify         (int* heap, int heapsize, int index){

  int l = left(index);
  int r = right(index);

  int max = index;

  //Keeps the max between parent and lchild (if exists)
  if (l<heapsize && heap[l]>heap[index]){
    max = l;
  } else {
    max = index;
  }

  //Keeps the max between previous max and rchild (if exists)
  if (r<heapsize && heap[r]>heap[max]){
    max = r;
  }

  //If the max is not the parent, swap  it and apply heapify recursively
  if (max!=index) {
    swap(&heap[index], &heap[max]);
    maxHeapify(heap, heapsize, max);
  }

}

void minHeapify         (int* heap, int heapsize, int index){

  //Comments are the same of maxHeapify (this function only differs for "<" and ">")

  int l = left(index);
  int r = right(index);

  int min = index;

  if (l<heapsize && heap[l]<heap[index]){
    min = l;
  } else {
    min = index;
  }

  if (r<heapsize && heap[r]<heap[min]){
    min = r;
  }

  if (min!=index) {
    swap(&heap[index], &heap[min]);
    minHeapify(heap, heapsize, min);
  }

}

int heapMax             (int* heap, int heapsize){

  if (heapsize<1){
    printf("Heapsize error.\n");
    return -1;
  }

  if(!isMaxHeap(heap, heapsize)){
    printf("Error: The heap is not a Max Heap.\n");
    return -1;
  }

  printf("%d\n", heap[0]);
  return heap[0];

}

int heapMin             (int* heap, int heapsize){

  if (heapsize<1){
    printf("Heapsize error.\n");
    return -1;
  }

  if(!isMinHeap(heap, heapsize)){
    printf("Error: The heap is not a Min Heap.\n");
    return -1;
  }

  printf("%d\n", heap[0]);
  return heap[0];

}

int heapExtractMax      (int* heap, int*heapsize){

    if (*heapsize<1){
      printf("Heapsize error.\n");
      return -1;
    }

    if(!isMaxHeap(heap, *heapsize)){
      printf("Error: The heap is not a Max Heap.\n");
      return -1;
    }

    int max = heap[0];
    heap[0] = heap[*heapsize-1];
    *heapsize = *heapsize-1;

    maxHeapify(heap, *heapsize, 0);

    printf("%d\n", max);
    return max;

}

int heapExtractMin      (int* heap, int*heapsize){

  if (*heapsize<1){
    printf("Heapsize error.\n");
    return -1;
  }

  if(!isMinHeap(heap, *heapsize)){
    printf("Error: The heap is not a Min Heap.\n");
    return -1;
  }

  int min = heap[0];
  heap[0] = heap[*heapsize-1];
  *heapsize = *heapsize-1;

  minHeapify(heap, *heapsize, 0);

  printf("%d\n", min);
  return min;

}

void maxHeapIncreaseKey (int* heap, int heapsize, int index, int value){

  if (index>=heapsize || index < 0){
    printf("Index error.\n");
    return;
  }

  if (!isMaxHeap(heap, heapsize)){
    printf("Error: The heap is not a Max Heap.\n");
    return;
  }

  if (value<heap[index]){
    printf("Error. Key is already greater then new Key.\n");
    return;
  }

  heap[index] = value;

  while(parent(index)>=0 && heap[parent(index)]<heap[index]){
    swap(&heap[index], &heap[parent(index)]);
    index = parent(index);
  }

}

void minHeapIncreaseKey (int* heap, int heapsize, int index, int value){

  if (index>=heapsize || index < 0){
    printf("Index error.\n");
    return;
  }

  if (!isMinHeap(heap, heapsize)){
    printf("Error: The heap is not a Min Heap.\n");
    return;
  }

  if (value<heap[index]){
    printf("Error. Key is already greater then new Key.\n");
    return;
  }

  heap[index] = value;

  minHeapify(heap, heapsize, index);

}

void maxHeapInsert      (int**heap, int*heapsize, int value){

  if (!isMaxHeap(*heap, *heapsize)){
    printf("Error: The heap is not a Max Heap.\n");
    return;
  }

  int* temp = malloc(sizeof(int) * (*heapsize));
  memcpy(temp, *heap, sizeof(int) * (*heapsize));
  free(*heap);

  *heapsize = *heapsize+1;
  *heap = malloc(sizeof(int) * (*heapsize));
  memcpy(*heap, temp, sizeof(int) * (*heapsize - 1));
  free(temp);

  (*heap)[*heapsize -1] = -1;

  maxHeapIncreaseKey(*heap, *heapsize, *heapsize-1, value);

}

void minHeapInsert      (int**heap, int* heapsize, int value){

  if (!isMinHeap(*heap, *heapsize)){
    printf("Error: The heap is not a Min Heap.\n");
    return;
  }

  int* temp = malloc(sizeof(int) * (*heapsize));
  memcpy(temp, *heap, sizeof(int) * (*heapsize));
  free(heap);

  *heapsize = *heapsize+1;
  *heap = malloc(sizeof(int) * (*heapsize));
  memcpy(*heap, temp, sizeof(int) * (*heapsize - 1));
  free(temp);

  *heap[*heapsize -1] = -1;
  minHeapIncreaseKey(*heap, *heapsize, *heapsize-1, value);

}
