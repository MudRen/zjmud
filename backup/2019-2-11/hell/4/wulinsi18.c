
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsi17",
		"west" : __DIR__"wulinsi19",
	]));
	set("price_build", 1000);
	setup();
}
