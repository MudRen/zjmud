inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("medical", 1) < 50)
		return notify_fail("��Ļ���ҽ������̫ǳ����"
				   "������������\n");

	if ((int)me->query_skill("medical", 1) < (int)me->query_skill("zhenjiu-shu", 1))
		return notify_fail("��Ļ���ҽ��ˮƽ���ޣ���"
				   "�����ո���µ��������\n");

	return 1;
}

