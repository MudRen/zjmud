// nyabi.c

inherit ROOM;
void create()
{
	set("short", "���±�");
	set("long", @LONG
������һ�����͵��±ڣ����ϵ����Ǳ��ȵúں����Ļ�ѩ��������
����м���Ѫ��������������
LONG );
	set("exits", ([
		"south" : __DIR__"shandong2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4,
	]));
	set("outdoors", "xuedao");
	set("for_family", "Ѫ����");
	setup();
}
