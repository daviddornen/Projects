﻿#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
#include <vector>
#include <string>

//de facut la fiecare text textX si textY si de recentrat meniul 

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

int grid_size = 50;
int padding = grid_size*2;

Color BACKGROUND_COLOR = { 20, 20, 20, 255 };
Color SNAKE_COLOR = { 0, 128, 0, 255 };
Color FOOD_COLOR = { 204, 204, 0, 255 };
Color TEXT_COLOR = RAYWHITE;

using namespace std;

int gameScore = 0;

double updateTime = 0;

bool ok = false;
bool lost = false;
bool inSettings = false;
bool allowTouchEdge = false;

struct coordinates {
	int x;
	int y;
};

struct setting {
	int options[3];
};




bool isInBody(coordinates elem, deque<coordinates> d) {
	for (int i = 0; i < d.size(); i++) {
		if ((elem.x == d[i].x) && (elem.y == d[i].y))
			return true;
	}
	return false;
}


bool snakeMoveInterval(double interval) {
	double Time0 = GetTime();

	if (Time0 - updateTime >= interval) {
		updateTime = Time0;
		return true;
	}
	return false;
}



class Snake {

public:
	deque<coordinates> body = { coordinates{(WINDOW_WIDTH/grid_size)/2,(WINDOW_HEIGHT/grid_size)/2}, 
								coordinates{(WINDOW_WIDTH/grid_size)/2-1,(WINDOW_HEIGHT/grid_size)/2}, 
								coordinates{(WINDOW_WIDTH/grid_size)/2-2,(WINDOW_HEIGHT/grid_size)/2}
							  };
	coordinates direction = { 1,0 };
	bool increaseLength = false;

	void drawSnake() {
		for (int i = 0; i < body.size(); i++) {
			float x = body[i].x;
			float y = body[i].y;
			Rectangle rect = Rectangle{ padding + x * grid_size, padding + y * grid_size, (float)grid_size, (float)grid_size };
			DrawRectangleRounded(rect, 0.6, 6, SNAKE_COLOR);
		}
	}

	void updateSnakePosition() {
		coordinates segmentAdded = { body[0].x + direction.x,body[0].y + direction.y };
		body.push_front(segmentAdded);
		if (increaseLength) {
			increaseLength = false;
		}
		else
		{
			body.pop_back();
		}
	}

	void reset() {
		body = { coordinates{(WINDOW_WIDTH / grid_size) / 2,(WINDOW_HEIGHT / grid_size) / 2},
								coordinates{(WINDOW_WIDTH / grid_size) / 2 - 1,(WINDOW_HEIGHT / grid_size) / 2},
								coordinates{(WINDOW_WIDTH / grid_size) / 2 - 2,(WINDOW_HEIGHT / grid_size) / 2}
		};

		direction = {1,0};
	}
	
};

class Food {

public:

	int foodX;
	int foodY;
	
	Food(deque<coordinates> body) {
		generateFoodPos(body);
	}

	coordinates generateFoodPos(deque<coordinates> body) {
		foodX = GetRandomValue(0, (WINDOW_WIDTH / grid_size) - 1) * grid_size + grid_size / 2;
		foodY = GetRandomValue(0, (WINDOW_HEIGHT / grid_size) - 1) * grid_size + grid_size / 2;

		coordinates pos = { foodX,foodY };
		while (isInBody(pos, body)) {
			foodX = GetRandomValue(0, (WINDOW_WIDTH / grid_size) - 1) * grid_size + grid_size / 2;
			foodY = GetRandomValue(0, (WINDOW_HEIGHT / grid_size) - 1) * grid_size + grid_size / 2;
		}
		return pos;

	}

	void drawFood() {
		DrawCircle(padding+foodX, padding+foodY, grid_size/2, FOOD_COLOR);
	}
};


class Menu {

public:

	int selectedSetting = 0; // Indexul setării selectate (0: Snake Speed, 1: Grid Size, 2: Edge Collision)
	vector<int> settingsValues = { 1, 50, 0 }; // Valorile curente ale setărilor
	vector<vector<int>> options = { {1, 2, 3}, {20, 30, 50}, {0, 1} }; // Opțiuni pentru fiecare setare
	vector<string> settingNames = { "Snake Speed", "Grid Size", "Edge Collision" };

	void drawMenu() {
		if (lost) {
			drawAfterLoseMenu();
		}
		else {
			ClearBackground(BACKGROUND_COLOR);
			string text1 = "Snake Game";
			int text1FontSize = 60;
			int text1Length = MeasureText(text1.c_str(), text1FontSize);
			DrawText(text1.c_str(), (2 * padding + WINDOW_WIDTH - text1Length) / 2, WINDOW_HEIGHT / 2, text1FontSize, LIGHTGRAY);

			string text2 = "Press ENTER to play";
			int text2FontSize = 20;
			int text2Length = MeasureText(text2.c_str(), text2FontSize);
			DrawText(text2.c_str(), (2 * padding + WINDOW_WIDTH - text2Length) / 2, WINDOW_HEIGHT / 2 + 70, text2FontSize, LIGHTGRAY);

			string text3 = "Press S to enter settings";
			int text3FontSize = 20;
			int text3Length = MeasureText(text3.c_str(), text3FontSize);
			DrawText(text3.c_str(), (2 * padding + WINDOW_WIDTH - text3Length) / 2, WINDOW_HEIGHT / 2 + 100, text3FontSize, LIGHTGRAY);

			if (IsKeyPressed(KEY_S)) {
				inSettings = true;
			}
			if (IsKeyPressed(KEY_ENTER)) {
				ok = true;
			}
		}
	}

	void drawAfterLoseMenu() {

		ClearBackground(BACKGROUND_COLOR);
		string text2 = "Press ENTER to play again";
		int text2FontSize = 23;
		int text2Length = MeasureText(text2.c_str(), text2FontSize);
		DrawText(text2.c_str(), (2 * padding + WINDOW_WIDTH - text2Length) / 2, WINDOW_HEIGHT + 2*padding - 130 , text2FontSize, LIGHTGRAY);
		

		string text3 = "Press BACKSPACE to go back to menu";
		int text3FontSize = 23;
		int text3Length = MeasureText(text3.c_str(), text3FontSize);
		DrawText(text3.c_str(), (2 * padding + WINDOW_WIDTH - text3Length) / 2, WINDOW_HEIGHT + 2 * padding - 100, text3FontSize, LIGHTGRAY);
		
		DrawText("Game Over", (2 * padding + WINDOW_WIDTH - MeasureText("Game Over", 90)) / 2, 2 * padding, 90, TEXT_COLOR);
		DrawText("Score", (2 * padding + WINDOW_WIDTH - MeasureText("Score", 50)) / 2, WINDOW_HEIGHT/2 - padding , 50, TEXT_COLOR);
		DrawText(TextFormat("%d", gameScore), (2 * padding + WINDOW_WIDTH - MeasureText(TextFormat("%d", gameScore), 150)) / 2, WINDOW_HEIGHT / 2 +padding + padding/2, 150, LIGHTGRAY);


		if (IsKeyPressed(KEY_ENTER)) {
			ok = true;
			gameScore = 0;
		}
		else if (IsKeyPressed(KEY_BACKSPACE)) {
			ok = false;
			lost = false;
			gameScore = 0;
		}
	}

	void drawSettingsMenu() {
		ClearBackground(BACKGROUND_COLOR);

		string text5 = "SETTINGS";
		int text5FontSize = 50;
		int text5Length = MeasureText(text5.c_str(), text5FontSize);
		DrawText(text5.c_str(), (2 * padding + WINDOW_WIDTH - text5Length) / 2, padding, text5FontSize, LIGHTGRAY);

		for (int i = 0; i < settingNames.size(); ++i) {
			string settingText = settingNames[i] + ": " + to_string(settingsValues[i]);
			int fontSize = 30;
			int textLength = MeasureText(settingText.c_str(), fontSize);
			Color color = (i == selectedSetting) ? YELLOW : LIGHTGRAY; 

			DrawText(settingText.c_str(), 2 * padding, (WINDOW_HEIGHT + 2 * padding) / 4 + i * 2 * padding, fontSize, color);
		}

		string text4 = "Press BACKSPACE to save settings and go back";
		int text4FontSize = 20;
		int text4Length = MeasureText(text4.c_str(), text4FontSize);
		DrawText(text4.c_str(), (2 * padding + WINDOW_WIDTH - text4Length) / 2, WINDOW_HEIGHT + padding, text4FontSize, LIGHTGRAY);

		handleInput();
	}

	void handleInput() {
		if (IsKeyPressed(KEY_UP)) {
			selectedSetting = (selectedSetting - 1 + settingNames.size()) % settingNames.size();
		}
		if (IsKeyPressed(KEY_DOWN)) {
			selectedSetting = (selectedSetting + 1) % settingNames.size();
		}

		if (IsKeyPressed(KEY_LEFT)) {
			int& value = settingsValues[selectedSetting];
			const vector<int>& settingOptions = options[selectedSetting];
			auto it = find(settingOptions.begin(), settingOptions.end(), value);
			if (it != settingOptions.begin()) value = *(--it);
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			int& value = settingsValues[selectedSetting];
			const vector<int>& settingOptions = options[selectedSetting];
			auto it = find(settingOptions.begin(), settingOptions.end(), value);
			if (it != settingOptions.end() - 1) value = *(++it);
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {
			applySettings();
			inSettings = false;
		}
	}

	void applySettings() {
		gameScore = 0; 
		updateTime = 0.2 / settingsValues[0]; 
		grid_size = settingsValues[1]; 
		allowTouchEdge = (settingsValues[2] == 1); 
	}
	 
};

class SnakeGame {
public:
	Food food = Food(snake.body);
	Snake snake = Snake();
	Menu _menu;

	void draw() {
		if (!ok)
			_menu.drawMenu();
		else if (ok) {
			food.drawFood();
			snake.drawSnake();
		}
	}

	void update() {
		if (ok) {
			snake.updateSnakePosition();
			eatFood();
			touchEdge();
			touchTail();
		}
	}

	void eatFood() {
		coordinates snakeHeadPos = { snake.body[0].x,snake.body[0].y };
		coordinates foodPos = { food.foodX/grid_size,food.foodY/grid_size};
		if ((snakeHeadPos.x == foodPos.x) && (snakeHeadPos.y == foodPos.y)){
			food.generateFoodPos(snake.body);
			snake.increaseLength = true;
			gameScore+=10;
		}

	}

	void touchEdge() {

		if (allowTouchEdge) {
			if (snake.body[0].x > WINDOW_WIDTH / grid_size - 1) {
				snake.body[0].x = 0;
			}
			if (snake.body[0].x < 0) {
				snake.body[0].x = WINDOW_WIDTH / grid_size - 1;
			}
			if (snake.body[0].y > WINDOW_HEIGHT / grid_size - 1) {
				snake.body[0].y = 0;
			}
			if (snake.body[0].y < 0) {
				snake.body[0].y = WINDOW_HEIGHT / grid_size - 1;
			}
		}
		if (!allowTouchEdge) {
			if (snake.body[0].x > WINDOW_WIDTH / grid_size - 1) {
				gameOver();
			}
			if (snake.body[0].x < 0) {
				gameOver();
			}
			if (snake.body[0].y > WINDOW_HEIGHT / grid_size - 1) {
				gameOver();
			}
			if (snake.body[0].y < 0) {
				gameOver();
			}
		}
	}

	void touchTail() {
		deque<coordinates> tail = snake.body;
		tail.pop_front();
		if (isInBody(snake.body[0], tail)) {
			gameOver();
		}
	}

	void gameOver() {
		lost = true;
		_menu.drawMenu();
		snake.reset();
		food.generateFoodPos(snake.body);
		ok = false;
	}
};


int main()
{
	InitWindow(2*padding + WINDOW_WIDTH,2*padding+WINDOW_HEIGHT, "Snake");
	SetTargetFPS(60);

	SnakeGame game = SnakeGame();

	while (!WindowShouldClose()) {

		BeginDrawing();
		 
		if (!ok && !inSettings) game.draw();
		else if (inSettings) game._menu.drawSettingsMenu();
		else if (ok) {
			if (snakeMoveInterval(0.2)) game.update();

			if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && game.snake.direction.y != 1) {
				game.snake.direction = { 0,-1 };
				ok = true;
			}
			if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && game.snake.direction.x != 1) {
				game.snake.direction = { -1,0 };
				ok = true;
			}
			if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && game.snake.direction.y != -1) {
				game.snake.direction = { 0,1 };
				ok = true;
			}
			if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && game.snake.direction.x != -1) {
				game.snake.direction = { 1,0 };
				ok = true;
			}

			ClearBackground(BACKGROUND_COLOR);
			DrawRectangleLinesEx(Rectangle{ (float)padding - 7,(float)padding - 7,WINDOW_WIDTH + 14,WINDOW_HEIGHT + 14 }, 7, DARKGREEN);
			DrawText(TextFormat("Score: %d", gameScore), (2 * padding + WINDOW_WIDTH - MeasureText(TextFormat("Score: %d", gameScore), 30)) / 2, padding / 2, 30, TEXT_COLOR);
			game.draw();
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}