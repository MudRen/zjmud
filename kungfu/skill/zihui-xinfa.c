// zihui-xinfa �ϻ��ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("zihui-xinfa", 1);
	return lvl * lvl * 15 * 7 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" && (int)me->query_skill("zihui-xinfa", 1) > 49)
		return notify_fail("���޸����ԣ�������������������������ϻ��ķ���\n");

	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�ϻ��ķ���\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�ϻ��ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"zihui-xinfa/" + func;
}
