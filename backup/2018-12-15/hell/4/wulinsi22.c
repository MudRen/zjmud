
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsi21",
		"west" : __DIR__"nanjie6",
	]));
	set("price_build", 1000);
	setup();
}
