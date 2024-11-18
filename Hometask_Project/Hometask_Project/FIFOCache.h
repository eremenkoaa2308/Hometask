#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <unordered_set>
#include <ios>


template <typename T>
class FIFOCache
{
	int misses = 0;
	int hits = 0;
	std::unordered_set<T> processed_data;

public:
	std::list<T> data;
	int size;
	std::string filename;
	std::list<T> cache;

	FIFOCache(std::list<T> datalist, int s, std::string name); //вызвать алгоритм кэша. передаем данные для обработки в виде массива, максимальный размер кэша, названия файла, в который скидываем все, что не уместилось в кэш

	bool FindInFile(std::string filename, T value); //поиск в файле
	bool FindInCache(const std::list<T>& cache, T value); //поиск в кэше
	void ReplaceInCache(T value, int id, std::string& filename, std::list<T>& cache); //вытенения из кэша в файл и замена на новое значение
	bool CheckIfProcessed(T value, const std::unordered_set<T>& processed_data); //проверка на то, было ли вообще обработан этот объект
	void WriteInFile(T value, std::string filename);
};

template<typename T>
inline bool FIFOCache<T>::FindInFile(std::string filename, T value)
{
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "File doesn't exist or broken" << std::endl;
		return 0;
	}
	T search;
	while (std::getline(file, search))
	{
		if (search == value)
		{
			return 1;
		}
	}
}
