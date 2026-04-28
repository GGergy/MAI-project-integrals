#include <cmath>
#include <iostream>

// функция 1/cos(x)
long double f(const long double x) {
    return 1.0 / std::cos(x);
}

// первообразная ln|tg(x/2 + pi/4)|
long double F(const long double x) {
    return std::log(std::fabs(std::tan(x / 2 + M_PI_4)));
}

// метод трапеций для n узлов
long double trapezoid(const long double a, const long double b, int n) {
    long double h = (b - a) / n;
    long double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        const long double x1 = a + i * h;
        const long double x2 = a + (i + 1) * h;

        sum += 0.5 * (f(x1) + f(x2)) * h;
    }

    return sum;
}

int main() {
    const size_t n = 1e6;
    const long double eps = 1e-6;
    constexpr long double a = 0.0;
    const long double b = M_PI_2 + eps; // Чуть сдвинуто, чтоб проверить при не улетающем в бесконечность значении
    long double ev = F(b) - F(a);

    long double val = trapezoid(a, b, n);
    std::cout << "Exact value: " << ev << std::endl;
    std::cout << "Trapezoid value: " << val << std::endl;
    std::cout << "Diff: " << std::fabs(ev - val) << std::endl;
    // Если результат трапеций отличается от точного не более, чем на эпсилон, то интеграл скорее всего сходится
    if (std::fabs(ev - val) < eps) {
        std::cout << "Shoditsia" << std::endl;
    }
    else {
        std::cout << "Rasshoditsia" << std::endl;
    }

    return 0;

}