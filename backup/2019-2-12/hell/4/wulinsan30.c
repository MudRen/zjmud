

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinsan31",
		"south" : __DIR__"wulinsan29",
	]));
	set("price_build", 1000);
	setup();
}
