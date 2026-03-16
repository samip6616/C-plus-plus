#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "Enter number of observations: ";
    cin >> n;

    vector<double> x(n), y(n);
    double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    double sum_y = 0, sum_xy = 0, sum_x2y = 0;

    cout << "Enter x values:" << endl;
    for (int i = 0; i < n; i++)
        cin >> x[i];
    cout << "Enter y values:" << endl;
    for (int i = 0; i < n; i++)
        cin >> y[i];

    // Calculate all required sums
    for (int i = 0; i < n; i++) {
        double xi = x[i], yi = y[i];
        sum_x   += xi;
        sum_x2  += xi * xi;
        sum_x3  += xi * xi * xi;
        sum_x4  += xi * xi * xi * xi;
        sum_y   += yi;
        sum_xy  += xi * yi;
        sum_x2y += xi * xi * yi;
    }

    // Form augmented matrix for normal equations
    double A[3][4] = {
        {n,      sum_x,   sum_x2,  sum_y},
        {sum_x,  sum_x2,  sum_x3,  sum_xy},
        {sum_x2, sum_x3,  sum_x4,  sum_x2y}
    };

    // Gaussian elimination (forward elimination)
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            double ratio = A[j][i] / A[i][i];
            for (int k = i; k < 4; k++)
                A[j][k] -= ratio * A[i][k];
        }
    }

    // Back substitution
    double a = A[2][3] / A[2][2];
    double b = (A[1][3] - A[1][2] * a) / A[1][1];
    double c = (A[0][3] - A[0][2] * a - A[0][1] * b) / A[0][0];

    cout << "\n=== Quadratic Fit Results ===" << endl;
    cout << "Quadratic equation: y = " << a << " x^2 + " << b << " x + " << c << endl;
    cout << "Coefficient a = " << a << endl;
    cout << "Coefficient b = " << b << endl;
    cout << "Constant c = " << c << endl;

    return 0;
}
