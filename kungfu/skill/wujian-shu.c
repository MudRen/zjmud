// �轣��

inherit SKILL;

string type() { return "art"; }

int valid_learn(object me)
{
	if (me->query_skill("art-cognize", 1) < 30)
		return notify_fail("����������̫ǳ�����������轣����\n");

	if (me->query_skill("wujian-shu", 1) > me->query_skill("art-cognize", 1))
		return notify_fail("�������������ޣ����������ո�������轣����\n");

	return 1;
}
