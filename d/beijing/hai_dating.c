inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","���ι�������");
	set("long", @LONG
���Ǻ��ι����Ĵ�������������װ��Ҳ�������������������ﾹȻ��һ
�ȹ����ľ�������ʱ��������һƬ���ӣ�������������Ѱ�µ���ǰ������
LONG );
	set("exits", ([
		"north" : __DIR__"hai_dayuan",
		"south" : __DIR__"hai_houyuan",
	]));
	set("objects", ([
		__DIR__"npc/duolong" : 1,
		__DIR__"npc/zheng" : 1,
		__DIR__"npc/feng" : 1,
	]));

	setup();
}
