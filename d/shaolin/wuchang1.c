// Room: /d/shaolin/wuchang1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
�����������µ����䳡����������޴�Ļ�����ʯ���̾͡�
��ǧ��Ĳ�̤��ʹ����Щʯ����ͬ���Ӱ�ƽ���⻬�����䳡�м�
�����Ų���ľ�ˡ�ʮ����ɮ��������ϰ���ա�������һ����ɮ����
LONG );
	set("exits", ([
		"south" : __DIR__"zoulang2",
		"west" : __DIR__"banruo5",
		"east" : __DIR__"wuchang",
		"north" : __DIR__"zoulang6",
	]));

	set("objects",([
		"/clone/npc/mu-ren" : 4
	]));

	set("outdoors", "shaolin");

	setup();
}

