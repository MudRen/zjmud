

inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wulinsi4",
		"east" : __DIR__"wulinsi6",
	]));
	set("price_build", 1000);
	setup();
}
