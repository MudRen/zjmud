

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"xijie5",
		"south" : __DIR__"wulinsan26",
	]));
	set("price_build", 1000);
	setup();
}
