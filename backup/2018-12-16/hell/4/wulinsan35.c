

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsan36",
		"west" : __DIR__"wulinsan34",
	]));
	set("price_build", 1000);
	setup();
}

