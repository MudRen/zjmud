// yaowang-mishu.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("medical", 1) < 100)
		return notify_fail("��Ļ���ҽ������̫ǳ����"
				   "�������µ�ҩ��������\n");

	if ((int)me->query_skill("medical", 1) < (int)me->query_skill("yaowang-miaoshu", 1))
		return notify_fail("��Ļ���ҽ��ˮƽ���ޣ���"
				   "�����ո���µ�ҩ��������\n");

	return 1;
}
