// /d/xingxiu/silk1.c
// Jay 3/17/96

inherit ROOM;

void create()
{
	set("short", "˿��֮·");
	set("long", @LONG
����һ����ԭ������֮����̵���������һ����ΰ�Ĺذ���������ͨ������
LONG );

	set("exits", ([
		"east" : __DIR__"jiayuguan",
		"west" : __DIR__"silk2",
	]));

	set("outdoors", "xiyu");

	setup();
}

