// Room: /d/fuzhou/ximen.c
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����Ǹ������š������������ɴ���ԭ��
LONG );
	set("exits", ([
		"east" : __DIR__"ximendajie",
		"west" : __DIR__"fzroad11",
	]));
	set("outdoors", "fuzhou");
	setup();
}

