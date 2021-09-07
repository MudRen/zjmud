// xiuluo-dao.c ���޵�
// modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N�ص����գ�һ�С�������ӥ�����������¶��ϻ��˸��뻡����$n��"
		  "$l��ȥ",
	"force" : 120,
	"attack": 30,
	"dodge" : 2,
	"parry" : 10,
	"damage": 30,
	"lvl"   : 0,
	"skill_name" : "������ӥ",
	"damage_type": "����"
]),
([      "action": "$N�����������⣬һ�С�Ͷ�������������$w��ֱ����$n��$l",  
	"force" : 130,
	"attack": 42,
	"dodge" : 10,
	"parry" : 18,
	"damage": 40,
	"lvl"   : 40,
	"skill_name" : "Ͷ�����",
	"damage_type": "����"
]),
([      "action": "$Nһ�С��ͷл�졹��$w�ƾ�������ˢ��һ�����϶�����$n����",
	"force" : 140,
	"attack": 50,
	"dodge" : 15,
	"parry" : 28,
	"damage": 45,
	"lvl"   : 60,
	"skill_name" : "�ͷл��",
	"damage_type": "����"
]),
([      "action": "$N���ַ�ִ������һ�С��۹ǳ��衹����һ����$wֱ��$n�ľ���նȥ",
	"force" : 160,
	"attack": 62,
	"dodge" : 25,
	"parry" : 30,
	"damage": 45,
	"lvl"   : 80,
	"skill_name" : "�۹ǳ���",
	"damage_type": "����",
]),
([      "action": "$Nһ�С�����ǧ�ơ����������⻯����㷱�ǣ���$n��$l��ȥ",
	"force" : 180,
	"attack": 65,
	"dodge" : 18,
	"parry" : 31,
	"damage": 50,
	"lvl"   : 100,
	"skill_name" : "����ǧ��",
	"damage_type": "����"
]),
([      "action": "$N˫�ֺ�ִ$w��һ�С����۲�ʩ����š��ת������ֱ����$n��˫��",
	"force" : 210,
	"attack": 72,
	"dodge" : 22,
	"parry" : 32,
	"damage": 55,
	"lvl"   : 120,
	"skill_name" : "���۲�ʩ",
	"damage_type": "����"
]),
([      "action": "$Nһ�С���Ƥ�龭��������$w����һ����ƽʮ�֣���$n�ݺ���ȥ",
	"force" : 240,
	"attack": 74,
	"dodge" : 25,
	"parry" : 35,
	"damage": 60,
	"lvl"   : 130,
	"skill_name" : "��Ƥ�龭",
	"damage_type": "����"
]),
([      "action": "$N��ת�����׼�Լ���һ�С����ľ�־����ȫ��һ��������$w��$n����նȥ",
	"force" : 280,
	"attack": 77,
	"dodge" : 27,
	"parry" : 41,
	"damage": 72,
	"lvl"   : 140,
	"skill_name" : "���ľ�־",
	"damage_type": "����"
]),
([      "action": "$Nһ�С������𡹣�$w�ĵ���·𻯳�һ�ش����棬��$n����Χ��",
	"force" : 320,
	"attack": 79,
	"dodge" : 30,
	"parry" : 42,
	"damage": 88,
	"lvl"   : 150,
	"skill_name" : "������",
	"damage_type": "����"
]),
([      "action": "$N����ƽָ��һ�С���Ѫ���ء���һƬƬ�йǵ�����쫷�����$n��ȫ��",
	"force" : 330,
	"attack": 87,
	"dodge" : 25,
	"parry" : 45,
	"damage": 95,
	"lvl"   : 160,
	"skill_name" : "��Ѫ����",
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("xiuluo-dao", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������޵�����\n");

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
	level = (int) me->query_skill("xiuluo-dao", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("����������������޵���\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("����������������޵���\n");

	me->receive_damage("qi", 65);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xiuluo-dao/" + action;
}
