#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <unordered_set>
#include <ios>
#include <list>
#include <deque>
#include <algorithm>


template <typename T>
class FIFOCache
{
	int misses = 0;
	int hits = 0;
	int total_operations = 0;
	std::unordered_set<T> processed_data;

public:
	int size;
	std::string filename;
	std::deque<T> cache;

	FIFOCache(int s, std::string name); 

	bool FindInFile(std::string filename, T value); 
	bool FindInCache(const std::deque<T>& cache, T value); 
	void ReplaceInCache(T value, std::string& filename, std::deque<T>& cache); 
	bool CheckIfProcessed(T value, const std::unordered_set<T>& processed_data); 
	void CacheFilling(std::deque<T>& data, T value, int size, std::string filename, int& total_operations);
	void Processing(FIFOCache& FIFO, const std::list<T>& datalist);
	int getHits() const { return hits; }
	int getMisses() const { return misses; }
	std::unordered_set<T> getProcessed_data() const { return processed_data; };
};

template<typename T>
inline FIFOCache<T>::FIFOCache( int s, std::string name)
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
	std::string search;
	while (std::getline(file, search))
	{
		if (search == std::to_string(value))
		{
			file.close();
			return 1;
		}
	}
}

template<typename T>
inline bool FIFOCache<T>::FindInCache(const std::deque<T>& cache, T value)
{
	if (cache.empty())
	{
		std::cout << "Cache is empty" << std::endl;
		return 0;
	}
	if (std::find(cache.begin(), cache.end(), value) != cache.end())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline void FIFOCache<T>::ReplaceInCache(T value, std::string& filename, std::deque<T>& cache)
{
	std::ofstream file(filename, std::ios::app);
	file << cache.front() << std::endl;
	file.close();
	cache.pop_front();
	cache.push_back(value);
}

template<typename T>
inline bool FIFOCache<T>::CheckIfProcessed(T value, const std::unordered_set<T>& processed_data)
{
	if (processed_data.count(value))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline void FIFOCache<T>::CacheFilling(std::deque<T>& cache, T value, int size, std::string filename, int& total_operations)
{
	if (cache.size() == size)
	{
		ReplaceInCache(value, filename, cache);
		total_operations = total_operations + 2;
	}
	else
	{
		cache.push_back(value);
	}
}

template<typename T>
inline void FIFOCache<T>::Processing(FIFOCache& FIFO, const std::list<T>& data)
{
	for (const auto& s : data)
	{
		if (CheckIfProcessed(s, FIFO.processed_data))
		{
			if (FindInCache(FIFO.cache, s))
			{
				FIFO.hits++;
				FIFO.total_operations++;
			}
			else
			{
				FindInFile(filename, s);
				total_operations++;
				FIFO.misses++;
				CacheFilling(FIFO.cache, s, FIFO.size, FIFO.filename, FIFO.total_operations);
			}
		}
		else
		{
			CacheFilling(FIFO.cache, s, FIFO.size, FIFO.filename, FIFO.total_operations);
			processed_data.insert(s);
		}
	}
	std::cout << "Total operations: " << FIFO.total_operations << std::endl;
}