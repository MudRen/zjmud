// poison.c ��������
// Modified by Java Mar.1998
inherit SKILL;

void create() { seteuid(getuid()); }
string type() { return "poison"; }

int valid_learn(object me)
{
	if (me->query("character") == "��������")
		return notify_fail("�����а��룺�����¹������䣬ѧʲô������\n");

	return 1;
}
