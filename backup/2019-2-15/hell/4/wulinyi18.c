// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wulinyi17",
		"east" : __DIR__"wulinyi19",
	]));
	//set("price_build", 1000);
	setup();
}
