// sroad2.c
inherit ROOM;
void create()
{
	set("short", "ɽ·");
	set("long", @LONG
һ��ɽ·������ɽ�䡣������ȥ�����Լ�����ѩɽ����ɫ��ѩ
�����������ԡ�
LONG );
	set("exits", ([
		"eastdown"  : __DIR__"sroad1",
		"westup"    : __DIR__"sroad3",
	]));
	set("outdoors", "xuedao");
	setup();
}
