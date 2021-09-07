// cibei-dao.c �ȱ���
// Modified by Venus Oct.1997
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N����$wбָ��һ�С�ͣ����·��������һ�٣�һ����$n��$l��ȥ",
	"force" : 40,
	"attack": 10,
	"dodge" : -10,
	"parry" : 5,
	"lvl"   : 0,
	"damage": 5,
	"skill_name" : "ͣ����·",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�ͯ�ӹһ�������������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
	"force" : 90,
	"attack": 20,
	"dodge" : -10,
	"parry" : 8,
	"damage": 5,
	"lvl"   : 10,
	"skill_name" : "ͯ�ӹһ�",
	"damage_type" : "����"
]),
([      "action": "$Nչ���鲽������Ծ�䣬һ�С��ƴ����¡�������һ������ն��$n",
	"force" : 140,
	"attack": 25,
	"dodge" : -5,
	"parry" : 12,
	"damage": 15,
	"lvl"   : 30,
	"skill_name" : "�ƴ�����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С����ż�ɽ����$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
	"force" : 190,
	"attack": 30,
	"dodge" : 5,
	"parry" : 15,
	"damage": 25,
	"lvl"   : 50,
	"skill_name" : "���ż�ɽ",
	"damage_type" : "����"
]),
([      "action": "$N����$wһ����һ�С���Ϫ���㡹��˫�ֳ����������У�����$n���ؿ�",
	"force" : 240,
	"attack": 35,
	"dodge" : 10,
	"parry" : 25,
	"damage": 30,
	"lvl"   : 80,
	"skill_name" : "��Ϫ����",
	"damage_type" : "����"
]),
([      "action": "$N����$w��ʹ��һ�С��Ź����ġ����������ã����ҿ�����������$n",
	"force" : 280,
	"attack": 40,
	"dodge" : 15,
	"parry" : 32,
	"damage": 35,
	"lvl"   : 100,
	"skill_name" : "�Ź�����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�С��������ۡ������Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
	"force" : 290,
	"attack": 45,
	"dodge" : 5,
	"parry" : 35,
	"damage": 50,
	"lvl"   : 120,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N����פ�أ�һ�С�������Ϣ�����ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
	"force" : 320,
	"attack": 50,
	"dodge" : 20,
	"parry" : 45,
	"damage": 60,
	"lvl"   : 150,
	"skill_name" : "ͣ����·",
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

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("cibei-dao", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ĵȱ�������\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("cibei-dao",1);
	for(i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("��������������ȱ�����\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("��������������ȱ�����\n");

	me->receive_damage("qi", 55);
	me->add("neili", -58);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"cibei-dao/" + action;
}
