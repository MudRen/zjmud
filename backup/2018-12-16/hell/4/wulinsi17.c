
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wulinsi18",
		"north" : __DIR__"wulinsi16",
	]));
	set("price_build", 1000);
	setup();
}
