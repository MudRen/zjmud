

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wuliner23",
		"north" : __DIR__"wuliner25",
	]));
	set("price_build", 1000);
	setup();
}
