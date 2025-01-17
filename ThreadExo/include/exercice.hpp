// exercice.hpp

#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>


//std::vector<std::vector<int>> ExerciceWithoutThread(const int& num_count, const int& num_vector);
inline std::vector<std::vector<int>> ExerciceWithoutThread(const int num_count, const int num_vector)
{
	std::vector<std::vector<int>> vects(num_vector);

	for (int i = 0; i < num_vector; i++) {
		vects[i].resize(num_count / (i + 1));
	}

	if (num_vector == 9) {
		for (int i = 1; i <= num_count; i++) {
			vects[0][i - 1] = i;
			for (int j = 8; j > 3; j--) {
				if (i % (j + 1) == 0) {
					switch (j) {
					case 8:
						vects[8][i / 9 - 1] = i;
						vects[2][i / 3 - 1] = i;
						break;
					case 7:
						vects[7][i / 8 - 1] = i;
						vects[3][i / 4 - 1] = i;
						vects[1][i / 2 - 1] = i;
						break;
					case 6:
					case 5:
					case 4:
						vects[j][i / (j + 1) - 1] = i;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else {
		for (int i = 1; i <= num_count; i++) {
			vects[0][i - 1] = i;
			for (int j = 1; j < num_vector; j++) {
				if (i % (j + 1) == 0) {
					vects[j][i / (j + 1) - 1] = i;
				}
			}
		}
	}

	return vects;
}
inline std::vector<std::vector<int>> ExerciceWithThread1(const int& num_count, const int& num_vector) {
	std::vector<std::vector<int>> vects;
	vects.resize(num_vector);

	int index = 0;
	std::for_each(std::execution::par, vects.begin(), vects.end(), [&index, &num_count](std::vector<int>& vect) {
		index++;
		vect.reserve(num_count / index + 1);
		vect.push_back(index);
		});

	for (int i = 1; i <= num_count; i++) {
		std::for_each(std::execution::par, vects.begin(), vects.end(), [&i](std::vector<int>& vect) {
			if (vect[0] == 1 || i % vect[0] == 0) {
				vect.push_back(i);
			}
			});
	}

	return vects;
}

inline std::vector<std::vector<int>> ExerciceWithThread2(const int& num_count, const int& num_vector) {
	std::vector<std::vector<int>> vects;
	vects.resize(num_vector);

	for (int i = 0; i < num_vector; i++) {
		vects[i].reserve(num_count / (i + 1) + 1);
		vects[i].push_back(i + 1);
	}

	for (int i = 1; i <= num_count; i++) {
		std::for_each(std::execution::par, vects.begin(), vects.end(), [&i](std::vector<int>& vect) {
			if (vect[0] == 1 || i % vect[0] == 0) {
				vect.push_back(i);
			}
			});
	}

	return vects;
}

inline std::vector<std::vector<int>> ExerciceWithThread3(const int num_count, const int num_vector) {
	std::vector<std::vector<int>> vects(num_vector);

	for (int i = 0; i < num_vector; i++) {
		vects[i].resize(num_count / (i + 1));
	}

	const int num_thread = std::thread::hardware_concurrency();
	const int chunk = num_count / num_thread + 1;
	//std::cout << "num_thread: " << num_thread << " / chunk: " << chunk << '\n';

	std::vector<std::thread> threads(num_thread);

	auto lambda = [](const int start, const int end, const int num_vector, std::vector<std::vector<int>>& vects) { // [start, end[ ; [1, num_vector[
		if (num_vector == 10) {
			for (int i = start + 1; i < end; i++) {
				vects[0][i - 1] = i;
				for (int j = 8; j > 3; j--) {
					if (i % (j + 1) == 0) {
						switch (j) {
						case 8:
							vects[8][i / 9 - 1] = i;
							vects[2][i / 3 - 1] = i;
							break;
						case 7:
							vects[7][i / 8 - 1] = i;
							vects[3][i / 4 - 1] = i;
							vects[1][i / 2 - 1] = i;
							break;
						case 6:
						case 5:
						case 4:
							vects[j][i / (j + 1) - 1] = i;
							break;
						default:
							break;
						}
					}
				}
			}
		}
		else {
			for (int i = start + 1; i < end; i++) {
				vects[0][i - 1] = i;
				for (int j = 2; j < num_vector; j++) {
					if (i % j == 0) {
						vects[j - 1][i / j - 1] = i;
					}
				}
			}
		}
	};
	
	for (int i = 0; i < num_thread; i++) {
		int start = i * chunk + 1;
		int end = start + chunk + 1;
		if (end > num_count) {
			end = num_count + 1;
		}
		threads[i] = std::thread(lambda, start, end + 1, num_vector + 1, std::ref(vects));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	return vects;
}


void PrintVect(const std::vector<std::vector<int>> vects) {
	for (int i = 0; i < vects.size(); i++) {
		std::cout << "Values in vect " << i + 1 << ": ";
		for (int j = 0; j < vects[i].size(); j++) {
			std::cout << vects[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

//std::vector<std::vector<int>> ExerciceWithThread1(const int& num_count, const int& num_vector);
//std::vector<std::vector<int>> ExerciceWithThread2(const int& num_count, const int& num_vector);
//std::vector<std::vector<int>> ExerciceWithThread3(const int& num_count, const int& num_vector);
//void PrintVect(const std::vector<std::vector<int>> vects);

template<typename T, typename... Args>
void TimeIt(int iterations, T func, Args... args)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iterations; i++)
	{
		func(std::forward<Args>(args)...);
	}
	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << "Function took on average: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) / iterations
		<< " | "
		<< std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1) / iterations
		<< " | "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1)  / iterations 
		<< " to execute\n";
}

template<typename T, typename A, typename... Args>
void TimeItPrint(T func, A p_func, Args... args) {
	auto t1 = std::chrono::high_resolution_clock::now();
	auto val = func(std::forward<Args>(args)...);
	auto t2 = std::chrono::high_resolution_clock::now();
	p_func(val);
	std::cout << "Function took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1) << " to execute\n";
}