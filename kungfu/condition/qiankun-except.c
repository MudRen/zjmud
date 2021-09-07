// qiankun-except.c

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int n;

	if (me != ob)
	{
		tell_object(ob, "�㷢��" + me->name() + "���������澭����ӿ�룬һʱ"
			    "�䵤��֮����Ϣ��ս����ǰ��ʱһ�ڡ�\n");
		tell_object(me, "����ͼ����" + ob->name() + "��������������"
			    "ȴ��" + ob->name() + "��ɫ�Ұף����ɴ󾪣���æס�֡�\n");
		if (living(ob)) ob->unconcious();
		return -1;
	}

	if (me->query_skill_mapped("force") != "jiuyang-shengong")
	{
		tell_object(me, HIW "��ֻ���õ������纮����һ������"
			    "�;�����ͬǧ�ٸ�����һ���̡ܴ�"NOR"\n");
		return -1;
	}

	if (me->query_skill("jiuyang-shengong", 1) + 30 < duration)
	{
		tell_object(me, "����ͼ���þ����񹦻������"
			    "����֮�����������ǹ���һ��\n");
		return -1;
	}

	n = me->query_condition("qiankun-except") -
	    (int)me->query_skill("jiuyang-shengong", 1) / 10;
	if (n < 1)
		me->clear_condition("qiankun-except");
	else
		me->apply_condition("qiankun-except", n);

	tell_object(me, "��ĬĬ�����þ����񹦻������ڵ�����������\n");

	return 1;
}

int update_condition(object me, int duration)
{
	int limit;

	if (! living(me) && (me->query("eff_qi") < 100 || me->query("eff_jing") < 50))
	{
		me->set_temp("die_reason", "��Ϊǿ������Ǭ����Ų���񹦣��߻���ħ����");
		me->die();
		return 0;
	} else
	{
		me->receive_wound("qi", 100);
		me->receive_wound("jing", 50);
		tell_object(me, HIR "����õ��������䣬��������ȴ"
			    "������һ������֮����"NOR"\n");
		message("vision", me->name() + "��ɫ������죬ǿ�����˹�������\n",
			environment(me), me);
	}

	return 1;
}
