// chongyang-shenzhang.c ��������

inherit SKILL;

mapping *action = ({
([      "skill_name": "��������",
	"action": "$N˫��һ��һ�С������������ó������Ӱ����$n��$l",
	"force" : 70,
	"attack": 5,
	"dodge" : 20,
	"parry" : 20,
	"damage": 50,
	"lvl"   : 0,
	"damage_type":  "����"
]),
([      "skill_name": "�ؾ��쳤",
	"action": "$N����һ����������Ȼ�Ƴ���һ�С��ؾ��쳤��ǿ�����Ʒ�ֱ��$n��$l",
	"force" : 90,
	"attack": 10,
	"dodge" : 25,
	"parry" : 25,
	"damage": 50,
	"lvl"   : 15,
	"damage_type":  "����"
]),
([      "skill_name": "����Ϸˮ",
	"action": "$N˫�Ʒ׷ɣ�һ�С�����Ϸˮ��ֱȡ$n��$l",
	"force" : 110,
	"attack": 20,
	"dodge" : 32,
	"parry" : 32,
	"damage": 33,
	"lvl"   : 30,
	"damage_type": "����"
]),
([      "skill_name": "���︴��",
	"action": "$N��������λ���ߣ�һ�С����︴�ա��������Ʒ��޿ײ����ػ���$n��$l",
	"force" : 140,
	"attack": 30,
	"dodge" : 30,
	"parry" : 45,
	"damage": 70,
	"lvl"   : 50,
	"damage_type": "����"
]),
([      "skill_name": "�عⷴ��",
	"action": "$N�������˫��ƽ�ƣ����������һ�С��عⷴ�ա�����$n��$l",
	"force" : 170,
	"attack": 35,
	"dodge" : 45,
	"parry" : 50,
	"damage": 30,
	"lvl"   : 70,
	"damage_type": "����"
]),
([      "skill_name": "���է��",
	"action": "$N����������ǰ�������Ƴ���һ�С����է�֡�ѸȻ����$n$l",
	"force" : 190,
	"attack": 40,
	"dodge" : 50,
	"parry" : 52,
	"damage": 30,
	"lvl"   : 90,
	"damage_type": "����"
]),
([      "skill_name": "����ǧ��",
	"action": "$Nʹ��������ǧ���������μ�����������$n���ƹ���",
	"force" : 220,
	"attack": 40,
	"dodge" : 65,
	"parry" : 55,
	"damage": 30,
	"lvl"   : 110,
	"damage_type": "����"
]),
([      "skill_name": "���ξ���",
	"action": "$Nһ�С����ξ��졹��˫������ʵʵ�Ļ���$n��$l",
	"force" : 250,
	"attack": 45,
	"dodge" : 60,
	"parry" : 57,
	"damage": 30,
	"lvl"   : 130,
	"damage_type": "����"
]),
([      "skill_name": "������λ",
	"action": "$N���ƻ��˸�ȦȦ�������Ƴ���һ�С�������λ������$n$l",
	"force" : 270,
	"attack": 50,
	"dodge" : 68,
	"parry" : 61,
	"damage": 30,
	"lvl"   : 150,
	"damage_type": "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������Ʊ�����֡�\n");

	if ((int)me->query("max_neili") < 600)
		return notify_fail("����������㣬�޷����������ơ�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

	return 1;
}

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "zhongnan-zhi"; }

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("chongyang-shenzhang", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

	if ((int)me->query("neili") < 65)
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

	me->receive_damage("qi", 60);
	me->add("force", -55);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"chongyang-shenzhang/" + action;
}
