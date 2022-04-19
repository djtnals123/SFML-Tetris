#include <SFML/Graphics.hpp>
#include <windows.h>
#pragma warning(disable: 4996)
//////////////////////////////////////////////////////////////
// 상수
//////////////////////////////////////////////////////////////
#define winX 30  //창의 시작 위치
#define winY 2  //창의 시작 위치
#define winWidth 10 //창의 폭
#define winHeight 20 //창의 높이
#define GIUED_DOT_SIZE 2.0f // 블럭 중앙점 크기
#define COLOR White	//블럭 색상
//////////////////////////////////////////////////////////////
// 함수
//////////////////////////////////////////////////////////////
void Setting(); //개체 상태 설정, 1초에 25프레임
void InputKeyBoard(); //게임 객체 상태 업데이트, 시뮬레이션
void Start(); //게임 초기 상태 설정
int IsCollision(); //충돌 검사
void FixBrick(); //블록 고정하기
void NewBrick(); //새 블록 만들기
void BarCheck(); //누적된 막대 확인 제거, 점수 상승
void CreateRectangleShape(); //게임판 블록 생성
void setText(); // 텍스트 생성
				 //////////////////////////////////////////////////////////////
				 // 게임 객체의 구조체
				 //////////////////////////////////////////////////////////////
int brick_x, brick_y; //객체의 윈도우 안의 위치
int brick_shape, brick_rotation; //객체의 모양, 회전
int win[winHeight][winWidth]; //창의 내용물
int free_drop_delay = 20; //낙하 시간 간격
int free_drop_count; //낙하 시간 카운트 
					 // 객체의 모양 7개, 회전 4개, y, x
char brick[7][4][4][4] = {
	// ㅗ 회전 0
	0,1,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	// ㅏ 회전 1
	0,1,0,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,
	// ㅜ 회전 2
	0,0,0,0,
	1,1,1,0,
	0,1,0,0,
	0,0,0,0,
	// ㅓ 회전 3
	0,1,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//Z 회전0
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//Z 회전1
	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//Z 회전2
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//Z 회전3
	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//Z 회전0
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//Z 회전1
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,
	//Z 회전2
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//Z 회전3
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,
	//ㄱ회전0
	1,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//ㄱ회전1
	0,0,1,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//ㄱ회전2
	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,
	//ㄱ회전3
	0,0,0,0,
	1,1,1,0,
	1,0,0,0,
	0,0,0,0,
	//ㄴ회전0
	0,1,1,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	//ㄴ회전1
	0,0,0,0,
	1,1,1,0,
	0,0,1,0,
	0,0,0,0,
	//ㄴ회전2
	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,
	//ㄴ회전3
	1,0,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,
	//직선 회전0
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	//직선 회전1
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	//직선 회전2
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	//직선 회전3
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	//상자 회전0
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//상자 회전1
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//상자 회전2
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,
	//상자 회전3
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
	Start();  //게임 초기 상태 설정
	while (window.isOpen())
	{
		if (!GameOver)
		{
			Setting(); //개체 상태 설정
			InputKeyBoard(); //키보드 입력 및 개체관리
			Sleep(40); //40ms 잠자기
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
void Start() //게임 초기 상태 설정
{
	int x, y;
	NewBrick(); //새 개체 만들기
	free_drop_count = free_drop_delay; //20 프레임에 1회 다운
									   //테트리스 윈도우 초기화
	
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
int IsCollision() //게임 객체 충돌 검사
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
					return 1; //충돌 있음
				}
			}
		}
	}
	return 0; //충돌 없음
}
//////////////////////////////////////////////////////////////
void FixBrick() //게임 객체 고정
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
void NewBrick() //새로운 객체 만들기
{
	srand(time(NULL)); //난수 발생 시작점 초기화
	brick_x = ( rand() % (winWidth-5) ) +1; //객체의 x위치 1 ~ winWidth-5
	brick_y = 1; //객체의 y 위치
	brick_shape = rand() % 7; //모양 0 ~ 6
	brick_rotation = rand() % 4; //회전 0 ~ 3
}
//////////////////////////////////////////////////////////////
void BarCheck() //누적 블록 제거 점수 올리기
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
void Setting() //화면 상태 관리
{
	int x, y;
	char point[16];
	//창 셋팅
	for (y = 0; y<winHeight; y++)
	{
		for (x = 0; x<winWidth; x++)
		{
			if (win[y][x] == 1) rect_b[y][x].setSize(RECT_SIZE);
			else if (win[y][x] == 2) rect_w[y][x].setSize(RECT_SIZE);
			else rect_b[y][x].setSize(NON_SIZE);
		}
	}
	//블록 셋팅
	for (y = 0; y<4; y++)
		for (x = 0; x<4; x++)
			if (brick[brick_shape][brick_rotation][y][x] == 1)
				rect_b[brick_y + y][brick_x + x].setSize(RECT_SIZE);
	//포인트 표시
	sprintf(point, "Point : %d", GamePoint);
	text2.setString(point);
}
//////////////////////////////////////////////////////////////
void InputKeyBoard() //키보드 입력 및 개체관리
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
				FixBrick(); //개체 고정
				BarCheck(); //누적 상태 확인
				NewBrick(); //새 개체 만들기
				free_drop_count = free_drop_delay; //20 프레임에 1회 다운
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceCheck ==true)
		{
			do {
				brick_y++;
			} while (!IsCollision());
			brick_y--;
			if (brick_y == 1) GameOver = 1;
			FixBrick(); //개체 고정
			BarCheck(); //누적 상태 확인
			NewBrick(); //새 개체 만들기
			free_drop_count = free_drop_delay; //20 프레임에 1회 다운
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
			FixBrick(); //개체 고정
			BarCheck(); //누적 상태 확인
			NewBrick(); //새 개체 만들기
			free_drop_count = free_drop_delay; //20 프레임에 1회 다운
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
				rect_c[i][j].setPosition(((j + 5) * 20) + 7.5f - GIUED_DOT_SIZE / 2, ((i + 3) * 20) + 7.5f - GIUED_DOT_SIZE / 2); //중앙점 좌표설정
			}
		}
	}

}
//////////////////////////////////////////////////////////////
void setText()
{
	if (font.loadFromFile("arial.ttf"))//화면에 텍스트를 출력하기 위한 설정
	{
		text1.setString("Game over");		text1.setPosition(50, 200);
		text1.setColor(sf::Color::COLOR);	text1.setOutlineColor(sf::Color::Black);
		text1.setCharacterSize(0);		text1.setOutlineThickness(5.0f);	text1.setFont(font);

		text2.setPosition(100, 480); //포인트 텍스트
		text2.setColor(sf::Color::COLOR);	text2.setOutlineColor(sf::Color::Black);
		text2.setCharacterSize(20);		text2.setOutlineThickness(5.0f);	text2.setFont(font);

		text3.setString("120151374 Uh-SuMin(computer engineering department)");		text3.setPosition(125, 580);
		text3.setColor(sf::Color::COLOR);	text3.setOutlineColor(sf::Color::Black);
		text3.setCharacterSize(10);		text3.setOutlineThickness(5.0f);	text3.setFont(font);
	}
	else {}
}