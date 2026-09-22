#include <stdio.h>

static void solve_hanoi(int count, char source, char auxiliary, char destination)
{
  if (count <= 0)
  {
    return;
  }

  /* Move top n - 1 disks from source to auxiliary */
  solve_hanoi(count - 1, source, destination, auxiliary);

  /* Move the largest disk from source to destination */
  printf("Move disk %d from rod %c to rod %c\n", count, source, destination);

  /* Move the n - 1 disks from auxiliary to destination */
  solve_hanoi(count - 1, auxiliary, source, destination);
}

int main(void)
{
  int disks = 0;

  printf("Enter number of disks: ");
  if (scanf("%d", &disks) != 1 || disks <= 0)
  {
    fprintf(stderr, "Error: Please enter a valid positive integer.\n");
    return 1;
  }

  printf("\nSolution for %d disks:\n", disks);
  solve_hanoi(disks, 'A', 'B', 'C');

  return 0;
}