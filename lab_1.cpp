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
void Test_Task(void);
void Test_Task_control(void);
Point initialization_point(void);


int main()
{
	setlocale(LC_ALL, "Russian");

	//Test_Task();
	Test_Task_control();

	return 0;
}


/*
	--- Функция для рассчетов тестовой задачи
	--- Вариант 4
	--- 2U
 */
double function(double x, double v)
{
	return 2 * v;
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

void Test_Task(void)
{

	// Инициализация стартовой точки и ввод значений
	Point operating_point = initialization_point();


	// Ввести числовое значение шага
	double h;
	cout << "Введите числовое значение шага?" << endl;
	cin >> h;


	// Количество итераций
	int number_of_steps;
	cout << "Сколько сделать шагов?" << endl;
	cin >> number_of_steps;

	for (int i = 0; i < number_of_steps; i++)// While(X)||(iter)
	{
		cout << "№" << i << "		" << "X" << i << " = " << operating_point.x << "		" << "V" << i << " = " << operating_point.v << endl;
		operating_point = Method_RK_4(operating_point, h);

	}
}

void Test_Task_control(void)
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
	int number_of_steps;
	cout << "Сколько сделать шагов?";
	cin >> number_of_steps;

	for (int i = 0; i < number_of_steps; i++)
	{
		cout << "№" << i << "  " << "Шаг = " << h << "  " << "X" << i << " = " << current_point.x << "  " << "V" << i << " = " << current_point.v << endl;

		// (Xn+1,Vn+1)
		Point next_point = Method_RK_4(current_point, h);

		// (Xn+1/2,Vn+1/2)
		Point next_point_half = Method_RK_4(current_point, h / 2);

		// (Xn+1,^Vn+1)
		Point next_point_cap = Method_RK_4(next_point_half, h / 2);

		// Число для сравнения с числом контроля локальной погрешности
		double S = (next_point_cap.v - next_point.v) / (pow(2, order) - 1);

		if ((abs(S) >= Eps / (pow(2, order + 1))) && (abs(S) <= Eps))
		{
			current_point = next_point;
		}

		if (abs(S) < Eps / (pow(2, order + 1)))
		{
			current_point = next_point;
			h = 2 * h;
		}

		if (abs(S) > Eps)
		{
			h = h / 2;
		}

	}
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