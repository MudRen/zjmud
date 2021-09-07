// xixing-fanshi.c

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int n;

	if (me != ob)
	{
		tell_object(ob, "�㷢��" + me->name() + "������ԴԴӿ����ԭ"
			    "�����ҵ���Ϣ������������ǰ��ʱһ�ڡ�\n");
		tell_object(me, "����ͼ����" + ob->name() + "��������������"
			    "ȴ��Ȼ�����Լ�������ԴԴ���ţ����ɴ󾪣���æס�֡�\n");
		if (living(ob)) ob->unconcious();
		return -1;
	}

	if (me->query_skill_mapped("force") != "yijinjing" &&
	    me->query_skill_mapped("force") != "freezing-force")
	{
		tell_object(me, "���������������ͻ�ҳ壬��Ϣ"
			    "���ң������޷�����������������\n");
		return -1;
	}

	n = me->query_condition("xixing-fanshi") -
	    (me->query_skill("yijinjing", 1) + me->query_skill("freezing-force")) / 4;
	if (n < 1)
		me->clear_condition("xixing-fanshi");
	else
		me->apply_condition("xixing-fanshi", n);

	tell_object(me, "��ĬĬ�������񹦻������ڵ�����������\n");

	return 1;
}

int update_condition(object me, int duration)
{
	int limit;

	if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))
	{
		me->set_temp("��Ϊ��ϰ���Ǵ󷨲���������������Ѫ������");
		me->die();
		return 0;
	} else
	{
		me->receive_wound("qi", 20);
		me->receive_wound("jing", 10);
		if (me->query("max_neili"))
			me->add("max_neili", -1);
		tell_object(me, HIR "����õ�����Ϣ����֮������������"
				"�ȣ���֫���������������������ʡ�"NOR"\n");
		message("vision", me->name() + "��ɫ������죬��֫��ס�Ĳ�����\n",
			environment(me), me);
	}

	if (me->query("max_neili") < 1)
		duration = 1;
	me->apply_condition("xixing-fanshi", duration - 1);
	if (! duration) return 0;
	return 1;
}
