// Room: /xiakedao/shidong8.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
����һ��ʯ���������ǹ⻬��ʯ�ڣ�ʯ���ڸɸɾ�����һ����Ⱦ��
���Ե��Ż�ѣ��ǳ�������������һ�����ڵ�ʯ�š�
LONG );
	set("exits", ([
		"east" : __DIR__"shidong7",
	       "south" : __DIR__"road5"
	]));

	set("item_desc", ([
		"door" : "����һ�ȼ����ʯ�š�\n"
	]));

	set("objects", ([
		__DIR__"npc/dizi" : 1,
	]));
	setup();
}
