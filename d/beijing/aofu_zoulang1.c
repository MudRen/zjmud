#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
һ��ľ�ƽṹ�����ȣ����汻������һ����Ⱦ�����ǹ⻬��������Ѿ�ߺ�
���˴��������С��ϱ��������Ĵ��ţ�������һ����԰��
LONG );

	set("exits", ([
		"north" : __DIR__"aofu_dayuan",
		"south" : __DIR__"aofu_men",
	]));
	set("objects", ([
		__DIR__"npc/yahuan_a" : 1,
	]));
	setup();
}
