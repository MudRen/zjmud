// ��������

inherit SKILL;

string type() { return "art"; }

int valid_learn(object me)
{
	return notify_fail("��������������������������޷�"
			   "ͨ����ѧϰ���������\n");
}

int valid_research(object me)
{
	return notify_fail("��������������������������޷�"
			   "ͨ�����о����������\n");
}
