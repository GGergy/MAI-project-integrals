## Условие (в моём понимании)

+ Дано (constexpr) - функция $f(x) = 1/cos(x)$ и соответствующая первообразная $F(x) = ln(|tg(\frac x2 + \frac \pi4)|)$
+ Input - интервалы A, B, C; количество узлов в методах n и m
+ Output
  + Вычислить точное значение интеграла на A через первообразную $I = F(b) - F(a)$
  + Вычислить значение на А через левое правило для n узлов ([теория 1](#1-метод-левых-прямоугольников))
  + Вычислить значение на А через правило средних точек для n узлов ([теория 2](#2-метод-средних-прямоугольников))
  + Определить особенности на интервале B ([теория 3](#3-определение-особенностей))
  + Показать отсутствие сходимости, используя, правило трапеций ([теория 4](#4-метод-трапеций))
  + Вычислить главное значение по коши на интервале С ([теория 5](#5-главное-значение-интеграла-по-коши))


## Теория
### 1. Метод левых прямоугольников
+ [Вики](https://ru.wikipedia.org/wiki/Метод_прямоугольников)
+ $\int_{a}^{b} f(x)\,dx \approx \sum_{i=0}^{n-1} f(x_i)(x_{i+1} - x_i)$
+ n - количество узлов, по идее просто бьем интервал на n подынтервалов длиной |A|/n и берем граничные точки как $x_i$

### 2. Метод средних прямоугольников
+ $\int_{a}^{b} f(x)\,dx \approx \sum_{i=0}^{n-1} f(\frac{x_i + x_{i+1}}2)(x_{i+1} - x_i)$
+ То же самое, что и метод левых прямоугольников, только значение функции берется в середине подынтервала

### 3. Определение особенностей
+ Просто найти все вхождения решения уравнения $cos(x) = 0$ $x = \frac \pi2 + \pi k$, в которых функция f(x) не определена, в наш интервал В
+ Нижняя граница k = $\frac {a - \pi/2} \pi$ округление вниз
+ Верхняя граница k = $\frac {b - \pi/2} \pi$ округление вверх
+ Гптшный код, не чекал. Векторы харам
```c++
std::vector<double> singularities(double a, double b) {
    std::vector<double> result;

    double pi = M_PI;

    int k_start = std::floor((a - pi/2) / pi);
    int k_end   = std::ceil((b - pi/2) / pi);

    for (int k = k_start; k <= k_end; ++k) {
        double xk = pi/2 + pi * k;
        if (xk >= a && xk <= b) {
            result.push_back(xk);
        }
    }

    return result;
}
```

### 4. Метод трапеций
+ [Вики](https://ru.wikipedia.org/wiki/Метод_трапеций)
+ $\int_{a}^{b} f(x)\,dx \approx \sum_{i=0}^{m-1} \frac {f(x_i) + f(x_{i+1})}2(x_{i+1} - x_i)$
+ Тут короче полное говно, я хз как это использовать, чтоб показать расходимость. Ну вот на нашем интервале будет что-то типа 1.28269e+13. Но если чуть сдвинуть интервал так, чтоб $\frac \pi2$ там всё равно осталась, уже будет норм цифра без ешки. Гпт предложил вариант с последовательным увеличением количества интервалов разбиения
```c++
#include <iostream>
#include <cmath>

double f(double x) {
    return 1.0 / std::cos(x);
}

double trapezoid(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;

        sum += 0.5 * (f(x1) + f(x2)) * h;
    }

    return sum;
}

int main() {
    double a = 0.0;
    double b = M_PI_2; 
    // Результат - -4.88388e+13, 1.28269e+13, 1.28269e+12
    // Но при b = 2, интеграл всё ещё расходится, но значения будут типа 1.12859, 2.5643, -52.8645
    std::cout << 1 / cos(b) << std::endl;
    for (int n : {100, 1000, 10000}) {
        double val = trapezoid(a, b, n);
        std::cout << "n = " << n << ", integral ~ " << val << "\n";
    }

    return 0;
}
```

### 5. Главное значение интеграла по Коши
+ [Вики](https://ru.wikipedia.org/wiki/Главное_значение_интеграла_по_Коши)
+ $\int_{a}^{c} f(x)\,dx = \lim_{\epsilon \to 0} [\int_{a}^{b - \epsilon}f(x)dx + \int_{b + \epsilon}^{c}f(x)dx]$
+ $[a, c]$ - интервал, b - особая точка
+ Если раскрывать по первообразной, то будет $\lim_{\epsilon \to 0}[F(b - \epsilon) - F(a) + F(c) - F(b - \epsilon)]$
+ У первообразной $F(x) = ln(|tg(\frac x2 + \frac \pi4)|)$ существуют неопределенности в точках
  + $x = \frac \pi2 + 2\pi k$, где $ln(|tg(\frac x2 + \frac \pi4)|) = ln(tg(\frac \pi 2)) = ln(\infty)$
  + $x = -\frac \pi2 + 2\pi k$ где $ln(|tg(\frac x2 + \frac \pi4)|) = ln(tg(\pi)) = ln(0)$
+ В предельном переходе на примере интервала $[0, \pi]$ $$lim_{\epsilon \to 0}[\int_{0}^{\frac \pi2 - \epsilon}\frac {dx}{cosx} + \int_{\frac \pi2 + \epsilon}^{\frac {3\pi}2 - \epsilon}\frac {dx}{cosx} + \int_{\frac {3\pi}2 + \epsilon}^{\pi}\frac {dx}{cosx}] =$$
$$= \lim_{\epsilon \to 0}[F(\frac \pi2 - \epsilon) - F(0) + F(\frac {3\pi}2 - \epsilon) - F(\frac \pi2 + \epsilon) + F(\pi) - F(\frac {3\pi}2 + \epsilon)] =$$
$$= F(\pi) - F(0) + \lim_{\epsilon \to 0}[ln(\frac {|tg(\frac {\pi/2 + \pi/2 - \epsilon}2)|}{|tg(\frac {\pi/2 + \pi/2 + \epsilon}2)|}) + ln(\frac {|tg(\frac {3\pi/2 + \pi/2 - \epsilon}2)|}{|tg(\frac {3\pi/2 + \pi/2 + \epsilon}2)|})] =$$
$$= [x = \frac \epsilon2 \Rightarrow x \to 0] = F(\pi) - F(0) + \lim_{x \to 0}[ln(\frac {|tg(\frac \pi2 - x)|}{|tg(\frac \pi2 + x)|}) + ln(\frac {|tg(\pi - x)|}{|tg(\pi + x)|})] =$$
$$= F(\pi) - F(0) + \lim_{x \to 0}[ln(\frac {|ctg(x)|}{|ctg(-x)|}) + ln(\frac {|tg(-x)|}{|tg(x)|})] = $$
$$= F(\pi) - F(0) + \lim_{x \to 0}[ln(1) + ln(1)] =  F(\pi) - F(0)$$
+ Следственно, при подсчете главного значения интеграла $\int\frac {dx}{cosx}$ особые точки нивелируются в предельном переходе и значение определяется как $F(b) - F(a)$