// huagong-dafa.c ������
// by yucao
// Modified by Venus Oct.1997

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

	lvl = (int)me->query_skill("huagong-dafa", 1);
	return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("character") == "��������")
		return notify_fail("�����а��룺��Ϊ�˹������䣬����ѧϰ���ֺ����书��\n");

	if (me->query("character") == "������")
		return notify_fail("�����а��룺����Ȼ����ǫǫ���ӣ����������˲��������书ѧ�����ã�\n");

	if ((int)me->query_skill("force", 1) < 80)
		return notify_fail("��Ļ����ڹ�����㣬����ѧ�����󷨡�\n");

	if ((int)me->query_skill("poison", 1) < 40)
		return notify_fail("��Ļ�����������㣬����ѧ�����󷨡�\n");

	if (me->query("gender") == "����" && (int)me->query_skill("huagong-dafa", 1) > 99)
		return notify_fail("���޸����ԣ���������������������Ļ����󷨡�\n");

	if ((int)me->query_skill("poison", 1) < 300 &&
	    (int)me->query_skill("poison", 1) < (int)me->query_skill("huagong-dafa", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ�������������Ļ����󷨡�\n");

	if ((int)me->query_skill("force", 1) < (int)me->query_skill("huagong-dafa", 1))
		return notify_fail("��Ļ����ڹ�ˮƽ���ޣ�������������Ļ����󷨡�\n");

	return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mapping result;
	int ap, dp;
	int jiali;

	if ((int) me->query_skill("huagong-dafa", 1) < 80 ||
	    ! living(me))
		return;

	if ((jiali = ob->query("jiali")) < 1)
		return;

	ap = ob->query_skill("force");
	dp = me->query_skill("force");
	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage" : -damage ]);

		switch (random(3))
		{
		case 0:
			result += ([ "msg" : HIM "$N" HIM "ֻ��������ԴԴ��й"
					     "�����ɵô��һ����"NOR"\n" ]);
			break;
		case 1:
			result += ([ "msg" : HIM "$N" HIM "ֻ���÷�����������"
					     "��ʯ���󺣣���֪���١�"NOR"\n" ]);
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
	return notify_fail("������ֻ����ѧ(learn)�������������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"huagong-dafa/" + func;
}
