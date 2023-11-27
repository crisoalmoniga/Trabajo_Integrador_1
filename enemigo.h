#pragma once

class enemigo
{
public:
	enemigo(int);
	int getHp();
	void takeDamage(int amount);
private:
	int mHp;
};

