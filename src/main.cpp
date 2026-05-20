// Final version by Big Boss Gosha

#include <iostream>
#include <cmath>

using namespace std;


//Чтение интервала
void ReadInterval(double &a, double &b, char interval);
//Чтение количества узлов
void ReadKnot(int &knot, const char *pravilo);
//Подынтегральная функциям
double InFunction(double x);
//Первообразная
double F(double x);
//Вычисление интеграла на интервале, используя левое правило
double CalcIntegralLeft(double a, double b, int n);
//Вычисление интеграла на интервале, используя правило средних точек
double CalcIntegralMiddle(double a, double b, int n);
//Нахождение особенностей
void SpecialPoints(double *set, int size_lim, int &count, double a, double b);
//Правило трапеций
double Trapezoid(double a, double b, int n);
//Определение расходимости с помощью правила трапеций
bool Rashodimost(double a, double b);
//Определение главного значения интеграла по Коши
double IntegralCauchy(double a, double b);


int main() {

    setlocale(LC_ALL, "Russian");
    const int MAX_SIZE = 1000;

    double begin_A, end_A; //Начало и конец интервала А
    double begin_B, end_B; //Начало и конец интервала B
    double begin_C, end_C; //Начало и конец интервала C
    int n, m; //Количество узлов при использовании правила левых и средних точек
    double specialPoints[MAX_SIZE]; //Массив для хранения точек с особенностями
    int countSpecialPoints = 0;

    //Чтение и печать начальных данных
    cout << "Функция для интегрирования: f(x)=1/cos(x)" << endl;
    ReadInterval(begin_A, end_A, 'A');
    ReadKnot(n, "левых");
    ReadKnot(m, "средних");
    ReadInterval(begin_B, end_B, 'B');
    ReadInterval(begin_C, end_C, 'C');

    //Точное значение интеграла на интервале А
    double resultAccurate = F(end_A) - F(begin_A);
    cout << "Точное значение интеграла на интервале [" << begin_A << "; " << end_A << "] равно " << resultAccurate <<
            endl;
    //Левое правило
    double resultLeftRule = CalcIntegralLeft(begin_A, end_A, n);
    cout << "Значение интеграла на интервале [" << begin_A << "; " << end_A << "]" <<
            ", если использовать левое правило для " << n << " узлов, равно " << resultLeftRule << endl;
    //Среднее правило
    double resultMiddleRule = CalcIntegralMiddle(begin_A, end_A, m);
    cout << "Значение интеграла на интервале [" << begin_A << "; " << end_A << "]" <<
            ", если использовать среднее правило для " << m << " узлов, равно " << resultMiddleRule << endl;

    //Определение особенностей на интервале В
    SpecialPoints(specialPoints, MAX_SIZE, countSpecialPoints, begin_B, end_B);
    if (countSpecialPoints > 0) {
        for (int i = 0; i < countSpecialPoints; i++) {
            cout << i + 1 << " точка с особенностью равна " << specialPoints[i] << endl;
        }
    } else {
        cout << "На интервале [" << begin_B << "; " << end_B << "]" << " нет особенностей" << endl;
    }

    //Проверка на сходимость/расходимость
    if (Rashodimost(begin_B, end_B)) {
        cout << "Функция расходится" << endl;
    } else {
        cout << "Функция сходится" << endl;
    }

    double resultCauchy = IntegralCauchy(begin_C, end_C);
    cout << "Главное значение интеграла по Коши на интервале [" << begin_C << "; " << end_C << "] равно " <<
            std::fixed << resultCauchy << endl;
    return 0;
}


//Чтение интервала
void ReadInterval(double &a, double &b, char interval) {
    do {
        cout << "Введите начало интервала " << interval << ": ";
        cin >> a;
        cout << "Введите конец интервала " << interval << ": ";
        cin >> b;
        if (a > b) {
            cout << "Ошибка: начало интервала не может быть больше конца. Повторите ввод, пожалуйста" << endl;
        }
    } while (a > b);
    cout << "Интервал " << interval << ": [" << a << "; " << b << "]" << endl;
}

//Чтение количества узлов
void ReadKnot(int &knot, const char *pravilo) {
    double temp;
    do {
        cout << "Введите количество узлов для правила " << pravilo << " точек: ";
        cin >> temp;
        if (temp <= 0 || fabs(temp - round(temp)) > 1e-12) {
            cout << "Ошибка: количество узлов должно быть натуральным числом. Повторите ввод, пожалуйста" << endl;
        }
    } while (temp <= 0 || fabs(temp - round(temp)) > 1e-12);
    knot = (int) round(temp);
    cout << "Количество узлов при использовании правила " << pravilo << " точек - " << knot << endl;
}

//Подынтегральная функциям
double InFunction(double x) {
    return 1.0 / cos(x);
}

//Первообразная
double F(double x) {
    return log(fabs(tan(x / 2 + M_PI_4)));
}

//Вычисление интеграла на интервале, используя левое правило
double CalcIntegralLeft(double a, double b, int n) {
    double result = 0.0; //Результат вычислений
    double h = (b - a) / n; //Шаг разбиения
    for (int i = 0; i < n; i++) {
        result += InFunction(a + i * h) * h;
    }
    return result;
}

//Вычисление интеграла на интервале, используя правило средних точек
double CalcIntegralMiddle(double a, double b, int n) {
    double result = 0.0; //Результат вычислений
    double h = (b - a) / n; //Шаг разбиения
    for (int i = 0; i <= n - 1; i++) {
        result += InFunction((a + (i + 1) * h + (a + i * h)) / 2.0) * h;
    }
    return result;
}

//Нахождение особенностей
void SpecialPoints(double *set, int size_lim, int &count, double a, double b) {
    int k_begin = floor((a - M_PI_2) / M_PI);
    int k_end = ceil((b - M_PI_2) / M_PI);
    for (int k = k_begin; k <= k_end; k++) {
        double x = M_PI_2 + M_PI * k;
        if (x >= a - 1e-6 && x <= b + 1e-6) {
            set[count] = x;
            count++;
            if (count == size_lim) {
                return;
            }
        }
    }
}

//Правило трапеций
double Trapezoid(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (InFunction(a + i * h) + InFunction(a + (i + 1) * h)) / 2 * h;
    }
    return sum;
}

//Определение расходимости с помощью правила трапеций
bool Rashodimost(double a, double b) {
    const double acceptable_eps = 0.1;
    int cur_n = 100;
    double prev_I = Trapezoid(a, b, cur_n);
    const int max_steps = 7;

    for (int i = 1; i < max_steps; i++) {
        cur_n *= 2;
        const double curr_I = Trapezoid(a, b, cur_n);
        // Процентное отклонение от предыдущего результата
        if (fabs(1 - curr_I / prev_I) < acceptable_eps) {
            // Если дошли до стабилизации результата, то интеграл сходится
            return false;
        }
        prev_I = curr_I;
    }
    return true;
}

//Определение главного значения интеграла по Коши
double IntegralCauchy(double a, double b) {
    double result = F(b) - F(a);
    return result;
}
