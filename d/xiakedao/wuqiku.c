// wuqiku.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���������͵��������⣬���ϰ����˸���������������������ʿ
����ѡ��
LONG );
	set("exits", ([
		"east" : __DIR__"dating",
	]));
	set("objects", ([
		"/clone/weapon/zhujian" : 2,
		"/clone/weapon/zhubang" : 2,
		"/clone/weapon/changbian" : 1,
		"/clone/weapon/duanjian" : 1,
		"/clone/weapon/gangdao" : 1,
	]));
	setup();
}
