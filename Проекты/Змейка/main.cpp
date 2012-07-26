#define dontMove 80
#define range_min 0
#define numberOfObjects 2
#define allQuads 290

#include <hge.h>
#include <hgefont.h>
#include "snake.h"
#include <string>
#include "tinyxml.h"
#include <time.h>

net temp[numberOfObjects];
std::string invalidTokens;
float increase = 0.0f;
HGE *hge=0;
hgeFont* fnt;
net quad[allQuads];
int noWay[dontMove] = { 1,2,4,0,1,1,2,5,5,6,6,4,7,8,9,11,11,11,11,11,11,11,13,14,15,16,17,17,15,15,14,15,16,23,22,21,20,21,22,20,
	1,3,1,4,6,7,10,4,5,4,5,8,1,1,6,3,4,5,6,9,10,11,0,0,0,2,2,3,5,6,8,8,8,7,3,4,5,7,7,7
						};
bool collect = true;
bool reflux = true;
XToken token;
std::string description;
bool giveTask = true;
__int64 scores = 0;
TiXmlElement* tkn;
int objectX;
int objectY;
TiXmlDocument doc( "Course.xml" );
std::string fullText;
int topic;

int RangedRand( int range_max )
{
	int u = rand() % range_max;
	return u;
}

void newGame()
{
	scores -= 150;
	snake.clear();
	search.clear();
	snake.push_back( quad[288] );
	snake.push_back( quad[289] );
	increase = 0.0f;
	reflux = true;
}

bool checkSnakeForWalls()
{
	vector <net>::iterator it = snake.begin();
	for ( int i = 0; i < dontMove / 2; i++ )
		if ( (*it).n == noWay[i] && (*it).m == noWay[i + dontMove/2] )
		{
			newGame();
			return false;
		}
	return false;
}

bool checkSnakeOutOfRange()
{
	vector <net>::iterator it = snake.begin();
	if ( (*it).square.v[0].x < 15 || (*it).square.v[2].x > 785 
		|| (*it).square.v[0].y < 63 || (*it).square.v[2].y > 449 )
	{
		newGame();
		return false;
	}
	return false;
}

void setZBuffer( net &tales, float x )
{
	tales.square.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
	for ( int i = 0; i < 4; i++ )
		tales.square.v[i].z=x;
}

void setColour( net &tales, DWORD colour )
{
	for ( int i = 0; i < 4; i++ )
		tales.square.v[i].col = colour;
}

void setTexture( net &tales )
{
	tales.square.v[0].tx=96.0/128.0; tales.square.v[0].ty=64.0/128.0; 
	tales.square.v[1].tx=128.0/128.0; tales.square.v[1].ty=64.0/128.0; 
	tales.square.v[2].tx=128.0/128.0; tales.square.v[2].ty=96.0/128.0; 
	tales.square.v[3].tx=96.0/128.0; tales.square.v[3].ty=96.0/128.0;
}

void setCoordsForNewPart( net &tales )
{
	int max = snake.size();
	if ( tales.previous == up )
	{
		for ( int i = 0; i < 4; i++ )
		{
			tales.square.v[i].x = snake[max - 1].square.v[i].x;
			tales.square.v[i].y = snake[max - 1].square.v[i].y + 32;
		}
		if ( quad[snake[max - 1].n * 12 + snake[max - 1].m + 1].various == wall )
		{
			tales.n = snake[max - 1].n - 1;
			tales.m = snake[max - 1].m + 1;
		}
		else
		{
			tales.n = snake[max - 1].n;
			tales.m = snake[max - 1].m + 1;
		}
	}
	if ( tales.previous == rght )
	{
		for ( int i = 0; i < 4; i++ )
		{
			tales.square.v[i].x = snake[max - 1].square.v[i].x - 32;
			tales.square.v[i].y = snake[max - 1].square.v[i].y;
		}
		if ( quad[snake[max - 1].n * 12 - 12 + snake[max - 1].m].various == wall )
		{
			tales.n = snake[max - 1].n - 1;
			tales.m = snake[max - 1].m - 1;
		}
		else
		{
			tales.n = snake[max - 1].n - 1;
			tales.m = snake[max - 1].m;
		}
	}
	if ( tales.previous == down )
	{
		for ( int i = 0; i < 4; i++ )
		{
			tales.square.v[i].x = snake[max - 1].square.v[i].x;
			tales.square.v[i].y = snake[max - 1].square.v[i].y - 32;
		}
		if ( quad[snake[max - 1].n * 12 + snake[max - 1].m - 1].various == wall )
		{
			tales.n = snake[max - 1].n + 1;
			tales.m = snake[max - 1].m - 1;
		}
		else
		{
			tales.n = snake[max - 1].n;
			tales.m = snake[max - 1].m - 1;
		}
	}
	if ( tales.previous == lft )
	{
		for ( int i = 0; i < 4; i++ )
		{
			tales.square.v[i].x = snake[max - 1].square.v[i].x + 32;
			tales.square.v[i].y = snake[max - 1].square.v[i].y;
		}
		if ( quad[snake[max - 1].n * 12 + 12 + snake[max - 1].m].various == wall )
		{
			tales.n = snake[max - 1].n + 1;
			tales.m = snake[max - 1].m + 1;
		}
		else
		{
			tales.n = snake[max - 1].n + 1;
			tales.m = snake[max - 1].m;
		}
	}
}

void drawBegin( net &quad, int i, int j )
{
	quad.square.v[0].x = (float)i; quad.square.v[0].y = (float)j;
	quad.square.v[1].x = (float)i; quad.square.v[1].y = (float)j + 32;
	quad.square.v[2].x = (float)i + 32; quad.square.v[2].y = (float)j+32;
	quad.square.v[3].x = (float)i + 32; quad.square.v[3].y = (float)j ;
}

bool FrameFunc()
{
	using namespace std;
	vector <net>::iterator it = snake.begin();
	bool isOnWall = checkSnakeForWalls();
	if ( isOnWall )
		return true;
	vector <work>::iterator jt;
	if ( isOnWall = checkSnakeOutOfRange() )
		return true;
	if ( hge -> Input_GetKeyState(HGEK_ESCAPE))
		return true;

	const int speed = 32;
	float dx = 0.0f;
	float dt = hge -> Timer_GetDelta();

	if ( hge -> Input_GetKeyState(HGEK_RIGHT) )
		(*it).queue = rght;
	if ( hge -> Input_GetKeyState(HGEK_DOWN) )
		(*it).queue = down;
	if ( hge -> Input_GetKeyState(HGEK_UP) )
		(*it).queue = up;
	if ( hge -> Input_GetKeyState(HGEK_LEFT) )
		(*it).queue = lft;

	int vision = snake.size();
	int yes = 0;
	bool remove = false;
	for ( it = snake.begin(); it != snake.end(); it++ )
	{
		for ( int k = 0; k < numberOfObjects; k++ )
		if ( it == snake.begin() && ( (*it).n == temp[k].n && (*it).m == temp[k].m ) )
		{
			if ( k == 1 && token.text != invalidTokens )
			{
				newGame();
				return false;
			}
			collect = true;
			int max = snake.size();
			net tales;
			tales.previous = snake[max - 1].previous;
			tales.queue = snake[max - 1].queue;
			tales.various = player;
			tales.toDown = snake[max - 1].toDown;
			tales.toLeft = snake[max - 1].toLeft;
			tales.toRight = snake[max - 1].toRight;
			tales.toUp = snake[max - 1].toUp;
			setZBuffer(tales, 0.5f);
			setColour( tales, 0xFFFFFFFF);
			setTexture( tales );
			tales.square.tex = hge->Texture_Load("MainActor.png");
			
			setCoordsForNewPart( tales );
			snake.push_back( tales );
			vision++;
			it = snake.begin();
			scores += 10;
			if ( scores > 0 )
				scores *= 1.2;
			fullText.append(token.text);
			if ( token.space )
				fullText.append(" ");
			if ( !token.hasNext )
				giveTask = true;
		}
		quad[(*it).n * 12 + (*it).m].various = player;
		yes++;
		if ( (*it).queue == down )
		{
			if ( (*it).previous == rght )
			{
				int i = 48;
				while ( (*it).square.v[2].x > i )
					i += 32;
				float module = (*it).square.v[2].x - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toRight = false;
					(*it).toDown = true;
					reflux = true;
					(*it).previous = down;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = down;
						search.push_back( temp );  }
					increase = 0.0f;
				}
			}
			if ( (*it).previous == lft )
			{
				int i = 16;
				while ( (*it).square.v[0].x > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].x - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toLeft = false;
					(*it).toDown = true;
					reflux = true;
					(*it).previous = down;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = down;
						search.push_back( temp );   }
					increase = 0.0f;
				}
			}
		}
		if ( (*it).queue == rght )
		{
			if ( (*it).previous == down )
			{
				int i = 96;
				while ( (*it).square.v[2].y > i )
					i += 32;
				float module = (*it).square.v[2].y - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toDown = false;
					(*it).toRight = true;
					reflux = true;
					(*it).previous = rght;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = rght;
						search.push_back( temp );   }
					increase = 0.0f;
				} 
			}
			if ( (*it).previous == up )
			{
				int i = 64;
				while ( (*it).square.v[0].y > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].y - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toUp = false;
					(*it).toRight = true;
					reflux = true;
					(*it).previous = rght;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = rght;
						search.push_back( temp );   }
					increase = 0.0f;
				}
			}
		}
		if ( (*it).queue == up )
		{
			if ( (*it).previous == rght )
			{
				int i = 48;
				while ( (*it).square.v[2].x > i )
					i += 32;
				float module = (*it).square.v[2].x - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toRight = false;
					(*it).toUp = true;
					reflux = true;
					(*it).previous = up;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = up;
						search.push_back( temp );   }
					increase = 0.0f;
				}
			}
			if ( (*it).previous == lft )
			{
				int i = 48;
				while ( (*it).square.v[0].x > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].x - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toLeft = false;
					(*it).toUp = true;
					reflux = true;
					(*it).previous = up;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = up;
						search.push_back( temp );  }
					increase = 0.0f;
				}
			}
		}
		if ( (*it).queue == lft )
		{
			if ( (*it).previous == up )
			{
				int i = 96;
				while ( (*it).square.v[0].y > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].y - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toUp = false;
					(*it).toLeft = true;
					reflux = true;
					(*it).previous = lft;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = lft;
						search.push_back( temp );  }
					increase = 0.0f;
				}
			}	
			if ( (*it).previous == down )
			{
				int i = 96;
				while ( (*it).square.v[2].y > i )
					i += 32;
				float module = (*it).square.v[2].y - i;
				if ( module > -0.45f && module < 0.45f )
				{
					for ( int z = 0; z < 4; z++ )
					{
						(*it).square.v[z].x = quad[(*it).n*12+(*it).m].square.v[z].x;
						(*it).square.v[z].y = quad[(*it).n*12+(*it).m].square.v[z].y;
					}
					(*it).toDown = false;
					(*it).toLeft = true;
					reflux = true;
					(*it).previous = lft;
					(*it).queue = unknown;
					if ( it == snake.begin() ) {
						work temp;
						temp.x = (*it).n;
						temp.y = (*it).m;
						temp.moveTo = lft;
						search.push_back( temp );  }
					increase = 0.0f;
				}
			}
		}
		dx = speed * dt;
		if ( (*it).toRight )
		{
			(*it).square.v[0].x += dx; (*it).square.v[1].x += dx;
			(*it).square.v[2].x += dx; (*it).square.v[3].x += dx;

		}
		if ( (*it).toLeft )
		{
			(*it).square.v[0].x -= dx; (*it).square.v[1].x -= dx;
			(*it).square.v[2].x -= dx; (*it).square.v[3].x -= dx;
		}
		if ( (*it).toUp )
		{
			(*it).square.v[0].y -= dx; (*it).square.v[1].y -= dx;
			(*it).square.v[2].y -= dx; (*it).square.v[3].y -= dx;

		}
		if ( (*it).toDown )
		{
			(*it).square.v[0].y += dx; (*it).square.v[1].y += dx;
			(*it).square.v[2].y += dx; (*it).square.v[3].y += dx;

		}
		if ( it != snake.begin() )
		{
			for ( jt = search.begin(); jt != search.end(); jt++ )
				if ( (*it).n == (*jt).x && (*it).m == (*jt).y )
				{
					(*it).queue = (*jt).moveTo;
					if ( yes == vision )
						remove = true;
				}
		}
		if ( remove )
			search.erase ( search.begin() );
		if ( !search.empty() )
			jt = search.begin();
	}
	vector <net>::iterator bt;
	for ( it = snake.begin(); it+1 != snake.end(); it++ )
	{
		for ( bt = it+1; bt != snake.end(); bt++ )
		{
			if ( (*it).m == (*bt).m && (*it).n == (*bt).n )
			{
				newGame();
				return false;
			}
		}
	}
	int mismatch = 0;
	increase += dx;
	if ( increase > 31.5f )
	{
		increase = 0;
		reflux = true;
	}
	for ( it = snake.begin(); it != snake.end(); it++ )
		if ( increase > 4.0f && reflux )
		{
			if ( (*it).previous == up )
			{
				if ( it == snake.begin() + snake.size() - 1 )
					quad[(*it).n * 12 + (*it).m].various = empty;
				(*it).m--;
			}
			if ( (*it).previous == down )
			{
				if ( it == snake.begin() + snake.size() - 1 )
					quad[(*it).n * 12 + (*it).m].various = empty;
				(*it).m++;
			}
			if ( (*it).previous == lft )
			{
				if ( it == snake.begin() + snake.size() - 1 )
					quad[(*it).n * 12 + (*it).m].various = empty;
				(*it).n--;
			}
			if ( (*it).previous == rght )
			{
				if ( it == snake.begin() + snake.size() - 1 )
					quad[(*it).n * 12 + (*it).m].various = empty;
				(*it).n++;
			}
			if ( mismatch == snake.size() - 1 )
				reflux = false;
			mismatch++;
		}
		// Continue execution
	return false;
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{	
	// Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);

	// Render quads here. This time just
	// one of them will serve our needs.
	for ( int i = 0; i < 288; i++ )
		hge->Gfx_RenderQuad(&quad[i].square);
	for ( int i = 0; i < 2; i++ )
		hge -> Gfx_RenderQuad( &(temp[i].square) );
	vector <net>::iterator it = snake.begin();
	while ( it != snake.end() )
	{
		hge->Gfx_RenderQuad( &(*it).square );
		it++;
	}
	if ( collect )
	{
		for ( int i = 0; i < 2; i++ )
		{
			do
			{
				objectX = RangedRand( 24 );
				objectY = RangedRand( 12 );
			}
			while ( quad[objectX * 12 + objectY].various != empty );
			if ( !giveTask && i == 0 )
			{
				tkn = getNextToken( token, tkn );
				invalidTokens = generateInvalidToken();
			}
			if ( i == 0 )
				quad[objectX * 12 + objectY].various = object;
			else 
				quad[objectX * 12 + objectY].various = invalid;
			temp[i].m = objectY;
			temp[i].n = objectX;
			temp[0].various = object;
			temp[1].various = invalid;
			temp[i].square.tex = hge->Texture_Load("walls.png");
			setZBuffer( temp[i], 0.5f );
			setColour( temp[i], 0xFFFFFFFF );
			setTexture( temp[i] );
			for ( int j = 0; j < 4; j++ )
			{
				temp[i].square.v[j].x=quad[objectX * 12 + objectY].square.v[j].x;
				temp[i].square.v[j].y=quad[objectX * 12 + objectY].square.v[j].y;
			}
		}
		collect = false;
	}
	if ( giveTask )
	{
		topic = rand() % 8;
		fullText.clear();
		description = getDescription( topic );
		tkn = doc.FirstChildElement( "Root" );
		tkn = getFirstToken( topic, token, tkn, description );
		giveTask = false;
		std::string hf_descr_first = description.substr( 0, description.length() / 2 );
		std::string hf_descr_second = description.substr( description.length() / 2, description.length() );
		description = hf_descr_first + "\n" + hf_descr_second;
		invalidTokens = generateInvalidToken();
	}
	fnt -> Render(5, 5, HGETEXT_LEFT, description.data());
	fnt -> printf(quad[temp[0].n * 12 + temp[0].m].square.v[0].x + 5, quad[temp[0].n * 12 + temp[0].m].square.v[0].y - 32,
		HGETEXT_LEFT, token.text.data());
	fnt -> printf(quad[temp[1].n * 12 + temp[1].m].square.v[0].x + 5, quad[temp[1].n * 12 + temp[1].m].square.v[0].y - 32,
		HGETEXT_LEFT, invalidTokens.data());
	fnt -> printf(16, 470, HGETEXT_LEFT, "%d", scores);
	fnt -> printf(16, 450, HGETEXT_LEFT, fullText.data() );
	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	doc.LoadFile();
	srand( time(NULL) );
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);
	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "Snake.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Snake - the game");

	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 540);
	hge->System_SetState(HGE_SCREENBPP, 32);

	int number = 0;
	int k = 0;
  	for ( int i = 16; i < 784; i += 32 )
	{
		int l = 0;
		for ( int j = 64; j < 448; j += 32)
		{
			quad[number].various = empty;
			quad[number].m = l;
			quad[number].n = k;
			drawBegin( quad[number], i, j );
			for ( int q = 0; q < dontMove / 2; q++ )
			{
				if ( k == noWay[q] && l == noWay[q+dontMove/2] ) 
					quad[number].various = wall;
			}
			if ( k == 2 && l == 2 )
			{
				quad[number].various = empty;
				quad[288].various = player;
				drawBegin( quad[288], i, j );
				quad[288].n = k;
				quad[288].m = l;
				quad[288].queue = rght;
				quad[288].previous = rght;
			}
			else if ( k == 1 && l == 2 )
			{
				quad[number].various = empty;
				quad[289].various = player;
				drawBegin( quad[289], i, j );
				quad[289].n = k;
				quad[289].m = l;
				quad[289].queue = rght;
				quad[289].previous = rght;
			
			}
			number++;
			l++;
		}
		k++;
	}
	
	if(hge->System_Initiate())
	{
		fnt=new hgeFont("font1.fnt");
		// Load sound and texture
		for ( int i = 0; i < allQuads; i++ )
		{
			if ( quad[i].various == empty )
				quad[i].square.tex=hge->Texture_Load("particles.png");
			if ( quad[i].various == wall )
				quad[i].square.tex = hge -> Texture_Load("wall.png");
			if ( quad[i].various == player )
				quad[i].square.tex = hge -> Texture_Load("MainActor.png");
		}
		if(!quad[0].square.tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, (LPCWSTR)"Can't load MENU.WAV or PARTICLES.PNG", (LPCWSTR)"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		for ( int j = 0; j < allQuads; j++ )
		{
			// Set up quad which we will use for rendering sprite
			for(int i=0;i<4;i++)
			{
				// Set up z-coordinate of vertices
				if ( quad[j].various == empty )
				{
					setTexture( quad[j] );
					setZBuffer( quad[j], 0.5f );
					// Set up color. The format of DWORD col is 0xAARRGGBB
					quad[j].square.v[i].col=0xFFFFFFFF;
				}
				if ( quad[j].various == player )
				{
					quad[j].square.v[i].col = 0xFFFFFFFF;
					setTexture( quad[j] );
					setZBuffer( quad[j], 0.5f );
				}
				if ( quad[j].various == wall )
				{
					quad[j].square.v[i].col = 0xFFFFFFFF;
					setTexture( quad[j] );
					setZBuffer( quad[j], 0.5f );
				}
				
			}
			// Set up quad's texture coordinates.
			// 0,0 means top left corner and 1,1 -
			// bottom right corner of the texture.
		}
		quad[288].toDown = false;
		quad[288].toLeft = false;
		quad[288].toRight = true;
		quad[288].toUp = false;
		quad[289].toDown = false;
		quad[289].toLeft = false;
		quad[289].toRight = true;
		quad[289].toUp = false;
		snake.push_back( quad[288] );
		snake.push_back( quad[289] );
		// Let's rock now!
		hge->System_Start();
		delete fnt;
		for ( int i = 0; i < allQuads; i++ )
			// Free loaded texture and sound
			hge->Texture_Free(quad[i].square.tex);
		snake.clear();
		search.clear();
	}
	else MessageBox(NULL, (LPCWSTR)hge->System_GetErrorMessage(), (LPCWSTR)"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}