// fushang-neigong ��ɣ�ڹ�
// By Hop

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("fushang-shengong", 1);
	return lvl * lvl * 15 * 4 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 50)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ��ɣ�ڹ���\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��ɣ�ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"fushang-neigong/" + func;
}
