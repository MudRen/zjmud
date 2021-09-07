// shedao-qigong  �ߵ��湦
inherit SKILL;

mapping *action = ({
([	"action" : "$Nʹһ�С��ɺ����᡹����$wһ�ᣬ����$n��$l",
	"attack": 10,
	"damage" : 25,
	"parry": 40,
	"force": 90,
	"lvl" : 0,
	"damage_type" : "����",
	"skill_name" : "�ɺ�����"
]),
([	"action": "$Nʹ�������߳�����������΢��������$wٿ����$n��$l��ȥ",
	"attack": 20,
	"damage" : 30,
	"dodge": 20,
	"parry": 10,
	"force": 140,
	"lvl"  : 30,
	"damage_type": "����",
	"skill_name" : "���߳���"
]),
([	"action": "$N����΢�������㷴�ߣ�����ת��ʹһ�С�����������������$w�Ѵ���$n$l",
	"attack": 30,
	"damage" : 40,
	"dodge": 30,
	"parry": 20,
	"force": 190,
	"lvl"  : 70,
	"damage_type": "����",
	"skill_name" : "��������"
]),
([	"action" : "$Nʹһʽ��������衹��������$n������һ����˳����$w��һ�㣬$w��Ȼ���Լ��ʺ��䣬����$N��������һ����$w�ӹ����ʺ�����$n�������",
	"attack": 40,
	"damage" : 50,
	"force" : 230,
	"dodge" : 45,
	"lvl" : 40,
	"lvl"  : 100,
	"damage_type" : "����",
	"skill_name" : "�������"
]),
([	"action": "$N�����ڵ���һ�����ʹһ�С�С����¡�����$n�������������$wֱ��$n",
	"attack": 50,
	"damage" : 55,
	"dodge": 40,
	"parry": 30,
	"force": 270,
	"lvl"  : 120,
	"damage_type": "����",
	"skill_name" : "С�����"
]),
([	"action": "$N���һ����ʹһ�С�����ٶ�������������$n��ȪҪѨ������$nˤ���ڵ�",
	"attack": 60,
	"dodge": 45,
	"parry": -10,
	"damage" : 60,
	"force": 330,
	"lvl"  : 140,
	"damage_type": "����",
	"skill_name" : "����ٶ�"
]),
([	"action": "$N˫��һ����������ݣ�һ�С�³�ﲦ��������ץ��$n�ҽ����ף�����$wֱ��$nС��",
	"attack": 70,
	"dodge": 75,
	"damage" : 88,
	"parry": -10,
	"force": 370,
	"lvl"  : 160,
	"damage_type": "����",
	"skill_name" : "³�ﲦ��"
]),
([	"action": "$NͻȻһ���������һ�С����ཱུ������˫��һ�֣����ڼ�ͷ��˫��ֱ��$n",
	"attack": 80,
	"dodge": 82,
	"damage" : 115,
	"parry": 30,
	"force": 400,
	"lvl"  : 180,
	"damage_type": "����",
	"skill_name" : "���ཱུ��"
]),
});

int valid_enable(string usage)
{
	return usage == "unarmed" ||
	       usage == "sword"||
	       usage == "staff"||
	       usage == "parry";
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ѧ�ߵ��湦.\n");

	if ((int)me->query_skill("shenlong-bashi", 1) < 100)
		return notify_fail("���������ʽ��򲻹����޷�ѧ�ߵ��湦��\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷�ѧ�ߵ��湦��\n");

	if ((int)me->query_skill("shenlong-bashi", 1) < (int)me->query_skill("shedao-qigong", 1))
		return notify_fail("���������ʽˮƽ���ޣ��޷�����ѧ�ߵ��湦��\n");

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

	level = (int) me->query_skill("shedao-qigong", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������ߵ��湦��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -67);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shedao-qigong/" + action;
}
