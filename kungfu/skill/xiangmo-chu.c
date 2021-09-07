// xiangmo-chu.c ��ս�ħ��

inherit SKILL;

mapping *action = ({
([      "action": "$N�߾�����$w��ʹ��һ�С������������ֱ��$n��$l  ",
	"force" : 100,
	"dodge" : -5,
	"parry" : 20,
	"lvl"   : 0,
	"damage": 30,
	"skill_name" : "�������",
	"damage_type": "����",
]),
([      "action": "$Nʹ������շ�ħ���������趯$w��һ����$w��ɨ$n������  ",
	"force" : 130,
	"attack": 5,
	"dodge" : 5,
	"parry" : 25,
	"lvl"   : 40,
	"damage": 40,
	"skill_name" : "��շ�ħ",
	"damage_type": "����",
]),
([      "action": "$N�������棬ʹ��һʽ�������������˫����$w��һ��ֱ��$n��$l  ",
	"force" : 150,
	"attack": 8,
	"dodge" : 10,
	"parry" : 25,
	"lvl"   : 80,
	"damage": 45,
	"skill_name" : "�������",
	"damage_type": "����",
]),
([      "action": "$Nʹ��һ�С���Ȥ��������˫�־ٹ�����$n���ɲ�  ",
	"force" : 160,
	"attack": 15,
	"dodge" : 0,
	"parry" : 31,
	"lvl"   : 100,
	"damage": 50,
	"skill_name" : "��Ȥ����",
	"damage_type": "����",
]),
([      "action": "$N�趯����$w��ʹ�����������ޡ�����ʱ��ס$n��ȫ��  ",
	"force" : 190,
	"attack": 22,
	"dodge" : 10,
	"parry" : 35,
	"lvl"   : 120,
	"damage": 55,
	"skill_name" : "��������",
	"damage_type": "����",
]),
([      "action": "$Nʹ��һ�С�����Ѫ������ȫ�����ض��ɣ�һ��ֱ��$n��$l  ",
	"force" : 230,
	"attack": 28,
	"dodge" : 15,
	"parry" : 38,
	"lvl"   : 130,
	"damage": 60,
	"skill_name" : "����Ѫ��",
	"damage_type": "����",
]),
([      "action": "$Nʹ��һʽ��������ħ�����Թ�֧�أ�˫��ɴ�$n������  ",
	"force" : 260,
	"attack": 33,
	"dodge" : 20,
	"parry" : 32,
	"lvl"   : 140,
	"damage": 70,
	"skill_name" : "������ħ",
	"damage_type": "����",
]),
([      "action": "$N�������ƣ�ʹ������ħ��������������������$w��ɨ$n��$l  ",
	"force" : 300,
	"attack": 35,
	"dodge" : 20,
	"parry" : 33,
	"lvl"   : 150,
	"damage" : 80,
	"skill_name" : "��ħ����",
	"damage_type": "����",
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("xiangmo-chu", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ľ�ħ�Ʒ���\n");

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
	level = (int) me->query_skill("xiangmo-chu",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) || 
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("������������������˽�ս�ħ�ơ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������˽�ս�ħ�ơ�\n");

	me->receive_damage("qi", 42);
	me->add("neili", -54);

	return 1;
}

string perform_action_file(string action)
{
       return __DIR__"xiangmo-chu/" + action;
}
