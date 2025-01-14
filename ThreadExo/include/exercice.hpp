// exercice.hpp

#pragma once

#include <chrono>
#include <iostream>
#include <vector>


std::vector<std::vector<int>> ExerciceWithoutThread(const std::size_t& num_count, const std::size_t& num_vector);
std::vector<std::vector<int>> ExerciceWithThread1(const std::size_t& num_count, const std::size_t& num_vector);
std::vector<std::vector<int>> ExerciceWithThread2(const std::size_t& num_count, const std::size_t& num_vector);
std::vector<std::vector<int>> ExerciceWithThread3(const std::size_t& num_count, const std::size_t& num_vector);
void PrintVect(const std::vector<std::vector<int>> vects);

template<typename T, typename... Args>
void TimeIt(T func, Args... args) {
	auto t1 = std::chrono::system_clock::now();
	func(std::forward<Args>(args)...);
	auto t2 = std::chrono::system_clock::now();
	std::cout << "Function took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << " to execute\n";
}

template<typename T, typename A, typename... Args>
void TimeItPrint(T func, A p_func, Args... args) {
	auto t1 = std::chrono::system_clock::now();
	auto val = func(std::forward<Args>(args)...);
	auto t2 = std::chrono::system_clock::now();
	p_func(val);
	std::cout << "Function took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << " to execute\n";
}