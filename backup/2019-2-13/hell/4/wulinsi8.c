
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinsi7",
		"south" : __DIR__"wulinsi9",
	]));
	set("price_build", 1000);
	setup();
}
