// exercice.cpp

//#include "../include/exercice.hpp"


//std::vector<std::vector<int>> ExerciceWithoutThread(const std::size_t& num_count, const std::size_t& num_vector) {
//	std::vector<std::vector<int>> vects;
//	vects.resize(num_vector);
//
//	for (std::size_t i = 0; i < num_vector; i++) {
//		vects[i].resize(num_count / (i + 1));
//	}
//
//	for (std::size_t i = 1; i <= num_count; i++) {
//		vects[0][i - 1] = i;
//		for (std::size_t j = 1; j < num_vector && j < i; j++) {
//			if (i % (j + 1) == 0) {
//				vects[j][i / (j + 1) - 1] = i;
//			}
//		}
//	}
//
//	return vects;
//}

//std::vector<std::vector<int>> ExerciceWithThread1(const std::size_t& num_count, const std::size_t& num_vector) {
//	std::vector<std::vector<int>> vects;
//	vects.resize(num_vector);
//
//	std::size_t index = 0;
//	std::for_each(std::execution::par, vects.begin(), vects.end(), [&index, &num_count](std::vector<int>& vect) {
//		index++;
//		vect.reserve(num_count / index + 1);
//		vect.push_back(index);
//	});
//
//	for (std::size_t i = 1; i <= num_count; i++) {
//		std::for_each(std::execution::par, vects.begin(), vects.end(), [&i](std::vector<int>& vect) {
//			if (vect[0] == 1 || i % vect[0] == 0) {
//				vect.push_back(i);
//			}
//		});
//	}
//
//	return vects;
//}
//
//std::vector<std::vector<int>> ExerciceWithThread2(const std::size_t& num_count, const std::size_t& num_vector) {
//	std::vector<std::vector<int>> vects;
//	vects.resize(num_vector);
//
//	for (std::size_t i = 0; i < num_vector; i++) {
//		vects[i].reserve(num_count / (i + 1) + 1);
//		vects[i].push_back(i + 1);
//	}
//
//	for (std::size_t i = 1; i <= num_count; i++) {
//		std::for_each(std::execution::par, vects.begin(), vects.end(), [&i](std::vector<int>& vect) {
//			if (vect[0] == 1 || i % vect[0] == 0) {
//				vect.push_back(i);
//			}
//		});
//	}
//
//	return vects;
//}
//
//std::vector<std::vector<int>> ExerciceWithThread3(const std::size_t& num_count, const std::size_t& num_vector) {
//	std::vector<std::vector<int>> vects;
//	vects.resize(num_vector);
//
//	for (std::size_t i = 0; i < num_vector; i++) {
//		vects[i].resize(num_count / (i + 1));
//	}
//
//	const std::size_t num_thread = std::thread::hardware_concurrency();
//	const std::size_t chunk = num_count / num_thread + 1;
//	//std::cout << "num_thread: " << num_thread << " / chunk: " << chunk << '\n';
//
//	std::vector<std::thread> threads;
//	threads.reserve(num_thread);
//
//	for (std::size_t i = 0; i < num_thread; i++) {
//		std::size_t start = i * chunk;
//		std::size_t end = start + chunk;
//		if (end > num_count) {
//			end = num_count;
//		}
//		threads.push_back(std::thread([start, end, &vects, num_vector]() {
//
//			for (std::size_t i = start + 1; i <= end; i++) {
//				vects[0][i - 1] = i;
//				for (std::size_t j = 2; j <= num_vector && j <= i; j++) {
//					if (i % j == 0) {
//						vects[j - 1][i / j - 1] = i;
//					}
//				}
//			}
//		}));
//	}
//
//	for (auto& thread : threads) {
//		thread.join();
//	}
//
//	return vects;
//}
//
//void PrintVect(const std::vector<std::vector<int>> vects) {
//	for (std::size_t i = 0; i < vects.size(); i++) {
//		std::cout << "Values in vect " << i + 1 << ": ";
//		for (std::size_t j = 0; j < vects[i].size(); j++) {
//			std::cout << vects[i][j] << ' ';
//		}
//		std::cout << '\n';
//	}
//}
