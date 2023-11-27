#include "enemigo.h"
#include <iostream>

int main() {
	enemigo enemigo{ 100 };
	enemigo.takeDamage(50);
	std::cout << "enemigo hp: " << enemigo.getHp() << '\n';

	return 0;
}