

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsan22",
		"north" : __DIR__"wulinsan24",
	]));
	set("price_build", 1000);
	setup();
}
