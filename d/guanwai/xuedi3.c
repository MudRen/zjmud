// /guanwai/xuedi3.c

inherit ROOM;

#include "gwxuedi.h"

void create()
{
	set("short", "ѩ��");
	set("long", @LONG
������һƬ��ãã��ѩ�أ�һ���������߼ʡ�����һ����ӰҲû�У���
��Ļ�ѩ������������֨�����������������һ���¶��Ľ�ӡ������ı���
��Х��������������ʹ��������̫����������ߣ��Ե���ô�԰ס�
LONG );
	set("exits", ([
		"north"  : __DIR__"chuanchang",
		"west"   : __DIR__"xuedi2",
	]));
	set("outdoors", "guanwai");
	setup();
}
