// nianhua-zhi.c - �黨ָ

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N����̧�ۣ���ָ���˸���Ȧ��һʽ��ƿ�����⡹����$n��$l",
	"force" : 100,
	"attack": 10,
	"parry" : 15,
	"dodge" : -5,
	"lvl"   : 0,
	"skill_name" : "ƿ������",
	"damage_type" : "����"
]),
([      "action": "$N�������У�һʽ����÷�������ָ��Ҹ������ָ��$n����ǰ",
	"force" : 140,
	"attack": 15,
	"parry" : 18,
	"dodge" : -5,
	"lvl"   : 10,
	"skill_name" : "��÷����",
	"damage_type" : "����"
]),
([      "action": "$N����б�У����ְ��ƣ�����һʽ�������ʾơ�����$n��$l����",
	"force" : 170,
	"attack": 20,
	"parry" : 25,
	"dodge" : 5,
	"lvl"   : 20,
	"skill_name" : "�����ʾ�",
	"damage_type" : "����"
]),
([      "action": "$N˫Ŀ΢����һʽ��¶��б������˫�ֻû���ǧ�ٸ�ָӰ������$n��$l",
	"force" : 210,
	"attack": 28,
	"parry" : 30,
	"dodge" : 5,
	"damage": 10,
	"lvl"   : 30,
	"skill_name" : "¶��б��",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ�����³��ء������ƻ�ס�������бָ���죬���Ƶ���$n��$l",
	"force" : 250,
	"attack": 30,
	"parry" : 35,
	"dodge" : 15,
	"damage": 10,
	"lvl"   : 50,
	"skill_name" : "���³���",
	"damage_type" : "����"
]),
([      "action": "$N˫��ƽ����ǰ��ʮָ�濪��һʽ��Ҷ����������ָ��$n�������Ѩ",
	"force" : 280,
	"attack": 45,
	"parry" : 40,
	"dodge" : 20,
	"damage": 15,
	"lvl"   : 70,
	"skill_name" : "Ҷ������",
	"damage_type" : "����"
]),
([      "action": "$N˫�Ʒ��ɣ�һʽ�������𡹣�ָ�˱ų�����������������$n��ȫ��",
	"force" : 310,
	"attack": 50,
	"parry" : 48,
	"dodge" : 25,
	"damage": 20,
	"lvl"   : 90,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��������˪������ָ���У�һ����������ٱ�ĵ�����������$n��$l��ȥ",
	"force" : 370,
	"attack": 60,
	"parry" : 55,
	"dodge" : 30,
	"damage": 30,
	"lvl"   : 120,
	"skill_name" : "������˪",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��٤Ҷ΢Ц����˫��ʳָ���棬ָ�����һ�����������$n��$l",
	"force" : 400,
	"attack": 68,
	"parry" : 60,
	"dodge" : 35,
	"damage": 40,
	"lvl"   : 150,
	"skill_name" : "٤Ҷ΢Ц",
	"damage_type" : "����"
]),
([      "action": "$N����������ǰ��һʽ�������黨��������ʳָ��סĴָ���������$nһ��",
	"force" : 440,
	"attack": 75,
	"parry" : 66,
	"dodge" : 50,
	"damage": 10,
	"lvl"   : 180,
	"skill_name" : "�����黨",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "sanhua-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���黨ָ������֡�\n");

	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ���򲻹����޷�ѧ�黨ָ��\n");

	if ((int)me->query("max_neili") < 300)
		return notify_fail("�������̫�����޷����黨ָ��\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("nianhua-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷�����������黨ָ��\n");

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
	level = (int) me->query_skill("nianhua-zhi",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������黨ָ��\n");

	me->receive_damage("qi", 50);
	me->add("neili", -64);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"nianhua-zhi/" + action;
}
