// Room: /d/henshan/hengyang.c
// Modified by Java on Feb.14.1998

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������Ǻ����سǡ������ش�ƫԶ���Լ�Զ������ԭ�����ˡ�
LONG );
	set("outdoors", "hengyang");
	set("exits", ([
		"east"   : __DIR__"hsroad3",
		"west"   : __DIR__"hengyang1",
		"south"  : __DIR__"chaguan",
		"north"  : __DIR__"lingxingmen",
	]));
	set("objects", ([
		__DIR__"npc/lu" : 1,
	]));
	setup();
}

