#include <SFML/Graphics.hpp>
#include <windows.h>
#pragma warning(disable: 4996)
//////////////////////////////////////////////////////////////
// ���
//////////////////////////////////////////////////////////////
#define winX 30  //â�� ���� ��ġ
#define winY 2  //â�� ���� ��ġ
#define winWidth 10 //â�� ��
#define winHeight 20 //â�� ����
#define GIUED_DOT_SIZE 2.0f // �� �߾��� ũ��
#define COLOR White	//�� ����
//////////////////////////////////////////////////////////////
// �Լ�
//////////////////////////////////////////////////////////////
void Setting(); //��ü ���� ����, 1�ʿ� 25������
void InputKeyBoard(); //���� ��ü ���� ������Ʈ, �ùķ��̼�
void Start(); //���� �ʱ� ���� ����
int IsCollision(); //�浹 �˻�
void FixBrick(); //��� �����ϱ�
void NewBrick(); //�� ��� �����
void BarCheck(); //������ ���� Ȯ�� ����, ���� ���
void CreateRectangleShape(); //������ ��� ����
void setText(); // �ؽ�Ʈ ����
				 //////////////////////////////////////////////////////////////
				 // ���� ��ü�� ����ü
				 //////////////////////////////////////////////////////////////
int brick_x, brick_y; //��ü�� ������ ���� ��ġ
int brick_shape, brick_rotation; //��ü�� ���, ȸ��
int win[winHeight][winWidth]; //â�� ���빰
int free_drop_delay = 20; //���� �ð� ����
int free_drop_count; //���� �ð� ī��Ʈ 
					 // ��ü�� ��� 7��, ȸ�� 4��, y, x
char brick[7][4][4][4] = {
	// �� ȸ�� 0
	0,1,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	// �� ȸ�� 1
	0,1,0,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,
	// �� ȸ�� 2
	0,0,0,0,
	1,1,1,0,
	0,1,0,0,
	0,0,0,0,
	// �� ȸ�� 3
	0,1,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//Z ȸ��0
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//Z ȸ��1
	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//Z ȸ��2
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//Z ȸ��3
	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//Z ȸ��0
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//Z ȸ��1
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,
	//Z ȸ��2
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//Z ȸ��3
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,
	//��ȸ��0
	1,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//��ȸ��1
	0,0,1,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//��ȸ��2
	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,
	//��ȸ��3
	0,0,0,0,
	1,1,1,0,
	1,0,0,0,
	0,0,0,0,
	//��ȸ��0
	0,1,1,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//��ȸ��1
	0,0,0,0,
	1,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//��ȸ��2
	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,
	//��ȸ��3
	1,0,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��0
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	//���� ȸ��1
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��2
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	//���� ȸ��3
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��0
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��1
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��2
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//���� ȸ��3
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0
};

int GameOver = 0;
int GamePoint = 0;

sf::Clock _clock;
sf::Time _time;
sf::Text text1, text2, text3;
sf::Font font;
sf::RenderWindow window(sf::VideoMode(400, 600), "Tetris");
sf::RectangleShape rect_w[winHeight][winWidth];
sf::RectangleShape rect_b[winHeight][winWidth];
sf::RectangleShape rect_c[winHeight][winWidth];
const sf::Vector2f RECT_SIZE = { 15.0f, 15.0f };
const sf::Vector2f NON_SIZE = { 0.0f, 0.0f };
bool spaceCheck =true;


void main()
{
	Start();  //���� �ʱ� ���� ����
	while (window.isOpen())
	{
		if (!GameOver)
		{
			Setting(); //��ü ���� ����
			InputKeyBoard(); //Ű���� �Է� �� ��ü����
			Sleep(40); //40ms ���ڱ�
		}
		else
		{
			text1.setCharacterSize(60);
		}
		

		window.clear();
		for (int i = 0; i < winHeight; i++)
		{
			for (int j = 0; j < winWidth; j++)
			{
				window.draw(rect_b[i][j]);
				window.draw(rect_w[i][j]);
				window.draw(rect_c[i][j]);
			}
		}
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}
}
//////////////////////////////////////////////////////////////
void Start() //���� �ʱ� ���� ����
{
	int x, y;
	NewBrick(); //�� ��ü �����
	free_drop_count = free_drop_delay; //20 �����ӿ� 1ȸ �ٿ�
									   //��Ʈ���� ������ �ʱ�ȭ
	
	for (x = 0; x<winWidth; x++)
	{
		for (y = 0; y<winHeight; y++)
		{
			if (x == 0 || x == winWidth - 1 ||
				y == 0 || y == winHeight - 1)
			{
				win[y][x] = 2;
			}
			else
			{
				win[y][x] = 0;
			}
		}
	}
	setText();
	CreateRectangleShape();
}
//////////////////////////////////////////////////////////////
int IsCollision() //���� ��ü �浹 �˻�
{
	int x, y;
	for (y = 0; y<4; y++)
	{
		for (x = 0; x<4; x++)
		{
			if (brick[brick_shape][brick_rotation][y][x] == 1)
			{
				if (win[brick_y + y][brick_x + x] != 0)
				{
					return 1; //�浹 ����
				}
			}
		}
	}
	return 0; //�浹 ����
}
//////////////////////////////////////////////////////////////
void FixBrick() //���� ��ü ����
{
	int x, y;
	for (y = 0; y<4; y++)
	{
		for (x = 0; x<4; x++)
		{
			if (brick[brick_shape][brick_rotation][y][x] == 1)
			{
				win[brick_y + y][brick_x + x] = 1;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
void NewBrick() //���ο� ��ü �����
{
	srand(time(NULL)); //���� �߻� ������ �ʱ�ȭ
	brick_x = ( rand() % (winWidth-5) ) +1; //��ü�� x��ġ 1 ~ winWidth-5
	brick_y = 1; //��ü�� y ��ġ
	brick_shape = rand() % 7; //��� 0 ~ 6
	brick_rotation = rand() % 4; //ȸ�� 0 ~ 3
}
//////////////////////////////////////////////////////////////
void BarCheck() //���� ��� ���� ���� �ø���
{
	int x, y, bar, i, j;
	for (y = 1; y<winHeight - 1; y++)
	{
		bar = 0;
		for (x = 1; x<winWidth - 1; x++)
		{
			bar += win[y][x];
		}
		if (bar == winWidth - 2)
		{
			GamePoint++;
			if (GamePoint % 20 == 0) free_drop_delay--;
			if (free_drop_delay < 0) free_drop_delay = 0;
			for (i = y - 1; i>0; i--)
			{
				for (j = 1; j<winWidth - 1; j++)
				{
					win[i + 1][j] = win[i][j];
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////
void Setting() //ȭ�� ���� ����
{
	int x, y;
	char point[16];
	//â ����
	for (y = 0; y<winHeight; y++)
	{
		for (x = 0; x<winWidth; x++)
		{
			if (win[y][x] == 1) rect_b[y][x].setSize(RECT_SIZE);
			else if (win[y][x] == 2) rect_w[y][x].setSize(RECT_SIZE);
			else rect_b[y][x].setSize(NON_SIZE);
		}
	}
	//��� ����
	for (y = 0; y<4; y++)
		for (x = 0; x<4; x++)
			if (brick[brick_shape][brick_rotation][y][x] == 1)
				rect_b[brick_y + y][brick_x + x].setSize(RECT_SIZE);
	//����Ʈ ǥ��
	sprintf(point, "Point : %d", GamePoint);
	text2.setString(point);
}
//////////////////////////////////////////////////////////////
void InputKeyBoard() //Ű���� �Է� �� ��ü����
{
	sf::Event event;
	_time = _clock.getElapsedTime();
	float sec = _time.asSeconds();
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sec > 0.1)
		{
			brick_rotation++;
			if (brick_rotation > 3) brick_rotation = 0;
			if (IsCollision())
			{
				brick_rotation--;
				if (brick_rotation < 0) brick_rotation = 3;
			}
			_clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			brick_x--;
			if (IsCollision()) brick_x++;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			brick_x++;
			if (IsCollision()) brick_x--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			brick_y++;
			if (IsCollision())
			{
				brick_y--;
				if (brick_y == 1) GameOver = 1;
				FixBrick(); //��ü ����
				BarCheck(); //���� ���� Ȯ��
				NewBrick(); //�� ��ü �����
				free_drop_count = free_drop_delay; //20 �����ӿ� 1ȸ �ٿ�
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceCheck ==true)
		{
			do {
				brick_y++;
			} while (!IsCollision());
			brick_y--;
			if (brick_y == 1) GameOver = 1;
			FixBrick(); //��ü ����
			BarCheck(); //���� ���� Ȯ��
			NewBrick(); //�� ��ü �����
			free_drop_count = free_drop_delay; //20 �����ӿ� 1ȸ �ٿ�
			spaceCheck = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			GameOver = 1;
		}
		else {}
	}
	free_drop_count--;
	if (free_drop_count < 0)
	{
		free_drop_count = free_drop_delay;
		brick_y++;
		if (IsCollision())
		{
			brick_y--;
			if (brick_y == 1) GameOver = 1;
			FixBrick(); //��ü ����
			BarCheck(); //���� ���� Ȯ��
			NewBrick(); //�� ��ü �����
			free_drop_count = free_drop_delay; //20 �����ӿ� 1ȸ �ٿ�
		}
		if (spaceCheck == false)
			spaceCheck = true;
	}
}
//////////////////////////////////////////////////////////////
void CreateRectangleShape()
{
	const sf::Vector2f _GIUED_DOT_SIZE = { GIUED_DOT_SIZE, GIUED_DOT_SIZE };
	for (int i = 0; i < winHeight; i++)
	{
		for (int j = 0; j < winWidth; j++)
		{
			rect_w[i][j].setSize(NON_SIZE);
			rect_w[i][j].setPosition((j + 5) * 20, (i + 3) * 20);
			rect_w[i][j].setFillColor(sf::Color::Black);
			rect_w[i][j].setOutlineColor(sf::Color::COLOR);
			rect_w[i][j].setOutlineThickness(1.0);
			rect_b[i][j].setSize(NON_SIZE);
			rect_b[i][j].setFillColor(sf::Color::COLOR);
			rect_b[i][j].setPosition((j + 5) * 20, (i + 3) * 20);
			if (!(i == winHeight - 1 || j == winWidth - 1 || i == 0 || j == 0))
			{
				rect_c[i][j].setSize(_GIUED_DOT_SIZE);
				rect_c[i][j].setFillColor(sf::Color::COLOR);
				rect_c[i][j].setPosition(((j + 5) * 20) + 7.5f - GIUED_DOT_SIZE / 2, ((i + 3) * 20) + 7.5f - GIUED_DOT_SIZE / 2); //�߾��� ��ǥ����
			}
		}
	}

}
//////////////////////////////////////////////////////////////
void setText()
{
	if (font.loadFromFile("arial.ttf"))//ȭ�鿡 �ؽ�Ʈ�� ����ϱ� ���� ����
	{
		text1.setString("Game over");		text1.setPosition(50, 200);
		text1.setColor(sf::Color::COLOR);	text1.setOutlineColor(sf::Color::Black);
		text1.setCharacterSize(0);		text1.setOutlineThickness(5.0f);	text1.setFont(font);

		text2.setPosition(100, 480); //����Ʈ �ؽ�Ʈ
		text2.setColor(sf::Color::COLOR);	text2.setOutlineColor(sf::Color::Black);
		text2.setCharacterSize(20);		text2.setOutlineThickness(5.0f);	text2.setFont(font);

		text3.setString("120151374 Uh-SuMin(computer engineering department)");		text3.setPosition(125, 580);
		text3.setColor(sf::Color::COLOR);	text3.setOutlineColor(sf::Color::Black);
		text3.setCharacterSize(10);		text3.setOutlineThickness(5.0f);	text3.setFont(font);
	}
	else {}
}