// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinyi3",
		"south" : __DIR__"wulinyi5",
	]));
	//set("price_build", 1000);
	setup();
}
