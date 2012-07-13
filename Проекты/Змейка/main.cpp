#include <hge.h>
#include <hgefont.h>
#include "snake.h"

#define count 6

HGE *hge=0;
hgeFont* fnt;
net quad[290];
int noWay[count] = { 7, 8, 7, 7, 8, 8 };

// Quad is the basic primitive in HGE
// used for rendering graphics.
// Quad contains 4 vertices, numbered
// 0 to 3 clockwise.

bool FrameFunc()
{
	using namespace std;
	vector <net>::iterator it = snake.begin();
	for ( int i = 0; i < count / 2; i++ )
		if ( (*it).n == noWay[i] && (*it).m == noWay[i + count/2] )
			return true;
	vector <work>::iterator jt;
	if ( (*it).square.v[0].x < 15 || (*it).square.v[2].x > 785 
		|| (*it).square.v[0].y < 63 || (*it).square.v[2].y > 449 )
		return true;
	if ( hge -> Input_GetKeyState(HGEK_ESCAPE))
		return true;

	const int speed = 32;
	float dx = 0.0f;
	float dy = 0.0f;
	float dt = hge -> Timer_GetDelta();

	if ( hge -> Input_GetKeyState(HGEK_RIGHT) )
		(*it).queue = right;
	if ( hge -> Input_GetKeyState(HGEK_DOWN) )
		(*it).queue = down;
	if ( hge -> Input_GetKeyState(HGEK_UP) )
		(*it).queue = up;
	if ( hge -> Input_GetKeyState(HGEK_LEFT) )
		(*it).queue = left;

	int kolvo = snake.size();
	int yes = 0;
	bool remove = false;
	for ( it = snake.begin(); it != snake.end(); it++ )
	{
		yes++;
		if ( (*it).queue == down )
		{
			if ( (*it).previous == right )
			{
				int i = 48;
				while ( (*it).square.v[2].x > i )
					i += 32;
				float module = (*it).square.v[2].x - i;
				if ( module > -0.11f )
				{
					(*it).toRight = false;
					(*it).toDown = true;
					(*it).reflux = true;
					(*it).previous = down;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = down;
					search.push_back( temp );
					(*it).increaseX = 0;
				}
			}
			if ( (*it).previous == left )
			{
				int i = 16;
				while ( (*it).square.v[0].x > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].x - i;
				if ( module > -0.11f )
				{
					(*it).toLeft = false;
					(*it).toDown = true;
					(*it).reflux = true;
					(*it).previous = down;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = down;
					search.push_back( temp );
					(*it).increaseX = 0;
				}
			}
		}
		if ( (*it).queue == right )
		{
			if ( (*it).previous == down )
			{
				int i = 96;
				while ( (*it).square.v[2].y > i )
					i += 32;
				float module = (*it).square.v[2].y - i;
				if ( module > -0.11f )
				{
					(*it).toDown = false;
					(*it).toRight = true;
					(*it).reflux = true;
					(*it).previous = right;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = right;
					search.push_back( temp );
					(*it).increaseY = 0;
				}
			}
			if ( (*it).previous == up )
			{
				int i = 64;
				while ( (*it).square.v[0].y > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].y - i;
				if ( module > -0.11f )
				{
					(*it).toUp = false;
					(*it).toRight = true;
					(*it).reflux = true;
					(*it).previous = right;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = right;
					search.push_back( temp );
					(*it).increaseY = 0;
				}
			}
		}
		if ( (*it).queue == up )
		{
			if ( (*it).previous == right )
			{
				int i = 48;
				while ( (*it).square.v[2].x > i )
					i += 32;
				float module = (*it).square.v[2].x - i;
				if ( module > -0.11f )
				{
					(*it).toRight = false;
					(*it).toUp = true;
					(*it).reflux = true;
					(*it).previous = up;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = up;
					search.push_back( temp );
					(*it).increaseX = 0;
				}
			}
			if ( (*it).previous == left )
			{
				int i = 48;
				while ( (*it).square.v[0].x > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].x - i;
				if ( module > -0.11f )
				{
					(*it).toLeft = false;
					(*it).toUp = true;
					(*it).reflux = true;
					(*it).previous = up;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = up;
					search.push_back( temp );
					(*it).increaseX = 0;
				}
			}
		}
		if ( (*it).queue == left )
		{
			if ( (*it).previous == up )
			{
				int i = 96;
				while ( (*it).square.v[0].y > i )
					i += 32;
				i -= 32;
				float module = (*it).square.v[0].y - i;
				if ( module > -0.11f )
				{
					(*it).toUp = false;
					(*it).toLeft = true;
					(*it).reflux = true;
					(*it).previous = left;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = left;
					search.push_back( temp );
					(*it).increaseY = 0;
				}
			}	
			if ( (*it).previous == down )
			{
				int i = 96;
				while ( (*it).square.v[2].y > i )
					i += 32;
				float module = (*it).square.v[2].y - i;
				if ( module > -0.11f )
				{
					(*it).toDown = false;
					(*it).toLeft = true;
					(*it).reflux = true;
					(*it).previous = left;
					(*it).queue = unknown;
					work temp;
					temp.x = (*it).n;
					temp.y = (*it).m;
					temp.moveTo = left;
					search.push_back( temp );
					(*it).increaseY = 0;
				}
			}
		}
		if ( (*it).toRight )
		{
			dx = speed * dt;
			(*it).square.v[0].x += dx; (*it).square.v[1].x += dx;
			(*it).square.v[2].x += dx; (*it).square.v[3].x += dx;
			(*it).increaseX += dx;
			if ( (32.0f - (*it).increaseX < 0.03f && 32.0f - (*it).increaseX > -0.03f) || (*it).increaseX > 32.0f )
			{
				(*it).increaseX = 0;
				(*it).reflux = true;
			}
			if ( (*it).increaseX > 1.0f && (*it).reflux )
			{
				(*it).n++;
				(*it).reflux = false;
			}
		}
		if ( (*it).toLeft )
		{
			dx = (-1) * speed * dt;
			(*it).square.v[0].x += dx; (*it).square.v[1].x += dx;
			(*it).square.v[2].x += dx; (*it).square.v[3].x += dx;
			(*it).increaseX -= dx;
			if ( (32.0f - (*it).increaseX < 0.03f && 32.0f - (*it).increaseX > -0.03f) || (*it).increaseX > 32.0f )
			{
				(*it).increaseX = 0;
				(*it).reflux = true;
			}
			if ( (*it).increaseX > 1.0f && (*it).reflux )
			{
				(*it).n--;
				(*it).reflux = false;
			}
		}
		if ( (*it).toUp )
		{
			dy = (-1) * speed * dt;
			(*it).square.v[0].y += dy; (*it).square.v[1].y += dy;
			(*it).square.v[2].y += dy; (*it).square.v[3].y += dy;
			(*it).increaseY -= dy;
			if ( (32.0f - (*it).increaseY < 0.03f && 32.0f - (*it).increaseY > -0.03f) || (*it).increaseY > 32.0f )
			{
				(*it).increaseY = 0;
				(*it).reflux = true;
			}
			if ( (*it).increaseY > 1.0f && (*it).reflux )
			{
				(*it).m--;
				(*it).reflux = false;
			}
		}
		if ( (*it).toDown )
		{
			dy = speed * dt;
			(*it).square.v[0].y += dy; (*it).square.v[1].y += dy;
			(*it).square.v[2].y += dy; (*it).square.v[3].y += dy;
			(*it).increaseY += dy;
			if ( (32.0f - (*it).increaseY < 0.03f && 32.0f - (*it).increaseY > -0.03f) || (*it).increaseY > 32.0f )
			{
				(*it).increaseY = 0;
				(*it).reflux = true;
			}
			if ( (*it).increaseY > 1.0f && (*it).reflux )
			{
				(*it).m++;
				(*it).reflux = false;
			}
		}

		




		if ( it != snake.begin() )
		{
			for ( jt = search.begin(); jt != search.end(); jt++ )
				if ( (*it).n == (*jt).x && (*it).m == (*jt).y )
				{
					(*it).queue = (*jt).moveTo;
					if ( yes == kolvo )
						remove = true;
				}
		}
		if ( remove )
			search.erase ( search.begin() );
		if ( !search.empty() )
			jt = search.begin();
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
	vector <net>::iterator it = snake.begin();
	while ( it != snake.end() )
	{
		hge->Gfx_RenderQuad( &(*it).square );
		it++;
	}
	it = snake.begin();
	int z = (*it).n;
	int x = (*it).m;
	it++;
	int c = (*it).n;
	int v = (*it).m;
	fnt->printf(5, 5, HGETEXT_LEFT, "x1 = %d | y1 = %d\n", z, x);
	
	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "hge_tut02.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGE Tutorial 02 - Using input, sound and rendering");

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
			quad[number].m = l;
			quad[number].n = k;
			quad[number].square.v[0].x = (float)i; quad[number].square.v[0].y = (float)j;
			quad[number].square.v[1].x = (float)i; quad[number].square.v[1].y = (float)j + 32;
			quad[number].square.v[2].x = (float)i + 32; quad[number].square.v[2].y = (float)j+32;
			quad[number].square.v[3].x = (float)i + 32; quad[number].square.v[3].y = (float)j;
			if ( (k == 7 && l == 7) || (k == 8 && l == 8) || (k == 7 && l == 8) )
				quad[number].various = wall;
			else if ( k == 2 && l == 2 )
			{
				quad[number].various = empty;
				quad[288].various = player;
				quad[288].square.v[0].x = (float)i; quad[288].square.v[0].y = (float)j;
				quad[288].square.v[1].x = (float)i; quad[288].square.v[1].y = (float)j + 32;
				quad[288].square.v[2].x = (float)i + 32; quad[288].square.v[2].y = (float)j+32;
				quad[288].square.v[3].x = (float)i + 32; quad[288].square.v[3].y = (float)j ;
				quad[288].n = k;
				quad[288].m = l;
				quad[288].queue = right;
				quad[288].previous = right;
			}
			else if ( k == 1 && l == 2 )
			{
				quad[number].various = empty;
				quad[289].various = player;
				quad[289].square.v[0].x = (float)i; quad[289].square.v[0].y = (float)j;
				quad[289].square.v[1].x = (float)i; quad[289].square.v[1].y = (float)j + 32;
				quad[289].square.v[2].x = (float)i + 32; quad[289].square.v[2].y = (float)j+32;
				quad[289].square.v[3].x = (float)i + 32; quad[289].square.v[3].y = (float)j ;
				quad[289].n = k;
				quad[289].m = l;
				quad[289].queue = right;
				quad[289].previous = right;
			
			}
			else
				quad[number].various = empty;
			number++;
			l++;
		}
		k++;
	}
	
	if(hge->System_Initiate())
	{
		fnt=new hgeFont("font1.fnt");
		// Load sound and texture
		for ( int i = 0; i < 290; i++ )
		{
			if ( quad[i].various == empty )
				quad[i].square.tex=hge->Texture_Load("particles.png");
			if ( quad[i].various == wall || quad[i].various == player)
				quad[i].square.tex = hge -> Texture_Load("walls.png");
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

		for ( int j = 0; j < 290; j++ )
		{
			// Set up quad which we will use for rendering sprite
			quad[j].square.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;

			for(int i=0;i<4;i++)
			{
				// Set up z-coordinate of vertices
				quad[j].square.v[i].z=0.5f;
				if ( quad[j].various == empty )
					// Set up color. The format of DWORD col is 0xAARRGGBB
					quad[j].square.v[i].col=0xFFFFFFFF;
				if ( quad[j].various == player )
					quad[j].square.v[i].col = 0xFFFFA000;
				if ( quad[j].various == wall )
					quad[j].square.v[i].col = 0xFFFFFFFF;
			}

			// Set up quad's texture coordinates.
			// 0,0 means top left corner and 1,1 -
			// bottom right corner of the texture.
			quad[j].square.v[0].tx=96.0/128.0; quad[j].square.v[0].ty=64.0/128.0; 
			quad[j].square.v[1].tx=128.0/128.0; quad[j].square.v[1].ty=64.0/128.0; 
			quad[j].square.v[2].tx=128.0/128.0; quad[j].square.v[2].ty=96.0/128.0; 
			quad[j].square.v[3].tx=96.0/128.0; quad[j].square.v[3].ty=96.0/128.0; 
		}
		quad[288].increaseX = 0.0f;
		quad[288].increaseY = 0.0f;
		quad[288].reflux = true;
		quad[288].toDown = false;
		quad[288].toLeft = false;
		quad[288].toRight = true;
		quad[288].toUp = false;

		quad[289].increaseX = 0.0f;
		quad[289].increaseY = 0.0f;
		quad[289].reflux = true;
		quad[289].toDown = false;
		quad[289].toLeft = false;
		quad[289].toRight = true;
		quad[289].toUp = false;
		
		snake.push_back( quad[288] );
		snake.push_back( quad[289] );

		// Let's rock now!
		hge->System_Start();

		delete fnt;
		for ( int i = 0; i < 290; i++ )
			// Free loaded texture and sound
			hge->Texture_Free(quad[i].square.tex);
	}
	else MessageBox(NULL, (LPCWSTR)hge->System_GetErrorMessage(), (LPCWSTR)"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
