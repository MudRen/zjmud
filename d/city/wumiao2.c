// Room: /city/wumiao2.c

#include <room.h>

inherit ROOM;
string look_shu();

void create()
{
	set("short", "�����¥");
	set("long", @LONG
������������Ķ�¥�����﹩�������ɵĳ������ƺ��������ܣ���������
���������Ӣ��������
LONG );

	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);

	set("exits", ([
		"down" : __DIR__"wumiao",
	]));
	setup();
}
