#include <iostream>
#include <pthread.h>
#include <ctime>
#include <cstdlib>

// Maximum size of matrix
#define MAX 4
// Maximum number of threads
#define MAX_THREAD 4
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

void* multi(void* arg) {
    int i = step_i++; // i denotes row number of resultant matC
    for (int j = 0; j < MAX; j++)
        for (int k = 0; k < MAX; k++)
            matC[i][j] += matA[i][k] * matB[k][j];
    return nullptr;
}

// Driver Code
int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(0)));

    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    // Displaying matA
    std::cout << std::endl << "Matrix A" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            std::cout << matA[i][j] << " ";
        std::cout << std::endl;
    }

    // Displaying matB
    std::cout << std::endl << "Matrix B" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            std::cout << matB[i][j] << " ";
        std::cout << std::endl;
    }

    // Declaring four threads
    pthread_t threads[MAX_THREAD];

    // Creating four threads, each evaluating its own part
    for (int i = 0; i < MAX_THREAD; i++) {
        int* p = nullptr;
        pthread_create(&threads[i], nullptr, multi, (void*)(p));
    }

    // Joining and waiting for all threads to complete
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], nullptr);

    // Displaying the result matrix
    std::cout << std::endl << "Multiplication of A and B" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            std::cout << matC[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}
