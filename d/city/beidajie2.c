// Room: /city/beidajie2.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ�ֵ��������Ǳ�����ͨ����⣬
�ϱ��Եúܷ�æ��������һ�������¥�����ǡ�����¥�������߾�
������ѧ��֮������ͬ�����������ˡ�
LONG );
	set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"zuixianlou",
		"south" : __DIR__"beidajie1",
		"west"  : __DIR__"wumiao",
		"north" : __DIR__"beimen",
	]));
	setup();
}

