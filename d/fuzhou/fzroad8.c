// Room: /d/fuzhou/fzroad8.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���Ӹ��ŷŽ����£�������ɽ�д䣬���㷺����С�۴�����
̲֮�У����ϻ���ˮ�죬����ƽ������������ʮ��ˮ·������Ϧ
����
LONG );
	set("exits", ([
		"northwest" : __DIR__"yanping",
		"southeast" : __DIR__"fzroad9",
	]));
	set("outdoors", "fuzhou");
	setup();
}

