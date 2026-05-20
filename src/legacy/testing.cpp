#include <iostream>
#include <cmath>

double InFunction(double x)
{
    return 1.0/cos(x);
}

//Правило трапеций
double Trapezoid(double a, double b, int n)
{
    double h = (b-a)/n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum+=(InFunction(a+i*h) + InFunction(a+(i+1)*h))/2*h;
    }
    return sum;
}

//Определение расходимости с помощью правила трапеций
bool Rashodimost(double a, double b) {
    const double acceptable_eps = 0.1;
    int cur_n = 100;
    double prev_I = Trapezoid(a, b, cur_n);
    const int max_steps = 7;

    for (int i = 1; i < max_steps; i++)
    {
        cur_n *= 2;
        const double curr_I = Trapezoid(a, b, cur_n);
        std::cout << "n = " << cur_n << "; I = " << curr_I << std::endl;
        // Процентное отклонение от предыдущего результата
        std::cout << "Gosha's metric: " << fabs(1 - curr_I / prev_I) << std::endl;
        if (fabs(1 - curr_I / prev_I) < acceptable_eps)
        {
            return false;
        }
        prev_I = curr_I;
    }
    return true;
}


int main() {
    double a, b;
    //std::cin >> a >> b;
    a = 0;
    b = M_PI - 0.02 ;

    bool R = Rashodimost(a, b);
    if (R) {
        std::cout << "Rashod detected";
    }
    else {
        std::cout << "Rashod not detected";
    }
}