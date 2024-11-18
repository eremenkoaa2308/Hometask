#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <unordered_set>

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

	bool FindInFile(std::string filename, T value);
	bool FindInCache(const std::list<T>& cache, T value);
	void ReplaceInCache(T value, int id, std::string& filename, std::list<T>& cache);
	bool CheckIfProcessed(T value, const std::unordered_set<T>& processed_data);
};


