// mingwang-jian.c ����������

inherit SKILL;

mapping *action = ({
([      "action": "$NŭĿԲ����ʹ��һ�С�������������$wһ����ֱ��$n��$l  ",
	"skill_name" : "����",
	"force" : 100,
	"dodge" : -10,
	"lvl"   : 0,
	"damage": 30,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һʽ�����ֳ�����������һ������â����$n��$l  ",
	"skill_name" : "���ֳ���",
	"force" : 140,
	"dodge" : 5,
	"lvl"   : 30,
	"damage": 30,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�ɽ����������Ծ���գ�$w��ɽ��������$n��$l  ",
	"skill_name" : "ɽ��",
	"force" : 180,
	"dodge" : -10,
	"lvl"   : 50,
	"damage": 40,
	"damage_type" : "����",
]),
([      "action": "$Nʹ����ǧ��ת������$w�����ĳ�һ�㣬��Ȼһ������$n��$l  ",
	"skill_name" : "ǧ��ת",
	"force" : 220,
	"dodge" : 10,
	"lvl"   : 70,
	"damage": 48,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С���ħ�衹��ȫ��������$w�У�����ֱָ$n��$l  ",
	"skill_name" : "��ħ��",
	"force" : 250,
	"dodge" : 10,
	"lvl"   : 90,
	"damage": 54,
	"damage_type" : "����",
]),
([      "action": "$N���������ʹ��һʽ�����衹��һ���������Ӱ����$n��$lɨȥ  ",
	"skill_name" : "����",
	"force" : 280,
	"dodge" : 15,
	"lvl"   : 120,
	"damage": 60,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С����ڡ�������$w������������$n��$l  ",
	"skill_name" : "����",
	"force" : 300,
	"dodge" : 20,
	"lvl"   : 140,
	"damage": 66,
	"damage_type" : "����",
]),
([      "action": "$N����һԾ���Ӹ�����ʹ�����������졹����ʱ�����������$n��$l  ",
	"skill_name" : "��������",
	"force" : 320,
	"dodge" : 25,
	"lvl"   : 160,
	"damage": 80,
	"damage_type" : "����",
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 400)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 70)
		return notify_fail("����ڹ����̫ǳ��\n");

	if (me->query_skill("sword", 1) < me->query_skill("mingwang-jian", 1))
		return notify_fail("��Ļ�������������ޣ��޷���������Ĳ�������������\n");

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
	level   = (int) me->query_skill("mingwang-jian",1);
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

	if ((int)me->query("qi") < 60)
		return notify_fail("������������������˲�����������\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������˲�����������\n");

	me->receive_damage("qi", 50);
	me->add("neili", -58);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"mingwang-jian/" + action;
}
