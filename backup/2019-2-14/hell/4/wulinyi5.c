// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wulinyi4",
		"south" : __DIR__"dongjie3",
	]));
	//set("price_build", 1000);
	setup();
}
