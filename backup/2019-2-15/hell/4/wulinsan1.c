

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"beijie5",
		"east" : __DIR__"wulinsan2",
	]));
	set("price_build", 1000);
	setup();
}
