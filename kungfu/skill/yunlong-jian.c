// yunlong-jian.c ������

inherit SKILL;

mapping *action = ({
([	"action":"\n$Nʹһʽ������˳��Ȼ��������$w����΢�񣬻ó�һ���׹����$n��$l",
	"force" : 40,
	"dodge" : -10,
	"damage": 8,
	"lvl" : 0,
	"skill_name" : "����˳��Ȼ",
	"damage_type":	"����"
]),
([	"action":"\n$N����ǰ��ʹ������ȥ�����С��������������ޣ�$w��������$n��$l��ȥ",
	"force" : 50,
	"dodge" : -10,
	"damage": 10,
	"lvl" : 30,
	"skill_name" : "��ȥ������",
	"damage_type":	"����"
]),
([	"action":"\n$Nһʽ��־�����Զ��������Ʈ�����ߣ��˷�����������$wңҡָ��$n��$l",
	"force" : 60,
	"dodge" : 5,
	"damage": 12,
	"lvl" : 60,
	"skill_name" : "־�����Զ",
	"damage_type":	"����"
]),
([	"action":"$N��������Ծ��һʽ�������γ�����������ˮ��һкǧ�����$nȫ��",
	"force" : 80,
	"dodge" : 10,
	"damage": 15,
	"lvl" : 80,
	"skill_name" : "�����γ�",
	"damage_type":	"����"
]),
([	"action":"$N����$w�й�ֱ����һʽ�����Ǳ��ҹ����������Ϣ�ض�׼$n��$l�̳�һ��",
	"force" : 100,
	"dodge" : 15,
	"damage": 18,
	"lvl" : 100,
	"skill_name" : "���Ǳ��ҹ",
	"damage_type":	"����"
]),
([	"action":"$N����$wһ����һʽ������ϸ��������������Ϣ�ػ���$n��$l",
	"force" : 120,
	"dodge" : 15,
	"damage": 20,
	"lvl" : 120,
	"skill_name" : "����ϸ����",
	"damage_type":	"����"
]),
([	"action":"\n$N����$wбָ���죬��â���£�һʽ������������������׼$n��$lбб����",
	"force" : 150,
	"dodge" : 25,
	"damage": 22,
	"lvl" : 140,
	"skill_name" : "����������",
	"damage_type":	"����"
]),
([	"action":"$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ������һ��졹����$n���ʺ�",
	"force" : 180,
	"dodge" : 15,
	"damage": 25,
	"lvl" : 150,
	"skill_name" : "����һ���",
	"damage_type":	"����"
]),
([	"action":"$N���Ƶ�����һʽ�����Ļ���������$w�Ի���Ծ�����缲�������$n���ؿ�",
	"force" : 200,
	"dodge" : 15,
	"damage": 30,
	"lvl" : 160,
	"skill_name" : "���Ļ�����",
	"damage_type":	"����"
]),
([	"action":"\n$N����һ���εض���һʽ��������ͬ�ԡ���$w�ó������Ӱ����$n����Χס",
	"force" : 220,
	"dodge" : 15,
	"damage": 35,
	"lvl" : 165,
	"skill_name" : "������ͬ��",
	"damage_type":	"����"
]),
([	"action":"$N�������Ʈ�䣬һʽ�����֪���⡹������$wƽָ����������$n����",
	"force" : 250,
	"dodge" : 15,
	"damage": 40,
	"lvl" : 170,
	"skill_name" : "���֪����",
	"damage_type":	"����"
]),
([	"action" : "$N����΢����������һ�С��ߴ���ʤ�������йǽ�����쫷�����$nȫ��",
	"force" : 290,
	"dodge" : 15,
	"damage": 45,
	"lvl" : 175,
	"skill_name" : "�ߴ���ʤ��",
	"damage_type":	"����"
]),
([	"action" : "$Nļ��ʹһ�С���Ҷ����ɽ������ʱ�����м���Ѫ������$nȫ��",
	"force" : 310,
	"dodge" : 25,
	"damage": 50,
	"lvl" : 180,
	"skill_name" : "��Ҷ����ɽ",
	"damage_type":	"����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 900)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ����������̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yunlong-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

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
	level   = (int) me->query_skill("yunlong-jian",1);
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

	if ((int)me->query("qi") < 70)
		return notify_fail("�����������������������\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�����������������������\n");

	me->receive_damage("qi", 55);
	me->add("neili", -67);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"yunlong-jian/" + action;
}
