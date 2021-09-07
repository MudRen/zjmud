inherit SKILL;

mapping *action = ({
([      "action": "$N��ǰб��һ����һ�С��������������$wֱ��$n�ĺ�",
	"force" : 60,
	"parry" : 0,
	"dodge" : 0,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "�������",
	"damage_type":  "����"
]),
([      "action": "$N����ǰ��һ�С�����ǧ��������������ޣ�$w��������$n��$l��ȥ",
	"force" : 70,
	"parry" : 10,
	"dodge" : 10,
	"damage": 15,
	"lvl"   : 30,
	"skill_name" : "����ǧ��",
	"damage_type":  "����"
]),
([      "action": "$Nһʽ�����б��¡�������Ʈ�����ߣ��˷�����������$wңҡָ��$n��$l",
	"force" : 97,
	"parry" : 12,
	"dodge" : 15,
	"damage": 21,
	"lvl"   : 50,
	"skill_name" : "���б���",
	"damage_type":  "����"
]),
([      "action": "$N��������Ծ��һʽ��������⡹��������ˮ��һкǧ�����$nȫ��",
	"force" : 109,
	"parry" : 23,
	"dodge" : 19,
	"damage": 25,
	"lvl"   : 70,
	"skill_name" : "�������",
	"damage_type":  "����"
]),
([      "action":"$N����ǰ��һ�С�����ǧ��������������ޣ�$w��������$n��$l��ȥ",
	"force" : 137,
	"parry" : 31,
	"dodge" : 27,
	"damage": 36,
	"lvl"   : 90,
	"skill_name" : "����ǧ��",
	"damage_type":  "����"
]),
([      "action":"$N����$w�й�ֱ����һʽ������һ�롹��������Ϣ�ض�׼$n��$l�̳�һ��",
	"force" : 148,
	"parry" : 49,
	"dodge" : 35,
	"damage": 49,
	"lvl"   : 110,
	"skill_name" : "����һ��",
	"damage_type":  "����"
]),
([      "action":"$N����$wһ����һʽ���ǹ����򡹣�������Ϣ�ػ���$n��$l",
	"force" : 169,
	"parry" : 52,
	"dodge" : 45,
	"damage": 52,
	"lvl"   : 130,
	"skill_name" : "�ǹ�����",
	"damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬��â���£�һʽ��ӳ������������׼$n��$lбб����",
	"force" : 187,
	"parry" : 55,
	"dodge" : 51,
	"damage": 58,
	"lvl"   : 150,
	"skill_name" : "ӳ������",
	"damage_type":  "����"
]),
([      "action":"$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ���������ȡ�����$n���ʺ�",
	"force" : 232,
	"parry" : 63,
	"dodge" : 55,
	"damage": 65,
	"lvl"   : 170,
	"skill_name" : "��������",
	"damage_type":  "����"
]),
([      "action":"$N���Ƶ�����һʽ��Ӱ����ԡ���$w�Ի���Ծ�����缲�������$n���ؿ�",
	"force" : 301,
	"parry" : 76,
	"dodge" : 65,
	"damage": 82,
	"lvl"   : 190,
	"skill_name" : "Ӱ�����",
	"damage_type":  "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹�������ѧϰ��Ӱ���½���\n");

	if (me->query_skill("sword", 1) < 80)
		return notify_fail("��Ļ���������򲻹�������ѧϰ��Ӱ���½���\n");

	if (me->query("max_neili") < 800)
		return notify_fail("�����������������ѧϰ��Ӱ���½���\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("liuyue-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ӱ���½���\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("liuyue-jian",1);
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

	if ((int)me->query("qi") < 80)
		return notify_fail("���������������Ӱ���½���\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("���������������Ӱ���½���\n");

	me->receive_damage("qi", 60);
	me->add("neili", -60);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liuyue-jian/" + action;
}

