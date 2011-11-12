#if !defined( __libPerstStat_link_h__ )
#define __libPerstStat_link_h__

#if defined (_MSC_VER) && defined (_LIB)
#	if defined(_DEBUG)
#	else
#	endif
#endif

#if defined (_MSC_VER) && !defined (_LIB)


#if _MSC_VER >= 1100

#ifdef _DEBUG
#else
#endif

#else  // _MSC_VER < 1100

#  pragma message ( "VC 5.0 libraries only supported")

#endif    // _MSC_VER >= 1100

#endif    //  _MSC_VER

#endif  // __libPerstStat_link_h__