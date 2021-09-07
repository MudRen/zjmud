// zhengting.c ����

#include <ansi.h>
inherit ROOM;

int do_sleep(string arg);

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǹ�Ĺ������������Ӧ��ͣ�����ѹ�ľ֮��Ķ�����ȴ��֪
�����˰㵽����ȥ�ˡ������ж�����һλ������Ů�������ϰڷ���һ
��ʯͷ���ɵĴ�(chuang)�����к�ϵ��һ�����ӣ���֪����ʲô��
�ģ�����֮�⣬���ް��衣
LONG
	);

	set("exits", ([
		"west"  : __DIR__"liangong",
		"north" : __DIR__"xiaoting",
		"south" : __DIR__"houting",
		"east"  : __DIR__"xiuxishi",
	]));

	set("objects", ([
		CLASS_D("gumu") + "/longnv" : 1,
		CLASS_D("gumu") + "/yang"   : 1,
	]));

	set("item_desc", ([
		"����": "����һ����"+HIB"ǧ�꺮��"NOR+"��ɵĺ��񴲡�\n"
				ZJOBACTS2"����ȥ:sleep\n",
	]) );
	set("valid_startroom",1);
	setup();
}

void init()
{
	add_action("do_sleep", "sleep");
}

int do_sleep(string arg)
{
	object me=this_player();
	int lvl_force;

	lvl_force = (int)me->query_skill("force", 1);
	if (lvl_force > 150)
	{
		message_vision("$N�����˺��񴲣���ʼǱ���ڹ���ʹ��Ϣ���д�С���졣\n", this_player());
		if (random(20) > 12)
		{
			message_vision("$N��Ϣ��ϣ�ֻ���þ���������Ϣ���������ڶ�����\n", this_player());
			if (me->can_improve_skill("force") && lvl_force < 180)
				me->improve_skill("force", 1 + lvl_force / 20);

			me->receive_damage("qi", lvl_force / 3 + random(lvl_force / 3));
		}
		else
		{
			message_vision("$N��Ϣ��ϣ�վ������������������������ûʲô������\n", this_player());
			me->receive_damage("qi", 10 + random(10));
		}
	} else
	{
		message_vision("$N���Ϻ��񴲣�ֻ���ñ���̹ǣ���������һ���Ǳ�����������������\n",this_player());
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	object yang;

	if ((dir == "west" || dir == "east") &&
	    objectp(yang = present("yang guo", this_object())))
		return yang->permit_pass(me, dir);

	return ::valid_leave(me, dir);
}
