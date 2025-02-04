#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = SUCCESS;
  if (!result || rows <= 0 || columns <= 0) {
    ret = FAILURE;
  }
  if (ret) {
    matrix_t res = {0};
    double **matrix =
        calloc(rows * columns * sizeof(double) + rows * sizeof(double *), 0);
    double *ptr = (double *)(matrix + rows);
    for (int i = 0; i < rows; i++) {
      matrix[i] = ptr + columns * i;
    }
    if (matrix) {
      res.matrix = matrix;
      res.rows = rows;
      res.columns = columns;
      *result = res;
    }
  }
  return ret;
}

void s21_remove_matrix(matrix_t *a) {
  if (a) {
    free(a->matrix);
    a->rows = 0;
    a->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *a, matrix_t *b) {
  int ret = SUCCESS;
  if (!a || !b || a->rows != b->rows || a->columns != b->rows)
    ret = FAILURE;
  if (ret) {
    int quit = 1;
    for (int i = 0; i < a->rows && quit; i++) {
      for (int j = 0; j < a->columns && quit; j++) {
        if (a->matrix[i][j] != b->matrix[i][j]) {
          quit = 0;
        }
      }
    }
    ret = quit;
  }
  return ret;
}

int s21_sum_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret = SUCCESS;
  if (!result || !a || !b || a->rows != b->rows || a->columns != b->rows)
    ret = FAILURE;
  if (ret) {
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];
      }
    }
  }
  return ret;
}

int s21_sub_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret = SUCCESS;
  if (!result || !a || !b || a->rows != b->rows || a->columns != b->rows)
    ret = FAILURE;
  if (ret) {
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];
      }
    }
  }
  return ret;
}

int s21_mult_number(matrix_t *a, double number, matrix_t *result) {
  int ret = SUCCESS;
  if (!result || !a)
    ret = FAILURE;
  if (ret) {
    result for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] * number;
      }
    }
  }
  return ret;
}
