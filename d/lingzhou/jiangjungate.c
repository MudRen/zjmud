// Room: /lingzhou/jiangjungate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�󽫾���");
	set("long", @LONG
�����������󽫾����������ĸ��ڣ��ڶ���ֵ����У����������
�š�һɫ���ܴ��ݣ�����Уξ����ȥ�뺷���£��˿����������ֵĿ���
�䵶������ǰ��
LONG );
	set("exits", ([
		"north"  : __DIR__"dongdajie",
		"south"  : __DIR__"jiangjunyuan",
	]));
	set("objects", ([
		__DIR__"npc/xiaowei" : 2,
	]));
	setup();
	create_door("south" , "��ľ����", "north" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
	int i;
	object wei;

	wei = present("xiao wei", environment(me));
	if (dir != "south" || ! objectp(wei) || ! living(wei))
		return ::valid_leave(me, dir);

	if (me->query("weiwang") >= 10000)
	{
		message_vision("$NЦ������" + RANK_D->query_respect(me) +
			       "���������������ȥ����ͨ������\n", wei, me);
		return ::valid_leave(me, dir);
	}

	if (me->query("special_skill/trick"))
	{
		message_vision("$N����$n���˹�����������ס��"
			       "ȴ��$nһ���Ϻȣ���ɢ������\n"
			       "���ɵ�����һ����ڨڨ�Ĳ���˵����\n", wei, me);
		return ::valid_leave(me, dir);
	}

	return notify_fail("Уξ��ǰ��ס�㣬����˵������λ"  +
			   RANK_D->query_respect(me) + "��ذɡ���ү�����͡�\n");
}
