// ����ȭ

inherit SKILL;

mapping *action = ({
([      "action": "ֻ��$N����һ�����������һ���������ڡ���׼$n�ı��Ӻ��������˹�ȥ",
	"force" : 60,
	"attack": 20,
	"dodge" : 40,
	"parry" : 5,
	"damage": 4,
	"lvl"   : 0,
	"skill_name" : "������",
	"damage_type":  "����"
]),
([      "action": "$N����һ�֣���ȭ������һ�С��β�Ѱ�ߡ�����$n��$l�к���ȥ",
	"force" : 80,
	"attack": 25,
	"dodge" : 43,
	"parry" : 6,
	"damage": 7,
	"lvl"   : 30,
	"skill_name" : "�β�Ѱ��",
	"damage_type":  "����"
]),
([      "action": "$N��ȭ��$n����һ�Σ�����ʹ�˸���Ҷ��͵�ҡ���$n��$l����һץ",
	"force" : 100,
	"attack": 28,
	"dodge" : 45,
	"parry" : 8,
	"damage": 10,
	"lvl"   : 60,
	"skill_name" : "Ҷ��͵��",
	"damage_type":  "ץ��"
]),
([      "action": "$N����һ������ȭ��������ȭ���磬һ�С��ڻ����ġ��Ʋ��ɵ��ػ���$n$l",
	"force" : 120,
	"attack": 35,
	"dodge" : 47,
	"parry" : 11,
	"damage": 17,
	"lvl"   : 80,
	"skill_name" : "�ڻ�����",
	"damage_type":  "����"
]),
([      "action": "ֻ��$N������ʽ��һ�С�˫������ʹ�û����з硣����ȴ����һ������$n$l",
	"force" : 140,
	"attack": 40,
	"dodge" : 49,
	"parry" : 13,
	"damage": 20,
	"lvl"   : 100,
	"skill_name" : "˫����",
	"damage_type":  "����"
]),
([      "action": "$N���һ����������$n���һ������ȭ����$n�������˹�ȥ",
	"force" : 160,
	"attack": 45,
	"dodge" : 52,
	"parry" : 16,
	"damage": 22,
	"lvl"   : 120,
	"skill_name" : "�����ཻ",
	"damage_type":  "����"
]),
([      "action": "$N�����󹭲���˫��ʹ�˸�������Ʊա���$n��$lһ��",
	"force" : 200,
	"attack": 48,
	"dodge" : 54,
	"parry" : 18,
	"damage": 28,
	"lvl"   : 140,
	"skill_name" : "����Ʊ�",
	"damage_type":  "����"
]),
([      "action": "ֻ��$N����������һ����ȭ����$n$l������һȭ"
		  "�߹�һȭ���������С�����������",
	"force" : 220,
	"attack": 51,
	"dodge" : 57,
	"parry" : 20,
	"damage": 32,
	"lvl"   : 160,
	"skill_name" : "��������",
	"damage_type":  "����"
]),
([      "action": "$N����һ�ݣ�����ʹ�˸��������̸���������ɨ��$n��$l",
	"force" : 260,
	"attack": 55,
	"dodge" : 61,
	"parry" : 21,
	"damage": 35,
	"lvl"   : 180,
	"skill_name" : "�����̸�",
	"damage_type":  "����"
]),
([      "action": "$Nһ��ת�����ƻ��أ����Ʒ���ʹ�˸���������ɽ����$n��ͷһ��",
	"force" : 280,
	"attack": 60,
	"dodge" : 63,
	"parry" : 23,
	"damage": 37,
	"lvl"   : 200,
	"skill_name" : "������ɽ",
	"damage_type":  "����"
]),
([      "action": "$N����Ծ������һ�С���ӥ���󡹣������һ"
		  "������$n���ţ��漴˫ȭ�ѵ���$n��$l",
	"force" : 300,
	"attack": 62,
	"dodge" : 65,
	"parry" : 25,
	"damage": 40,
	"lvl"   : 220,
	"skill_name" : "",
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");

	if (me->query("max_neili") < 100)
		return notify_fail("��������������޷���ϰ����ȭ����\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("hujia-quan", 1))
		return notify_fail("��Ļ���ȭ��������ޣ��޷���������ĺ���ȭ����\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo) { return combo=="tianchang-zhang"; }

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
	level = (int)me->query_skill("hujia-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70 )
		return notify_fail("����������������Ϣһ�������ɡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -40);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hujia-quan/" + action;
}
