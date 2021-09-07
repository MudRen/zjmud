// longcheng-shendao.c ������

inherit SKILL;

mapping *action = ({
([      "action": "$N����$w��ӣ�һ�С���ȥ������������һת��һ����$n��$l��ȥ",
	"force" : 120,
	"attack": 25,
	"dodge" : 10,
	"parry" : 40,
	"damage": 30,
	"lvl"   : 0,
	"skill_name" : "��ȥ����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�������¥���������㣬$wһ��һ�ƣ�ƽ�л���$n������",
	"force" : 160,
	"attack": 28,
	"dodge" : 12,
	"parry" : 45,
	"damage": 45,
	"lvl"   : 30,
	"skill_name" : "������¥",
	"damage_type" : "����"
]),
([      "action": "$N�鲽����һ�С��ƴ����¡�������һ������ն��$n",
	"force" : 200,
	"attack": 31,
	"dodge" : 25,
	"parry" : 49,
	"damage": 65,
	"lvl"   : 60,
	"skill_name" : "�ƴ�����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С��ζ���ɽ����$w���϶��»���һ���󻡣���ֱ����$n",    
	"force" : 240,
	"attack": 48,
	"dodge" : 25,
	"parry" : 54,
	"damage": 80,
	"lvl"   : 90,
	"skill_name" : "�ζ���ɽ",
	"damage_type" : "����"
]),
([      "action": "$N�ಽš��һ�С����Ƕ��ǡ����������У�$w����$n���ؿ�",    
	"force" : 270,
	"attack": 60,
	"dodge" : 30,
	"parry" : 72,
	"damage": 90,
	"lvl"   : 120,
	"skill_name" : "���Ƕ���",
	"damage_type" : "����"
]),
([      "action": "$N����$w��ʹ��һ�С��¹����졹������ƬƬ��Ӱ����������$n",
	"force" : 300,
	"attack": 71,
	"dodge" : 35,
	"parry" : 80,
	"damage": 96,
	"lvl"   : 150,
	"skill_name" : "�¹�����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С����½��ԡ���ֻ�����쵶����˸�����ص�Ӱ��$n��ȫ��ӿȥ",
	"force" : 330,
	"attack": 80,
	"dodge" : 42,
	"parry" : 94,
	"damage": 105,
	"lvl"   : 180,
	"skill_name" : "���½���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("blade", 1) < 80)
		return notify_fail("��Ļ���������򲻹���\n");

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("longcheng-shendao", 1))
		return notify_fail("��ĵ���ˮƽ���ޣ��޷���������������񵶡�\n");

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
	level = (int) me->query_skill("longcheng-shendao",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������������������񵶡�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("������������������񵶡�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -68);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"longcheng-shendao/" + action;
}
