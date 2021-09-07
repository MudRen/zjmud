// huanyin-zhi.c

inherit SKILL;

mapping *action = ({
([      "action": "$Nһֱ����������һ��ָӰ������$n��$l",
	"force" : 250,
	"attack": 19,
	"parry" : 22,
	"dodge" : 18,
	"damage": 28,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action": "$Nȫ��֮������һָ��ֱָ��$n����ǰ",
	"force" : 270,
	"attack": 36,
	"parry" : 31,
	"dodge" : 28,
	"damage": 35,
	"lvl"   : 30,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N����ȴ�������ֺ��ĵ������$n��$l����",
	"force" : 290,
	"attack": 39,
	"parry" : 22,
	"dodge" : 38,
	"damage": 45,
	"lvl"   : 60,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([      "action": "$N����������˫ָ���ƵĴ���$n�Ķ�����硢�ۡ��ء���",
	"force" : 300,
	"attack": 47,
	"parry" : 42,
	"dodge" : 35,
	"damage": 48,
	"lvl"   : 90,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N�����������⣬��ָ���Ƶ���$n��$l",
	"force" : 330,
	"attack": 55,
	"parry" : 50,
	"dodge" : 48,
	"damage": 55,
	"lvl"   : 120,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N���������ʮָ�濪��Сָ����$n��̫ԨѨ",
	"force" : 350,
	"attack": 70,
	"parry" : 60,
	"dodge" : 58,
	"damage": 60,
	"lvl"   : 150,
	"skill_name" : "���߱���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ָ��������֡�\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ָ����\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("�������̫�����޷�������ָ����\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("huanyin-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ļ���ָ����\n");

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
	level = (int) me->query_skill("huanyin-zhi",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 80)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 75)
		return notify_fail("�����������������ָ����\n");

	me->receive_damage("qi", 72);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huanyin-zhi/" + action;
}
