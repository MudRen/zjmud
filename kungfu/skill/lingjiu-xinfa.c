// lingjiu-xinfa.c �����ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "bahuang-gong"; }

int valid_learn(object me)
{
	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�����ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"lingjiu-xinfa/" + func;
}
