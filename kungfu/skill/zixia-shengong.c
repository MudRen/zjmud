// zixia-shengong.c ��ϼ��
// By Hop

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "huashan-xinfa"; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("zixia-shengong", 1);
	return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" &&
	    (int)me->query_skill("zixia-shengong", 1) > 49)
		return notify_fail("���޸����ԣ������������������������ϼ�񹦡�\n");

	if ((int)me->query_skill("force", 1) < 60)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ��ϼ�񹦡�\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��ϼ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"zixia-shengong/" + func;
}
