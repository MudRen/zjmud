// qiantang.c
// Date: Nov.1997 by Venus

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "Ǯ������");
	set("long", @LONG
Ǯ������ÿ�����ʮ���ǹ۳��ĺ����ӡ�������ʮ�˳���׳����
���ޡ������Ǻ���һ���澰����������ɽ�㵽����������
LONG);
	set("exits", ([
	    "north"     : __DIR__"road17",
	    "westup"    : __DIR__"liuheta",
	]));
	set("objects", ([
	    __DIR__"npc/jian-ke" : 1,
	]));
	set("outdoors", "hangzhou");
	setup();
}
