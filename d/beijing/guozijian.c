#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���Ӽ�");
	set("long", @LONG
������Ǿ��ǵĹ��Ӽࡣ���Ӽ��ǳ�͢�����˲ŵĵط����߸ߵ͵͵�����
�������š������ﲻʱ���Կ�������������ѧ��ģ�����˴���������ʲô���⣬
����һЩ������������üͷ�Ҵҵ��߹���������˼����ʲô���⡣
LONG NOR);
	set("exits", ([
		"south" : __DIR__"dong_2",
	]));
	set("objects", ([
		__DIR__"npc/shusheng1" : 3,
	]));
	set("outdoors", "beijing");
	setup();
}

