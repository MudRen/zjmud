// liangonge.c ������

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����Ƕ��������������������һЩ�����߳��õ�ľ�ˡ�
LONG );
	set("exits", ([
		"west" : __DIR__"liangong",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4
	]));
	set("for_family", "�������");
	setup();
}
