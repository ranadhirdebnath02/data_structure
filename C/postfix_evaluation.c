#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

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
  if (n == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }
  n->data = d;
  n->next = NULL;
  return n;
}

void push(int d)
{
  node *n = create_node(d);
  if (n == NULL)
  {
    return;
  }

  n->next = top;
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

void clear()
{
  node *temp = top;
  while (temp != NULL)
  {
    node *next_node = temp->next;
    free(temp);
    temp = next_node;
  }
  top = NULL;
}

int apply_operator(char op, int val1, int val2)
{
  switch (op)
  {
  case '+':
    return val1 + val2;
  case '-':
    return val1 - val2;
  case '*':
    return val1 * val2;
  case '/':
    if (val2 == 0)
    {
      printf("Error: Division by zero\n");
      clear();
      exit(EXIT_FAILURE);
    }
    return val1 / val2;
  case '^':
    return (int)pow(val1, val2);
  default:
    printf("Error: Unsupported operator '%c'\n", op);
    clear();
    exit(EXIT_FAILURE);
  }
}

int evaluate_postfix(const char *expr)
{
  clear();
  for (int i = 0; expr[i] != '\0'; i++)
  {
    if (isspace((unsigned char)expr[i]))
    {
      continue;
    }

    if (isdigit((unsigned char)expr[i]))
    {
      int num = 0;
      while (isdigit((unsigned char)expr[i]))
      {
        num = num * 10 + (expr[i] - '0');
        i++;
      }
      i--;
      push(num);
    }
    else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
             expr[i] == '/' || expr[i] == '^')
    {
      int val2 = pop();
      int val1 = pop();

      if (val1 == INT_MIN || val2 == INT_MIN)
      {
        printf("Error: Invalid postfix syntax (insufficient operands)\n");
        clear();
        exit(EXIT_FAILURE);
      }

      int result = apply_operator(expr[i], val1, val2);
      push(result);
    }
    else
    {
      printf("Error: Invalid character '%c' in expression\n", expr[i]);
      clear();
      exit(EXIT_FAILURE);
    }
  }

  int final_result = pop();

  if (!is_empty())
  {
    printf("Error: Malformed postfix expression (excess operands)\n");
    clear();
    exit(EXIT_FAILURE);
  }

  return final_result;
}

int main(void)
{
  char expr[256];

  printf("Enter a postfix expression (e.g., 20 4 2 + * 3 /):\n> ");
  if (fgets(expr, sizeof(expr), stdin) != NULL)
  {
    int result = evaluate_postfix(expr);
    printf("Evaluated Result: %d\n", result);
  }

  return 0;
}