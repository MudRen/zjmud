#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���ſ�");
	set("long", @LONG
�����Ǿ������ǳǱ߿������ŵ�һ�������Ĵ�����������Ǿ��ǵ�������
�ˣ���ʵ��̵Ĺų�ǽ�߸������š�ÿ�춼������˾�������������뾩�ǡ�
�����Ǿ��ǵ���������֡�
LONG );
	set("exits", ([
		"west" : __DIR__"xichengmen",
		"east" : __DIR__"bei_1",
	]));
	set("objects", ([
		__DIR__"npc/tiaofu" : 1,
		__DIR__"npc/old2" : 1,
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

