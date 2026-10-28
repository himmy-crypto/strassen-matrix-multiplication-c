#include <stdio.h>
#include <stdlib.h>

int **allocate_memo4_matrix(int size);
void takeElement(int row, int column, int **mat);
int **add(int n, int **A,int **B,int **C);
int **sub(int n, int **A,int **B,int **C);
void display(int row, int column, int **M);
int getNearestPowOf2(int row, int column);
void free_matrix(int size, int **mat);
void strassen(int n, int**A,int**B,int**C);

int main()
{
    int r1,c1,r2,c2;
    printf("enter the row and column of both matrices: r1 c1 r2 c2: ");
    scanf("%d %d %d %d",&r1, &c1, &r2, &c2);
    if(c1 != r2){
        printf("Matrix multiplication can't be done!");
        return 0;
    }
    int n = getNearestPowOf2(r1,c2);
    int **A, **B, **C;
    A = allocate_memo4_matrix(n);
    B = allocate_memo4_matrix(n);
    C = allocate_memo4_matrix(n);
    printf("Enter elements of first matrix:\n");
    takeElement(r1,c1,A);
    printf("Enter elements of second matrix:\n");
    takeElement(r2,c2,B);
    printf("\n---First matrix---\n");
    display(r1,c2,A);
    printf("\n---Second matrix---\n");
    display(r2,c2,B);

    strassen(n, A, B, C);
    printf("\n## Resultant matrix---\n");
    display(r1, c2, C);

    free_matrix(n,A);
    free_matrix(n,B);
    free_matrix(n,C);

    return 1;
}
int **allocate_memo4_matrix(int size)
{
    int**arr = (int**)calloc(size,sizeof(int*));
    for(int i = 0; i < size; i++)
        arr[i] = (int*)calloc(size,sizeof(int));
    if(arr != NULL)
    return arr;
}

void takeElement(int row, int column, int **mat)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
            scanf("%d",&mat[i][j]);
    }
    return;
}

int **add(int n, int **A,int **B,int **C)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n;j++)
            C[i][j] = A[i][j] + B[i][j];
    }
    return C;
}

int **sub(int n, int **A,int **B,int **C)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n;j++)
            C[i][j] = A[i][j] - B[i][j];
    }
    return C;
}

void display(int row, int column, int **M)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
            printf("%d  ",M[i][j]);
        printf("\n");
    }
    return;
}

int getNearestPowOf2(int row, int column)
{
    int max = 2;
    while(max < column || max < row)
        max *= 2;
    return max;
}

void strassen(int n, int**A,int**B,int**C)
{
    if(n == 1)
    {
        C[0][0] = A[0][0]*B[0][0];
        return;
    }
    int k = n/2;
    int **A11 = allocate_memo4_matrix(k);
    int **A12 = allocate_memo4_matrix(k);
    int **A21 = allocate_memo4_matrix(k);
    int **A22 = allocate_memo4_matrix(k);

    int **B11 = allocate_memo4_matrix(k);
    int **B12 = allocate_memo4_matrix(k);
    int **B21 = allocate_memo4_matrix(k);
    int **B22 = allocate_memo4_matrix(k);

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    int **S1 = allocate_memo4_matrix(k);
    int **S2 = allocate_memo4_matrix(k);
    int **S3 = allocate_memo4_matrix(k);
    int **S4 = allocate_memo4_matrix(k);
    int **S5 = allocate_memo4_matrix(k);
    int **S6 = allocate_memo4_matrix(k);
    int **S7 = allocate_memo4_matrix(k);
    int **S8 = allocate_memo4_matrix(k);
    int **S9 = allocate_memo4_matrix(k);
    int **S10 = allocate_memo4_matrix(k);

    S1 = sub(k, B12, B22, S1);//S1 = B12 - B22
    S2 = add(k, A11, A12, S2);//S2 = A11 + A12
    S3 = add(k, A21, A22, S3);//S3 = A21 + A22
    S4 = sub(k, B21, B11, S4);//S4 = B21 - B11
    S5 = add(k, A11, A22, S5);//S5 = A11 + A22
    S6 = add(k, B11, B22, S6);//S6 = B11 + B22
    S7 = sub(k, A12, A22, S7);//S7 = A12 - A22
    S8 = add(k, B21, B22, S8);//S8 = B21 + B22
    S9 = sub(k, A11, A21, S9);//S9 = A11 - A21
    S10 = add(k, B11, B12, S10);//S10 = B11 + B12

    int **P1 = allocate_memo4_matrix(k);
    int **P2 = allocate_memo4_matrix(k);
    int **P3 = allocate_memo4_matrix(k);
    int **P4 = allocate_memo4_matrix(k);
    int **P5 = allocate_memo4_matrix(k);
    int **P6 = allocate_memo4_matrix(k);
    int **P7 = allocate_memo4_matrix(k);

    strassen(k, A11, S1, P1);//P1 = A11*S1
    strassen(k, S2, B22, P2);//P2 = S2*B22
    strassen(k, S3, B11, P3);//P3 = S3*B11
    strassen(k, A22, S4, P4);//P4 = A22*S4
    strassen(k, S5, S6, P5);//P5 = S5*S6
    strassen(k, S7, S8, P6);//P6 = S7*S8
    strassen(k, S9, S10, P7);//P7 = S9*S10

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < k; j++)
        {
            //C11 = P5 + P4 - P2 + P6
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];

            //C12 = P1 + P2
            C[i][j+k] = P1[i][j] + P2[i][j];

            //C21 = P3 + P4
            C[i+k][j] = P3[i][j] + P4[i][j];

            //C22 = P5 + P1 - P3 - P7
            C[i+k][j+k] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    free_matrix(k, A11); free_matrix(k, A12); 
    free_matrix(k, A21); free_matrix(k, A22);

    free_matrix(k, B11); free_matrix(k, B12); 
    free_matrix(k, B21); free_matrix(k, B22);

    free_matrix(k, S1);  free_matrix(k, S2);  free_matrix(k, S3);
    free_matrix(k, S4);  free_matrix(k, S5);  free_matrix(k, S6);
    free_matrix(k, S7);  free_matrix(k, S8);  free_matrix(k, S9);
    free_matrix(k, S10);

    free_matrix(k, P1);  free_matrix(k, P2);  free_matrix(k, P3);
    free_matrix(k, P4);  free_matrix(k, P5);  free_matrix(k, P6);
    free_matrix(k, P7);
}

void free_matrix(int size, int **mat)
{
    for(int i = 0; i < size; i++)
    {
        free(mat[i]);
    }   
    free(mat);
}