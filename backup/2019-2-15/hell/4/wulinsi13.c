
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wulinsi14",
		"north" : __DIR__"wulinsi12",
	]));
	set("price_build", 1000);
	setup();
}
