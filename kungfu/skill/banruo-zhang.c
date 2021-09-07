// banruo-zhang.c ������

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nǰ���߳������Ƚż��أ�һʽ����ճ�����������ֱ��������$n"
		  "����������·",
	"force" : 120,
	"attack": 17,
	"dodge" : 5,
	"parry" : 12,
	"damage": 5,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name" : "��ճ���"
]),
([      "action": "$N���ƻ�һ��Բ��һʽ��������ա�������б������������$n����ǰ"
		  "��Ѩ",
	"force" : 150,
	"attack": 25,
	"dodge" : 5,
	"parry" : 18,
	"damage": 10,
	"lvl"   : 10,
	"damage_type" : "����",
	"skill_name" : "�������"
]),
([      "action": "$Nʹһʽ���ƶ����롹�����������������ɺ����һ��˦����ն��$n"
		  "��$l",
	"force" : 170,
	"attack": 32,
	"dodge" : 6,
	"parry" : 22,
	"damage": 10,
	"lvl"   : 20,
	"damage_type" : "����",
	"skill_name" : "�ƶ�����"
]),
([      "action": "$N���ƻ��أ���ȭ�����󷢣�һʽ����������������������$n��$l",
	"force" : 190,
	"attack": 38,
	"dodge" : -5,
	"parry" : 32,
	"damage": 10,
	"lvl"   : 40,
	"damage_type" : "����",
	"skill_name" : "��������"
]),
([      "action": "$Nʹһʽ������ء���ȫ�������ת��˫��һǰһ���͵�����$n"
		  "���ؿ�",
	"force" : 210,
	"attack": 51,
	"dodge" : 10,
	"parry" : 27,
	"damage": 15,
	"lvl"   : 70,
	"damage_type" : "����",
	"skill_name" : "�����"
]),
([      "action": "$N���Ʊ�������һ������һʽ�����б��¡���˫�Ƽ�����$n�ļ�ͷ",
	"force" : 250,
	"attack": 52,
	"dodge" : 5,
	"parry" : 38,
	"damage": 15,
	"lvl"   : 90,
	"damage_type" : "����",
	"skill_name" : "���б���"
]),
([      "action": "$N���ϸ߸�Ծ��һʽ����ɽ��ˮ�����Ӹ����£���������$n��ȫ��",
	"force" : 280,
	"attack": 62,
	"dodge" : 20,
	"parry" : 56,
	"damage": 15,
	"lvl"   : 110,
	"damage_type" : "����",
	"skill_name" : "��ɽ��ˮ"
]),
([      "action": "$Nʹһʽ��ժ�ǻ�����������������˫�����֣�һ������$n��$l�ȥ",
	"force" : 300,
	"attack": 67,
	"dodge" : 10,
	"parry" : 52,
	"damage": 20,
	"lvl"   : 130,
	"damage_type" : "����",
	"skill_name" : "ժ�ǻ���"
]),
([      "action": "$N�������»��أ�һʽ����������������Ȼ��Ϊ�������꣬����$n",
	"force" : 320,
	"attack": 71,
	"dodge" : 30,
	"parry" : 65,
	"damage": 20,
	"lvl"   : 140,
	"damage_type" : "����",
	"skill_name" : "��������"
]),
([      "action": "$Nһʽ����շ�ħ����˫�ֺ�ʮ������$n΢΢һҾ��ȫ���ھ������"
		  "����ӿ����",
	"force" : 350,
	"attack": 78,
	"dodge" : 10,
	"parry" : 68,
	"damage": 30,
	"lvl"   : 150,
	"damage_type" : "����",
	"skill_name" : "��շ�ħ"
])
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "yizhi-chan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹����޷��������ơ�\n");

	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷��������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("banruo-zhang", 1))
		return notify_fail("��Ļ����Ʒ����ˮƽ���ޣ��޷���������İ�������\n");

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
	level = (int)me->query_skill("banruo-zhang", 1);
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
		return notify_fail("������������������ơ�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -64);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"banruo-zhang/" + action;
}
