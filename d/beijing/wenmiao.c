#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ġ���");
	set("long", @LONG
����������������п׷����������ʵ۶������������˼��������
�Լ��Ľ�ɽ��𢣬�����ʵ���ȻҲ�����⡣���ۺ��˵��ˣ����Ϲ��Ͼ�����
����ݡ�
LONG );
	set("exits", ([
		"south" : __DIR__"dong_3",
	]));

	set("objects", ([
		__DIR__"npc/shusheng1" : 2,
		__DIR__"npc/shusheng2" : 1,
	]));

	setup();
}

