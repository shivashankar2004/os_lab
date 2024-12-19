#include <stdio.h>
#include <stdlib.h>

void sstf_scheduling(int access[], int initial, int n)
{
    int cost = 0;
    int current = initial;
    int remaining_tracks = n; 

    while (remaining_tracks > 0)
    {
        int min_seek = 199;
        int next_index = -1; 

        for (int i = 0; i < n; i++)
        {
            if (access[i] != -1 && abs(access[i] - current) < min_seek)
            {
                min_seek = abs(access[i] - current);
                next_index = i;
            }
        }

        if (next_index != -1) 
        {
            printf("%d - %d = %d\n", current, access[next_index], abs(current - access[next_index]));
            cost += abs(current - access[next_index]);
            current = access[next_index];
            access[next_index] = -1; 
            remaining_tracks--;
        }
        else
        {
            break; 
        }
    }

    printf("Number of cylinders moved: %d\n", cost);
}

int main()
{
    int tracks = 200;
    int initial = 45;
    int disk_access[] = {92, 100, 40, 148, 67, 170, 29, 10};
    int no_of_access = sizeof(disk_access) / sizeof(disk_access[0]);
    sstf_scheduling(disk_access, initial, no_of_access);

    return 0;
}