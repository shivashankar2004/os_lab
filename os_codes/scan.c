#include <stdio.h>
#include <stdlib.h>

void sort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]<arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void scan_scheduling(int access[],int initial, int n,int tracks)
{
    int *disk_access = malloc(sizeof(int)*n);
    for(int i=0;i<n-1;i++) 
        disk_access[i] = access[i];
    disk_access[n-1] = 0;
    sort(disk_access,n);
    
    int cost = 0;
    int current = initial;
    int start, index;

    for(int j=0;j<n+1;j++)
    {
        if(disk_access[j]>current && current>disk_access[j+1])
        {
            start = j+1;
            break;
        }
    }

    for(int i=start;i<n+1;i++)
    {
        printf("%d - %d = %d\n",current,disk_access[i],abs(current - disk_access[i]));
        cost = cost + abs(current - disk_access[i]);
        current = disk_access[i];
    }
    for(int i=start-1;i>=0;i--)
    {
        printf("%d - %d = %d\n",current,disk_access[i],abs(current - disk_access[i]));
        cost = cost + abs(current - disk_access[i]);
        current = disk_access[i];
    }

    printf("Number of cylinders moved : %d\n",cost);
}

int main()
{
    int tracks = 200;
    int initial = 54;
    int access[] = {98, 137, 122, 183, 14, 133, 65, 78};
    int n = sizeof(access)/sizeof(access[0]) + 1;
    scan_scheduling(access,initial,n,tracks);

    return 0;
}