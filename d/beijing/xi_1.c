#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����������������Ҳ�Ǿ�����ķ����ضΡ�����������ʮ�����֡�����
��������һ���������������Ǿ��ǵĳ�����֡�������һ�����У�����ר��Ϊ
���ݳ���Ĺ��Ӹ������ġ����߲�Զ��������������ˡ�
LONG );
       set("exits", ([
		"east" : __DIR__"xi_2",
		"west" : __DIR__"niaoshi",
		"north" : __DIR__"bei_1",
		"south" : __DIR__"caroad_w1",
	]));
	set("objects", ([
		__DIR__"npc/boy1" : 1,
		__DIR__"npc/tiaofu" : 1,
		"/clone/npc/walker" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}
