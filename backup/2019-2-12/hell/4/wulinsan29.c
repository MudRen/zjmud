

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinsan30",
		"south" : __DIR__"wulinsan28",
	]));
	set("price_build", 1000);
	setup();
}
