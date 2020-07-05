﻿#pragma warning(disable : 4996).
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
#include "view.h"//подключили код с видом камеры
#include <iostream> // подключаем, чтобы посмотреть на время в консоли
#include <sstream>
using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
private: float x, y;//объявили переменные, в конструкторе Player ниже дадим им значения
public:
	float w, h, dx, dy, speed,health; // dx dy speed будут = 0 в конструкторе класса ниже
	//новая переменная, хранящая жизни игрока
	bool life;//переменная жизнь, логическая
	int dir, playerScore;//новая переменная, хранящая очки игрока; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H) { //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		dx = 0; dy = 0; speed = 2; dir = 0; playerScore = 0; health = 40; // инициализировали переменную жизни в конструкторе
		life = true;//инициализировали логическую переменную жизни
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile(File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов

	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}

		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy*time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y);
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <= 0){life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти
	}
	float getplayercoordinateX() {	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY() {	//этим методом будем забирать координату Y 	
		return y;
	}
	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		for (int i = y / 16; i < (y + h) / 16; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 16; j<(x + w) / 16; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0)//если мы шли вниз,
					{
						y = i * 16 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy<0)
					{
						y = i * 16 + 16;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx>0)
					{
						x = j * 16 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 16 + 16;//аналогично идем влево
					}
				}

				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
					playerScore++;//если взяли камень, переменная playerScore=playerScore+1;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
						health -= 40;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
						TileMap[i][j] = ' ';//убрали цветок
					}

				if (TileMap[i][j] == 'h') {
						health += 20;//если взяли сердечко,то переменная health=health+20;
						TileMap[i][j] = ' ';//убрали сердечко
					}
				
			}
	}
};

int main()
{
	Font font;//шрифт 
	font.loadFromFile("Calibri.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 15);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	Text text1("", font, 50);
	Text text2("", font, 15);
	text1.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text1.setStyle(Text::Bold);//жирный текст.
	RenderWindow window(sf::VideoMode(640, 480), "Tanks");
Image map_image;//объект изображения для карты
map_image.loadFromFile("1.png");//загружаем файл для карты
Texture map;//текстура карты
map.loadFromImage(map_image);//заряжаем текстуру картинкой
Sprite s_map;//создаём спрайт для карты
s_map.setTexture(map);//заливаем текстуру спрайтом
float CurrentFrame = 0;//хранит текущий кадр
Clock clock;

Player p("1.png", 1, 2, 13, 13);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

while (window.isOpen())
{

	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 800;


	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}


	///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
	if (p.life) {
		if ((Keyboard::isKeyPressed(Keyboard::Left))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			p.sprite.setTextureRect(IntRect(34, 1, 13, 13)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right))) {
			p.dir = 0; p.speed = 0.1;//направление вправо, см выше
			p.sprite.setTextureRect(IntRect(97, 1, 13, 13));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up))) {
			p.dir = 3; p.speed = 0.1;//направление вниз, см выше
			p.sprite.setTextureRect(IntRect(1, 2, 13, 13));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down))) { //если нажата клавиша стрелка влево или англ буква А
			p.dir = 2; p.speed = 0.1;//направление вверх, см выше
			p.sprite.setTextureRect(IntRect(65, 1, 13, 13)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

		}
	}
	p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
	viewmap(time);//функция скроллинга карты, передаем ей время sfml
	window.clear();
	/////////////////////////////Рисуем карту/////////////////////
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(288, 48, 16, 16)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(336, 112, 15, 14));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(256, 16, 16, 16));//если встретили символ 0, то рисуем 3й квадратик
			if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(256, 49, 15, 14));//добавили цветок
			if ((TileMap[i][j] == 's')) s_map.setTextureRect(IntRect(304, 112, 15, 14));//и сердечко
			s_map.setPosition(j * 16, i * 16);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
		}

	std::ostringstream playerHealthString;    // объявили переменную
	playerHealthString << p.health;		//занесли в нее число здоровья, то есть формируем строку
	text.setString("Health:" + playerHealthString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text.setPosition(view.getCenter().x +50, view.getCenter().y -480);//задаем позицию текста, отступая от центра камеры
	window.draw(text);//рисую этот текст
	std::ostringstream playerScoreString;    // объявили переменную
	playerScoreString << p.playerScore;//занесли в нее число очков, то есть формируем строку
	text.setString("Points:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text.setPosition(view.getCenter().x +50, view.getCenter().y - 460);//задаем позицию текста, отступая от центра камеры
	window.draw(text);//рисую этот текст
	text2.setString("--> point");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text2.setPosition(view.getCenter().x+55, view.getCenter().y - 90);//задаем позицию текста, отступая от центра камеры
	window.draw(text2);//рисую этот текст
	text2.setString("--> enemy");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text2.setPosition(view.getCenter().x +55, view.getCenter().y - 73);//задаем позицию текста, отступая от центра камеры
	window.draw(text2);//рисую этот текст
	text2.setString("--> health");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text2.setPosition(view.getCenter().x +55, view.getCenter().y - 56);//задаем позицию текста, отступая от центра камеры
	window.draw(text2);//рисую этот текст
	if (p.playerScore == 5) {
		window.clear();
		text1.setString("You win!");//задаем строку тексту и вызываем сформированную выше строку методом .str() 	
		text1.setPosition(view.getCenter().x - 260, view.getCenter().y - 320);//задаем позицию текста, отступая от центра камеры
		window.draw(text1);

	};
	if (p.health <= 0) {
		window.clear();
		text1.setString("Game over!");//задаем строку тексту и вызываем сформированную выше строку методом .str() 	
		text1.setPosition(view.getCenter().x - 280, view.getCenter().y - 320);//задаем позицию текста, отступая от центра камеры
		window.draw(text1);

	};
	window.draw(p.sprite);//рисуем спрайт объекта p класса player
	window.display();
}

return 0;
}

