// Room: /city/guest.c

inherit ROOM;

void create()
{
	set("short", "���ͷ�");
	set("long", @LONG
���������ݹ㳡�������ϵ�����--���ͷ���angelus�����Ŀ��˶�ס�����
�����������ƣ������ɼ�һЩ���������ȥ�������˼�ʤ�ء�
LONG );
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"level_up",
		
	]));
	set("objects", ([
		"/clone/npc/learn_fly": 1,
		
	]));
	setup();
}

