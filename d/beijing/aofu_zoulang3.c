#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
һ��ľ�ƽṹ�����ȣ����汻������һ����Ⱦ�����ǹ⻬��������Ѿ�ߺ�
���˴��������С����������ݵ��鷿�����������ݸ��ĺ�Ժ��
LONG );

	set("exits", ([
		"east" : __DIR__"aofu_houyuan",
		"west" : __DIR__"aofu_shufang",
	]));
	set("objects", ([
		__DIR__"npc/jiading_a" : 1,
		__DIR__"npc/yahuan_a" : 1,
	]));
	setup();
}
