#include <stdio.h>

int faults = 0;
int hits = 0;
int num_of_frames = 3;

void optimal_replacement(int page[], int n)
{
    int frame[num_of_frames];
    int to_be_replaced = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < num_of_frames; j++)
        {
            if (page[i] == frame[j])
            {
                found = 1;
                hits++;
                break;
            }
        }

        if (found == 0)
        {
            faults++;
            int farthest = -1;

            for (int k = 0; k < num_of_frames; k++)
            {
                int j;
                for (j = i + 1; j < n; j++)
                {
                    if (page[j] == frame[k])
                    {
                        if (j > farthest)
                        {
                            to_be_replaced = k;
                            farthest = j;
                        }
                        break;
                    }
                }
                
                if (j == n)
                {
                    to_be_replaced = k;
                    break;
                }
            }

            frame[to_be_replaced] = page[i];
        }
    }

    printf("Page faults: %d\n", faults);
    printf("Page hits: %d\n", hits);
}


int main()
{
  int page[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1, 7, 9, 6};
  optimal_replacement(page,sizeof(page)/sizeof(page[0]));

  return 0;
}