// Room: /d/songshan/shandao2.c
inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
��������ɽɽ�������ɴ�أ�ɽ�����ʱ��Ʈ����Զ��ɽ��
Ȯ�ͼ��䣬�����ɷ�֮�С�
LONG );
	set("exits", ([
		"northup"   : __DIR__"shuyuan",
		"southdown" : __DIR__"qimushi",
	]));
	set("no_clean_up", 0);
	set("outdoors", "songshan");
	setup();
}

