// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wulinyi19",
		"east" : __DIR__"beijie3",
	]));
	//set("price_build", 1000);
	setup();
}
