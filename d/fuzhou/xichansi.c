// Room: /d/fuzhou/xichansi.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������ʼ�����������������¥���Ϊ�����ͣ�����
ׯ�ϣ�������𲻾�������������������󣬶�����顣
LONG );
	set("exits", ([
		"north" : __DIR__"ximendajie",
	]));
	set("objects", ([
		"/d/wudang/npc/guest" : 1,
	]));
	set("outdoors", "fuzhou");
	setup();
}

