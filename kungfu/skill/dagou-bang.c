// dagou-bang.c �򹷰���
// Modified by Venus Oct.1997
// write by Xiang

inherit SKILL;

mapping *action = ({
([      "action": "$Nʹ��һ�С�����˫Ȯ��������$w���������������$n��$l",
	"force" : 280,
	"attack": 98,
	"dodge" : 120,
	"parry" : 100,
	"damage": 80,
	"damage_type": "����"
]),
([      "action": "$N����$w���һζ���һ�С�����Ѱ�ߡ���$n��$l��ȥ",
	"force" : 300,
	"attack": 100,
	"dodge":  100,
	"parry" : 120,
	"damage": 100,
	"damage_type": "����"
]),
([      "action": "$N����$w���Ӹ�����ʹһ�С���ݾ��ߡ�����$n��$l",
	"force" : 290,
	"attack": 99,
	"dodge":  120,
	"parry" : 100,
	"damage": 70,
	"damage_type": "����"
]),
([      "action": "$Nʩ�����������졹��$w����������$n��ȥ",
	"force" : 310,
	"attack": 105,
	"dodge" : 80,
	"parry" : 140,
	"damage": 90,
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 500)
		return notify_fail("��������������޷�ѧϰ�򹷰�����\n");

	if ((int)me->query_int() < 30)
		return notify_fail("���������Բ������������򹷰�����\n");

	if ((int)me->query_skill("staff", 1) < 100)
		return notify_fail("��Ļ����ȷ���򲻹����޷�ѧϰ�򹷰�����\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ĵ򹷰�����\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("��������������򹷰�����\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("��������������򹷰�����\n");

	me->receive_damage("qi", 64);
	me->add("neili", -71);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dagou-bang/" + action;
}
