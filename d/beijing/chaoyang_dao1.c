#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ڳ�������ĳ������ϣ���·��������������������֣���ʱ������
��������߷ɳ۶���������һ·���������߲�Զ�����ǳ������ˣ������Ƿ�
������������֣��������У�ʮ�����֡�
LONG );
       set("exits", ([
		"west" : __DIR__"wang_4",
		"east" : __DIR__"chaoyang_dao2",
	]));
	set("objects", ([
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

