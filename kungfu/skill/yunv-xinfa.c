// yunv-xinfa.c ��Ů�ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("yunv-xinfa", 1);
	return lvl * lvl * 15 * 6 / 100 / 200;
}

int valid_force(string force)
{
    return (force == "yunv-xinjing");
}

int valid_learn(object me)
{
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ������ѵ���������ϰ��Ů�ķ���\n");

	if ((int)me->query_skill("force", 1) < 30)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��Ů�ķ�ֻ����ѧ(learn)�����������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yunv-xinfa/" + func;
}
