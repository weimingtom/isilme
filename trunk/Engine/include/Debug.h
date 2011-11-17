#ifndef ISILME_DEBUG_H
#define ISILME_DEBUG_H

#ifdef _DEBUG

#define ASSERT( STATEMENT ) _ASSERT(STATEMENT)

#else

#define ASSERT( STATEMENT ) 

#endif
#endif