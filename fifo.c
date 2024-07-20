#include <stdio.h>

int faults = 0;
int num_of_frames = 3;
int hits = 0;

void fifo_replacement(int page[],int n)
{
  int frame[num_of_frames];
  int to_be_replaced = 0;
  for(int i=0;i<n;i++)
  {
    int found = 0;
    for(int j=0;j<num_of_frames;j++)
      if(page[i]==frame[j]) {
        found = 1;
        hits++;
        break;
      }

    if(found==0)
    {
      faults++;
      frame[to_be_replaced] = page[i];
      to_be_replaced = (to_be_replaced + 1) % num_of_frames;
    }
  }

  printf("Page faults: %d\n",faults);
  printf("Page hits: %d\n",hits);
}

int main()
{
  int page[] = {6, 7, 8, 9, 6, 7, 1, 6, 7, 8, 9, 1};
  int size = sizeof(page)/sizeof(page[0]);
  fifo_replacement(page,size);

  return 0;
}