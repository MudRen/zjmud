// gate.c

#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "���Ź�" );
	set("long", 
		"�������������������ڡ����Źء���������ǰ������һ���ߴ��\n"
		"��ɫ��¥������������޿�������ж�ǰ������Ϊһ�����Źؾ��޷���\n"
		"�������ˡ�\n");
	set("exits", ([
		"north" : "/d/death/gateway",
	]) );
	set("objects", ([
		__DIR__"npc/wgargoyle":1
	]) );

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
}
