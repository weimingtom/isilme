#if !defined( __libPerstStat_link_h__ )
#define __libPerstStat_link_h__

#if defined (_MSC_VER) 
#	if defined(_DEBUG)
#		pragma comment(lib, "xinput.lib")
#		pragma comment(lib, "luabind_d.lib")
#		pragma comment(lib, "hge_d.lib")
#		pragma comment(lib, "hgehelp_d.lib")
#		pragma comment(lib, "GUIChan_d.lib")
#		pragma comment(lib, "tinyxml_d.lib")
#		pragma comment(lib, "box2d_d.lib")
#		pragma comment(lib, "lua514_d.lib")
#	else
#		pragma comment(lib, "xinput.lib")
#		pragma comment(lib, "luabind.lib")
#		pragma comment(lib, "hge.lib")
#		pragma comment(lib, "hgehelp.lib")
#		pragma comment(lib, "GUIChan.lib")
#		pragma comment(lib, "tinyxml.lib")
#		pragma comment(lib, "box2d.lib")
#		pragma comment(lib, "lua514.lib")
#	endif
#endif

#endif  // __libPerstStat_link_h__