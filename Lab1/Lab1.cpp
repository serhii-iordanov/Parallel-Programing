// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "omp.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <intrin.h>

using namespace std;

#pragma region Counters
void ArraySum(int *arr, int n)
{	
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += arr[i];
	}
}

template<class T> void ArraySum2(int n)
{
	T *m = new T[n];
	T sum = 0;
	for (int i = 0; i < n; ++i)
	{
		m[i] = 1 + rand() % 9;
		sum += m[i];
	}
}

template<class T> void MatrixMultiplyingGeneral(int n)
{
	int i, j, l;
	T s(0), res;

	for (i = 0; i<n; i++) {
		for (l = 0; l<n; l++) {
			s = 0;
			for (j = 0; j<n; j++) {
				s += (T)5 * (T)5;
			}
			res = s;
		}
	}
}

unsigned __int64 GetTactsAsm()
{
	__asm
	{
		rdtsc
	}
}

unsigned __int64 GetTactsFunc()
{
	return __rdtsc();
}

void GetCountAndTime(int n, int &count, double &time, double &min)
{
	double begin, end;
	int *m = new int[n];
	for (int i = 0; i < n; ++i)
	{
		m[i] = rand() % 9;
	}

	for (int i = 0; i < 10; ++i)
	{
		begin = omp_get_wtime();
		//begin = (DWORD)GetTactsFunc();
		ArraySum(m, n);
		end = omp_get_wtime();
		//end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}

	begin = GetTickCount();
	while (true)
	{
		++count;
		ArraySum(m, n);
		end = GetTickCount();
		if (end - begin >= 2000)
			break;
	}
}
#pragma endregion

#pragma region Matrix 
class Matrix
{
public:
	int *arr;
	int *arr2;
	int *res;
	int n;
	Matrix(int);
	void Multiply(void);
};

Matrix::Matrix(int length)
{
	Matrix::n = length;
	Matrix::arr = new int[n * n];
	for (int i = 0; i < n * n; ++i)
		Matrix::arr[i] = 1 + rand() % 10;
	Matrix::arr2 = new int[n * n];
	for (int i = 0; i < n * n; ++i)
		Matrix::arr2[i] = 1 + rand() % 10;
	Matrix::res = new int[n * n];
}

void Matrix::Multiply()
{
	int r;
	int indi = 0;
	memset(Matrix::res, 0, Matrix::n * Matrix::n);
	for (int i = 0; i < Matrix::n; ++i)
	{
		for (int j = 0; j < Matrix::n; ++j)
		{
			r = 0;
			for (int k = 0; k < Matrix::n; ++k)
			{
				r += Matrix::arr[indi + k] * Matrix::arr2[k * Matrix::n + j];
			}
			Matrix::res[indi + j] = r;
		}
		indi += Matrix::n;
	}
}


// int arr[10000000][10000000] - define here
void MultiplyMatrix(DWORD n)
{
	unsigned i, j, l;
	DWORD s(0), res;

	for (i = 0; i<n; i++) {
		for (l = 0; l<n; l++) {
			s = 0;
			for (j = 0; j<n; j++) {
				s += 5 * 5;
			}
			res = s;
		}
	}
}

void ExecuteMatrixMultiplying(int n) {
	DWORD begin, end;
	DWORD time, min;
	cout << "N = " << n << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = GetTickCount();
		MultiplyMatrix(n);
		end = GetTickCount();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "Without class = " << min << endl;

	Matrix mat(n);
	for (int i = 0; i < 10; ++i)
	{
		begin = GetTickCount();
		mat.Multiply();
		end = GetTickCount();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "With class = " << min << endl;
}

#pragma endregion

int _tmain(int argc, _TCHAR* argv[])
{
	//1
	cout << "\n----- Task 1 -----\n" << endl;
	time_t time1(0x7FFFFFFF);
	cout << "0x7FFFFFFF in SystemTime = " << asctime(localtime(&time1)) << endl;


	//2
	cout << "\n----- Task 2 -----\n" << endl;
	FILETIME start, finish;
	GetSystemTimeAsFileTime(&start);
	while (true)
	{
		GetSystemTimeAsFileTime(&finish);
		if (finish.dwLowDateTime != start.dwLowDateTime)
			break;
	}
	printf("%I64d (10^-4 ms)\n",
		FILETIMETOUINT64(finish) - FILETIMETOUINT64(start));

	DWORD begin, end;
	begin = GetTickCount();
	while (true)
	{
		if ((end = GetTickCount()) != begin)
			break;
	}
	printf("%d ms\n", end - begin);

	//3
	cout << "\n----- Task 3 -----\n" << endl;
	int n = 1000;
	int *m = new int[n];
	for (int i = 0; i < n; ++i)
	{
		m[i] = rand() % 9;
	}

	DWORD t, min;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsAsm();
		ArraySum(m, n);
		end = (DWORD)GetTactsAsm();
		t = end - begin;
		if (i == 0)
			min = t;
		if (t < min)
			min = t;
	}
	cout << "Asm get tacts = " << min << " ticks" << endl;

	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		ArraySum(m, n);
		end = (DWORD)GetTactsFunc();
		t = end - begin;
		if (i == 0)
			min = t;
		if (t < min)
			min = t;
	}
	cout << "Func get tacts = " << min << " ticks" << endl;

	LARGE_INTEGER l;
	ULONGLONG begin_t, end_t, total_t, min_t;
	for (int i = 0; i < 10; ++i)
	{
		QueryPerformanceCounter(&l);
		begin_t = l.QuadPart;
		ArraySum(m, n);
		QueryPerformanceCounter(&l);
		end_t = l.QuadPart;
		total_t = end_t - begin_t;
		if (i == 0)
			min_t = total_t;
		if (total_t < min_t)
			min_t = total_t;
	}
	cout << "QueryPerformanceCounter = " << min_t << " ms" << endl;
	
	//4
	cout << "\n----- Task 4 -----\n" << endl;

	double time10, time20, time30, minTime;
	int count10 = 0, count20 = 0, count30 = 0;

	GetCountAndTime(100000, count10, time10, minTime);
	cout << "Time for 100000 elements = " << minTime << endl;
	cout << "Count for 100000 elements = " << count10 << "\n" << endl;
	time10 = minTime;
	GetCountAndTime(200000, count20, time20, minTime);
	cout << "Time for 200000 elements = " << minTime << endl;
	cout << "Count for 200000 elements = " << count20 << "\n" << endl;
	time20 = minTime;
	GetCountAndTime(300000, count30, time30, minTime);
	cout << "Time for 300000 elements = " << minTime << endl;
	cout << "Count for 300000 elements = " << count30 << "\n" << endl;
	time30 = minTime;

	cout << "Time: T(200000)/T(100000) = " << (double)time20 / (double)time10 << "; T(300000)/T(100000) = " << (double)time30 / (double)time10 << endl;
	cout << "Count: T(100000)/T(200000) = " << count10 / count20 << "; T(100000)/T(300000) = " << count10 / count30 << endl;

	//5, 6, 7, 8
	cout << "\n----- Tasks 5, 6, 7, 8 -----\n" << endl;
	//ExecuteMatrixMultiplying(3);
	ExecuteMatrixMultiplying(256);
	ExecuteMatrixMultiplying(512);

	//9
	DWORD time;
	cout << "\n----- Task 9 -----\n" << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<__int8>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  int8 = " << min << "\n" << endl;

	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<__int16>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  int16 = " << min << "\n" << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<int>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  int32 = " << min << "\n" << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<__int64>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  int64 = " << min << "\n" << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<float>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  float = " << min << "\n" << endl;
	for (int i = 0; i < 10; ++i)
	{
		begin = (DWORD)GetTactsFunc();
		MatrixMultiplyingGeneral<double>(512);
		end = (DWORD)GetTactsFunc();
		time = end - begin;
		if (i == 0)
			min = time;
		if (time < min)
			min = time;
	}
	cout << "  double = " << min << "\n" << endl;
	
	getchar();
	return 0;
}

