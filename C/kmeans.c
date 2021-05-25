#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    float * vector_sum;
    int size;

}cluster;

cluster* cluster_init(cluster *, int,int);
float* array_copy(float*,const float*,  int);
void array_2dim_copy(float **, float **,int ,int );
int array_equal(float** , float** , int ,int ) ;
float diff(const float *,const float * ,int);
int min(const float *, int );
float** new_centroid(float **,  cluster* , int , int );
void update_centroid(const float* , cluster*  , int, int );
void reset_cluster(cluster * , int ,  int );
void print_cents_array(float **,int ,int );

/*initializing clusters*/
cluster* cluster_init(cluster * clusters, int k, int d){
    int i,j;
    for (j=0;j<k; j++){
        cluster c;
        c.size=0;
        c.vector_sum = (float *) malloc(d * sizeof(float));
        assert(c.vector_sum != NULL);
        for (i=0;i<d; i++) {
            c.vector_sum[i] = 0;
        }
        clusters[j] = c;
    }
    return clusters;
}

/*copy array to other array*/
float* array_copy(float* arr1,const float* arr2,  int d){
    int k;
    for(k=0;k<d;k++){
        arr1[k]=arr2[k];
    }
    return arr1;
}

/*copys 2d array to other 2d array*/
void array_2dim_copy(float **pDouble, float **pDouble1,int K,int d) {
    int l,m;
    for(l=0;l<K;l++){
        for(m=0;m<d;m++){
            pDouble[l][m]=pDouble1[l][m];
        }
    }
}

/*checks if 2 arrays are equal*/
int array_equal(float** prev, float** curr, int k,int d) { 
    int p,r;
    for ( p = 0; p < k; p++) {
        for (r = 0; r < d; r++) {
            if (prev[p][r] != curr[p][r]) {
                return 0;
            }
        }
    }
    return 1;
}

/*returns the index of the min*/
int min(const float *arr, int k) {
    int r, index;
    float min;
    index = 0;
    min = arr[0];
    for(r=0;r<k;r++){
        if (arr[r] < min){
            index = r;
            min = arr[r];
        }
    }
    return index;
}

/*calculates the distance between 2 vectors*/
float diff(const float * vec1,const float * vec2,int d){
    float sum;
    int j;
    sum=0;
    for (j=0;j<d;j++){
        sum+=(vec1[j]-vec2[j])*(vec1[j]-vec2[j]);
    }
    return sum;

}
/*updates the vector_sum field when new vector is added*/
void update_centroid(const float* vec, cluster * clusters,int min_index, int d){
    int q;
    for (q=0;q<d;q++){
        clusters[min_index].vector_sum[q]+=vec[q];
    }

}
/*calculates the new centroids*/
float** new_centroid(float **curr_cent,  cluster* clusters, int k, int d) {
    int i,j;
    for(i=0; i<k; i++){
        for (j=0;j<d;j++){
            curr_cent[i][j] = clusters[i].vector_sum[j]/ (float)clusters[i].size;
        }
    }
    return curr_cent;
}

/*resets the clusters by filling with 0s*/
void reset_cluster(cluster * cluster1, int k,  int d) {
    int x,y;
    for(y=0;y<k;y++) {
        cluster1[y].size=0;
        for (x = 0; x < d; x++) {
            cluster1[y].vector_sum[x] = 0;
        }
    }
}
/*prints the centroides*/
void print_cents_array(float **pDouble,int K,int d) {
    int x, y;
    for (x = 0; x < K; x++) {
        for (y = 0; y < d; y++) {
            if (y < d - 1) {
                printf("%.4f,", pDouble[x][y]);
            } else {
                printf("%.4f\n", pDouble[x][y]);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    int K, MAX_ITER;
    int d;
	int N=0;
    int cnt;
    int e,m;
    int r;
    int p;
    int i;
    int x,b;
    int j;
    int length=1;
    const char delimiter[2] = ",";
    char* token;
    char** strings_array;
    char* vector_string=NULL;
    
    float **vectors_array;
    cluster *clusters;
    float **prev;
    float **curr;
    K = atoi(argv[1]);
    MAX_ITER = atoi(argv[2]);
    (void)argc;
    clusters = (cluster *) malloc(K * sizeof(cluster));
    strings_array= (char**) malloc(sizeof(char*));
    vector_string= (char*) malloc(sizeof(char));

    printf("%s","kaki");
    while (scanf("%s", vector_string)==1) {
        length++;
        strings_array = (char **) realloc(strings_array, length * sizeof(char*));
        strings_array[N] = (char *) malloc(sizeof(char *));
        strcpy(strings_array[N],vector_string);
        N++;
    }


    vectors_array = (float **) malloc(N * sizeof(float *));
    prev = (float **) malloc(K * sizeof(float *));
    curr = (float **) malloc(K * sizeof(float *));
    token = strtok(strings_array[0], delimiter);

    d = 0;
    while (token != NULL) {
        token = strtok(NULL, delimiter);
        d++;
    }

    for (e = 0; e < N; e++) {
        vectors_array[e] = (float *) malloc(d * sizeof(float));
        assert(vectors_array[e] != NULL);
    }

    for (e = 0; e < K; e++) {
        prev[e] = (float *) malloc(d * sizeof(float));
        assert(prev[e] != NULL);
        curr[e] = (float *) malloc(d * sizeof(float));
        assert(prev[e] != NULL);
        for(m=0;m<d;m++){
            prev[e][m]=0;
        }
    }

    i=0;
    while (i < N) {
        char* token1;
        int tokenCoun;
        token1 = strtok(strings_array[i], delimiter);
        r = 0;
        printf("%s","kaki");
        vectors_array[i][r] = (float) atof(token1);
        tokenCoun = 1;
        while (tokenCoun < d) {
            printf("%f",vectors_array[i][r]);
            r++;
            token1 = strtok(NULL, delimiter);
            vectors_array[i][r] = (float) atof(token1);
            printf("%f",vectors_array[i][r]);
            tokenCoun++;
        }
        i++;
    }

    clusters = cluster_init(clusters,K,d);
    for(j=0;j<K;j++) {
        clusters[j].vector_sum= array_copy(clusters[j].vector_sum, vectors_array[j], d);
        curr[j]= array_copy(curr[j], vectors_array[j], d);
    }

    cnt=0;
    while(cnt<MAX_ITER && !array_equal(curr,prev,K,d)){
        array_2dim_copy(prev,curr,K,d);
        reset_cluster(clusters,K,d);
        for(x=0;x<N;x++) {
            float *diff1;
            int min_index;
            diff1 = (float *)malloc(K* sizeof(float));
            for (b = 0; b < K; b++) {
                diff1[b] = diff(vectors_array[x], prev[b], d);
            }
            min_index = min(diff1, K);
            update_centroid(vectors_array[x],clusters,min_index,d);
            clusters[min_index].size++;
        }
        curr =new_centroid(curr,clusters,K,d);
        cnt++;
    }

    print_cents_array(curr,K,d);

    free(vector_string);
    vector_string=NULL;

    for (p=0 ; p < N; p++) {
        free(strings_array[p]);
        strings_array[p] = NULL;
    }
    free(strings_array);
    strings_array=NULL;

    for (p=0 ; p < N; p++) {
        free(vectors_array[p]);
        vectors_array[p] = NULL;
    }
    free(vectors_array);
    vectors_array=NULL;

    for (p=0 ; p < K; p++) {
        free(prev[p]);
        free(curr[p]);
        curr[p] = NULL;
        prev[p] = NULL;
    }
    free(prev);
    prev=NULL;
    free(curr);
    curr=NULL;


    for (r=0;r<K; r++){
        free(clusters[r].vector_sum);
        clusters[r].vector_sum = NULL;
    }
    free(clusters);
    clusters=NULL;

    return 1;
}
