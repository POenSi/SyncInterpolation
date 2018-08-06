#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>

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




    ifstream input("input.txt");
    long fullSize = 1000000;
    auto *initial = (double *) malloc(fullSize * sizeof(double));

    unsigned int lineCount = 0;
    for (string line; getline(input, line);) {
        double d;
        input >> d;
        initial[lineCount] = d;
        lineCount++;
    }
    input.close();
    cout << lineCount << "\n";

    const clock_t start = clock();

    unsigned int initialSize = lineCount;
    unsigned int discretization = 50;
    unsigned int calculationHalfWidth = 200;
    double T = discretization;
    int discretizationLength = initialSize * discretization;


    auto *interpolated = (double *) malloc(discretizationLength * sizeof(double));


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


    clock_t now = clock();
    clock_t delta = now - start;
    double milliSecondsElapsed = static_cast<double>(delta) / CLOCKS_PER_SEC * 1e3;
    cout << "calculation time " << milliSecondsElapsed << " ms\n";



    file2.close();

    ofstream file;
    file.open("file.txt");
    file.precision(10);
    file.setf(ios::fixed);
    file.setf(ios::showpoint);

    for (int i = 0; i < discretizationLength; i++) {
        file << interpolated[i] << "\n";
    }

    file.close();

    return 0;
}