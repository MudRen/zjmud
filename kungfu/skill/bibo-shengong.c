// bibo-shengong.c �̲���
// By Jungu

inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("bibo-shengong", 1);
    return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_force(string force)
{
    return (force == "luoying-xinfa");
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("bibo-shengong", 1);

	if (me->query("gender") == "����" && lvl > 49)
		return notify_fail("���޸����ԣ�������������"
				   "��������ı̲��񹦡�\n");

	if (me->query_skill("chuixiao-jifa", 1) < 100)
		return notify_fail("��û�о�ͨ���＼�����޷�"
				   "���̲��񹦵İ��ء�\n");
       if (me->query_skill("force",1) <= me->query_skill("bibo-shengong",1) )
	return notify_fail("��Ļ����ڹ��������޷���������ı̲��񹦡�\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("�̲���ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

string exert_function_file(string func)
{
    return __DIR__"bibo-shengong/" + func;
}
