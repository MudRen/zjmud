// jinshe-zhui.c

inherit SKILL;

int valid_learn(object me)
{
	object ob;

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������������û�а취������׶����\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹���û�а취������׶����\n");

	if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("jinshe-zhui", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ���׶����\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "throwing";
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("�����������û�а취��ϰ����׶����\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�������������û�а취��ϰ����׶����\n");

	me->receive_damage("qi", 35);
	me->add("neili", -48);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jinshe-zhui/" + action;
}
