inherit SKILL;

mapping *action = ({
([      "action": "$N΢һ����$wЯ���Ŵ̶����쬷���������ɨ��$n�Ľ���",
	"force" : 100,
	"attack": 10,
	"dodge" : -5,
	"parry" : 9,
	"damage": 15,
	"damage_type":"����"
]),
([      "action": "$N������ס�ȶˣ����ƾ���һ��������ƾ���Ե���$n�ļ�ͷ",
	"force" : 110,
	"attack": 15,
	"dodge" : -10,
	"parry" : 15,
	"damage": 15,
	"damage_type":"����"
]),
([      "action": "$Nһ����ȣ�����$wƹƹ���ҵ��������ã���$n�����ұܣ��Ǳ�����",
	"force" : 120,
	"attack": 20,
	"dodge" : -5,
	"parry" : 19,
	"damage": 20,
	"damage_type":"����"
]),
([      "action": "$N����Ծ������$w������ֱ�����������$n���ɲ�",
	"force" : 280,
	"attack": 50,
	"dodge" : -5,
	"parry" : 55,
	"damage": 50,
	"lvl"   : 130,
	"damage_type":"����"
]),
([      "action": "$N�߾�$w����������Ȱ�Ʈ������׼$n�������һ�ȴ���",
	"force" : 330,
	"attack": 61,
	"dodge" : -5,
	"parry" : 62,
	"damage": 60,
	"damage_type":"����"
]),
([      "action": "$N˫�۷��죬������$w���ǧ�ٸ����ƣ���������$nȫ�����Ҫ��",
	"force" : 350,
	"attack": 65,
	"dodge" : -5,
	"parry" : 67,
	"damage": 60,
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("fengmo-zhang", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������ķ�ħ�ȷ���\n");

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
	level = (int) me->query_skill("fengmo-zhang",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("���������������ħ�ȷ���\n");

	if ((int)me->query("neili") < 75)
		return notify_fail("���������������ħ�ȷ���\n");

	me->receive_damage("qi", 70);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"fengmo-zhang/" + action;
}

