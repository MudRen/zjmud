// wuchang1.c

inherit ROOM;

void create()
{
	set("short", "��ң��");
	set("long", @LONG
������û��ʲô����İ��裬ֻ������һЩ�������ɵ������õ�ľ�ˣ�
���������ǹ�����ң�ɵ��������õĳ�����
LONG
	);
	set("exits", ([
		"south" : __DIR__"xiaodao1",
		"north" : __DIR__"wuchang3",
	]));

 	set("objects", ([
		"/clone/npc/mu-ren" : 4,
	]));

	set("outdoors", "xiaoyao");
	set("for_family", "��ң��");
	setup();
}
