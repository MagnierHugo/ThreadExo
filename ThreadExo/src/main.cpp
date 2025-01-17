// main.cpp

#include "../include/exercice.hpp"


int main() {

	int iterations = 100'000'000;
	int tests = 10;
	int vectors = 9;
	
	std::cout << "Exercice Without Thread : \n";
	//TimeItPrint(ExerciceWithoutThread, PrintVect, 100, 10);
	TimeIt(tests, ExerciceWithoutThread, iterations, vectors);
	//std::cout << "Exercice With Thread 1:\n";
	//TimeItPrint(ExerciceWithThread1, PrintVect, 100, 10);
	//TimeIt(tests0, ExerciceWithThread1, iterations, vectors);
	//std::cout << "Exercice With Thread 2:\n";
	//TimeIt(tests, ExerciceWithThread2, iterations, vectors);
	std::cout << "Exercice With Thread 3:\n";
	//TimeItPrint(ExerciceWithThread3, PrintVect, 100, 10);
	TimeIt(tests, ExerciceWithThread3, iterations, vectors);

	return 0;
}