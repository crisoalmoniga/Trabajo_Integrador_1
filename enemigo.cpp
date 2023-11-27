#include "enemigo.h"


enemigo::enemigo(int hp) {
	mHp = hp;
}

int enemigo::getHp(){
	return mHp;
}

void enemigo::takeDamage(int amount){
	mHp -= amount;

	if (mHp < 0) {
		mHp = 0;
	}


}