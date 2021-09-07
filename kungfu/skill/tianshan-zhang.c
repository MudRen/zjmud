// tianshan-zhang.c, based on dagou-bang.c
// by yucao
// Modified by Hop 97.01.05
// Added by Yzuo 97.04.08

inherit SKILL;

mapping *action = ({
([	"action": "$Nʹ��һ�С����ӿ�����������$w�󿪴���ɨ��$n��$l",
	"force" : 150,
	"attack": 30,
	"parry" : 11,
	"dodge" : -5,
	"damage": 35,
	"damage_type": "����"
]),
([	"action": "$N����$w������죬һ�С�ɽ����������$n��$l��ȥ",
	"force" : 160,
	"attack": 71,
	"parry" : 50,
	"dodge" : 16,
	"damage": 45,
	"damage_type": "����"
]),
([	"action": "$N����$w���Ӹ�����ʹһ�С���ɽѩ��������$n��$l",
	"force" : 160,
	"attack": 80,
	"parry" : 15,
	"dodge" : 5,
	"damage": 60,
	"damage_type": "����"
]),
([	"action": "$Nһ�С�������ѩ��������Ʈ�����ߣ�����$w����$n��$l",
	"force" : 130,
	"attack": 41,
	"parry" : 22,
	"dodge" : 71,
	"damage": 30,
	"damage_type": "����"
]),
([	"action": "$Nʹһ�С��ع�õ硹������$w��һ���������$n��$l",
	"force" : 180,
	"attack": 70,
	"parry" : 70,
	"dodge" : -20,
	"damage": 40,
	"damage_type": "����"
]),
([	"action": "$Nʹ���ġ���˪��Ӱ����$w������Ӱ��������$n��$l",
	"force" : 220,
	"attack": 52,
	"parry" : 55,
	"dodge" : -20,
	"damage": 42,
	"damage_type": "����"
]),
([	"action": "$N��$wƾ��һָ��һ�С���ʯ���̡�����$n��$l",
	"force" : 150,
	"attack": 40,
	"parry" : 26,
	"dodge" : 20,
	"damage": 40,
	"damage_type": "����"
]),
([	"action": "$N����һԾ������$wһ�С�������������׼$n��$lɨȥ",
	"force" : 170,
	"attack": 71,
	"parry" : 46,
	"dodge" : -40,
	"damage": 60,
	"damage_type": "����"
]),
([	"action": "$N����$w�й�ֱ����һʽ�����ȳ��硹��׼$n��$l��ȥ",
	"force" : 180,
	"attack": 80,
	"parry" : 100,
	"dodge" : -40,
	"damage": 60,
	"damage_type": "����"
]),
([	"action": "$Nһ�С����·ת����$w�����ػ���$n��$l��ȥ",
	"force" : 210,
	"attack": 66,
	"parry" : 65,
	"dodge" : -5,
	"damage": 80,
	"damage_type": "����"
]),
});

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
	if (me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹�������ѧϰ��ɽ�ȷ���\n");

	if (me->query("max_neili") < 100)
		return notify_fail("�����������������ѧϰ��ɽ�ȷ���\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("tianshan-zhang", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷������������ɽ�ȷ���\n");

	return 1;
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("���������������ɽ�ȷ���\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("���������������ɽ�ȷ���\n");

	me->receive_damage("qi", 42);
	me->add("neili", -26);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tianshan-zhang/" + action;
}

