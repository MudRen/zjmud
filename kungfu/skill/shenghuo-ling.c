inherit SKILL;

mapping *action = ({
([      "action": "$N̤��һ���������ڵ���һ�����ѱ�ס��$nС�ȡ�ʮָ����$nС���ϵ��ж���"
		  "������Ѩ",
	"force" : 180,
	"attack": 70,
	"dodge" : 30,
	"damage": 30,
	"parry" : 70,
	"lvl"   : 0,
	"damage_type": "����"
]),
([      "action": "ͻȻ֮�䣬$N���λζ���ͬʱ�۽�������$w��$n���ϻ�ȥ�����²�֪����ƶ���"
		  "\n����ȴ����䡣����ͬʱץ��$n�ĺ���",
	"force" : 240,
	"attack": 80,
	"dodge" : 33,
	"parry" : 79,
	"damage": 38,
	"lvl"   : 40,
	"damage_type": "����"
]),
([      "action": "$N����ֱ�������ֳ�$w��$n����������䡣������һ˲֮�䣬$n����������"
		  "\nȻһȭ����$n�Ȳ���$nһ�����ģ�$N���$w����$n����",
	"force" : 260,
	"attack": 90,
	"dodge" : 41,
	"parry" : 85,
	"damage": 52,
	"lvl"   : 80,
	"damage_type": "����"
]),
([      "action": "$N���ط��֣������Ǳ�$wβ�����ϵ���ֱ��$n����",
	"force" : 280,
	"attack": 95,
	"dodge" : 45,
	"parry" : 92,
	"damage": 60,
	"lvl"   : 120,
	"damage_type": "����"
]),
([      "action": "$N��Ȼ��ͷ��һ��ͷ����$nײ����$n������ɫ����������һ�ã�ͻ���ؿ�һ��"
		  "���磬ֻ��$N����Ϯ��",
	"force" : 320,
	"attack": 97,
	"dodge" : 47,
	"parry" : 99,
	"damage": 72,
	"lvl"   : 160,
	"damage_type": "����"
]),
([      "action": "$N��Ȼ��ͷ��һ��ͷ����$nײ����$n������ɫ����������һ�ã�ͻ���ؿ�һ�飬"
		  "\n$N����$w���Ӻ�ɨ��ͻȻ�����������Ľ��$w�ѵ�$n�Ҽ�",
	"force" : 360,
	"attack": 100,
	"dodge" : 50,
	"parry" : 100,
	"damage": 100,
	"lvl"   : 180,
	"damage_type": "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻵����޷�ѧϰʥ�����\n");

	if (me->query("max_neili") < 1200)
		return notify_fail("����ڹ���Ϊ���㣬�޷�ѧϰʥ�����\n");

	if (me->query_int() < 35)
		return notify_fail("�������޷�����ʥ�����Ҫ�衣\n");

	if (me->query_dex() < 25)
		return notify_fail("��������̫��޷�ѧϰʥ�����\n");

	if (me->query_skill("sword", 1) < me->query_skill("shenghuo-ling", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ʥ�����\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("shenghuo-ling", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) || 
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("shenghuo-ling", 1) < 180)
		return notify_fail("�㻹û������ʥ��������еİ���޷�ͨ���������������\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("�������������ʥ�����\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�������������ʥ�����\n");

	me->receive_damage("qi", 50);
	me->add("neili", -70);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shenghuo-ling/" + action;
}
