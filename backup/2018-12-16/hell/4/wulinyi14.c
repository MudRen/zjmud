// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wulinyi13",
		"north" : __DIR__"wulinyi15",
	]));
	//set("price_build", 1000);
	setup();
}
