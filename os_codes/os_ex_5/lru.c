#include <stdio.h>

int faults = 0;
int num_of_frames = 3;
int hits = 0;

void lru_replacement(int page[], int n)
{
    int frame[num_of_frames];
    int time[num_of_frames]; 

    for (int i = 0; i < num_of_frames; i++) {
        frame[i] = -1;
        time[i] = 0; 
    }

    for (int i = 0; i < n; i++) 
    {
        int found = 0;
        for (int j = 0; j < num_of_frames; j++) 
        {
            if (page[i] == frame[j]) 
            {
                found = 1;
                hits++;
                time[j] = i; 
                break;
            }
        }

        if (found == 0) 
        {
            faults++;
            int least_recently_used = 0;
            for (int j = 1; j < num_of_frames; j++) 
            {
                if (time[j] < time[least_recently_used]) 
                {
                    least_recently_used = j;
                }
            }
            frame[least_recently_used] = page[i];
            time[least_recently_used] = i; 
        }
    }

    printf("Page faults: %d\n", faults);
    printf("Page hits: %d\n", hits);
}


int main()
{
  int page[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1, 7, 9, 6};
  lru_replacement(page,sizeof(page)/sizeof(page[0]));

  return 0;
}