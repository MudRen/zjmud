// xiantian-gong.c ���칦
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "duanshi-xinfa" ||
	       force == "quanzhen-xinfa";
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("xiantian-gong", 1);
	return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" && (int)me->query_skill("xiantian-qigong", 1) > 49)
		return notify_fail("���޸����ԣ������ѵ����޷�ѧϰ����������칦��\n");

	if ((int)me->query_skill("force", 1) < 110)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if ((int)me->query_skill("taoism", 1) < 100)
		return notify_fail("��Ե����ķ������̫ǳ���޷�������칦��\n");

	if ((int)me->query_skill("taoism", 1) < 500 &&
	    (int)me->query_skill("taoism", 1) < (int)me->query_skill("xiantian-gong", 1))
		return notify_fail("��Ե����ķ���������ޣ��޷������������칦��\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("���칦ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiantian-gong/" + func;
}
