// room2.c

inherit ROOM;

void create()
{
	set("short","������");
	set("long",
		"�����ǰ���ɽ���ӵ������ҡ��м����������µ�ľ������������\n"
	);
	set("exits",([
		"out" : __DIR__"fang",
	]));
	set("for_family", "ŷ������");

	set("objects",([
		"/clone/npc/mu-ren" : 4,
	]));

	setup();
}
