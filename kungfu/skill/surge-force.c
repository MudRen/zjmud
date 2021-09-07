// surge-force.c ŭ������

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("surge-force", 1);
	return lvl * lvl * 15 * 19 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") != "����")
		return notify_fail("�㲻�������Ե�����֮�����޷���ϰŭ�����Ρ�\n");

	if ((int)me->query_skill("force", 1) < 150)
		return notify_fail("��Ļ����ڹ���򻹲���������������ŭ�����Ρ�\n");

	if (me->query_str() < 45)
		return notify_fail("����������㣬������ϰŭ�����Ρ�\n");


	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("ŭ������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"surge-force/" + func;
}
