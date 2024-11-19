#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <unordered_set>
#include <ios>
#include <list>


template <typename T>
class FIFOCache
{
	int misses = 0;
	int hits = 0;
	std::unordered_set<T> processed_data;

public:
	int size;
	std::string filename;
	std::list<T> cache;

	FIFOCache(std::list<T> datalist, int s, std::string name); //вызвать алгоритм кэша. передаем данные для обработки в виде массива, максимальный размер кэша, названия файла, в который скидываем все, что не уместилось в кэш

	bool FindInFile(std::string filename, T value); //поиск в файле
	bool FindInCache(const std::list<T>& cache, T value); //поиск в кэше
	void ReplaceInCache(T value, int id, std::string& filename, std::list<T>& cache); //вытеснение из кэша в файл и замена на новое значение
	bool CheckIfProcessed(T value, const std::unordered_set<T>& processed_data); //проверка на то, было ли вообще обработан этот объект
	void CacheFilling(std::list<T>& data, T value, int size, int& id, std::string filename);
	void Processing(FIFOCache& FIFO, std::list<T>& datalist);
};

template<typename T>
inline FIFOCache<T>::FIFOCache(std::list<T> datalist, int s, std::string name)
{
	size = s;
	filename = name;
}

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
			file.close();
			return 1;
		}
	}
}

template<typename T>
inline bool FIFOCache<T>::FindInCache(const std::list<T>& cache, T value)
{
	if (cache.empty())
	{
		std::cout << "Cache is empty" << std::endl;
		return 0;
	}
	for (const auto& search : cache)
	{
		if (search == value)
		{
			return 1;
		}
	}
}

template<typename T>
inline void FIFOCache<T>::ReplaceInCache(T value, int id, std::string& filename, std::list<T>& cache)
{
	std::ifstream file(filename, std::ios::app);
	file << cache[id] << std::endl;
	file.close();
	cache[id] = value;
}

template<typename T>
inline bool FIFOCache<T>::CheckIfProcessed(T value, const std::unordered_set<T>& processed_data)
{
	if (processed_data.contains(value))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline void FIFOCache<T>::CacheFilling(std::list<T>& cache, T value, int size, int& id, std::string filename)
{
	if (cache.size() == size)
	{
		ReplaceInCache(value, filename, cache);
		id = ((id + 1) == size) ? 0: id + 1;
	}
	else
	{
		cache.push_back(value);
		id++;
	}
}

template<typename T>
inline void FIFOCache<T>::Processing(FIFOCache& FIFO, std::list<T>& data)
{
	auto start = std::chrono::high_resolution_clock::now();
	int id = 0;
	for (const auto& s : data)
	{
		if (CheckIfProcessed(s, FIFO.processed_data))
		{
			if (FindInCache(FIFO.cache, s))
			{
				FIFO.hits++;
			}
			else
			{
				FindInFile(filename, s);
				FIFO.misses++;
				CacheFilling(FIFO.cache, s, FIFO.size, id, FIFO.filename);
			}
		}
		else
		{
			CacheFilling(FIFO.cache, s, FIFO.size, id, FIFO.filename);
			processed_data.insert(s);
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto overall_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << "Processing time: " << overall_time.count() << std::endl;
	std::cout << "Cache hits: " << FIFO.hits << std::endl;
	std::cout << "Cache misses " << FIFO.misses << std::endl;
}




