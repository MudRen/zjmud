// fumo-jian.c ��ħ��
// Modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nһʽ�������ơ�������ƽָ��������磬һ���ǳɺ�ɨ$n������",
	"force" : 90,
	"attack": 15,
	"dodge" : -10,
	"parry" : 20,
	"damage": 25,
	"lvl"   : 0,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N��ǰԾ��һ�������ֽ���������$wʹ��һʽ�������ơ�ֱ��$n��$l",
	"force" : 130,
	"attack": 30,
	"dodge" : -10,
	"parry" : 30,
	"damage": 30,
	"lvl"   : 40,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N�β�ͦ����һʽ����ɽ�ơ�������$w�����ޱȣ������ӽ�ײ��$n��$l",
	"force" : 170,
	"attack": 40,
	"dodge" : 5,
	"parry" : 32,
	"damage": 35,
	"lvl"   : 60,
	"skill_name" : "��ɽ��",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ�������ơ���$w������һ���һ���󻡣�ƽƽ����$n��$l��ȥ",
	"force" : 190,
	"attack": 50,
	"dodge" : 5,
	"parry" : 35,
	"damage": 40,
	"lvl"   : 80,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N����š���������鱧��Բ��һʽ�������ơ���$w�й�ֱ��������$n���ؿ�",
	"force" : 240,
	"attack": 60,
	"dodge" : 10,
	"parry" : 45,
	"damage": 50,
	"lvl"   : 100,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ�������ơ���$w������������������ֱ����Ю����֮����Ȼն"
		  "��$n��$l",
	"force" : 260,
	"attack": 65,
	"dodge" : 5,
	"parry" : 50,
	"damage": 60,
	"lvl"   : 120,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N����ʩ���������ơ���$w����Ƴ�һ����â��������ƿ�����$n��$l",
	"force" : 280,
	"attack": 70,
	"dodge" : 5,
	"parry" : 52,
	"damage": 75,
	"lvl"   : 140,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action" : "$N˫�Ȱ�����ף�һʽ�������ơ������⻮������ԲȦ���������"
		   "�������",
	"force" : 310,
	"attack": 75,
	"dodge" : 5,
	"parry" : 64,
	"damage": 90,
	"lvl"   : 150,
	"skill_name" : "������",
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 250)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("fumo-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ķ�Ħ������\n");

    return 1;
}

string query_skill_name(int level)
{
	int i;

	for(i = sizeof(action) - 1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;

	level = (int) me->query_skill("fumo-jian", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("������аѽ����ܹ���ϰ��Ħ����\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("���������������ħ����\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("���������������ħ����\n");

	me->receive_damage("qi", 65);
	me->add("neili", -62);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"fumo-jian/" + action;
}
