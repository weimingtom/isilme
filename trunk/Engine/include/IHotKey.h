#ifndef IHOT_KEY_H
#define IHOT_KEY_H

typedef DWORD Key;

class IHotKeyHandler
{
public:
	virtual void SetHotKey(Key) = 0;
};

#endif