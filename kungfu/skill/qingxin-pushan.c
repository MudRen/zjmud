// qingxin-pushan.c ����������

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "tanqin-jifa"; }

int valid_learn(object me)
{
	if (me->query_skill("tanqin-jifa", 1) < 50)
		return notify_fail("��ĵ��ټ���ˮƽ̫�������������˵�ɣ�\n");

	if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qingxin-pushan", 1))
		return notify_fail("��ĵ��ټ����������ޣ��޷�������������������䡣\n");

	return 1;
}

int practice_skill(object me)
{
	object ob;

	if (! objectp(ob = me->query_temp("handing")) ||
	    ! ob->valid_as_qin())
		return notify_fail("�㲻���������ϣ���ô��ϰ��\n");

	if ((int)me->query("jing") < 80)
		return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

	if ((int)me->query("qi") < 30)
		return notify_fail("�����ڿڸ����ʵ����̫���ˡ�\n");

	me->receive_damage("jing", 25);
	me->receive_damage("qi", 10);

	return 1;
}

void do_effect(object me)
{
	object *obs;
	int lvl;

	lvl = me->query_skill("tanqin-jifa", 1) / 2 +
	      me->query_skill("qingxin-pushan", 1);

	if (lvl < 100)
		return;

	// special effort
	obs = all_inventory(environment(me)) - ({ me });
	obs->receive_heal("jing", random(lvl / 10) + 10);
	message("vision", HIG "������" + me->name() +
		HIG "�����ӣ�����������ˬ������Ҳ�ö��ˡ�"NOR"\n",
		obs);
}

