#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node
{
  int data;
  struct Node *next;
} node;

node *head = NULL;

bool is_empty()
{
  return head == NULL;
}

node *create_node(int d)
{
  node *n = (node *)malloc(sizeof(node));
  n->data = d;
  n->next = NULL;
  return n;
}

void insert_start(int d)
{
  node *n = create_node(d);
  if (n == NULL) // if memory not allocated
  {
    printf("Memory not allocated\n");
    return;
  }

  if (!is_empty())
  {
    n->next = head;
  }
  head = n;
}

void insert_end(int d)
{
  node *n = create_node(d);
  if (n == NULL) // if memory not allocated
  {
    printf("Memory not allocated\n");
    return;
  }

  if (is_empty())
  {
    head = n;
  }
  else
  {
    node *temp = head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = n;
  }
}

void insert_after(int v, int s)
{
  bool is_found = false;
  node *t = head;
  while (t != NULL)
  {
    if (t->data == s)
    {
      is_found = true;
      break;
    }
    t = t->next;
  }
  if (is_found)
  {
    node *t1 = create_node(v);
    t1->next = t->next;
    t->next = t1;
  }
  else
  {
    printf("%d is not found\n", s);
  }
}

int delete_start()
{
  if (is_empty())
  {
    printf("List is empty\n");
    return INT_MIN;
  }

  node *temp = head;
  head = head->next;
  int d = temp->data;
  free(temp);
  return d;
}

int delete_end()
{
  if (is_empty())
  {
    printf("List is empty\n");
    return INT_MIN;
  }

  node *temp = head, *temp1 = head;
  while (temp->next != NULL)
  {
    temp1 = temp;
    temp = temp->next;
  }
  int d = temp->data;
  free(temp);
  if (temp == temp1)
  {
    head = NULL;
  }
  else
  {
    temp1->next = NULL;
  }
  return d;
}

int delete_any(int s)
{
  if (is_empty())
  {
    printf("List is empty\n");
    return INT_MIN;
  }

  bool is_found = false;
  node *temp = head, *temp1 = head;
  while (temp != NULL)
  {
    if (temp->data == s)
    {
      is_found = true;
      break;
    }
    temp1 = temp;
    temp = temp->next;
  }
  if (is_found)
  {
    int d = temp->data;
    if (temp == temp1)
    {
      head = NULL;
    }
    else
    {
      temp1->next = temp->next;
    }
    free(temp);
    return d;
  }
  else
  {
    printf("%d is not found\n", s);
    return INT_MIN;
  }
}

void print()
{
  if (is_empty())
  {
    printf("List is empty\n");
    return;
  }

  node *temp = head;
  printf("List items are: ");
  while (temp != NULL)
  {
    printf("%d\t", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

bool search(int s)
{
  bool is_found = false;
  if (is_empty())
  {
    return is_found;
  }

  node *temp = head;
  while (temp != NULL)
  {
    if (temp->data == s)
    {
      is_found = true;
      break;
    }
    temp = temp->next;
  }
  return is_found;
}

void clear()
{
  if (is_empty())
  {
    return;
  }
  node *temp = head, *temp1 = head;
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
    printf("1. Insert start\n2. Insert end\n3. Insert anywhere\n4. Delete start\n5. Delete end\n6. Delete anywhere\n7. Print\n8. Search\n9. Exit\nEnter your choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      printf("Enter value to insert: ");
      scanf("%d", &v);
      insert_start(v);
      break;
    case 2:
      printf("Enter value to insert: ");
      scanf("%d", &v);
      insert_end(v);
      break;
    case 3:
      printf("Enter value to insert: ");
      scanf("%d", &v);
      printf("Enter the element after which %d will be inserted: ", v);
      scanf("%d", &s);
      insert_after(v, s);
      break;
    case 4:
      v = delete_start();
      if (v != INT_MIN)
      {
        printf("Deleted element: %d\n", v);
      }
      break;
    case 5:
      v = delete_end();
      if (v != INT_MIN)
      {
        printf("Deleted element: %d\n", v);
      }
      break;
    case 6:
      printf("Enter the element to delete: ");
      scanf("%d", &s);
      v = delete_any(s);
      if (v != INT_MIN)
      {
        printf("Deleted element: %d\n", v);
      }
      break;
    case 7:
      print();
      break;
    case 8:
      printf("Enter element to search: ");
      scanf("%d", &s);
      printf(search(s) ? "Element found\n" : "Element not found\n");
      break;
    case 9:
      clear();
      exit(0);
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }
}