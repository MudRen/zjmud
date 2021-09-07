// wudang-zhang �䵱�Ʒ�
// ��̫��ȭ������

inherit SKILL;

mapping *action = ({
([	"action": "$Nһ�С�����ӭ�͡�������ƽ�ƣ�����$n��$l",
	"force" : 10,
	"dodge" : 5,
	"parry" : 2,
	"lvl"   : 0,
	"skill_name" : "����ӭ��",
	"damage_type": "����"
]),
([	"action": "$Nʹһ�С����·ת�������ֻ���һ��Ȧ�ӣ����ֻӳ�������$n��$l",
	"force" : 15,
	"dodge" : 18,
	"parry" : 17,
	"lvl"   : 10,
	"skill_name" : "���·ת",
	"damage_type": "����"
]),
([	"action": "$N�����ɹ����ƣ�ʹһ�С����ͻ�֡�����ɨ$n��$l",
	"force" : 15,
	"dodge" : 16,
	"parry" : 19,
	"lvl"   : 20,
	"skill_name" : "���ͻ��",
	"damage_type": "����"
]),
([	"action": "$N˫�ֻ������������ϣ��������£�ʹһ�С��׺����᡹���ֻ�$n�����ź�$l",
	"force" : 25,
	"dodge" : 24,
	"parry" : 21,
	"lvl"   : 30,
	"skill_name" : "�׺�����",
	"damage_type": "����"
]),
([	"action": "$N���ֻ���һ����Ȧ��ʹһ�С��������䡹������$n��$l",
	"force" : 25,
	"dodge" : 24,
	"parry" : 28,
	"lvl"   : 40,
	"skill_name" : "��������",
	"damage_type": "����"
]),
([	"action": "$N˫�ֺ��ƣ�ʹһ�С������ҡ���˫�Ʒֱ���$n��$l��ȥ",
	"force" : 30,
	"dodge" : 28,
	"parry" : 30,
	"lvl"   : 50,
	"skill_name" : "������",
	"damage_type": "����"
]),
([	"action": "$N���ֺ�����ǰ������ֱ��$n��$l������һ�С�����ָ·��",
	"force" : 35,
	"dodge" : 24,
	"parry" : 21,
	"lvl"   : 60,
	"skill_name" : "����ָ·",
	"damage_type": "����"
]),
([	"action": "$N���ǰ̤�벽��˫����Ȼ���,һ�С����׳�н������$n��$l��ȥ",
	"force" : 35,
	"dodge" : 26,
	"parry" : 25,
	"lvl"   : 70,
	"skill_name" : "���׳�н",
	"damage_type": "����"
]),
([	"action": "$N˫�ַ��ɣ�����������Ӱ��һ�С����컨�衹��ֱ��$n",
	"force" : 20,
	"dodge" : 28,
	"parry" : 15,
	"lvl"   : 80,
	"skill_name" : "���컨��",
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "taiji-quan" || combo == "paiyun-shou";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���䵱�Ʒ�������֡�\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹����޷�ѧ�䵱�Ʒ���\n");

	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷����䵱�Ʒ���\n");

	if (me->query_skill("strike", 1) < me->query_skill("wudang-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�����������䵱�Ʒ���\n");

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
	level = (int) me->query_skill("wudang-zhang", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("��������������䵱�Ʒ���\n");

	me->receive_damage("qi", 25);
	me->add("neili", -8);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wudang-zhang/" + action;
}
