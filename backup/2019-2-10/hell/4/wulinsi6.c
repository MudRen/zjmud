
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wulinsi5",
		"south" : __DIR__"wulinsi7",
	]));
	set("price_build", 1000);
	setup();
}
