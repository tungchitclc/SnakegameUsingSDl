// Game_usingSDL.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL.h> 
#include <SDL_ttf.h> 

using namespace std;


//Hien thi player len man hinh
void renderPlayer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	player.w = scale;
	player.h = scale;

	// Gets x and y of all tail blocks and renders them
	for (int i = 0; i < tailLength; i++) {
		player.x = tailX[i];
		player.y = tailY[i];
		SDL_RenderFillRect(renderer, &player);
	}

	player.x = x;
	player.y = y;

	SDL_RenderFillRect(renderer, &player);
}
//Ve hcn dai dien cho thuc an
void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//thuc an mau xanh la cay 
	SDL_RenderFillRect(renderer, &food);
}
//Hien thi diem so game
void renderScore(SDL_Renderer* renderer, int tailLength, int scale, int wScale) {
	SDL_Color Black = { 0, 0, 0 };

	// Font su dung hien thi score
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	//Check font
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	//Kich thuoc va vi tri Score
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);
}
//Check va cham
bool checkCollision(int foodx, int foody, int playerx, int playery) {

	if (playerx == foodx && playery == foody) {
		return true;
	}

	return false;
}

// Tao thuc an moi bat ki khong trung snake
pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
	bool valid = false;
	int x = 0;
	int y = 0;
	srand(time(0));
	x = scale * (rand() % wScale);
	y = scale * (rand() % wScale);
	valid = true;

	// Check all toa do cua duoi va player
	for (int i = 0; i < tailLength; i++) {

		if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
			valid = false;
		}

	}

	if (!valid) {
		pair<int, int> foodLoc;
		foodLoc = make_pair(-100, -100);
		return foodLoc;
	}

	pair<int, int> foodLoc;
	foodLoc = make_pair(x, y);

	return foodLoc;
}
//Hien thi man hinh GameOver
void gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wScale) / 2) - (gameoverRect.w / 2);
	gameoverRect.y = ((scale*wScale) / 2) - (gameoverRect.h / 2) - 50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wScale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wScale) / 2) - ((retryRect.h / 2)) + 150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Hien thi man hinh GameOver va doi nguoi choi an phim
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) { // check tuong tac nguoi choi

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

void youWin(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };

	
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You won!", Yellow);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to play again", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wScale) / 2) - (gameoverRect.w / 2);
	gameoverRect.y = ((scale*wScale) / 2) - (gameoverRect.h / 2) - 50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wScale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wScale) / 2) - ((retryRect.h / 2)) + 150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Tuong tac cua nguoi choi
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}

int main(int argc, char* argv[]) {

	// Khoi tao tat ca thanh phan SDl
	SDL_Init(SDL_INIT_EVERYTHING);

	// Khoi tao TTF va check loi
	if (TTF_Init() < 0) {
		cout << "Error: " << TTF_GetError() << endl;
	}

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	// Snake hcn , cac gia tri dat thanh  0
	SDL_Rect player;
	player.x = 0;
	player.y = 0;
	player.h = 0;
	player.w = 0;

	// Chieu dai duoi duoc tang len moi khi snake an food
	int tailLength = 0;

	// Vectors luu tru cac vi tri duoi
	vector<int> tailX;
	vector<int> tailY;

	// Kich thuoc cua o
	int scale = 24;
	int wScale = 24;

	// Vi tri cua nguoi choi
	int x = 0;
	int y = 0;
	int prevX = 0;//vi tri truoc do
	int prevY = 0;

	// Dieu khien chuyen dong
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	bool inputThisFrame = false;
	bool redo = false;

	// Do an
	SDL_Rect food;
	food.w = scale;
	food.h = scale;
	food.x = 0;
	food.y = 0;

	pair<int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
	food.x = foodLoc.first;
	food.y = foodLoc.second;

	// Hien thi cua so voi cac setting nay
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale*wScale + 1, scale*wScale + 1, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	float time = SDL_GetTicks() / 100;

	// Vong lap chinh cua tro choi
	while (true) {

		float newTime = SDL_GetTicks() / 75; //Toc do cua cac hcn
		float delta = newTime - time;// do chenh lech thoi gian giua lan truoc va hien tai
		time = newTime;

		inputThisFrame = false;

		// Check dieu kien thang, duoi phu all o
		if (tailLength >= 575) {
			youWin(renderer, event, scale, wScale, tailLength);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			// neu food vo han, can sinh food moi
			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			food.x = foodLoc.first;
			food.y = foodLoc.second;
		}

		// Controls
		if (SDL_PollEvent(&event)) {//check xem co event nao xay ra k

			// check xem phai thoat khoi chuong trinh k
			if (event.type == SDL_QUIT) {
				exit(0);
			}

			// Neu 1 phim duoc nhan
			if (event.type == SDL_KEYDOWN && inputThisFrame == false) {

				// Kiem tra phim dang dc nhan va thay doi huong
				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
					inputThisFrame = true;//danh dau nguoi choi da nhap lieu trong frame nay tranh snake chuyen huong nhieu lan
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
					inputThisFrame = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
					inputThisFrame = true;
				}

			}

		}

		//Luu vi tri truoc do cua snake
		prevX = x;
		prevY = y;

		if (up) {
			y -= delta * scale;
		}
		else if (left) {
			x -= delta * scale;
		}
		else if (right) {
			x += delta * scale;
		}
		else if (down) {
			y += delta * scale;
		}

		if (redo == true) {//check xem co can tao lai vi tri food 

			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}

		// Phat hien va cham, da va cham voi food chua
		if (checkCollision(food.x, food.y, x, y)) {

			// Sinh them food moi sau khi no da dc an va tang do dai
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

			tailLength++;
		}

		// Chi chay trong cac o ma snake da di chuyen
		if (delta * scale == 24) {

			// Update kich thuoc và vi tri duoi
			if (tailX.size() != tailLength) {
				tailX.push_back(prevX);
				tailY.push_back(prevY);
			}

			//Di chuyen cac o den gan nhat cac o phia trc
			for (int i = 0; i < tailLength; i++) {

				if (i > 0) {
					tailX[i - 1] = tailX[i];
					tailY[i - 1] = tailY[i];
				}

			}

			if (tailLength > 0) {
				tailX[tailLength - 1] = prevX;
				tailY[tailLength - 1] = prevY;
			}

		}

		// Gameover khi va cham voi duoi, reset moi thu
		for (int i = 0; i < tailLength; i++) {

			if (x == tailX[i] && y == tailY[i]) {
				gameOver(renderer, event, scale, wScale, tailLength);
				x = 0;
				y = 0;
				up = false;
				left = false;
				right = false;
				down = false;
				tailX.clear();
				tailY.clear();
				tailLength = 0;
				redo = false;

				foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
				if (food.x == -100 && food.y == -100) {
					redo = true;
				}

				food.x = foodLoc.first;
				food.y = foodLoc.second;
			}

		}

		// Game over neu player vuot qua man hinh và reset
		if (x < 0 || y < 0 || x > scale * wScale - scale || y > scale * wScale - scale) {
			gameOver(renderer, event, scale, wScale, tailLength);
			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;
			redo = false;
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			if (food.x == -100 && food.y == -100) {
				redo = true;
			}

		}

		// Hien thi moi thu
		renderFood(renderer, food);
		renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
		renderScore(renderer, tailLength, scale, wScale);
		//Ve cac duong thang tao thanh vien
		SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
		SDL_RenderDrawLine(renderer, 0, 24 * 24, 24 * 24, 24 * 24);
		SDL_RenderDrawLine(renderer, 24 * 24, 24 * 24, 24 * 24, 0);
		SDL_RenderDrawLine(renderer, 24 * 24, 0, 0, 0);

		// Dua moi thu len man hinh
		// Khong co gi duoc dua len mh cho den khi cai nay duoc goi
		SDL_RenderPresent(renderer);

		
		// Mau nen
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
		SDL_RenderClear(renderer);
	}

	SDL_DestroyWindow(window);

	TTF_Quit();

	SDL_Quit();

	return 0;

}