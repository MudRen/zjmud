// Room: /city/zhujuan.c
#include <room.h>
inherit ROOM;
int is_chat_room() { return 1; }
void create()
{
	set("short", "��Ȧ");
	set("long", @LONG
������һ����������Ȧ�����Ϲ���һ������(paizi)��
LONG );
	set("no_fight", 1);
	set("no_sleep_room",1);
	set("item_desc", ([
		"�����ӡ�" : "���һ�𷢴�������̶���������硣\n",
	]));
	set("exits", ([
		"up"   : __DIR__"kedian",
	]));

	setup();
}

