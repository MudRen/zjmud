

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wulinsan16",
		"west" : __DIR__"wulinsan18",
	]));
	set("price_build", 1000);
	setup();
}