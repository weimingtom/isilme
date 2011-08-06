//-----------------------------------------------------------------------------
// ������ � EAX �����������
// ��������� ��������� ��������� "�����"
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _EAX_H_INCLUDED_
#define _EAX_H_INCLUDED_

// ���������
#include <dsound.h>

////////////////////////////////////////////////
// �������
////////////////////////////////////////////////
#define EAX_NUM      3     // ������������ ����� ������ EAX ����������

#define EAX_LISTENER 0     // ��� ���������
#define EAX_BUFFER   1     // ��� �����

////////////////////////////////////////////////
// ������� ������
////////////////////////////////////////////////
LPKSPROPERTYSET   eax_GetBufferInterface(          // ��������� eax ���������� ��� ��������� ������
                  LPDIRECTSOUNDBUFFER buffer);

LPKSPROPERTYSET   eax_GetBuffer3DInterface(        // ��������� eax ���������� ��� ����������� ��������� ������
                  LPDIRECTSOUND3DBUFFER buffer3d);
/*
int               eax_TestQuerySupport(            // �������� ����������� ����������
                  LPKSPROPERTYSET prop,
                  int type,
                  int version);
*/
int               eax_Set(                         // ��������� eax ���������� 
                  LPKSPROPERTYSET prop,
                  int type,
                  int version,
                  void* data);

int               eax_Get(                         // ��������� eax ����������
                  LPKSPROPERTYSET prop,
                  int type,
                  int version,
                  void* data);

int               eax_Preset(                      // ��������� �������
                  LPKSPROPERTYSET prop,
                  int version,
                  int preset);

int               eax_TestSupport(                 // �������� ��������� ����������
                  LPDIRECTSOUND direct,
                  int version);

#endif
