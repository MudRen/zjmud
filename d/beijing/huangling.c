#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ʮ������");
	set("long", @LONG
���������������ʮ�����꣬�൱�ĺ�ΰ׳�ۡ�ʮ�������������Ͻ��ǵ�
������������������͵��������ࡣ
LONG NOR);
	set("exits", ([
		"south" : __DIR__"guandao_2",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 2,
	]));
	set("outdoors", "beijing");
	setup();
}

