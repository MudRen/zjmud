
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsi20",
		"west" : __DIR__"wulinsi22",
	]));
	set("price_build", 1000);
	setup();
}
