// beimin-shengong.c ��ڤ��
// by doing

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "xiaoyao-xinfa" ||
	       force == "xiaowuxiang";
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("beiming-shengong", 1);
	return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("beiming-shengong", 1);

	if (me->query("gender") == "����" && lvl > 49)
		return notify_fail("���޸����ԣ���������������������ı�ڤ�񹦡�\n");

	if (me->query("int") < 32)
		return notify_fail("����ñ�ڤ�񹦼����ޱȣ�������ᡣ\n");

	if (me->query("con") < 24)
		return notify_fail("��������ת��һ����������ǰ��ʱһ�ڣ�\n");

	return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mapping result;
	int ap, dp;
	int jiali;

	if ((int) me->query_skill("beiming-shengong", 1) < 70 ||
	    ! living(me))
		return;

	if ((jiali = ob->query("jiali")) < 1)
		return;

	ap = ob->query_skill("force");
	dp = me->query_skill("force");
	if (ap / 2 + random(ap) < dp)
	{
		if (me->query("neili") < me->query("max_neili") * 2)
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
    return notify_fail("��ڤ��ֻ��ͨ��ѧϰ�����Ǵ�����(exert)�����������ȡ�\n");
}

string exert_function_file(string func)
{
    return __DIR__"beiming-shengong/" + func;
}
