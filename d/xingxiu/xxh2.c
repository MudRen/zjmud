// Room: /d/xingxiu/xxh2.c
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "���޺�");
	set("long", @LONG
���������޺��ߡ�˵�Ǻ�����ʵ��Ƭ���������󣬵���ʮ���ն�
������������ͨ�����޺�������ϱ����������ܶ桪�����¶���
��������һ�����ӡ�
LONG );
	set("exits", ([
	     "north" : __DIR__"riyuedong",
	     "south" : __DIR__"xxh1",
	     "northeast" : __DIR__"xxh3",
	     "northwest" : __DIR__"xxh4",
	]));

	set("item_desc", ([
		"�����ӡ�" : "���޺����أ����¶����졣\n",
	]));

	set("outdoors", "xingxiu");
	setup();
}
