#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    double * vector_sum;
    int size;

}cluster;

double* array_copy(double*,const double*, int);
void array_2dim_copy(double **, double **,int ,int );
int array_equal(double** , double** , int ,int ) ;
double diff(const double *,const double* ,int);
int min(const double *, int);
void update_centroid(const double* , cluster*  , int, int );
double** new_centroid(double**,  cluster* , int , int );
cluster* cluster_init(cluster*, int,int);
void reset_cluster(cluster* , int, int );
void print_cents_array(double **,int ,int );

/*initializing clusters*/
cluster* cluster_init(cluster * clusters, int k, int d){
    int i,j;
    for (j=0;j<k; j++){
        cluster c;
        c.size=0;
        c.vector_sum = (double*) malloc(d * sizeof(double));
        assert(c.vector_sum != NULL);
        for (i=0;i<d; i++) {
            c.vector_sum[i] = 0;
        }
        clusters[j] = c;
    }
    return clusters;
}

/*copy array to other array*/
double* array_copy(double* array1,const double* array2,  int d){
    int k;
    for(k=0;k<d;k++){
        array1[k]=array2[k];
    }
    return array1;
}

/*copys 2d array to other 2d array*/
void array_2dim_copy(double **Double, double **Double1,int K,int d) {
    int l,m;
    for(l=0;l<K;l++){
        for(m=0;m<d;m++){
            Double[l][m]=Double1[l][m];
        }
    }
}

/*checks if 2 arrays are equal*/
int array_equal(double** prev_array, double** curr_array, int k,int d) {
    int p,r;
    for (p = 0; p < k; p++) {
        for (r = 0; r < d; r++) {
            if (prev_array[p][r] != curr_array[p][r]) {
                return 0;
            }
        }
    }
    return 1;
}

/*returns the index of the min*/
int min(const double *array, int k) {
    int r, index;
    double min;
    index = 0;
    min = array[0];
    for(r=0;r<k;r++){
        if (array[r] < min){
            index = r;
            min = array[r];
        }
    }
    return index;
}

/*calculates the distance between 2 vectors*/
double diff(const double * vector1,const double * vector2,int d){
    double sum;
    int j;
    sum=0;
    for (j=0;j<d;j++){
        sum+=(vector1[j]-vector2[j])*(vector1[j]-vector2[j]);
    }
    return sum;

}
/*updates the vector_sum field when new vector is added*/
void update_centroid(const double* vector, cluster * clusters,int min_index, int d){
    int q;
    for (q=0;q<d;q++){
        clusters[min_index].vector_sum[q]+=vector[q];
    }

}
/*calculates the new centroids*/
double** new_centroid(double **curr_cent,  cluster* clusters, int k, int d) {
    int i,j;
    for(i=0; i<k; i++){
        for (j=0;j<d;j++){
            curr_cent[i][j] = clusters[i].vector_sum[j]/ (double)clusters[i].size;
        }
    }
    return curr_cent;
}

/*resets the clusters by filling with 0s*/
void reset_cluster(cluster* cluster1, int k,  int d) {
    int x,y;
    for(y=0;y<k;y++) {
        cluster1[y].size=0;
        for (x = 0; x < d; x++) {
            cluster1[y].vector_sum[x] = 0;
        }
    }
}
/*prints the centroides*/
void print_cents_array(double** Double,int K,int d) {
    int x, y;
    for (x = 0; x < K; x++) {
        for (y = 0; y < d; y++) {
            if (y < d - 1) {
                printf("%.4f,", Double[x][y]);
            } else {
                printf("%.4f\n", Double[x][y]);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    int K, max_iter;
    int d = 0;
    int N = 0;
    int cnt;
    int e,m;
    int r;
    int p;
    int i=0;
    int x,b;
    int j;
    int length = 1;
    const char delimiter[2] = ",";
    char* token;
    char* token1;
    char* first_line;
    char* first_line_copy;
    char* vector_string;
    cluster *clusters;
    double **vectors_array;
    double **prev_centroids;
    double **curr_centroids;
    K = atoi(argv[1]);

    if (K <= 0) {
        printf("ERROR");
        return 0;
    }

    if(argc < 4) {
        max_iter = 200;
    }
    else {
        max_iter = atoi(argv[2]);
        if (max_iter <= 0 ) {
            printf("ERROR");
            return 0;
        }
    }

    first_line= (char*) malloc(1000*sizeof(char*));
    assert(first_line != NULL);
    first_line_copy= (char*) malloc(1000*sizeof(char*));
    assert(first_line_copy != NULL);
    vector_string= (char*) malloc(1000*sizeof(char*));
    assert(vector_string != NULL);
    vectors_array = (double **) malloc( sizeof(double *));
    assert(vectors_array != NULL);
    clusters = (cluster*) malloc(K*sizeof (cluster));
    assert(clusters != NULL);
    prev_centroids = (double **) malloc(K * sizeof(double *));
    assert(prev_centroids != NULL);
    curr_centroids = (double **) malloc(K * sizeof(double *));
    assert(curr_centroids != NULL);

    scanf("%s", first_line); /*reading the first line to calculate d*/

    strcpy(first_line_copy,first_line);
    token = strtok(first_line, delimiter);

    while (token != NULL) {
        token = strtok(NULL, delimiter);
        d++;
    }
    N++;
    if (d <= 0) {
        printf("ERROR");
        return 0;
    }

    vectors_array[0] = (double*) malloc(d*sizeof (double));
    assert(vectors_array[0]!=NULL);
    token = strtok(first_line_copy, delimiter);
    while (token != NULL) {
        vectors_array[0][i] = (double) atof(token);
        token = strtok(NULL, delimiter);
        i++;
    }

    while (scanf("%s", vector_string) == 1) { /*reading the input file and filling the vectors array*/
        length++;
        vectors_array =(double**) realloc(vectors_array, length*d*sizeof(double*));
        assert(vectors_array!=NULL);
        vectors_array[N] = (double *) malloc(d * sizeof(double));
        assert(vectors_array[N] != NULL);
        token1 = strtok(vector_string, delimiter);/*split the string*/
        r = 0;
        vectors_array[N][r] = (double) atof(token1);
        cnt = 1;
        while (cnt < d) {
            r++;
            token1 = strtok(NULL, delimiter);
            vectors_array[N][r] = (double) atof(token1); 
            cnt++;
        }
        N++;
    }

    if (N <= K) {
        printf("ERROR");
        return 0;
    }

    clusters = cluster_init(clusters,K,d);

    for (e = 0; e < K; e++) {
        prev_centroids[e] = (double *) malloc(d * sizeof(double));
        assert(prev_centroids[e] != NULL);
        curr_centroids[e] = (double *) malloc(d * sizeof(double));
        assert(curr_centroids[e] != NULL);
        for(m=0;m<d;m++){
            prev_centroids[e][m]=0;
        }
    }


    for(j=0;j<K;j++) {
        clusters[j].vector_sum= array_copy(clusters[j].vector_sum, vectors_array[j], d);
        curr_centroids[j]= array_copy(curr_centroids[j], vectors_array[j], d);
    }

    cnt=0;
    while(cnt < max_iter && !array_equal(curr_centroids,prev_centroids,K,d)){ /*the main function*/
        array_2dim_copy(prev_centroids,curr_centroids,K,d);
        reset_cluster(clusters,K,d);
        for(x=0;x<N;x++) {
            double *distance;
            int min_index;
            distance = (double *)malloc(K* sizeof(double));
            assert(distance!=NULL);
            for (b = 0; b < K; b++) {
                distance[b] = diff(vectors_array[x], prev_centroids[b], d);
            }
            min_index = min(distance, K);
            update_centroid(vectors_array[x],clusters,min_index,d);
            clusters[min_index].size++;
        }
        curr_centroids =new_centroid(curr_centroids,clusters,K,d);
        cnt++;
    }

    print_cents_array(curr_centroids,K,d);

    free(first_line_copy);
    first_line_copy=NULL;

    free(first_line);
    first_line=NULL;

    free(vector_string);
    vector_string=NULL;

    for (p=0 ; p < N; p++) {
        free(vectors_array[p]);
        vectors_array[p] = NULL;
    }
    free(vectors_array);
    vectors_array=NULL;

    for (p=0 ; p < K; p++) {
        free(prev_centroids[p]);
        free(curr_centroids[p]);
        curr_centroids[p] = NULL;
        prev_centroids[p] = NULL;
    }
    free(prev_centroids);
    prev_centroids=NULL;
    free(curr_centroids);
    curr_centroids=NULL;


    for (r=0;r<K; r++){
        free(clusters[r].vector_sum);
        clusters[r].vector_sum = NULL;
    }
    free(clusters);
    clusters=NULL;

    return 1;
}
