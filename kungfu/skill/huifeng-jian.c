//huifeng-jian.c �ط������

inherit SKILL;

mapping *action = ({
([      "skill_name" : "���Ϯ��",
	"action": "$N���⽣â������һ�С����Ϯ�¡�������$w�����´󿪴��أ�"
		  "һ����������$n��$l",
	"force" : 100,
	"attack": 15,
	"dodge" : 5,
	"damage": 30,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "skill_name" : "Ʈѩ����",
	"action": "$N����Ȧת��һ�С�Ʈѩ���ơ�������$wƽչ�´̣�һ�����Ữ"
		  "��$n��$l",
	"force" : 120,
	"attack": 19,
	"dodge" : 10,
	"damage": 40,
	"lvl"   : 20,
	"damage_type" : "����"
]),
([      "skill_name" : "ǧ�徺��",
	"action": "$N��������������������������$wʹ��һʽ��ǧ�徺�㡹����$n��$l",
	"force" : 150,
	"attack": 21,
	"dodge" : 10,
	"damage": 50,
	"lvl"   : 40,
	"damage_type" : "����"
]),
([      "skill_name" : "��������",
	"action": "$N������ָ��������ת��һ�С��������ڡ�ֱȡ$n��$l",
	"force" : 170,
	"attack": 25,
	"dodge" : 10,
	"damage": 55,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([      "skill_name" : "��������",
	"action": "$N��â���£��������ߣ�����$wʹ��һʽ���������������������"
		  "����$n��$l",
	"force" : 200,
	"attack": 34,
	"dodge" : 10,
	"damage": 60,
	"lvl"  : 90,
	"damage_type" : "����"
]),
([      "skill_name" : "������ɳ",
	"action": "$N�����ƽ���������ʵ��׷ɣ��ó�����ǹ⣬����$wʹ��һʽ"
		  "��������ɳ��ԾԾ����Ʈ��$n��$l",
	"force" : 230,
	"attack": 37,
	"dodge" : 15,
	"damage": 65,
	"lvl"   : 100,
	"damage_type" : "����"
]),
([      "skill_name" : "��������",
	"action": "$N�ӽ��ֻ�����������ǰԾ��������$wһʽ���������Ρ�������"
		  "����֮�ƣ�����$n��$l",
	"force" : 250,
	"attack": 41,
	"dodge" : 15,
	"lvl"   : 110,
	"damage": 65,
	"damage_type" : "����"
]),
([      "skill_name" : "��غ���",
	"action": "$N�˲������ֽ�ָ��ת������һŤ������$wһ�ǡ���غ��衹����"
		  "���ϴ���$n��$l",
	"force" : 275,
	"attack": 45,
	"dodge" : 25,
	"damage": 70,
	"lvl"   : 120,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ����̫ǳ��\n");

	if (me->query_skill("sword", 1) < me->query_skill("huifeng-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ļط罣��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;

	level = (int) me->query_skill("huifeng-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
		       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("��������������ط��������\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("��������������ط��������\n");

	me->receive_damage("qi", 45);
	me->add("neili", -58);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huifeng-jian/" + action;
}
