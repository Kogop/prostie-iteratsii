#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
class Matr
{
private:
    double eps = 0.001;
    static const int n = 4;
    double masA[n][n] = { { 0.05, -0.06, -0.12, 0.14 },
                          { 0.04, -0.12, 0.68, 0.11 },
                          { 0.34, 0.08, -0.06, 0.44 },
                          { 0.11, 0.12, -0.03, -0.8 } };

    double masB[n] = { -2.17, 1.4, -2.1, -0.8 };

public:

    void Itera()
    {
        double x[n];
        double x0[n];
        double E[n];
        double max = 0;

        for (int i = 0; i < n; i++)
            x0[i] = masB[i];
        int counter = 0;
        do
        {
            for (int i = 0; i < n; i++)
            {
                x[i] = 0;
                for (int j = 0; j < n; j++)
                {
                    x[i] += masA[i][j] * x0[j];
                }
                x[i] += masB[i];
                E[i] = fabs(x[i] - x0[i]);
            }
            max = 0;
            int i;
            for (i = 0; i < n; i++)
            {
                if (max < E[i]) max = E[i];
                x0[i] = x[i];
            }
            counter++;
        } while (max > eps);
        cout << endl << "Kol iter: " << counter << endl << endl;
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << "=" << x[i] << " " << endl;
    }
};



int main() {
    Matr T;

    T.Itera();

}