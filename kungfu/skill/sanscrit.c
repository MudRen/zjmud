inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
	if ((int)me->query_skill("literate", 1) < 100)
		return notify_fail("��������д�ֶ�ûѧ�ã���ôѧϰ���ģ�\n");

	if ((int)me->query_skill("literate", 1) < (int)me->query_skill("sanscrit", 1))
		return notify_fail("��Ķ���д��ˮƽ���ޣ��޷����ո���µ����ġ�\n");

	return 1;

}

