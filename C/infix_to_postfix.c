#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Node
{
  char data;
  struct Node *next;
} node;

node *top = NULL;

bool is_empty(void)
{
  return top == NULL;
}

void push(char ch)
{
  node *n = (node *)malloc(sizeof(node));
  if (n == NULL)
  {
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  n->data = ch;
  n->next = top;
  top = n;
}

char pop(void)
{
  if (is_empty())
  {
    return '\0';
  }
  node *temp = top;
  top = top->next;
  char val = temp->data;
  free(temp);
  return val;
}

char peek(void)
{
  if (is_empty())
  {
    return '\0';
  }
  return top->data;
}

void clear_stack(void)
{
  while (!is_empty())
  {
    pop();
  }
}

int precedence(char op)
{
  switch (op)
  {
  case '^':
    return 3;
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 1;
  default:
    return 0;
  }
}

// Associativity check
bool is_right_associative(char op)
{
  return (op == '^');
}

bool is_operator(char ch)
{
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

char *infix_to_postfix(const char *infix)
{
  clear_stack();
  size_t len = strlen(infix);

  char *postfix = (char *)malloc(len + 1);
  if (postfix == NULL)
  {
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  int k = 0;

  for (size_t i = 0; i < len; i++)
  {
    char ch = infix[i];

    if (isspace((unsigned char)ch))
    {
      continue;
    }
    if (isalnum((unsigned char)ch))
    {
      postfix[k++] = ch;
    }
    else if (ch == '(')
    {
      push(ch);
    }
    else if (ch == ')')
    {
      while (!is_empty() && peek() != '(')
      {
        postfix[k++] = pop();
      }

      if (is_empty())
      {
        fprintf(stderr, "Error: Mismatched parentheses\n");
        free(postfix);
        clear_stack();
        exit(EXIT_FAILURE);
      }
      pop();
    }
    else if (is_operator(ch))
    {
      while (!is_empty() && peek() != '(')
      {
        int top_prec = precedence(peek());
        int curr_prec = precedence(ch);

        if ((top_prec > curr_prec) || (top_prec == curr_prec && !is_right_associative(ch)))
        {
          postfix[k++] = pop();
        }
        else
        {
          break;
        }
      }
      push(ch);
    }
    else
    {
      fprintf(stderr, "Error: Invalid character '%c'\n", ch);
      free(postfix);
      clear_stack();
      exit(EXIT_FAILURE);
    }
  }

  while (!is_empty())
  {
    char ch = pop();
    if (ch == '(' || ch == ')')
    {
      fprintf(stderr, "Error: Mismatched parentheses\n");
      free(postfix);
      clear_stack();
      exit(EXIT_FAILURE);
    }
    postfix[k++] = ch;
  }

  postfix[k] = '\0';
  return postfix;
}

int main(void)
{
  char infix[256];

  printf("Enter an infix expression (e.g., (A+B)*(C-D) or A+B*C^D):\n> ");
  if (fgets(infix, sizeof(infix), stdin) != NULL)
  {
    infix[strcspn(infix, "\r\n")] = '\0';

    if (strlen(infix) == 0)
    {
      printf("Empty expression provided.\n");
      return 0;
    }

    char *postfix = infix_to_postfix(infix);
    printf("Postfix Expression: %s\n", postfix);
    free(postfix);
  }

  return 0;
}