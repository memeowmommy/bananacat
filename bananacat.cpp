#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include "banan.h"




using namespace sf;



class CAT { // класс персонажа
public:
	float x, y, w, h, dx, dy, speed = 0;
	int dir = 0; 
	String File; 
	Image image;
	Texture texture;
	Sprite sprite;

	CAT(String F, float X, float Y, float W, float H) 
	{
		File = F;
		w = W; h = H; 
		image.loadFromFile("Images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; 
		y = Y;
		sprite.setTextureRect(IntRect(x, y, w, h));
		
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break; //left
		case 1: dx = -speed; dy = 0; break; //right
		case 2: dx = 0; dy = speed; break; //down
		case 3: dx = 0; dy = -speed; break; //up
		}

		x += dx * time;
		y += dy * time;


		speed = 0;
		sprite.setPosition(x+600, y+100); //чтобы кот выводился в середине
		//std::cout << "x: " << x << std::endl;
		//std:: cout<< "y: " << y << std::endl;
		
		
	}
};



 int main() {
	RenderWindow window(sf::VideoMode(1280, 720), "bananacat");
	
	//мяуканье
	SoundBuffer meow; 
	meow.loadFromFile("Sounds/meow.ogg");
	Sound m(meow);
	m.setVolume(30.f);

	//грустный мяу, когда бананакот врезается в стену
	SoundBuffer sad;
	sad.loadFromFile("Sounds/sad.ogg");
	Sound a(sad);
	a.setVolume(40.f);

	//фон
	Texture texture;
	texture.loadFromFile("Images/background.png");
	Sprite maze;
	maze.setTexture(texture);

	//банан
	Image banan;
	banan.loadFromFile("Images/banan.png");
	Texture b;
	b.loadFromImage(banan);
	Sprite ban;
	ban.setTexture(b);
	
	
	//часы, чтобы все двигалось
	float CurrentFrame = 0;
	Clock clock;

	//вызываем бананакота
	CAT p("bananacat.png", 0, 240, 76, 120);

	
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
		}

		
		//Управление персонажем с анимацией

		//вверх
		if ((Keyboard::isKeyPressed(Keyboard::W)) && (p.y>-70))
		{
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(76 * int(CurrentFrame), 360, 76, 120));
		}

		if ((Keyboard::isKeyPressed(Keyboard::W)) && (p.y <= -70)) { a.play(); }

		//вниз
		if (Keyboard::isKeyPressed(Keyboard::S) && (p.y<467)) 
		{
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(76 * int(CurrentFrame), 240, 76, 120));
		}

		if (Keyboard::isKeyPressed(Keyboard::S) && (p.y >= 467)) { a.play(); }

		//вправо
		if (Keyboard::isKeyPressed(Keyboard::D) && (p.x<575)) 
		{
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(76 * int(CurrentFrame), 120, 76, 120));
		}
		
		if (Keyboard::isKeyPressed(Keyboard::D) && (p.x >= 575)){ a.play(); }

		//влево
		if (Keyboard::isKeyPressed(Keyboard::A) && (p.x>-575)) 
		{
			p.dir = 1; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(76 * int(CurrentFrame), 0, 76, 120));
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && (p.x <= -575)) { a.play(); }
		
		//шипение
		if (Keyboard::isKeyPressed(Keyboard::G)) { a.play(); }
		//мяуканье
		if (Keyboard::isKeyPressed(Keyboard::M)) { m.play(); }
		
		// если бананкот нашел кожуру, то она исчезает
		for (int i = (p.y+100 ) / 64; i < (p.y + 170) / 64; i++)
		{
			for (int j = (p.x + 600) / 64; j < (p.x + 676) / 64; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					TileMap[i][j] = ' ';
					m.play();
				}

			}
		}
		p.update(time);

		window.clear();
		window.draw(maze);

		for (int i = 1; i < HEIGHT_MAP; i++)
			for (int j = 1; j < WIDTH_MAP-1; j++)
			{
				if (TileMap[i][j] == ' ')  ban.setTextureRect(IntRect(64, 0, 64, 64)); 
				if (TileMap[i][j] == 'B')  ban.setTextureRect(IntRect(0, 0, 64, 64));
				


				ban.setPosition(j * 64, i * 64);

				window.draw(ban);
			}

		
		window.draw(p.sprite);
		
		
		window.display();
	}

	return 0;
 }