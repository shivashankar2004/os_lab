#include <stdio.h>
#include <stdlib.h>

void sort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void cscan_scheduling(int access[],int initial, int n,int tracks)
{
    int *disk_access = malloc(sizeof(int)*n);
    for(int i=0;i<n-2;i++) 
        disk_access[i] = access[i];
    disk_access[n-2] = 0;
    disk_access[n-1] = tracks-1;
    sort(disk_access,n);
    
    int cost = 0;
    int current = initial;
    int start, index;

    for(int j=0;j<n;j++)
    {
        if(disk_access[j]<current && current<disk_access[j+1])
        {
            start = j+1;
            break;
        }
    }
    
    for(int i=0;i<n;i++)
    {
        index = (start+i) % n;
        printf("%d - %d = %d\n",current,disk_access[index],abs(current - disk_access[index]));
        cost = cost + abs(current - disk_access[index]);
        current = disk_access[index];
    }

    printf("Number of cylinders moved : %d\n",cost);
}

int main()
{
    int tracks = 171;
    int initial = 60;
    int access[] = {70, 140, 50, 125, 30, 25, 160};
    int n = sizeof(access)/sizeof(access[0]) + 2;
    cscan_scheduling(access,initial,n,tracks);

    return 0;
}