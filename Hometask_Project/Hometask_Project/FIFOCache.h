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

	FIFOCache(std::list<T> datalist, int s, std::string name); //������� �������� ����. �������� ������ ��� ��������� � ���� �������, ������������ ������ ����, �������� �����, � ������� ��������� ���, ��� �� ���������� � ���

	bool FindInFile(std::string filename, T value); //����� � �����
	bool FindInCache(const std::list<T>& cache, T value); //����� � ����
	void ReplaceInCache(T value, int id, std::string& filename, std::list<T>& cache); //��������� �� ���� � ���� � ������ �� ����� ��������
	bool CheckIfProcessed(T value, const std::unordered_set<T>& processed_data); //�������� �� ��, ���� �� ������ ��������� ���� ������
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
