// count.c

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{
}

int valid_learn(object me)
{
	object ob;

	if ((int)me->query_skill("mathematics", 1) < 50)
		return notify_fail("�������֪ʶ̫��޷�����������Եİ��\n");
	if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
		return notify_fail("�������֪ʶ���ޣ��޷�������µ��������ԡ�\n");
	if ((int)me->query_skill("count", 1) > (int)me->query("int")*10)
		return notify_fail("����������Բ������޷�������µ��������ԡ�\n");

	return 1;
}
