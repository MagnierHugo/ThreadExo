// main.cpp

#include "../include/exercice.hpp"


int main(int argc, char* argv[]) {

	std::cout << "Exercice Without Thread:\n";
	//TimeItPrint(ExerciceWithoutThread, PrintVect, 100, 10);
	TimeIt(ExerciceWithoutThread, 100000, 10);
	std::cout << "Exercice With Thread 1:\n";
	//TimeItPrint(ExerciceWithThread1, PrintVect, 100, 10);
	TimeIt(ExerciceWithThread1, 100000, 10);
	std::cout << "Exercice With Thread 2:\n";
	TimeIt(ExerciceWithThread2, 100000, 10);
	std::cout << "Exercice With Thread 3:\n";
	//TimeItPrint(ExerciceWithThread3, PrintVect, 100, 10);
	TimeIt(ExerciceWithThread3, 100000, 10);

	return 0;
}