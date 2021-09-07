// jingang-quan.c -����ȭ
// Modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N��ϥ���������ֺ�ʮ��һʽ������������˫ȭ���ƶ���������$n��$l",
	"force" : 120,
	"dodge" : 10,
	"damage": 30,
	"lvl"   : 0,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ���һ�׶����˫�������»���ȭ�����棬��ž����",
	"force" : 170,
	"dodge" : 15,
	"damage": 45,
	"lvl"   : 40,
	"skill_name" : "�һ�׶",
	"damage_type" : "����"
]),
([      "action": "$N�ڿշ���һʽ���˷��꡹��˫��˫���������$n�޿ɶ��",    
	"force" : 220,
	"dodge" : 25,
	"damage": 60,
	"lvl"   : 70,
	"skill_name" : "�˷���",
	"damage_type" : "����"
]),
([      "action": "$N˫���麬����Ե�³���һʽ�������ס���������$n�Ƴ�",
	"force" : 270,
	"dodge" : 25,
	"damage": 70,
	"lvl"   : 100,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$Nһ��ǰ�죬һ�ۺ�ָ��һʽ����ָɽ��������$n����ǰ���",    
	"force" : 320,
	"dodge" : 30,
	"damage": 80,
	"lvl"   : 120,
	"skill_name" : "��ָɽ",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ�������ɡ�������ʮָ���$n��ȫ����ʮ����ҪѨ",
	"force" : 340,
	"dodge" : 35,
	"damage": 85,
	"lvl"   : 140,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N��Ŀ���ӣ�˫��������һʽ����������������˷������������ǵ�����",
	"force" : 360,
	"dodge" : 35,
	"damage": 90,
	"lvl"   : 160,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action" : "$N��Ц��Ц��˫ȭ�����޶���һʽ������Ц������Ȼ����$n��ǰ��",
	"force" : 395,
	"dodge" : 40,
	"damage": 100,
	"lvl"   : 180,
	"skill_name" : "����Ц",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return  usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ȭ��\n");

	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷�������ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("jingang-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������Ĵ���ȭ��\n");

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
	level = (int) me->query_skill("jingang-quan",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[random(i)];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�����������������ȭ��\n");

	me->receive_damage("qi", 59);
	me->add("neili", -58);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jingang-quan/" + action;
}
