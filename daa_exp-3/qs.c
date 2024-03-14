#include<stdio.h>
#include<stdio.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
int partion(int arr[],int l,int h){
    int pivot=arr[h];
    int i=l-1;
    for(int j=l;j<h;j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[h]);
    return (i+1);
}
void qs(int arr[],int l,int h){
    if(l<h){
        int p=partion(arr,l,h);
        qs(arr,l,p-1);
        qs(arr,p+1,h);
    }
}
void print(int arr[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", arr[i]);
  }
  printf("\n");
}

void main(){
    int arr[]={5,1,4,3,9,2,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    printf("before qs\n");
    print(arr,n);
    qs(arr,0,n-1);
    printf("after qs \n");
    print(arr,n);

}