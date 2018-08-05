#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double sinc(double x);

double sinc(double x) {
    if (x == 0) {
        return 1;
    } else {
        return sin(x) / x;
    }

}

int main() {

    unsigned int initialSize = 200;
    unsigned int discretization = 50;
    unsigned int calculationHalfWidth = 20;
    double T = 50;
    int discretizationLength = initialSize * discretization;


    auto *initial = (double *) malloc(initialSize * sizeof(double));
    auto *interpolated = (double *) malloc(discretizationLength * sizeof(double));

    for (int i = 0; i < initialSize; i++) {
        if ((i > 50) && (i < 150)) {
            initial[i] = 1;
        } else {
            initial[i] = 0;
        }
    }

    initial[initialSize / 2] = 100;

    ofstream file2;
    file2.open("file2.txt");

    for (int externalIndex = calculationHalfWidth;
         externalIndex < initialSize - calculationHalfWidth; externalIndex++) {
        for (int internalIndex = 0; internalIndex < discretization; internalIndex++) {
            int t = externalIndex * discretization + internalIndex;
            for (int summingIndex = externalIndex - calculationHalfWidth;
                 summingIndex < externalIndex + calculationHalfWidth; summingIndex++) {
                interpolated[t] += initial[summingIndex] * sinc((t - summingIndex * T) / T);
            }

        }
    }


    file2.close();

    ofstream file;
    file.open("file.txt");

    for (int i = 0; i < discretizationLength; i++) {
        file << interpolated[i] << "\n";
    }

    file.close();

    return 0;
}