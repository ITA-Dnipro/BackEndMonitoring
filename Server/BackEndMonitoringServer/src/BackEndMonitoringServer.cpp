// BackendMonitoring.cpp : Этот файл содержит функцию "main". Здесь начинается и
// заканчивается выполнение программы.
//
#include "stdafx.h"
#include <fstream>

#include <iostream>
#include "JSONFormatter.h"
#include <vector>
#include "JSONFormatSaver.h"

nlohmann::json TryParse(nlohmann::json buff)
{
	nlohmann::json a = { "disk", buff };

	return a;
}

int main( )
{
	
	std::string ag = "chi";
	nlohmann::json b = nlohmann::json::array({ "capacity", 20, "free_space", 12 });
	nlohmann::json a = { "C:/", b};
	JSONFormatter* ga = JSONFormatter::FactoryJSONFormatter();
	ga->AddNewPair("C:/", b);
	ga->AddNewPair("D:/", b);
	
	std::string p = "info.json";
	JSONFormatSaver saver(p);
	
	saver.TrySaveToFile(*ga);

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и
//   другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый
//   элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий
//   элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" >
//   "Открыть" > "Проект" и выберите SLN-файл.
