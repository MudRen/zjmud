// sword-cognize.c
// ��������

inherit SKILL;

int valid_learn(object me)
{
	return notify_fail("��������������ѧ����������޷�"
			   "ͨ����ѧϰ���������\n");
}

int valid_research(object me)
{
	return notify_fail("���������������ʵս���ļ�ȡ��"
			   "�գ��޷�ͨ���о�������\n");
}
