// eyabi.c

inherit ROOM;

void create()
{
	set("short", "���±�");
	set("long", @LONG
������һ���ǳ����͵��±ڣ����ڵط�̫��խ�����������������
�˲����࣬����Ѫ���ŵ���Ҳ���治�����ĺ���֮ͽ���˼���ľ������
��������
LONG );
	set("exits", ([
		"west" : __DIR__"shandong2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 3,
	]));
	set("outdoors", "xuedao");
	set("for_family", "Ѫ����");
	setup();
}
