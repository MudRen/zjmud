// xixing-dafa.c ���Ǵ�
// by doing

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return 1;
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("xixing-dafa", 1);
	return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("xixing-dafa", 1);

	if (me->query("character") == "��������")
		return notify_fail("�����а��������ֺ����书����ѧ��������\n");

	if (me->query("con") < 20)
		return notify_fail("�����Ű��շ�����ת��һ����Ϣ����Ȼ"
				   "������������������ȴ��һ�������\n");

	if (lvl >= 10 && lvl < 50 && me->query("max_neili"))
		return notify_fail("��û�а������Ǵ󷨵ľ��Ͻ���"
				   "��ɢȥ�����ڻ��������Լ������д󷨡�\n");

	return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mapping result;
	int ap, dp;
	int jiali;

	if ((int) me->query_skill("xixing-dafa", 1) < 80 ||
	    ! living(me))
		return;

	if ((jiali = ob->query("jiali")) < 1)
		return;

	ap = ob->query_skill("force");
	dp = me->query_skill("force");
	if (ap / 2 + random(ap) < dp)
	{
		if (me->query("neili") < me->query("max_neili") * 15 / 10)
			me->add("neili", jiali);

		result = ([ "damage" : -damage ]);

		switch (random(4))
		{
		case 0:
			result += ([ "msg" : HIM "$N" HIM "ֻ��������ԴԴ��й"
					     "�����ɵô��һ����"NOR"\n" ]);
			break;
		case 1:
			result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
					     "��ʯ���󺣣���֪���١�"NOR"\n" ]);
			break;
		case 2:
			result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
					     "��Ӱ���٣���Ȼ��֪���䡣"NOR"\n" ]);
			break;
		default:
			result += ([ "msg" : HIM "$N" HIM "��ס�߶�����������"
					     "ֻ����$n" HIM "���ƺ���������"NOR"\n" ]);
			break;
		}
		return result;
	}
}

int practice_skill(object me)
{
	return notify_fail("���Ǵ�ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xixing-dafa/" + func;
}

void check_count(object me)
{
	if (me->query("max_neili") >= 3000 &&
	    me->query("exception/xixing-count") > 1000)
	{
		me->apply_condition("xixing-fanshi",
			me->query_condition("xixing-fanshi") +
			me->query("exception/xixing-count") / 10);
		me->delete("exception/xixing-count");
	}
}

void skill_improved()
{
	this_player()->add("exception/xixing-count",
			   (int)this_player()->query_skill("xixing-dafa", 1) + 1);
	check_count(this_player());
}
