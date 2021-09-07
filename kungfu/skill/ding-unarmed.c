// ding-unarmed.c һ��һ��ȭ
inherit SKILL;

mapping *action = ({
([	"action" : "$N��������һĨ����$n��$l��ȥ",
	"force"  : 180,
	"damage" : 80,
	"damage_type" : "����"
]),
([	"action" : "$N����һ�ᣬ����$n��$l",
	"force"  : 230,
	"damage" : 100,
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("�������������һ��һ��ȭ��\n");

	me->receive_damage("qi", 35);
	me->add("neili", -32);

	return 1;
}
