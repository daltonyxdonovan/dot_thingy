#include <SFML/Graphics.hpp>
#include <atlstr.h>
#include <SFML/Network.hpp>

//in the standard namespace
using namespace std;

//variables
const int WIDTH{ 1920 };
const int HEIGHT{ 1080 };
const int amount{ 1000 };
bool terminal_disabled{ false };
int timer{ 0 };

class Dot
{
public:
	int x;
	int y;
	int r;
	int g;
	int b;
	int alpha;
	int speed_x;
	int speed_y;

	Dot(int x, int y)
	{
		this->x = x;
		this->y = y;
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		alpha = 255;
		speed_x = rand() % 4;
		speed_y = rand() % 4;
		if (speed_x == 0)
			speed_x = rand() % 4;
		if (speed_y == 0)
			speed_y = rand() % 4;
	}

	void draw(sf::RenderWindow &window)
	{
		sf::CircleShape circle(5);
		circle.setFillColor(sf::Color(r, g, b, alpha));
		circle.setPosition(x, y);
		window.draw(circle);
	}
};

vector<Dot> dots;

int main()
{
	//set up window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "collision_test", sf::Style::Fullscreen);
	sf::Event event;

	//hide terminal if needed
	if (terminal_disabled)
	{
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE);
	}
	
	for (int i = 0; i < amount; i++)
	{
		dots.push_back(Dot(rand()%1920,rand()%1080));
	}

	//look for events while the window is open
	while (window.isOpen())
	{
		
			
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::F1)
					terminal_disabled = !terminal_disabled;
			}
		}
		//clear the window
		window.clear(sf::Color::White);

		timer++;
		for (int i = 0; i < dots.size(); i++)
		{
			if (timer > 50)
			{
				dots[i].speed_x = (rand() % 8)-4;
				dots[i].speed_y = (rand() % 8)-4;
			}
			for (int j = 0; j < dots.size(); j++)
				if (i != j)
				{
					int dx = 0;
					int dy = 0;

					if (dots[i].x > dots[j].x)
						dx = dots[i].x - dots[j].x;
					else
						dx = dots[j].x - dots[i].x;

					if (dots[i].y > dots[j].y)
						dy = dots[i].y - dots[j].y;
					else
						dy = dots[j].y - dots[i].y;

					int dz = sqrt((dy * dy) + (dx * dx));
					if (dz < 50)
					{
						//draw a line between the points
						sf::Vertex line[] =
						{
							sf::Vertex(sf::Vector2f(dots[i].x + 5, dots[i].y + 5)),
							sf::Vertex(sf::Vector2f(dots[j].x + 5, dots[j].y + 5))
						};
						line->color = sf::Color::Black;
						window.draw(line, 4, sf::Lines);
					}
				}
			dots[i].draw(window);
			dots[i].x += dots[i].speed_x;
			dots[i].y += dots[i].speed_y;
			if (dots[i].x > WIDTH)
				dots[i].x = 0;
			if (dots[i].x < 0)
				dots[i].x = WIDTH;
			if (dots[i].y > HEIGHT)
				dots[i].y = 0;
			if (dots[i].y < 0)
				dots[i].y = HEIGHT;

			
		}
		if (timer > 50)
		{
			timer = 0;
		}







		
		//draw the window
		window.setFramerateLimit(60);
		window.display();
	}

	
	

	//return okay if the program exits properly
    return 0;
}