
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wulinsi13",
		"north" : __DIR__"dongjie6",
	]));
	set("price_build", 1000);
	setup();
}
