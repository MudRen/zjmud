// Room: /d/shaolin/maowu.c

inherit ROOM;

void create()
{
	set("short", "é��");
	set("long", @LONG
����һ�������é�ݣ����Ʋ�ȫ��������ȥ���Կ����������
������������������������������ӻ�������һ���龰��
LONG );

	set("exits", ([
		"north" : "/d/songshan/taishique",
	]));

	set("objects", ([
		__DIR__"npc/miao" : 1,
	]));

	setup();
}
