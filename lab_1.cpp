// От пользователя требуется ввести начальную точку и шаг

#include <iostream>
#include<locale.h>

using namespace std;

//Объявление структуры точка
struct Point
{
	double x; // Координата х
	double v; // Координата v
};

//Прототипы функций
double function(double x, double v);
void Method_RK_4(Point& starting_point, double h);


int main()
{
	setlocale(LC_ALL, "Russian");

	Point operating_point;

	// Ввод начальных условий
	cout << "Введите начальную координату Xo исходной точки";
	cin >> operating_point.x;
	cout << "Введите начальную координату Uo исходной точки";
	cin >> operating_point.v;



	// Ввести числовое значение шага
	double h;
	cout << "Введите числовое значение шага?";
	cin >> h;


	// Количество итераций
	int number_of_steps;
	cout << "Сколько сделать шагов?";
	cin >> number_of_steps;

	for (int i = 0; i < number_of_steps; i++)
	{
		cout << "Шаг №" << i << "		" << "X" << i << " = " << operating_point.x << "		" << "V" << i << " = " << operating_point.v << endl;
		Method_RK_4(operating_point, h);

	}

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
void Method_RK_4(Point& starting_point, double h)
{

	// Объявление результирующий точки данного шага
	//Point resulting_point;

	//Объявление и инициализация набора коээфициентов для метода
	double koef1, koef2, koef3, koef4;

	koef1 = function(starting_point.x, starting_point.v);
	koef2 = function(starting_point.x + h / 2, starting_point.v + (h / 2) * koef1);
	koef3 = function(starting_point.x + h / 2, starting_point.v + (h / 2) * koef2);
	koef4 = function(starting_point.x + h, starting_point.v + h * koef3);

	// Вычисление следующей точки
	starting_point.x += h;
	starting_point.v += h * (koef1 + 2 * koef2 + 2 * koef3 + koef4) / 6;



}