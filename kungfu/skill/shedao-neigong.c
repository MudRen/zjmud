// shedao-neigong �ߵ��ڹ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force=="shenlong-xinfa";
}

int valid_learn(object me)
{
	return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("�ߵ��ڹ�ֻ��ͨ��ѧ���Ǵ�����(exert)�����������ȡ�\n");
}

string exert_function_file(string func)
{
    return __DIR__"shedao-neigong/" + func;
}
