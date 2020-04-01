#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

#include "BlockBreakerSystem.h"

//advanced blockbreaker.

BlockBreaker MakeField(std::size_t W,std::size_t H,std::size_t BL = 4) {
	BlockBreaker BB;

	BB.Initialize({ W,H }, { W / 2,1 }, { W / 2 - BL / 2,0 }, BL);
	//BB.Initialize({ W,H }, { W / 2,1 }, {0,0 }, W);

	for (std::size_t i = H-2; i < H; i++) {
		for (std::size_t j =  1; j < W - 1; j++) {
			BB.SetBlock(j, i);
		}
	}

	return BB;
}
bool Locate(std::uintmax_t X, std::uintmax_t Y) {
	std::cout << "\x1b[" << Y << ';' << X << "H";
	return true;
}

bool CLS() {
	std::cout << "\x1b[2J";
	return true;
}
int Keyin() {
	int K = -1;
	if (_kbhit()) {
		K = _getch();
	}
	return K;
}
bool ShowBlockBreaker(const BlockBreaker& In) {
	//CLS();
	for (std::size_t i = 0; i <= In.Width()+2; i++) {
		Locate(i, 0);
		std::cout << '*';
	}
	for (std::size_t i = 0; i <= In.Height()+2; i++) {
		Locate(0, i);
		std::cout << '*';
		Locate(In.Width()+2, i);
		std::cout << '*';
	}
	for (std::size_t i = 0; i < In.GetBlockCount(); i++) {
		Locate(std::get<0>(In.GetBlock(i))+2, (In.Height()-std::get<1>(In.GetBlock(i)))+2);
		std::cout << 'B';
	}
	for (std::size_t i = 0; i < In.GetBarLength(); i++) {
		Locate(std::get<0>(In.GetBar())+i+2, (In.Height()-std::get<1>(In.GetBar())+2));
		std::cout << 'T';
	}

	Locate(std::get<0>(In.GetBall())+2 , (In.Height() -std::get<1>(In.GetBall())+2));
	std::cout << 'O';
	Locate(In.Width()+2+7 , 1);
	std::cout << std::get<0>(In.GetBall()) << ',' << std::get<1>(In.GetBall());
	Locate(In.Width()+2+7 , 2);
	std::cout << std::get<0>(In.GetBar()) << ',' << std::get<1>(In.GetBar());
	return true;
}

int main() {
	std::size_t W = 30;
	std::size_t H = 24;
	std::size_t BL = W / 2;
	BlockBreaker BB = MakeField(W, H, BL);
	std::size_t FPS = 10;
	int Key = 0;
	
	while (Key != 27 && BB.IsEnd() == false) {
		BB.MoveBall();
		Key = Keyin();
		if (Key == 'a') { BB.MoveBarLeft(); }
		if (Key == 'd') { BB.MoveBarRight(); }
		if (Key == 'w') { BB.MoveBarUp(); }
		if (Key == 's') { BB.MoveBarDown(); }
		if (Key == ' ') { BB.SetBar({std::get<0>(BB.GetBar()),0}); }
		CLS();
		ShowBlockBreaker(BB);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 /FPS));
	}

	return true;

}