// Room: /d/mingjiao/donglu.c

#include <room.h>
inherit ROOM;

int query_rate();

void create()
{
	set("short", "�����ľ�");
	set("long", @LONG
���ﶼ��һЩǧ���ľ������ߴ�ïʢ���˼������������ޱȡ�
������Ȼ�о���Щ�������Ĳ���������ǸϿ��뿪����Ϊ�á�
LONG );
	set("exits", ([
		"south" : __DIR__"donglu",
	]));

	set("insects/bingcan", (: query_rate :));

	set("outdoors", "mingjiao");
	setup();
}

int query_rate()
{
	object me;

	if (present("shenmu wangding", this_object()))
		return 3000;
	else
		return 500;

	return 0;
}
