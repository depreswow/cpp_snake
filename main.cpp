#include "Snake.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <iomanip>

void printLogo() {

	std::cout << R"(                                       
  ,---.                  ,--.           
 '   .-' ,--,--,  ,--,--.|  |,-. ,---.  
 `.  `-. |      \' ,-.  ||     /| .-. : 
 .-'    ||  ||  |\ '-'  ||  \  \\   --. 
 `-----' `--''--' `--`--'`--'`--'`----' 
                                       )" << std::endl << std::endl << std::endl;

}

std::vector<std::vector<char>> createField(int width, int height) {
	std::vector<std::vector<char>> field(height);
	for (int i = 0; i < height; i++) {
		field[i] = std::vector<char>(width);
		for (int j = 0; j < width; j++)
			field[i][j] = ' ';
	}
	return field;
}

void printField(std::vector<std::vector<char>>& in_field, const Snake& snake, const Snake::coordinates& food) {
	system("cls");

	printLogo();

	std::cout << "\t"; //line on top
	for (int i = 0; i < in_field[0].size(); i++)
		std::cout << "-";
	std::cout << "--" << std::endl;

	for (int i = 0; i < in_field.size(); i++) {
		std::cout << "\t" << "|";
		for (int j = 0; j < in_field[i].size(); j++)
			if (snake.getHead() == Snake::coordinates(i, j))
				std::cout << "O";
			else {
				if (snake.has(Snake::coordinates(i, j)))
					std::cout << "#";
				else {
					if (food == Snake::coordinates(i, j))
						std::cout << "@";
					else
						std::cout << in_field[i][j];
				}
			}
		std::cout << "|" << std::endl;
	}

	std::cout << "\t"; //line at the bottom
	for (int i = 0; i < in_field[0].size(); i++)
		std::cout << "-";
	std::cout << "--" << std::endl << std::endl;
	std::cout << "Press Esc to exit." << std::endl;
}

Snake::coordinates createFood(std::vector<std::vector<char>>& in_field, const Snake& snake) {
	Snake::coordinates coords;
	do {
		coords = Snake::coordinates(rand() % in_field.size(), rand() % in_field[0].size());
	} while (snake.has(coords));
	return coords;
}

int main() {
	srand(time(0));

	int WIDTH = 20;
	int HEIGHT = 10;

	int SLEEP_TIME = 250;

	std::vector<std::vector<char>> field = createField(WIDTH, HEIGHT);
	Snake snake;

	int dir;
	Snake::coordinates food = createFood(field, snake);
	
	bool game_on = true;
	while (game_on) {
		printField(field, snake, food);

		Sleep(SLEEP_TIME);

		if (_kbhit()) {
			dir = _getch();
			if (dir == 27)
				break;
			if (dir == 0 || dir == 224) {
				switch (_getch()) {
				case 72:
					snake.setDirection(0);
					break;
				case 80:
					snake.setDirection(2);
					break;
				case 75:
					snake.setDirection(3);
					break;
				case 77:
					snake.setDirection(1);
					break;
				}
			}
		}

		if (!snake.move(WIDTH, HEIGHT, food))
			game_on = false;
		if (snake.getHead() == food)
			food = createFood(field, snake);
		
	}

	system("pause");
}