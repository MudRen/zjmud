// mizong-neigong

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "longxiang" ||
	       force == "xiaowuxiang" ||
	       force == "xuehai-mogong";
}

int valid_learn(object me)
{
	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�����ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"mizong-neigong/" + func;
}
