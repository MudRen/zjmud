#include <room.h>

inherit ROOM;

void create()
{
	set("short", "С��");
	set("long", @LONG
һ���������Ͻ������ߵķ��ӣ�����İ���Ҳ�ܼ򵥡����ӵ����з���һ
��ˮ�ף�Ҳ��֪����������ʲô�ġ�ˮ���Ա�����һλ���ϵ�̫�࣬���Ի���
һ��С̫�����ź�
LONG );
	set("exits", ([
		"east" : __DIR__"hg",
	]));

	set("objects", ([
		__DIR__"npc/haigonggong" : 1,
		__DIR__"npc/xiaoguizi" : 1,
	]));

	setup();
}

void init()
{
	add_action("do_body", "tang");
}

