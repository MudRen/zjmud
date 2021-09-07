//hanxing-bada.c ���ǰ˴�

inherit SKILL;

int valid_learn(object me)
{
	object ob;

	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������������û�а취�����ǰ˴�\n");

	if ((int)me->query_skill("throwing", 1) < 180)
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������ǰ˴�����\n");

	if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("hanxing-bada", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ĺ��ǰ˴�����\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "throwing";
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("����������㣬�޷���ϰ���ǰ˴�\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�������������û�а취��ϰ���ǰ˴�\n");

	me->receive_damage("qi", 40);
	me->add("neili", -45);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hanxing-bada/" + action;
}
