// void.c

inherit ROOM;

void create()
{
	set("short","���");
	set("long",@LONG
������Ǵ�˵�е��޾���գ��㿴�����ܰ�ãã��һƬ��ʲôҲû�С�
ֻ�ǽ�����һ�����⣬�ƺ�������Ϥ��������
LONG
	);

	set("exits", ([
		"down" : "/d/city/zuixianlou",
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
	replace_program(ROOM);
}
