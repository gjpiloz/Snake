#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
int N = 30, M = 20;
int size = 16;
int w = size*N;
int h = size*M;
int dir, prevDir, num = 4;

struct Snake
{int x, y;}  s[100];

struct Fruct
{int x, y;} f;

void Tick() {
	
	/*
	This FOR loop is what is moving the snake. 
	Counts it backwards making the current segment xy to be the xy value of the segment before it.
	*/
	for (int i = num; i > 0; i--) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	
	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	//If the snake head is touching the fruit
	if ((s[0].x == f.x) && (s[0].y == f.y)){
	    num++; // add one to the snake length
            f.x = rand() % N; // Move the fruit X position
            f.y = rand() % M; // Move the fruit Y position
	}

    if (s[0].x>N) s[0].x=0; if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0; if (s[0].y<0) s[0].y=M;

    for (int i = 1; i < num; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;
    }
}

int main() {
    srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake");

	Texture t1, t2, t3;
	t1.loadFromFile("images/black.png");
	t2.loadFromFile("images/green.png");
	t3.loadFromFile("images/red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);

	Clock clock;
	float timer=0, delay=0.1;

	f.x = 10;
	f.y = 10;

	while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}
		prevDir = dir;

		if (Keyboard::isKeyPressed(Keyboard::Left) && prevDir != 2) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right) && prevDir != 1) dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) && prevDir != 0) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down) && prevDir != 3) dir = 0;

		if (Keyboard::isKeyPressed(Keyboard::A) && prevDir != 2) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::D) && prevDir != 1) dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::W) && prevDir != 0) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::S) && prevDir != 3) dir = 0;

		if (timer > delay) {timer=0; Tick();}

        window.clear();

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                {sprite1.setPosition(i*size, j*size); window.draw(sprite1);}

        for (int i = 0; i < num; i++)
            {sprite2.setPosition(s[i].x*size, s[i].y*size); window.draw(sprite2);}

        sprite3.setPosition(f.x*size, f.y*size); window.draw(sprite3);

        window.display();
	}
    return 0;
}
