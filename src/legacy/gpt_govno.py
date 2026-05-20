import numpy as np

def f(x):
    return 1 / np.cos(x)

# точный интеграл
def exact_integral(a, b):
    def F(x):
        return np.log(np.abs(1/np.cos(x) + np.tan(x)))
    return F(b) - F(a)

# левое правило
def left_rect(a, b, n):
    h = (b - a) / n
    x = np.linspace(a, b - h, n)
    return h * np.sum(f(x))

# средние точки
def midpoint(a, b, n):
    h = (b - a) / n
    x = a + (np.arange(n) + 0.5) * h
    return h * np.sum(f(x))

# трапеции
def trapezoid(a, b, n):
    h = (b - a) / n
    x = np.linspace(a, b, n+1)
    return h * (0.5*f(x[0]) + np.sum(f(x[1:-1])) + 0.5*f(x[-1]))

# главное значение (численно с разрывом)
def cauchy_pv(a, b, n, eps=1e-6):
    mid = np.pi/2
    left = np.linspace(a, mid - eps, n)
    right = np.linspace(mid + eps, b, n)
    return np.trapz(f(left), left) + np.trapz(f(right), right)


# параметры
A = (0, np.pi/4)
B = (0, np.pi/2)
C = (0, 3*np.pi/4)

n = 5
m = 8

print("Точный интеграл A:", exact_integral(*A))
print("Левые прямоугольники:", left_rect(*A, n))
print("Средние точки:", midpoint(*A, n))
print("Трапеции на B (расходится):", trapezoid(*B, n))
print("PV на C:", cauchy_pv(*C, m))