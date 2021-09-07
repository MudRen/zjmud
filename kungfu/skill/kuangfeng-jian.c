//kuangfeng-jian ���콣

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N����Ծ������$w��ӣ�ն��$n��",
	"force"  : 80,
	"attack" : 35,
	"parry"  : 10,
	"dodge"  : 30,
	"damage" : 75,
	"lvl"    : 0,
	"skill_name" : "��ƽ�˾�",
	"damage_type" : "����"
]),
([      "action" : "$N����$w�����������Σ���$n���ұ����ն��",
	"force"  : 100,
	"attack" : 45,
	"parry"  : 22,
	"dodge"  : 45,
	"damage" : 88,
	"lvl"    : 30,
	"skill_name" : "������ӿ",
	"damage_type" : "����"
]),
([      "action" : "$N����һ����ˢˢˢˢ�Ľ�����$n�أ������������Ĵ�����",
	"force"  : 120,
	"attack" : 51,
	"parry"  : 18,
	"dodge"  : 53,
	"damage" : 95,
	"lvl"    : 60,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action" : "$N����һ����Х��б����ǰ��$w����ֱ����Ѹ���ޱȣ�����$n��$l",
	"force"  : 150,
	"attack" : 58,
	"parry"  : 20,
	"dodge"  : 52,
	"damage" : 110,
	"lvl"    : 90,
	"skill_name" : "������ɢ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 200)
		return notify_fail("��������������޷���ϰ���콣��\n");

	if ((int)me->query_skill("dodge") < 90)
		return notify_fail("����Ṧ���̫ǳ���޷���ϰ���콣��\n");

	if ((int)me->query_dex() < 25)
		return notify_fail("��������������޷���ϰ���콣��\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("kuangfeng-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ŀ��콣��\n");

	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;
	int i;

	lvl = me->query_skill("sword-cognize", 1);
	i = random(lvl);

	if (me->query("family/family_name") == "��ɽ����" &&
	    i > 40 && random(2) == 0)
	{
		if (i < 100)
		{
			victim->receive_wound("qi", damage_bonus / 6);
			return HIC "ֻ��$N" HIC "����һ̽����â���ǣ�����$n��"NOR"\n";
		}
		if (i < 200)
		{
			victim->receive_wound("qi", damage_bonus / 4);
			return HIY "ֻ��$N" HIY "һ����Х��������ɣ�$n" HIY "�������У�"NOR"\n";
		} else
		{
			victim->receive_wound("qi", damage_bonus / 2);
			return HIW "����$N" HIW "΢΢һЦ�������ƶ�������$n" HIW "��Ȼ���У�"NOR"\n";
		}
	}
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action) - 1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	int j;

	level = (int) me->query_skill("kuangfeng-jian",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
		{
			j = me->query_skill("sword-cognize", 1);

			if (me->query("family/family_name") == "��ɽ����" && 
    			    random(j) > 180 &&
    			    random(level) > 180 && random(3) == 0)
			{
				return ([ "action" : WHT "$N" WHT "˫Ŀ���ؾ������䣬һ�С�" HIY 
    						     "�������" NOR WHT "���Ʋ��ɵ��ع���$n",
					  "force"  : (j - 50),
					  "attack" : j / 5,
					  "parry"  : (level / 2 + 50),
					  "dodge"  : (level / 2),
					  "damage" : j / 2,
					  "skill_name" : "�������",
					  "damage_type" : "����",
					]);
			}
			else return action[NewRandom(i, 20, level / 5)];
		}
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 65)
		return notify_fail("����������������콣��\n");

	if ((int)me->query("neili") < 20)
		return notify_fail("����������������콣��\n");

	me->receive_damage("qi", 60);
	me->add("neili", -16);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"kuangfeng-jian/" + action;
}

