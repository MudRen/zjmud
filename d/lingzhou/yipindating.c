// Room: /lingzhou/yipindating.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "һƷ�ô���");
	set("long", @LONG
����������һƷ�õĴ��������������Ե��е����ޡ���ʮ���ϱ�
�������ſ����嶥�ķ��ܣ��������պ���ɭɭɷ�ˡ���������һ���ľ
�Ҷ�(bian)�������������ף�����������
LONG );
	set("item_desc", ([
		"bian"  : "һƷ��\n",
	]));
	set("exits", ([
		"south"  : __DIR__"yipindayuan",
	]));
	set("objects", ([
		__DIR__"npc/yipinwushi" :4,
	]));
	setup();
}
