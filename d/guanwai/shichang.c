// /guanwai/shichang.c

#include <room.h>

inherit PRODUCING_ROOM;

void create()
{
	set("short", "��ʯ��");
	set("long", @LONG
������ɽ�ţ���ǰ��Ȼ������һ����ɽ������һ���Ѿ���ը��֧��
���飬����������������������ʯ�ϡ��ڱ���Ҳ����ô���ʯɽ���㲻
����Щ���ȡ���ǰ��һ���ˣ�����������๤��
LONG );
	set("exits", ([
		"west" : __DIR__"tulu",
	]));

	set("objects", ([
		__DIR__"npc/jiangong" : 1,
	]));

	set("no_fight", 1);

	set("product/stone", ([ "name" : "ʯ��",
				"rate" : 1000,
				"max"  : 200000, ]));

	set("outdoors", "guanwai");
	setup();

	set_heart_beat(120);
}
