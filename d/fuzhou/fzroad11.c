// Room: /d/fuzhou/fzroad11.c
inherit ROOM;

void create()
{
	set("short", "���д��");
	set("long", @LONG
�������ǳǽ�����������Ҳ�����������������ݵĹٻ�����
���̶��Ѷ�����������ٴ죬����һ����ζ��
LONG );
	set("exits", ([
		"east"   : __DIR__"ximen",
		"west"   : __DIR__"fzroad9",
	]));
	set("outdoors", "fuzhou");
	setup();
}

