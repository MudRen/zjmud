// duanshi-xinfa.c �����ķ�
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "xiantian-qigong" ||
	       force == "quanzhen-xinfa"  ||
	       force == "kurong-changong";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("duanshi-xinfa", 1);
    return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
    	if (me->query("gender") == "����" &&
	    (int)me->query_skill("duanshi-xinfa") > 49)
    		    return notify_fail("���޸����ԣ���������������������Ķ����ķ���\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�����ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"duanshi-xinfa/" + func;
}
