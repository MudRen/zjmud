
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/q/q456789/hell/qian",
		"north" : __DIR__"wulinsi10",
		"south" : __DIR__"dongjie6",
	]));
	set("price_build", 1000);
	setup();
}
