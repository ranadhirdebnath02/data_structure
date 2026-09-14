#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node
{
  int data;
  struct Node *next;
} node;

node *top = NULL;

bool is_empty()
{
  return top == NULL;
}

node *create_node(int d)
{
  node *n = (node *)malloc(sizeof(node));
  n->data = d;
  n->next = NULL;
  return n;
}

void push(int d)
{
  node *n = create_node(d);
  if (n == NULL) // if memory not allocated
  {
    printf("Memory not allocated\n");
    return;
  }

  if (!is_empty())
  {
    n->next = top;
  }
  top = n;
}

int pop()
{
  if (is_empty())
  {
    printf("Stack Underflow\n");
    return INT_MIN;
  }

  node *temp = top;
  top = top->next;
  int d = temp->data;
  free(temp);
  return d;
}

void peek()
{
  if (is_empty())
  {
    printf("Stack Underflow\n");
    return;
  }
  printf("At Top: %d\n", top->data);
}

void print()
{
  if (is_empty())
  {
    printf("Stack Underflow\n");
    return;
  }

  node *temp = top;
  printf("List items are: ");
  while (temp != NULL)
  {
    printf(temp == top ? "%d (top)\t" : "%d\t", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

void clear()
{
  if (is_empty())
  {
    return;
  }
  node *temp = top, *temp1 = top;
  while (temp != NULL)
  {
    temp1 = temp->next;
    free(temp);
    temp = temp1;
  }
}

void main()
{
  int v, ch, s;
  while (true)
  {
    printf("1. Push\n2. Pop\n3. Peek\n4. Print\n5. Exit\nEnter your choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      printf("Enter value to push: ");
      scanf("%d", &v);
      push(v);
      break;
    case 2:
      v = pop();
      if (v != INT_MIN)
      {
        printf("Popped element: %d\n", v);
      }
      break;
    case 3:
      peek();
      break;
    case 4:
      print();
      break;
    case 5:
      clear();
      exit(0);
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}