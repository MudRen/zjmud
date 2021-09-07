// longzhua-gong.c ��צ��
// modified by Venus Oct.1997
// Updated by Doing

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "�ں��������У�$Nʹһ�С�����ʽ����˫���繳��ꫣ�����$n��$l",
	"force" : 100,
	"attack": 30,
	"dodge" : 25,
	"parry" : 5,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N�͵���ǰԾ����һ�С�׽Ӱʽ���������߳���˫��ץ��$n������",
	"force" : 110,
	"attack": 41,
	"dodge" : 30,
	"parry" : 5,
	"damage": 20,
	"lvl"   : 10,
	"skill_name" : "׽Ӱʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N˫��ƽ�죬ʮָ΢΢���¶�����һ�С�����ʽ������$n��$l",    
	"force" : 120,
	"attack": 49,
	"dodge" : 35,
	"parry" : 10,
	"damage": 25,
	"lvl"   : 20,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N���������������ڻӣ�һ�С�����ʽ������$n�ؿ�",
	"force" : 140,
	"attack": 54,
	"dodge" : 36,
	"parry" : 11,
	"damage": 30,
	"lvl"   : 30,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N�������գ�����������ɽ��һ�С�����ʽ�����͵ػ���$n��$l",  
	"force" : 160,
	"attack": 57,
	"dodge" : 38,
	"parry" : 15,
	"damage": 40,
	"lvl"   : 40,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N�ڲ���ǰ�����ֻ��أ�����̽����һ�С�����ʽ������$n���ɲ�",
	"force" : 190,
	"attack": 60,
	"dodge" : 42,
	"parry" : 19,
	"damage": 45,
	"lvl"   : 50,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N˫��ƽ����ǰ�����ֻ�ס���ţ�һ�С�����ʽ����������$n��$l",
	"force" : 220,
	"attack": 65,
	"dodge" : 47,
	"parry" : 21,
	"damage": 51,
	"lvl"   : 60,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N������ǰ������Ҹ�º��գ���ָ�繳��һ�С���ȱʽ������$n�Ķ���",
	"force" : 260,
	"attack": 71,
	"dodge" : 52,
	"parry" : 22,
	"damage": 54,
	"lvl"   : 80,
	"skill_name" : "��ȱʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N����б��$n����֮�䣬һ�С�����ʽ��������ȡĿ�����ַ���$n���ɲ�",
	"force" : 300,
	"attack": 76,
	"dodge" : 55,
	"parry" : 25,
	"damage": 57,
	"lvl"   : 100,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$Nһ����ָ$n�Ľ�����һ�С��ὣʽ����һ������ץ��$n���еĳ���",
	"force" : 320,
	"attack": 82,
	"dodge" : 61,
	"parry" : 31,
	"damage": 62,
	"lvl"   : 120,
	"skill_name" : "�ὣʽ" ,
	"damage_type" : "����"
]),
([      "action": "$N����ָ��$n��ǰ�������Ѩ������бָ̫��Ѩ��һ�С�����ʽ��ʹ"
		  "$n��������",
	"force" : 340,
	"attack": 85,
	"dodge" : 62,
	"parry" : 35,
	"damage": 65,
	"lvl"   : 140,
	"skill_name" : "����ʽ" ,
	"damage_type" : "����"
]),
([      "action": "$Nǰ���ŵأ�һ�ֶ����צ��һ��ָ�أ�һ�С�׷��ʽ����������$n"
		  "��ȫ��",
	"force" : 360,
	"attack": 90,
	"dodge" : 65,
	"parry" : 38,
	"damage": 70,
	"lvl"   : 160,
	"skill_name" : "׷��ʽ" ,
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "qianye-shou"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����צ��������֡�\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ���򲻹����޷�ѧ��צ����\n");

	if ((int)me->query("max_neili") < 250)
		return notify_fail("�������̫�����޷�����צ����\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("longzhua-gong", 1))
		return notify_fail("��Ļ���צ�����ˮƽ���ޣ��޷������������צ����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i - 1]["lvl"])
			return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("longzhua-gong", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("���������������צ����\n");

	me->receive_damage("qi", 60);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"longzhua-gong/" + action;
}
