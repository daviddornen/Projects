#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int grid_size = 25;
int padding = grid_size*3;


Color BACKGROUND_COLOR = { 34, 34, 34, 255 };
Color SNAKE_COLOR = { 0, 255, 0, 255 };
Color FOOD_COLOR = { 255, 0, 0, 255 };

using namespace std;

double updateTime = 0;

struct coordinates {
	int x;
	int y;
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

class SnakeGame {
public:
	Food food = Food(snake.body);
	Snake snake = Snake();

	bool ok = true;

	void draw() {
		food.drawFood();
		snake.drawSnake();
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
		}

	}

	void touchEdge() {
		if (snake.body[0].x > WINDOW_WIDTH / grid_size -1) {
			snake.body[0].x = 0;
		}
		if (snake.body[0].x < 0 ) {
			snake.body[0].x = WINDOW_WIDTH / grid_size;
		}
		if (snake.body[0].y > WINDOW_HEIGHT / grid_size -1) {
			snake.body[0].y = 0;
		}
		if (snake.body[0].y < 0) {
			snake.body[0].y = WINDOW_HEIGHT / grid_size;
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

		if (snakeMoveInterval(0.3)) game.update();
		
		if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && game.snake.direction.y != 1) {
			game.snake.direction = { 0,-1 };
			game.ok = true;
		}
		if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && game.snake.direction.x != 1) {
			game.snake.direction = { -1,0 };
			game.ok = true;
		}
		if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && game.snake.direction.y != -1) {
			game.snake.direction = { 0,1 };
			game.ok = true;
		}
		if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && game.snake.direction.x != -1) {
			game.snake.direction = { 1,0 };
			game.ok = true;
		}

		ClearBackground(BACKGROUND_COLOR);
		DrawRectangleLinesEx(Rectangle{ (float)padding - 7,(float)padding - 7,WINDOW_WIDTH + 14,WINDOW_HEIGHT + 14 }, 7, DARKGREEN);
		game.draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}