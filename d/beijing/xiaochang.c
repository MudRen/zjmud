#include <room.h>
inherit ROOM;

void create()
{
	set("short", "У��");
	set("long", @LONG
�����Ǿ��Ǳ�Ӫ������һ����У����У�����������鵽�����ǹٱ�������
����ָ�����жӲ�����һ�����ٱ������������������š�����Щ̫������
���߶��������Ǿ�������������������֡�
LONG );
	set("exits", ([
		"east" : __DIR__"wang_3",
	]));

	set("objects", ([
		__DIR__"npc/taijian" : 1,
		__DIR__"npc/bing1" : 2,
		__DIR__"npc/bing2" : 2,
		__DIR__"npc/bing3" : 2,
		__DIR__"npc/yuqian1" : 1,
	]));

	setup();
}


