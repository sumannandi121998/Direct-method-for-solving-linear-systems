#include <stdio.h>
#include <gsl/gsl_linalg.h>


int main()
{
    double a[] = {1.0, 0.67,0.33,0.45,1.0,0.55,0.67,0.33,1.0};
    double c[] = {2.0, 2.0, 2.0};

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 3); //matrix view of a data
    gsl_vector_view b = gsl_vector_view_array(c, 3); //vector view of c data

    gsl_vector *x = gsl_vector_alloc(3); // memory allocation for solution vector
    gsl_permutation *p = gsl_permutation_alloc(3); // memory allocation for permutation

    int s,i,j,k;
    double L[3][3],U[3][3],B[3][3],C[3][3],D[3][3];
   
    for (i=0;i<3;i++) //store the elements of A matrix in 2d array C
    { for (j=0;j<3;j++)
     {C[i][j]=gsl_matrix_get(&A.matrix,i,j);}}
    
    gsl_linalg_LU_decomp(&A.matrix,p, &s); //LU decomposition using gsl function

    printf("The cyclic permutation is\n");
    gsl_permutation_fprintf (stdout, p, " %u"); //print the permutation vector
    printf("\n");
    
    printf("The U matrix is \n");
    for (i=0;i<3;i++) //Loop for printing U matrix
    {for (j=0;j<3;j++)
     {
     if (i<=j)
       {U[i][j]=gsl_matrix_get(&A.matrix,i,j); //This gives the ij element of A matrix
       printf("%g  ",U[i][j]);}
     else
       {U[i][j]=0;
       printf("%g  ",U[i][j]);}}
     printf("\n");}
   
    printf("The L matrix is \n");
    for (i=0;i<3;i++) //Loop for printing L matrix
    {for (j=0;j<3;j++)
     {
     if (i>j)
       {L[i][j]=gsl_matrix_get(&A.matrix,i,j);
       printf("%g  ",L[i][j]);}
     else if (i==j)
       {L[i][j]=1;
       printf("%g  ",L[i][j]);}
     else 
       {L[i][j]=0;
       printf("%g  ",L[i][j]);}}
     printf("\n");}
  
    printf("The LU matrix is \n");
    for (i=0;i<3;i++) //Loop for multiplication of L and U
    {for (k=0;k<3;k++)
    {B[i][k]=0;
    for (j=0;j<3;j++)
    {B[i][k]=B[i][k]+L[i][j]*U[j][k];}
    printf("%g  ",B[i][k]);}
    printf("\n");}
   
    printf("The PA matrix is \n");
    for (i=0;i<3;i++) //Applying permutation to A matrix
    {
    for (j=0;j<3;j++)
    {D[i][j]=C[gsl_permutation_get(p,i)][j]; //It exchange the row of matrix C according to the permutation p
    printf("%g  ",D[i][j]);}printf("\n");} //D matrix is same as B matrix ie LU=PA.So,the LU decomposition is correct
   
    gsl_permutation_free(p); //free the memory

    return 0;
}
