/**
 * @file array_traverse.c
 * @brief Implementation of Array Traversing in C.
 *
 * @author Ranadhir Debnath (ranadhirdebnath05@gmail.com)
 *
 * @version 1.0.0
 * @date 2026-08-23
 *
 * @license SPDX-License-Identifier: CC0-1.0
 * @note This software is released into the public domain under CC0 1.0.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Traverse an array.
 *
 * @param array Pointer to the array.
 * @param size Size of the array.
 */
void traverse_array(int *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%d ", array[i]);
  }
}

int main(void)
{
  int array[] = {1, 2, 3, 4, 5};
  int size = sizeof(array) / sizeof(array[0]);
  traverse_array(array, size);

  return EXIT_SUCCESS;
}
