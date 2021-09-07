// panyun-shou.c ������

inherit SKILL;

mapping *action = ({
([	"action" : "$N�翪��������ǰ����ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",
	"force" : 30,
	"dodge" : 1,
	"parry" : 4,
	"damage": 0,
	"lvl" : 0,
	"damage_type" : "ץ��"
]),
([	"action" : "$N�˺�һ����˫��һ���ų����繳��ꫣ�����$n��$l",
	"force" : 40,
	"dodge" : 15,
	"parry" : 5,
	"damage": 0,
	"lvl"   : 15,
	"damage_type" : "����"
]),
([	"action" : "$N����һת�����ֻ��ۣ�£��Ȧ״���ͻ�$n�����",
	"force" : 60,
	"dodge" : 18,
	"parry" : 7,
	"damage": 10,
	"lvl" : 30,
	"damage_type" : "����"
]),
([	"action" : "$N˫��ƽ�죬ʮָ΢΢���¶���������$n��$l",
	"force" : 80,
	"dodge" : 25,
	"parry" : 11,
	"damage": 12,
	"lvl"   : 40,
	"damage_type" : "����"
]),
([	"action" : "$N���ֻ��أ�Ҹ�º��գ�������ָ�繳������$n��ҪѨ",
	"force" : 100,
	"dodge" : 30,
	"parry" : 14,
	"damage": 15,
	"lvl"   : 50,
	"damage_type" : "����"
]),
([	"action" : "$N����б�ϣ�����ȡĿ�����ַ���$n���ɲ�",
	"force" : 115,
	"dodge" : 35,
	"parry" : 17,
	"damage": 19,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([	"action" : "$Nһ����ָ$n�Ľ���������ץ��$n���еı���",
	"force" : 130,
	"dodge" : 32,
	"parry" : 13,
	"damage": 21,
	"lvl"   : 70,
	"damage_type" : "ץ��"
]),
([	"action" : "$N����ָ��$n��ǰ�������Ѩ������бָ̫��Ѩ������л�$n",
	"force" : 150,
	"dodge" : 38,
	"parry" : 18,
	"damage": 24,
	"lvl"   : 80,
	"damage_type" : "����"
]),
([	"action" : "$Nһ�ֳ��죬һ��ָ�أ���������$n��ȫ��",
	"force" : 170,
	"dodge" : 42,
	"parry" : 12,
	"damage": 27,
	"lvl"   : 90,
	"damage_type" : "����"
]),
([	"action" : "$Nȭ�����������֣��������ޣ�����������$n�ĵ���",
	"force" : 190,
	"dodge" : 50,
	"parry" : 15,
	"damage": 30,
	"lvl" : 100,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "hand" ||  usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "taiji-quan" || combo == "wudang-zhang";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ֱ�����֡�\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ���򲻹����޷�ѧ�����֡�\n");

	if ((int)me->query("max_neili") < 250)
		return notify_fail("�������̫�����޷��������֡�\n");

	if (me->query_skill("hand", 1) < me->query_skill("paiyun-shou", 1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������������ַ���\n");

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

	level = (int) me->query_skill("paiyun-shou", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}


int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("������������������֡�\n");

	me->receive_damage("qi", 37);
	me->add("neili", -25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"paiyun-shou/" + action;
}
