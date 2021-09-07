// Room: /d/shaolin/fumoquan.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��շ�ħȦ");
	set("long", @LONG
���ô������������ϸ����˸�������һ�˵Ĵ󶴣��и�����
¶����ɫɮ��һ�ǣ��ƺ�ס�����ˡ�������һƬ���ƺ�����Ĵ�
��ͺͺ�ģ��ƺ������ܴ����������´�ݲ�����
LONG );
	set("exits", ([
		"out" : __DIR__"qyping",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/du-nan" : 1,
		CLASS_D("shaolin") + "/du-e" : 1,
		CLASS_D("shaolin") + "/du-jie" : 1,
	]));
	setup();
}

void init()
{	
	mapping mine;
	object me;
	object ob1, ob2, ob3;

	me = this_player();
	mine = me->query("family");

	if (me->query_temp("valid_in_fumoquan"))
		return;

	if (mapp(mine) &&
	    mine["family_name"] == "������" &&
	    mine["generation"] <= 37)
	{
		me->set_temp("valid_in_fumoquan", 1);
		return;
	}

	if (! objectp(ob1 = present("du nan", this_object())) ||
	    ! living(ob1) ||
	    ! objectp(ob2 = present("du e", this_object())) ||
	    ! living(ob2) ||
	    ! objectp(ob3 = present("du jie", this_object())) ||
	    ! living(ob3) ||
	    ! interactive(me))
	{
		me->set_temp("valid_in_fumoquan", 2);
		return;
	}

	if (ultrap(me))
	{
		message_vision(HIG "��λ��ɮ�������������£���Ȼ��˿�������򶨲�����������
֪����ĵ�����"NOR"\n", me);
		CHANNEL_D->do_channel(this_object(), "rumor", "����ʦ" +
				      me->name(1) + "�����շ�ħȦ��");
		me->set_temp("valid_in_fumoquan", 1);
		return;
	}

	message_vision(HIR "ͻȻ�侢���ݺᣬ��������������������͵ع�����˲�����
����һ����ֱ�ı��У��糤ì����˰������������ֱ���$N��ͷ��
�أ�������Ҫ�����̶�����$NһƳ�䣬����������ɮ�־�������
��֮�У���ȫ���ֱ���$N������$N��������������֮�̺����Ͻ�
ħ�󷨵Ľ�շ�ħȦ��"NOR"\n", me);

	if (me->query("family/family_name") == "������" &&
	    me->query("combat_exp") < 200000)
	{
		message_vision(HIR "$N��һ����ɽ������ľ������У���ʱ���˳�ȥ !"NOR"\n", this_player());
		me->unconcious();
		me->move("/d/shaolin/qyping");
		return;
	}
/*
	if (me->query("family/family_name") == "������" &&
	    me->query("combat_exp") > 200000)
	{
		message_vision("��λ��ɮ����$N����¶�����΢Ц��"NOR"\n", this_player());
		me->set_temp("valid_in_fumoquan", 1);
		return;
	}
*/
	COMBAT_D->do_attack(ob1, me, ob1->query_temp("weapon"));
	COMBAT_D->do_attack(ob2, me, ob2->query_temp("weapon"));
	COMBAT_D->do_attack(ob3, me, ob3->query_temp("weapon"));
	if (me->query("qi") < 0)
	{
		me->unconcious();
		me->move("/d/shaolin/qyping");
		return;
	}

	me->set_temp("valid_in_fumoquan", 1);
	message_vision("��λ��ɮ�ջر��ӣ�����һ����\n\n", me);
	CHANNEL_D->do_channel(this_object(), "rumor", (mapp(mine) ? mine["family_name"] : "") +
			      me->name(1) + "�����շ�ħȦ��");
}

int valid_leave(object me, string dir)
{
	me->delete_temp("valid_in_fumoquan");
	return ::valid_leave(me, dir);
}

