// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����������ʯ�������������ն�����Ƶģ�����᷶���������ڡ�
LONG );
	set("exits", ([
		"southdown" : __DIR__"yueguan",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}

