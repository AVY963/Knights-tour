#include <iostream>
#include <ctime>
#include <iomanip>
#define N 8 //для всего кода
using  namespace std;

static int mov1[N] = { 1,1,2,2,-1,-1,-2,-2 };
static int mov2[N] = { 2,-2,1,-1,2,-2,1,-1 };

bool pole(int x, int y)
{
    return (x >= 0) && (y >= 0) && (x < N) && (y < N); // конь не выходит за пределы поля
}

bool empty(int a[], int x, int y)
{
    return (pole(x, y)) && (a[y * N + x] < 0); // посещали ли квадрат, не вышли ли за пределы
}

int getDegree(int a[], int x, int y) // функция возвращает количество пустых клеток, которые находятся рядом, включая диагональ
{
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (empty(a, (x + mov1[i]), (y + mov2[i])))
            count++;
    return count;
}

// Подбираем следующую клетку, которая будет способна привести к минимальному количеству ходов и если не получается найти
// возвращаем false
bool nextMove(int a[], int* x, int* y)
{
    int min_deg_idx = -1, c, min_deg = (N + 1), next_x, next_y; // максимальное кол-во клеток, которые рядом - 9, минимальное - -1(то есть ни одной)
    int start = rand() % N; // начинаем на случайной из клеток, в которые может пойти конь (из 8 возможных)
    for (int count = 0; count < N; ++count)
    {
        int i = (start + count) % N; // выбираем индекс для x и y, чтобы пойти дальше
        next_x = *x + mov1[i];
        next_y = *y + mov2[i];
        if ((empty(a, next_x, next_y)) && (c = getDegree(a, next_x, next_y)) < min_deg) // поиск смежных клеток с минимальной степенью
        {
            min_deg_idx = i;
            min_deg = c;
        }
    }
    if (min_deg_idx == -1) // если не получилось найти след. клетку - возвращаем false
        return false;
    // сохраняем координаты следующей клетки
    next_x = *x + mov1[min_deg_idx];
    next_y = *y + mov2[min_deg_idx];
    //помечаем следующий ход
    a[next_y * N + next_x] = a[(*y) * N + (*x)] + 1;
    // инициализируем x и y ещё раз
    *x = next_x;
    *y = next_y;
    return true;
}
//Вывод поля со всеми доступными ходами коня
void writeboard(int a[])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout <<  "|"  << setw(2) << (a[j * N + i]) << "| " ;

        }
        cout << "\n---------------------------------------\n";

    }
}
// поиск с эвристикой
bool FindSolution()
{
    int a[N * N];
    for (int i = 0; i < N * N; ++i)
        a[i] = -1; // заполняем массив значениями "-1" для дальнейшей работы с номерами ходов

    // Для рандомной инициализации x и y
    /*int x = rand() % N;
    int y = rand() % N;*/

    // Для определенной инициализации x и y
    int x = 5, y = 5;

    a[y * N + x] = 1; // Отмечаем первый ход
    // просчитываем шаги в следующие точки
    for (int i = 0; i < N * N - 1; ++i)
        if (nextMove(a, &x, &y) == false) // если шагов нет - возвращаем false
            return false;
    writeboard(a);
    return true;
}

int main()
{
    unsigned int start_time = clock();
    srand(time(NULL)); // для рандомных чисел
    // до тех пор, пока решение не будет найдено
    while (!FindSolution())
    {
        ;
    }
    cout << "\n";

}
