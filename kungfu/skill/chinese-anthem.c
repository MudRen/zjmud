// chinese-anthem.c ���¾�������

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa" ||
					usage == "tanqin-jifa" ||
					usage == "guzheng-jifa"; }

int valid_learn(object me)
{
	return 1;
}

int practice_skill(object me)
{
	object ob;

	if ((int)me->query("jing") < 80)
		return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������ʵ����̫���ˡ�\n");

	me->receive_damage("jing", 50);
	me->receive_damage("qi", 50);

	return 1;
}

void do_effect(object me)
{
	object *obs;
	object attacker;
	object target;
	string msg;
	int lvl;
	int i;

	lvl = me->query_skill("chinese-anthem", 1);

	if (lvl < 200) return;
	
	// special effort
	target = 0;
	attacker = 0;
	obs = all_inventory(environment(me));
	for (i = 0; i < sizeof(obs); i++)
	{
		if (obs[i] == me || ! living(obs[i]))
			continue;

		if (obs[i]->is_fighting() && (target = obs[i]->query_competitor()) &&
		    target->query("nation") == "�ձ�")
		{
			attacker = obs[i];
			break;
		}
	}

	message("vision", HIY "���������׿��������Ĺ��裬������"
		"����֣�˵�������˷ܡ�"NOR"\n", obs, ({ me }));
	tell_object(me, HIY "�������������׿��������Ĺ��裬������"
		"����֣�˵�������˷ܡ�"NOR"\n");
	if (attacker)
	{
		if (attacker->query("gender") == "Ů��")
			msg = HIR "\nһʱ��$N" HIR "�������ĳ����ȣ�����"
			      "���ѣ���ĿԲ��������һ�����ȣ��������������ɣ���"NOR"\n";
		else
			msg = HIR "\nһʱ��$N" HIR "��������Ѫ���ڣ���$n"
			      HIR "��ȵ���������������������������"NOR"\n";
		message_vision(msg, attacker, target);
		
		i = (lvl - 200) / 10;
		if (i > 10) i = 10;
		while (i--)
			COMBAT_D->do_attack(attacker, target, attacker->query_temp("weapon"), 0);
	}
}
