// yunv-xinfa.c ��Ů�ľ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("yunv-xinjing", 1);
	return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_force(string force)
{
    return (force == "yunv-xinfa");
}

int valid_learn(object me)
{
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ������ѵ���������ϰ��Ů�ľ���\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if ((int)me->query_skill("yunv-xinfa", 1) < 180)
		return notify_fail("�����Ů�ķ���򻹲�����\n");

	//if ( me->query("gender") == "����")
	//	return notify_fail("������̫ʢ���ֲ�����ϰ��Ů�ľ���\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��Ů�ľ�ֻ����ѧ(learn)�����������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yunv-xinjing/" + func;
}
