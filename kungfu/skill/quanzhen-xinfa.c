// quanzhen-xinfa ȫ���ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "xiantian-gong" ||
	       force == "duanshi-xinfa";
}

int valid_learn(object me)
{
       if (me->query_skill("force",1) <= me->query_skill("quanzhen-xinfa",1) )
	return notify_fail("��Ļ����ڹ������������޷����������ȫ���ķ���\n");
	   else    return 1;
}

int practice_skill(object me)
{
	return notify_fail("ȫ���ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"quanzhen-xinfa/" + func;
}
