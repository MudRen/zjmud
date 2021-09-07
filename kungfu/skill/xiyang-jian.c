// xiyang-jian ������

inherit SKILL;

mapping *action = ({
([      "action": "$N˫Ŀŭ��������$w��Ȼ�̳�����������",
	"force" : 100,
	"attack": 35,
	"dodge" : 10,
	"parry" : 5,
	"lvl"   : 0,
	"damage": 85,
	"damage_type" : "����"
]),
([      "action": "$N���е�$w��ס�Ļζ���ѹ��$n����Ȼ�ֺ�����$n��$l",
	"force" : 125,
	"attack": 42,
	"dodge" : 10,
	"parry" : 15,
	"damage": 100,
	"lvl"   : 10,
	"damage_type" : "����"
]),
([      "action": "$N���е�$w�����任�����������ͻȻֱ��$n��$l",
	"force" : 150,
	"attack": 45,
	"dodge" : 15,
	"parry" : 25,
	"damage": 100,
	"lvl"   : 30,
	"damage_type" : "����"
]),
([      "action": "$N���е�$w��Ȼ���أ��漴����$n��ȥ���쳣����",
	"force" : 160,
	"attack": 50,
	"dodge" : 25,
	"parry" : 29,
	"damage": 110,
	"lvl"   : 50,
	"damage_type" : "����"
]),
([      "action": "$N����$wһ����бб������$n��$l",
	"force" : 180,
	"attack": 48,
	"dodge" : 20,
	"parry" : 31,
	"damage": 115,
	"lvl"   : 80,
	"damage_type" : "����"
]),
([      "action": "$N���һ�������е�$w�������̳����������콣Ӱ����$n",
	"force" : 240,
	"attack": 52,
	"dodge" : 25,
	"parry" : 37,
	"damage": 120,
	"lvl"   : 100,
	"damage_type" : "����"
]),
([      "action": "$N��ǰ������$w����ǰ�̣����޷��˵Ĺ���$n",
	"force" : 260,
	"attack": 55,
	"dodge" : 15,
	"parry" : 37,
	"damage": 125,
	"lvl"   : 120,
	"damage_type" : "����"
]),
([      "action": "$N��Ȼ����������$w��Ȼһ�����˽���һ�ɴ���$n",
	"force" : 280,
	"attack": 60,
	"dodge" : 30,
	"parry" : 45,
	"damage": 130,
	"lvl"   : 150,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xiyang-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������������\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xiyang-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������������\n");

	return 1;
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
	level = (int) me->query_skill("xiyang-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("���������������������\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("���������������������\n");

	me->receive_damage("qi", 70);
	me->add("neili", -40);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xiyang-jian/" + action;
}
