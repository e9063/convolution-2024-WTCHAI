#include<stdio.h>
#include<stdlib.h>
#include <omp.h> 

int main(){

    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here
    omp_set_num_threads(4);

    // FF initialize creating reverse array of F
    int *FF = malloc(sizeof(int) *NF) ; 
    for ( int i = 0 ; i < NF ; i++) { 
        FF[i] = F[NF-i-1] ; 
    }
    // printf("FF reverse list :  ")  ; 
    // for (int i = 0 ; i < NF ; i++){
    //     printf("%d ", FF[i]) ;
    // }

    // Convolution logic implementation
    // Initialize R as a result array
    int *R = malloc(sizeof(int) * (NA - NF + 1)) ;

    double start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i <= NA - NF; i++) {
        R[i] = 0; 
        for (int j = 0; j < NF; j++) {
            R[i] += A[i + j] * FF[j]; 
        }
    }
    double end_time = omp_get_wtime();
    printf("Parallel execution time: %f seconds\n", end_time - start_time);


    for (int i = 0 ; i <= NA - NF ; i++){
        printf("%d\n", R[i]) ;
    }
    // ---- free memory ----
    free(FF);
    free(F);
    free(A);
    free(R);
    // ---- end free ----
    return 0;
}

