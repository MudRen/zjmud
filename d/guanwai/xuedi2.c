// /guanwai/xuedi2.c

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
		"east"       : __DIR__"xuedi3",
		"southwest"  : __DIR__"xuedi1",
	]));
	set("outdoors", "guanwai");
	setup();
}
