#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

const double PI = acos(-1.0);

// f(x) = 1 / cos(x)
double f(double x) {
    return 1.0 / std::cos(x);
}

// точный интеграл: ln|sec x + tan x|
double exact_integral(double a, double b) {
    auto F = [](double x) {
        return std::log(std::fabs(1.0 / std::cos(x) + std::tan(x)));
    };
    return F(b) - F(a);
}

// левое правило прямоугольников
double left_rect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

// метод средних точек
double midpoint(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }
    return h * sum;
}

// трапеции
double trapezoid(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    return h * sum;
}

// главное значение по Коши (разрыв в pi/2)
double cauchy_pv(double a, double b, int n) {
    double eps = 1e-1;
    double mid = PI / 2.0;

    int n2 = n;

    double h1 = (mid - eps - a) / n2;
    double h2 = (b - (mid + eps)) / n2;

    double sum = 0.0;

    // левая часть
    for (int i = 0; i < n2; i++) {
        double x = a + i * h1;
        sum += f(x);
    }
    sum *= h1;

    // правая часть
    for (int i = 0; i < n2; i++) {
        double x = mid + eps + i * h2;
        sum += f(x) * h2;
    }

    return sum;
}

int main() {
    double A1 = 0.0, A2 = PI / 4.0;
    double B1 = 0.0, B2 = PI / 2.0;
    double C1 = 0.0, C2 = 3.0 * PI / 4.0;

    int n = 5;
    int m = 8;

    std::cout << "Exact integral on A: "
              << exact_integral(A1, A2) << "\n";

    std::cout << "Left rectangles (A): "
              << left_rect(A1, A2, n) << "\n";

    std::cout << "Midpoint rule (A): "
              << midpoint(A1, A2, n) << "\n";

    std::cout << "Trapezoid rule (B): "
              << trapezoid(B1, B2, n) << "\n";

    std::cout << "Cauchy principal value (C): "
              << cauchy_pv(C1, C2, m) << "\n";

    return 0;
}