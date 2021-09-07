// bahuang-gong.c �˻�����Ψ�Ҷ���

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "lingjiu-xinfa"; }

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("bahuang-gong", 1);
    return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 80)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if (me->query("gender") == "����" &&
	(int)me->query_skill("bahuang-gong", 1) > 49)
		return notify_fail("���޸����ԣ���������������������İ˻�����Ψ�Ҷ��𹦡�\n");

    	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�˻�����Ψ�Ҷ���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"bahuang-gong/" + func;
}
