#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�����η�");
	set("long", @LONG
����һ���谵�ķ��䣬�����������������Ϸ���Ƥ�ޡ�ľ�����̾ߣ���Ȼ
��������˽�����ã���Ѷ�˷������ڡ�һ������������ǽ�ϣ���Ѫ���죬����
���ˡ�
LONG );
	set("exits", ([
		"south" :  __DIR__"aofu_houyuan",
	]));
	set("objects", ([
		 __DIR__"npc/zhuangyu" : 1,
	]));

	setup();
}
