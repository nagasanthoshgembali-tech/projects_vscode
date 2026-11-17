#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int a[],int low,int high){
    int start = low;
    int end = high;
    int pivot= a[low];
    while(start<end){
        while(a[start]<=pivot && start<high)
        start++;
        while(a[end]>pivot)
        end--;
        if(start<end)
            swap(&a[start],&a[end]);
    }
    swap(&a[end],&a[low]);
    return end;
}
void quick_sort(int a[],int low, int high){
    if(low<high){
        int loc=partition(a,low,high);
        quick_sort(a,low,loc-1);
        quick_sort(a,loc+1,high);
    }
}
int main(){
    int n;
    system("cls");
    printf("enter the size of the array: ");
    scanf("%d",&n);
    printf("enter n elements: ");
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    quick_sort(a,0,n-1);
    printf("sorted array: ");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}