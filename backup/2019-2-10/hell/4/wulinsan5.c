

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wulinsan4",
		"south" : __DIR__"wulinsan6",
	]));
	set("price_build", 1000);
	setup();
}
