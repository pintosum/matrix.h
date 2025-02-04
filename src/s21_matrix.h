#ifndef S21_MATRIX_H
#define S21_MATRIX_H

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int, int, matrix_t *);
void s21_remove_matrix(matrix_t *);
int s21_eq_matrix(matrix_t *, matrix_t *);
int s21_sum_matrix(matrix_t *, matrix_t *, matrix_t *);
int s21_sub_matrix(matrix_t *, matrix_t *, matrix_t *);
int s21_mult_number(matrix_t *, double, matrix_t *);
int s21_mult_matrix(matrix_t *, matrix_t *, matrix_t *);
int s21_transpose(matrix_t *, matrix_t *);
int s21_calc_complements(matrix_t *, matrix_t *);
int s21_determinant(matrix_t *, double *);
int s21_inverse_matrix(matrix_t *, matrix_t *);

#endif
