// Room: /d/fuzhou/fzroad9.c
inherit ROOM;

void create()
{
	set("short", "���д��");
	set("long", @LONG
������������������ϡ�����������ɽ���࣬��ˮ���䣬ɽ
�����������ˣ����������㷡������й�����ð���ƺ��м�Ұ
�ꡣ
LONG );
	set("exits", ([
		"northwest" : __DIR__"fzroad8",
		"north"     : __DIR__"fzroad10",
		"east"      : __DIR__"fzroad11",
	]));
	set("objects", ([
		"/d/qingcheng/npc/jia" : 1,
	]));
	set("outdoors", "fuzhou");
	setup();
}

