// xiaoyao-xinfa.c ��ң�ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "beiming-shengong" ||
	       force == "xiaowuxiang";
}

int valid_learn(object me)
{
	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��ң�ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiaoyao-xinfa/" + func;
}
