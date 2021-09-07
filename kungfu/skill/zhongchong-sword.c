// six-fingers.c ������ - �г彣
#include <ansi.h>
inherit SKILL;

mapping *action = ({
	([ "name":   "�г彣",
	   "action": "$N������ָһ�������г彣����ǰ�̳��������ĵ�����Ȼ���죬"
		     "���ν���ֱָ$n��$l",
	   "force":  490,
	   "dodge":  -15,
	   "damage": 110,
	   "damage_type": "����"
	]),
});

string main_skill() { return "six-finger"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���г彣������֡�\n");

	if ((int)me->query("max_neili") < 2250)
		return notify_fail("�������̫�����޷�ѧ�г彣��\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("zhongchong-sword", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��޷�����������г彣��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
	object* ob, obj;
	int i, skill, damage;

	if ((int)me->query_skill("six-finger", 1))
		return notify_fail("���Ѿ�ѧ���������ˡ�\n");

	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("��������������г彣��\n");

	me->receive_damage("qi", 40);
	me->add("neili", -80);
	return 1;
}
					  
mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;

	if( random(damage_bonus/4) > victim->query_str() )
	{
		victim->receive_wound("qi", (damage_bonus - 100) / 2 );
		return HIR "��������������һ�����죬���Ͼ�����һЩѪ�Σ�"NOR"\n";
	}
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}
