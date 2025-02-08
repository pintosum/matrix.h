#include "s21_matrix.h"
#include <math.h>
#include <stdio.h>

int s21_is_valid_matrix_t(matrix_t *a) {
  return a && a->matrix && a->rows > 0 && a->columns > 0;
}

int s21_is_square_matrix(matrix_t *a) {
  return s21_is_valid_matrix_t(a) && a->rows == a->columns;
}

void print_matrix(matrix_t *a, const char *name) {
  printf("\n%s\n", name);
  if (s21_is_valid_matrix_t(a)) {
    for (int i = 0; i < a->rows; i++) {
      printf("\t");
      for (int j = 0; j < a->columns; j++) {
        printf("%6.2f  ", a->matrix[i][j]);
      }
      puts("");
    }
  } else
    printf("Invalid matrix");
}

int s21_equal_double(double a, double b) { return fabs(a - b) < 1e-7; }

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;
  if (!result || rows <= 0 || columns <= 0) {
    ret = ERROR;
  } else {
    double **matrix = calloc(rows, sizeof(double *));
    if (matrix) {
      for (int i = 0; i < rows; i++) {
        matrix[i] = calloc(rows * columns, sizeof(double));
      }
      s21_remove_matrix(result);
      result->matrix = matrix;
      result->rows = rows;
      result->columns = columns;
    } else
      ret = ERROR;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *a) {
  if (a && s21_is_valid_matrix_t(a)) {
    free(a->matrix);
    a->matrix = NULL;
    a->rows = 0;
    a->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *a, matrix_t *b) {
  int ret = OK;
  if (!s21_is_valid_matrix_t(a) || !s21_is_valid_matrix_t(b)) {
    ret = ERROR;
  } else if (a->rows == b->rows && a->columns == b->columns) {
    int quit = 0;
    for (int i = 0; i < a->rows && !quit; i++) {
      for (int j = 0; j < a->columns && !quit; j++) {
        if (!s21_equal_double(a->matrix[i][j], b->matrix[i][j])) {
          quit = 1;
        }
      }
    }
    ret = quit;
  } else
    ret = CALCULATION_ERROR;
  return ret;
}

int s21_sum_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret = OK;
  if (!result || !s21_is_valid_matrix_t(a) || !s21_is_valid_matrix_t(b)) {
    ret = ERROR;
  } else if (a->rows == b->rows && a->columns == b->columns) {
    s21_create_matrix(a->rows, a->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];
      }
    }
  } else {
    ret = CALCULATION_ERROR;
  }
  return ret;
}

int s21_sub_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret = OK;
  if (!result || !s21_is_valid_matrix_t(a) || !s21_is_valid_matrix_t(b)) {
    ret = ERROR;
  } else if (a->rows == b->rows && a->columns == b->columns) {
    s21_create_matrix(a->rows, a->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];
      }
    }
  } else {
    ret = CALCULATION_ERROR;
  }
  return ret;
}

int s21_mult_number(matrix_t *a, double number, matrix_t *result) {
  int ret = OK;
  if (!result || !s21_is_valid_matrix_t(a)) {
    ret = ERROR;
  } else {
    s21_create_matrix(a->rows, a->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = a->matrix[i][j] * number;
      }
    }
  }
  return ret;
}

int s21_mult_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret = OK;
  if (!a || !b || !result || !s21_is_valid_matrix_t(a) ||
      !s21_is_valid_matrix_t(b)) {
    ret = ERROR;
  } else if (a->columns == b->rows) {
    s21_create_matrix(a->rows, b->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < b->columns; j++) {
        for (int r = 0; r < b->rows; r++) {
          result->matrix[i][j] += a->matrix[i][r] * b->matrix[r][j];
        }
      }
    }

  } else {
    ret = CALCULATION_ERROR;
  }
  return ret;
}

int s21_transpose(matrix_t *a, matrix_t *result) {
  int ret = OK;
  if (!result || !s21_is_valid_matrix_t(a))
    ret = ERROR;
  else {
    s21_create_matrix(a->columns, a->rows, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[j][i] = a->matrix[i][j];
      }
    }
  }
  return ret;
}

double *s21_sum_rows_by_element(double *a, double *b, int element, int len) {
  if (!s21_equal_double(b[element], 0.0)) {
    double coef = b[element] / a[element];
    for (int i = 0; i < len; i++) {
      b[i] -= a[i] * coef;
    }
  }
  return b;
}

int s21_make_triangle_matrix(matrix_t *a) {
  int ret = 0;
  for (int r = 1; a->matrix[0][0] == 0 && r < a->rows; r++) {
    if (a->matrix[r][0] != 0.0) {
      double *temp = a->matrix[0];
      a->matrix[0] = a->matrix[r];
      a->matrix[r] = temp;
      ret = 1;
    }
  }
  for (int j = 0; a->matrix[0][0] != 0 && j < a->columns - 1; j++) {
    for (int i = j + 1; i < a->rows; i++) {
      a->matrix[i] =
          s21_sum_rows_by_element(a->matrix[j], a->matrix[i], j, a->columns);
    }
  }
  return ret;
}

double s21_minor_matrix_det(matrix_t *a, int i, int j) {
  double ret = 1. / 0.;
  matrix_t minor = {0};
  s21_create_matrix(a->rows - 1, a->columns - 1, &minor);
  int rows = 0;
  int columns = 0;
  for (int k = 0; k < a->rows; k++) {
    if (k == i)
      continue;
    for (int m = 0; m < a->columns; m++) {
      if (m == j)
        continue;
      minor.matrix[rows][columns] = a->matrix[k][m];
      columns++;
    }
    columns = 0;
    rows++;
  }
  // printf("\ni %d, j %d", i, j);
  // print_matrix(&minor, "minor");
  s21_determinant(&minor, &ret);
  if ((i + j) % 2)
    ret = -ret;
  return ret;
}

int s21_calc_complements(matrix_t *a, matrix_t *result) {
  int ret = OK;
  if (!result || !s21_is_valid_matrix_t(a)) {
    ret = ERROR;
  }
  if (ret == OK && s21_is_square_matrix(a)) {
    s21_create_matrix(a->rows, a->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        result->matrix[i][j] = s21_minor_matrix_det(a, i, j);
      }
    }
  } else {
    ret = CALCULATION_ERROR;
  }
  return ret;
}

matrix_t s21_copy_matrix(matrix_t *a) {
  matrix_t ret = {0};
  s21_create_matrix(a->rows, a->columns, &ret);
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->columns; j++) {
      ret.matrix[i][j] = a->matrix[i][j];
    }
  }
  return ret;
}

int s21_determinant(matrix_t *a, double *result) {
  int ret = OK;
  if (!a || !result || !s21_is_valid_matrix_t(a))
    ret = ERROR;
  if (ret == OK && s21_is_square_matrix(a)) {
    matrix_t copy = s21_copy_matrix(a);
    double det = 1.0;
    int swap = s21_make_triangle_matrix(&copy);
    swap %= 2;
    // print_matrix(&copy, "triangle");
    for (int i = 0; i < copy.rows; i++) {
      det *= copy.matrix[i][i];
    }

    if (swap) {
      det = -det;
    }
    *result = det;
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *a, matrix_t *result) {
  int ret = OK;
  if (!a || !result || !s21_is_valid_matrix_t(a)) {
    ret = ERROR;
  } else if (s21_is_square_matrix(a)) {
    double det;
    s21_determinant(a, &det);
    if (det != 0) {
      matrix_t temp = {0};
      s21_calc_complements(a, result);
      s21_transpose(result, &temp);
      s21_mult_number(&temp, 1. / det, result);
      s21_remove_matrix(&temp);
    }
  } else {
    ret = CALCULATION_ERROR;
  }
  return ret;
}

int main() {
  matrix_t a = {0};
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 2.;
  a.matrix[0][1] = 5.;
  a.matrix[0][2] = 7.;
  a.matrix[1][0] = 6.;
  a.matrix[1][1] = 3.;
  a.matrix[1][2] = 4.;
  a.matrix[2][0] = 5.;
  a.matrix[2][1] = -2.;
  a.matrix[2][2] = -3.;
  print_matrix(&a, "a");
  matrix_t result = {0};
  s21_inverse_matrix(&a, &result);
  print_matrix(&result, "result");
}
