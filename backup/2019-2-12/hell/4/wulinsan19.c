

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"nanjie5",
		"west" : __DIR__"wulinsan20",
	]));
	set("price_build", 1000);
	setup();
}
