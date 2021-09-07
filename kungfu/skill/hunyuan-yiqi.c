// hunyuan-yiqi.c ���� ��Ԫһ����
// dts@xkx, cleansword@xkx

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int query_neili_improve(object me)
{
	int lvl;

	if (me->query("sex"))
		return 0;

	lvl = (int)me->query_skill("hunyuan-yiqi", 1);
	return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_force(string force)
{
	return force == "yijinjing" ||
	       force == "taiji-shengong" ||
	       force == "wudang-xinfa" ||
	       force == "shaolin-xinfa";
}

int valid_learn(object me)
{
	int i, nb, nf, nh, ns, ts;
	nb = (int)me->query_skill("buddhism", 1);
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("hunyuan-yiqi", 1);
	ns = (int)me->query("guilty");

	if (me->query("sex"))
		return notify_fail("���Ѿ�����ɫ�䣬�޷���ѧϰ��Ԫһ������\n");

	if (me->query("gender") != "����")
		return notify_fail("���ͯ��֮�壬������ϰ��Ԫһ������\n");

	if (nb < nh && nb < 200)
		return notify_fail("��������ķ���Ϊ�������޷���������Ļ�Ԫһ������\n");

	if (nf < 30)
		return notify_fail("��Ļ����ڹ���򻹲������޷�ѧϰ��Ԫһ������\n");

	if (nf < nh)
		return notify_fail("��Ļ����ڹ���򻹲������޷���������Ļ�Ԫһ������\n");

	if (ns > 0)
		return notify_fail("���ŷ�ɮ�����䣬�޷���������Ļ�Ԫһ������\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��Ԫһ����ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"hunyuan-yiqi/" + func;
}
