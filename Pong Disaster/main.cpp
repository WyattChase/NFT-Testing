#include "raylib.h"
#include <string>

const int screenWidth = 900;
const int screenHeight = 500;

const int paddleWidth = 20;
const int paddleHeight = 80;
const int paddleSpeed = 5;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

Sound hitSound;
Sound scoreSound;



int main()
{
	InitWindow(screenWidth, screenHeight, "Pong Disaster");

	Rectangle player1 = { 30, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };
	Rectangle player2 = { screenWidth - 30 - paddleWidth, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };

	Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };
	Vector2 ballSpeed = { 3, 3 };

	SetTargetFPS(60);
	hitSound = LoadSound("./pong_ball.wav");
	scoreSound = LoadSound("./packman_dying.wav");

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_W) && player1.y > 0)
			player1.y -= paddleSpeed;
		if (IsKeyDown(KEY_S) && player1.y + player1.height < screenHeight)
			player1.y += paddleSpeed;


		if (IsKeyDown(KEY_UP) && player2.y > 0)
			player2.y -= paddleSpeed;
		if (IsKeyDown(KEY_DOWN) && player2.y + player2.height < screenHeight)
			player2.y += paddleSpeed;

		if (IsKeyPressed(KEY_ENTER))
		{
			// Restart the game
			scorePlayer1 = 0;
			scorePlayer2 = 0;
		}


		ballPosition.x += ballSpeed.x;
		ballPosition.y += ballSpeed.y;

		if (ballPosition.x + ballSpeed.x > screenWidth || ballPosition.x + ballSpeed.x < 0)
			ballSpeed.x *= -1;
		if (ballPosition.y + ballSpeed.y > screenHeight || ballPosition.y + ballSpeed.y < 0)
			ballSpeed.y *= -1;
		
		if (CheckCollisionCircleRec(ballPosition, 10, player1) || CheckCollisionCircleRec(ballPosition, 10, player2))
		{
			PlaySound(hitSound);
			ballSpeed.x *= -1;
		}

		if (ballPosition.x + ballSpeed.x > screenWidth - 10 && ballSpeed.x > 0)
		{
			// Ball collides with player 2's paddle
			if (CheckCollisionCircleRec(ballPosition, 10, player2))
			{
				ballSpeed.x *= -1; // Reverse ball direction on collision
			}
			else
			{
				// Player 1 scores a point
				scorePlayer1++;
				PlaySound(scoreSound);
				ballPosition = { screenWidth / 2, screenHeight / 2 };
				ballSpeed = { -3, 3 };
			}
		}
		else if (ballPosition.x + ballSpeed.x < 10 && ballSpeed.x < 0)
		{
			// Ball collides with player 1's paddle
			if (CheckCollisionCircleRec(ballPosition, 10, player1))
			{
				ballSpeed.x *= -1; // Reverse ball direction on collision
			}
			else
			{
				// Player 2 scores a point
				scorePlayer2++;
				PlaySound(scoreSound);
				ballPosition = { screenWidth / 2, screenHeight / 2 };
				ballSpeed = { 3, 3 };
			}
		}


		BeginDrawing();
		{
			ClearBackground(BLACK);

			DrawRectangleRec(player1, WHITE);
			DrawRectangleRec(player2, WHITE);
			DrawCircleV(ballPosition, 10, WHITE);

			DrawText("Player 1: W = Up and S = Down", 10, 10, 20, WHITE);

			DrawText("Player 2: Arrow Up = Up and Arrow Down = Down", screenWidth - 500, 10, 20, WHITE);

			DrawText(("Player 1:" + std::to_string(scorePlayer1)).c_str(), 10, 50, 20, WHITE);
			DrawText(("Player 2:" + std::to_string(scorePlayer2)).c_str(), screenWidth - 500, 50, 20, WHITE);




		}
		const int winningScore = 5;
		if (scorePlayer1 >= winningScore || scorePlayer2 >= winningScore)
		{
			//Game over condition met, display a "Game Over" message
			DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 40) / 2, screenHeight / 2 - 40, 40, WHITE);
		}


		EndDrawing();
	}

	CloseWindow();

	return 0;
		
}