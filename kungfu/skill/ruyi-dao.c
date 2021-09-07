// ruyi-dao.c ���⵶

inherit SKILL;

mapping *action = ({
([	"action": "$N����$wбָ��һ�С����粻����������һ�٣�һ����$n��$l��ȥ",
	"force" : 110,
	"dodge" : -10,
	"lvl"   : 0,
	"skill_name" : "���粻��",
	"damage_type" : "����"
]),
([	"action": "$Nһ�С������ơ�����������㣬$wһ��һ�գ�ƽ�л���$n�ľ���",
	"force" : 130,
	"dodge" : -10,
	"damage": 5,
	"lvl"   : 20,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([	"action": "$Nչ���鲽������Ծ�䣬һ�С��ƴ����¡�������һ������ն��$n",
	"force" : 150,
	"dodge" : -5,
	"damage": 15,
	"lvl"   : 40,
	"skill_name" : "�ƴ�����",
	"damage_type" : "����"
]),
([	"action": "$Nһ�С��������ҡ���$w�󿪴��أ����϶��»���һ���󻡣���ֱ����$n",
	"force" : 180,
	"dodge" : 5,
	"damage": 25,
	"lvl"   : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action": "$N����$wһ����һ�С���Ϫ���㡹��˫�ֳ����������У�����$n���ؿ�",
	"force" : 220,
	"dodge" : 10,
	"damage": 30,
	"lvl"   : 80,
	"skill_name" : "��Ϫ����",
	"damage_type" : "����"
]),
([	"action": "$N����$w��ʹ��һ�С��Ź����ġ����������ã����ҿ�����������$n",
	"force" : 250,
	"dodge" : 15,
	"damage": 35,
	"lvl"   : 100,
	"skill_name" : "�Ź�����",
	"damage_type" : "����"
]),
([	"action": "$Nһ�С��﷫Զȥ�������Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
	"force" : 280,
	"dodge" : 10,
	"damage": 50,
	"lvl"   : 120,
	"skill_name" : "�﷫Զȥ",
	"damage_type" : "����"
]),
([	"action": "$N����פ�أ�һ�С�������Ϣ�����ӳ�һƬ�����ĵ�Ӱ����$n��ȫ��ӿȥ",
	"force" : 310,
	"dodge" : 25,
	"damage": 60,
	"lvl"   : 140,
	"skill_name" : "������Ϣ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 350)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ����̫ǳ��\n");

	if (me->query_skill("blade", 1) < me->query_skill("ruyi-dao", 1))
		return notify_fail("��Ļ����������̫ǳ������������������⵶����\n");

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
	level   = (int) me->query_skill("ruyi-dao",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("����������������⵶��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("����������������⵶��\n");

	me->receive_damage("qi", 65);
	me->add("neili", -53);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"ruyi-dao/" + action;
}
