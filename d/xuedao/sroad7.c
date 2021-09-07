// sroad7.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��ѩɽ��");
	set("long", @LONG
Ⱥɽ���ƣ����ܻ�ѩ���겻�����ϱ߲�Զ����һ��ɽ�ȡ�
LONG );
	set("exits", ([
		"eastdown"  : __DIR__"sroad6",
		"southdown"   : __DIR__"sroad8",
	]));
	set("objects", ([
		__DIR__"npc/caiyaoren": 1,
	]));
	set("outdoors", "xuedao");
	setup();
}

int valid_leave(object me, string dir)
{
	if (! playerp(me))
		return ::valid_leave(me, dir);

	if (dir == "southup")
	{
		message_vision(HIW "ͻȻ��¡һ�����죬$N����̤"
			       "�˸��գ�... ��...ѩ���ˣ�"NOR"\n", me);
		if (me->query_dex() / 2 + random(me->query_dex()) < 13)
		{
			me->receive_damage("qi", 70);
			me->receive_wound("qi", 70);
		}
		tell_object(me, HIW "ֻ����Ƭ�Ļ�ѩ��ɽ���ϱ��ڶ��£���������"
				"�ǵص��˹�������;���д��˲�����ʯ���Ͻ������ɣ�"NOR"\n");
		message("vision", HIW "ֻ����Ƭ�Ļ�ѩ��ɽ���ϱ��ڶ��£���" + me->name(1) +
				  "����ǵص��˹�������;���д��˲�����ʯ���Ͻ������ɣ�"NOR"\n",
				  environment(me), ({ me }));
		if (me->query_dex() / 2 + random(me->query_dex()) >= 15)
		{
			me->move(__DIR__"sroad8");
			return -1;
		} else 
		{
			me->move(__DIR__"sroad5");
			return -1;
		}
	}
	return ::valid_leave(me,dir);
}

