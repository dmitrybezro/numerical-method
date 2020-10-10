// От пользователя требуется ввести начальную точку и шаг

#include <iostream>
#include<locale.h>
#include <math.h>

using namespace std;

//Объявление структуры точка
struct Point
{
	double x; // Координата х
	double v; // Координата v
};

//Прототипы функций
double function(double x, double v);
Point Method_RK_4(Point& starting_point, double h);
void Task(void);
void Task_control(void);
Point initialization_point(void);

// Костыль для выбора задачи
int select_task;

int main()
{
	setlocale(LC_ALL, "Russian");

	//Выбор задачи задачи( Пока только тест и первая)
	cout << "Выбор задачи" << endl;
	cout << "1 - основная первая" << endl;
	cout << "2 - тестовая" << endl;
	cin >> select_task;

	//Выбор метода решения (с контролем ЛП или без)
	int control;
	cout << "Решить задачу" << endl;
	cout << "0 - без контроля локальной погрешности" << endl;
	cout << "1 - с контролем локальной погрешности" << endl;
	cin >> control;

	if (control)
		Task_control();
	else
		Task();

	return 0;
}


/*
	--- Функция для рассчетов тестовой задачи
	--- Вариант 4
	--- 2U
 */
double function(double x, double v)
{
	if (select_task == 2)
		return 2 * v;
	if (select_task == 1)
		return ((pow(x, 3)) / (pow(x, 5))) * pow(v, 2) + v - pow(v, 3) * sin(10 * x);
}

//Метод Рунге-Кутта 4го порядка
Point Method_RK_4(Point& starting_point, double h)
{

	// Объявление результирующий точки данного шага
	Point resulting_point;

	//Объявление и инициализация набора коээфициентов для метода
	double koef1, koef2, koef3, koef4;

	koef1 = function(starting_point.x, starting_point.v);
	koef2 = function(starting_point.x + h / 2, starting_point.v + (h / 2) * koef1);
	koef3 = function(starting_point.x + h / 2, starting_point.v + (h / 2) * koef2);
	koef4 = function(starting_point.x + h, starting_point.v + h * koef3);

	// Вычисление следующей точки
	starting_point.x += h;
	starting_point.v += h * (koef1 + 2 * koef2 + 2 * koef3 + koef4) / 6;

	//Присвоение значения и возврат результирующей точки
	resulting_point.x = starting_point.x;
	resulting_point.v = starting_point.v;
	return resulting_point;

}

void Task(void)
{

	// Инициализация стартовой точки и ввод значений
	Point operating_point = initialization_point();


	// Ввести числовое значение шага
	double h;
	cout << "Введите числовое значение шага?" << endl;
	cin >> h;


	// Количество итераций
	int max_steps;
	cout << "Введите максимально возможное число итераций?" << endl;
	cin >> max_steps;

	// Граница Х и V
	double Xmax;
	cout << "Введите границу Х" << endl;
	cin >> Xmax;

	for (int i = 0; (i < max_steps) && (operating_point.x < Xmax); i++)
	{
		cout << "№" << i << "	";
		cout << "X" << i << " = " << operating_point.x << "	";
		cout << "V" << i << " = " << operating_point.v << endl;
		operating_point = Method_RK_4(operating_point, h);

	}
}

void Task_control(void)
{
	// Порядок метода
	const double order = 4;

	// Инициализация стартовой точки и ввод значений
	// (Xn,Vn)
	Point current_point = initialization_point();


	// Ввести числовое значение шага
	double h;
	cout << "Введите начальное числовое значение шага?" << endl;
	cin >> h;

	// Определение числа контроля локальной погрешности
	double Eps;
	cout << "Введите число контроля локальной погрешности" << endl;
	cin >> Eps;

	// Количество итераций
	int max_steps;
	cout << "Введите максимально возможное число итераций?" << endl;
	cin >> max_steps;

	// Граница Х и V
	double Xmax;
	cout << "Введите границу Х" << endl;
	cin >> Xmax;

	// Счетчики увеличения и уменьшения шага
	double reduct_step = 0;
	double decrease_step = 0;

	// Максимальная оценка локальной погрешности
	double max_OLP = 0;

	// Минимальный и максимальный шаг при Х
	// Задается точкой, где x - это х, а v - это шаг
	Point max_h;
	max_h.v = 0;
	int i_max;
	Point min_h;
	min_h.v = h;
	int i_min;

	// Для тестовой задачи
	// v - max|Ui - Vi| , а x - это x
	int i_max_test = 0;
	Point max_uv;
	max_uv.v = 0;

	int i;
	for (i = 0; (i < max_steps) && (current_point.x < Xmax); i++)
	{

		// (Xn+1,Vn+1)
		Point next_point = Method_RK_4(current_point, h);

		// (Xn+1/2,Vn+1/2)
		Point next_point_half = Method_RK_4(current_point, h / 2);

		// (Xn+1,^Vn+1)
		Point next_point_cap = Method_RK_4(next_point_half, h / 2);

		// Число для сравнения с числом контроля локальной погрешности
		double S = (next_point_cap.v - next_point.v) / (pow(2, order) - 1);

		// Оценка локальной погрешности
		double OLP = S * pow(2, order);

		if (fabs(OLP) > max_OLP)
			max_OLP = OLP;

		// Определения максимума и минимума шага
		if (max_h.v <= h)
		{
			max_h.v = h;
			max_h.x = current_point.x;
			i_max = i;
		}
		if (min_h.v >= h)
		{
			min_h.v = h;
			min_h.x = current_point.x;
			i_min = i;
		}

		// Вывод данных
		if (i % 10 == 0)
			cout << endl;
		cout << i << "  " << "X" << i << "=" << current_point.x << "  " << "V" << i << "=" << current_point.v;
		cout << i << "  " << "(V2)" << i << "=" << next_point_cap.v << "  " << "V" << i << " -(V2)" << i << "=" << current_point.v - next_point_cap.v << "  ";
		cout << "OLP=" << OLP << "  " << "h" << i << "=" << h << "  ";
		cout << "C1=" << reduct_step << "  " << "C2=" << decrease_step << "  ";
		if (select_task == 2)
		{
			cout << "U" << i << function(current_point.x, current_point.v) << "  ";
			cout << "|U" << i << "-V" << i << "|=" << fabs(function(current_point.x, current_point.v) - current_point.v) << endl;

			if (fabs(function(current_point.x, current_point.v) - current_point.v) > max_uv.v)
			{
				max_uv.v = fabs(function(current_point.x, current_point.v) - current_point.v);
				max_uv.x = current_point.x;
				i_max_test = i;
			}
		}
		else
			cout << endl;

		if ((fabs(S) >= Eps / (pow(2, order + 1))) && (fabs(S) <= Eps))
		{
			current_point = next_point;
		}

		if (fabs(S) < Eps / (pow(2, order + 1)))
		{
			current_point = next_point;
			h = 2 * h;
			reduct_step++;
		}

		if (fabs(S) > Eps)
		{
			h = h / 2;
			decrease_step++;
		}

	}

	// Выходные данные программы
	cout << "n = " << i + 1 << endl;
	cout << "Xmax - X" << i << " = " << Xmax - current_point.x << endl;
	cout << "max |ОЛП| = " << max_OLP << endl;
	cout << "Общее число удвоения шага :  " << reduct_step << endl;
	cout << "Общее число деления шага :  " << decrease_step << endl;
	cout << "Максимальный шаг h" << i_max << " = " << max_h.v << " при Х = " << max_h.x << endl;
	cout << "Минимальный шаг h" << i_min << " = " << min_h.v << " при Х = " << min_h.x << endl;

	// + Для тестовой задачи
	if (select_task == 2)
		cout << "max| U" << i_max_test << " - V" << i_max_test << " | = " << max_uv.v << " при x = " << max_uv.x << endl;
}

Point initialization_point(void)
{
	Point baze_point;

	// Ввод начальных условий
	cout << "Введите начальную координату Xo исходной точки" << endl;
	cin >> baze_point.x;
	cout << "Введите начальную координату Uo исходной точки" << endl;
	cin >> baze_point.v;

	return baze_point;
}