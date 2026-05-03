#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

const int MAX_SIZE = 1000;

//Подынтегральная функция
double InFunction(double x)
{
    return 1.0/cos(x);
}

//Первообразная
double F(double x)
{
    double PI = acos(-1.0);
    return log(fabs(tan(x/2 + PI/4)));
}

//Вычисление интеграла на интервале, используя левое правило
double CalcIntegralLeft(double a, double b, int n)
{
    double result = 0.0; //Результат вычислений
    double h = (b-a)/n; //Шаг разбиения
    for (int i = 0; i<=n-1; i++)
    {
        result+=InFunction(a+i*h)*(a+(i+1)*h-(a+i*h));
    }
    return result;
}

//Вычисление интеграла на интервале, используя правило средних точек
double CalcIntegralMiddle(double a, double b, int n)
{
    double result = 0.0; //Результат вычислений
    double h = (b-a)/n; //Шаг разбиения
    for (int i = 0; i<=n-1; i++)
    {
        result+=InFunction((a+(i+1)*h + a+i*h)/2.0)*(a+(i+1)*h-(a+i*h));
    }
    return result;
}

//Нахождение особенностей
void SpecialPoints(double set[MAX_SIZE], int& count, double a, double b)
{
    const double PI = acos(-1.0);
    int k_begin = floor((a-PI/2.0)/PI);
    int k_end = ceil((b-PI/2.0)/PI);
    for (int k = k_begin; k <= k_end; k++)
    {
        double x = PI/2.0 + PI*k;
        if (x>=a-1e-6 && x<=b+ 1e-6)
        {
            set[count]=x;
            count++;
        }
    }
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
    double n_values[] = {100, 200, 400, 800, 1600};
    double prev_I = Trapezoid(a, b, n_values[0]);
    int count = 0;
    int steps = sizeof(n_values)/sizeof(n_values[0]);
    for (int i = 1; i < steps; i++) 
    {
        double curr_I = Trapezoid(a, b, n_values[i]);
        if (prev_I<curr_I)
        {
            count++;
        }
        prev_I = curr_I;
    }
    if (count == steps-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Определение главного значения интеграла по Коши
double IntegralCauchy(double a, double b)
{
    double result = F(b) - F(a);
    return result;
}

int main()
{
    double begin_A, end_A; //Начало и конец интервала А
    double begin_B, end_B; //Начало и конец интервала B
    double begin_C, end_C; //Начало и конец интервала C
    int n, m; //Количество узлов при использовании правила левых и средних точек
    double specialPoints[MAX_SIZE]; //Массив для хранения точек с особенностями
    int countSpecialPoints=0;
    
    //Вывод начальных данных
    cout << "Функция для интегрирования - f(x)=1/cos(x)" << endl;
    cin >> begin_A >> end_A;
    cout << "Интервал А: [" << begin_A << "; " << end_A << "]" << endl;
    cin >> n;
    cin >> m;
    cout << "Количество узлов при использовании левого правила - " << n << endl;
    cout << "Количество узлов при использовании правила средних точек - " << m << endl;
    cin >> begin_B >> end_B;
    cout << "Интервал B: [" << begin_B << "; " << end_B << "]" << endl;
    cin >> begin_C >> end_C;
    cout << "Интервал C: [" << begin_C << "; " << end_C << "]" << endl;

    //Точное значение интеграла на интервале А
    double resultAccurate=F(end_A)-F(begin_A);
    cout << "Точное значение интеграла на интервале [" << begin_A << "; " << end_A << "] равно " << resultAccurate << endl;
    //Левое правило
    double resultLeftRule=CalcIntegralLeft(begin_A,end_A,n);
    cout << "Значение интеграла на интервале [" << begin_A << "; " << end_A << "]" << ", если использовать левое правило для " << n << " узлов, равно " << resultLeftRule << endl;
    //Среднее правило
    double resultMiddleRule=CalcIntegralMiddle(begin_A,end_A,m);
    cout << "Значение интеграла на интервале [" << begin_A << "; " << end_A << "]" << ", если использовать среднее правило для " << m << " узлов, равно " << resultMiddleRule << endl;
    
    //Определение особенностей на интервале В
    SpecialPoints(specialPoints, countSpecialPoints, begin_B, end_B);
    if (countSpecialPoints>0)
    {
        for (int i=0; i<countSpecialPoints; i++)
        {
            cout << i << " точка с особенностью равна " << specialPoints[i] << endl;
        }
    }
    else
    {
        cout << "На интервале [" << begin_B << "; " << end_B << "]" << " нет особенностей" << endl;
    }

    //Проверка на сходимость/расходимость
    bool rashodimost = Rashodimost(begin_B,end_B);
    if (rashodimost)
    {
        cout << "Функция расходится" << endl;
    }
    else
    {
        cout << "Функция сходится" << endl;
    }
    
    double resultCauchy = IntegralCauchy(begin_C, end_C);
    cout << "Главное значение интеграла по Коши на интервале [" << begin_C << "; " << end_C << "] равно" << resultCauchy << endl;
    return 0;
}
