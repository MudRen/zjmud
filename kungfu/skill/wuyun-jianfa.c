// wuyun-jianfa.c
inherit SKILL;

mapping *action = ({
([      "action" : "$N��Сָ�ᵯ��һ�С����ϡ���Ȼ����$n�ĺ���",
	"force" : 100,
	"dodge" : 20,
	"damage" : 20,
	"lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$N��������ָ�������޵�һ���������Ҳ���һ����[����]�ѽ�$n����",
	"force" : 120,
	"dodge" : 15,
	"damage" : 30,
	"lvl" : 20,
	"damage_type" : "����"
]),
([      "action" : "$N��ָ���ӣ�һʽ[����]���εĴ���$n������",
	"force" : 150,
	"dodge" : 15,
	"damage" : 40,
	"lvl" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N�����н���ɨ��ͬʱ�������������Ƶļ���������һ��[֧��]",
	"force" : 180,
	"dodge" : 10,
	"damage" : 50,
	"lvl" : 60,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ�������ϡ��������������ߣ���ͬ��������������������$n��$l",
	"force" : 210,
	"dodge" : 10,
	"damage" : 60,
	"lvl" : 80,
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry")
; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 400)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹���\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("wuyun-jianfa",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("��������������������ҽ���\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("��������������������ҽ���\n");

	me->receive_damage("qi", 40);
	me->add("neili", -38);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wuyun-jianfa/" + action;
}
