// Room: /d/songshan/fawangsi.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����������ɽ�������£���Լ��ï�������У��˵����� "��ɽ
��һʤ��" ֮�ơ�
LONG );
	set("exits", ([
		"southdown" : __DIR__"shandao4",
		"northeast" : __DIR__"shandao5",
		"northup"   : __DIR__"tayuan",
		"west"      : __DIR__"yuetai",
	]));
	set("objects", ([
		__DIR__"npc/zhong" : 1,
		__DIR__"npc/deng" : 1,
		__DIR__"npc/gao" : 1,
	]));
	setup();
}

