// ������

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" &&
	    (int)me->query_skill("yunlong-shengong", 1) > 49)
		return notify_fail("���޸����ԣ���������������������������񹦡�\n");

	if ((int)me->query_skill("force", 1) < 30)
		return notify_fail("��Ļ����ڹ���򻹲������޷���������񹦡�\n");

	return ::valid_learn(me);
}


int practice_skill(object me)
{
	return notify_fail("�����ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yunlong-shengong/" + func;
}
