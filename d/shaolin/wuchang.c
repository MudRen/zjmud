// Room: /d/shaolin/wuchang.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
�����������µ����䳡����������޴�Ļ�����ʯ���̾͡�
��ǧ��Ĳ�̤��ʹ����Щʯ����ͬ���Ӱ�ƽ���⻬�����߽��ϻ�
����������ɳ�ӣ�ʮ����ɮ��������ϰ���ա��������������һ����
����
LONG );
	set("exits", ([
		"south" : __DIR__"houdian",
		"east" : __DIR__"wuchang2",
		"west" : __DIR__"wuchang1",
		"north" : __DIR__"fzlou",
	]));
	set("outdoors", "shaolin");
	set("objects",([
		CLASS_D("shaolin") + "/dao-jue" : 1,
	]));
	setup();
}
