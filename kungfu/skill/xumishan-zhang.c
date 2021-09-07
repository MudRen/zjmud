// xumishan-zhang.c ����ɽ��

inherit SHAOLIN_SKILL;

mapping *action = ({
([	"action": "$Nǰ���߳������Ƚż��أ�һʽ���嶡��ɽ����˫��ֱ��$n������",
	  "force" : 150,
	  "attack": 15,
	  "dodge" : 5,
	  "parry" : 20,
	  "lvl"   : 0,
	  "damage_type" : "����",
	  "skill_name" : "�嶡��ɽ"
]),
([	"action": "$N���ƻ�һ��Բ��һʽ������ǧ�С�������б������������$n����ǰ��Ѩ",
	  "force" : 180,
	  "attack": 30,
	  "dodge" : 5,
	  "parry" : 20,
	  "damage": 10,
	  "lvl"   : 30,
	  "damage_type" : "����",
	  "skill_name" : "����ǧ��"
]),
([	"action": "$Nʹһʽ���ƶ����롹�����������������ɺ����һ��˦����ն��$n��$l",
	  "force" : 200,
	  "attack": 40,
	  "dodge" : 5,
	  "parry" : 10,
	  "damage": 20,
	  "lvl"   : 50,
	  "damage_type" : "����",
	  "skill_name" : "�ƶ�����"
]),
([	"action": "$N���ƻ��أ����������󷢣�һʽ����׹��ɽ������������$n��$l",
	  "force" : 240,
	  "attack": 50,
	  "dodge" : -5,
	  "parry" : 10,
	  "damage": 30,
	  "lvl"   : 80,
	  "damage_type" : "����",
	  "skill_name" : "��׹��ɽ"
]),
([	"action": "$Nʹһʽ��ɽ���Ƶ���������һ�ݣ�˫��һǰһ���͵ػ���$n��ͷ���ٻ��Ѩ",
	  "force" : 250,
	  "attack": 70,
	  "dodge" : 20,
	  "parry" : 60,
	  "damage": 35,
	  "lvl"   : 100,
	  "damage_type" : "����",
	  "skill_name" : "ɽ���Ƶ�"
]),
([	"action": "$N˫�ƺ�ʮ������һ������һʽ������Ⱥɽ����˫����Ȼ����һƬ��Ӱ������$n��ǰ��",
	  "force" : 280,
	  "attack": 70,
	  "dodge" : 25,
	  "parry" : 30,
	  "damage": 40,
	  "lvl"   : 125,
	  "damage_type" : "����",
	  "skill_name" : "����Ⱥɽ"
]),
([	"action": "$N���ϸ߸�Ծ��һʽ����ɽ��ˮ�����Ӹ����£���������$n��ȫ��",
	  "force" : 300,
	  "attack": 90,
	  "dodge" : 30,
	  "parry" : 35,
	  "damage": 45,
	  "lvl"   : 150,
	  "damage_type" : "����",
	  "skill_name" : "��ɽ��ˮ"
]),
([	"action": "$Nʹһʽ�����·ת��������������˫�����֣�һ��ǿ��һ�Ƶ���$n��ȥ",
	  "force" : 350,
	  "attack": 95,
	  "dodge" : 30,
	  "parry" : 55,
	  "damage": 50,
	  "lvl"   : 175,
	  "damage_type" : "����",
	  "skill_name" : "���·ת"
]),
([	"action": "$N�������»��أ�һʽ��ɽ��ˮ��������Ȼ��Ϊ�������꣬����$n",
	  "force" : 400,
	  "attack": 110,
	  "dodge" : 30,
	  "parry" : 60,
	  "damage": 55,
	  "lvl"   : 200,
	  "damage_type" : "����",
	  "skill_name" : "ɽ��ˮ��"
]),
([	"action": "$Nһʽ����ɽ��������˫��һȦ��ȫ����������˰���ӿ������$n�پ����޿ɱ�",
	  "force" : 450,
	  "attack": 125,
	  "dodge" : 50,
	  "parry" : 80,
	  "damage": 60,
	  "lvl"   : 250,
	  "damage_type" : "����",
	  "skill_name" : "��ɽ����"
])
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "jingang-zhi"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ɽ�Ʊ�����֡�\n");

	if ((int)me->query_skill("force", 1) < 300)
		return notify_fail("��Ļ����ڹ���򲻹����޷�ѧ����ɽ�ơ�\n");

	if ((int)me->query("max_neili") < 2000)
		return notify_fail("�������̫�����޷�������ɽ�ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xumishan-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷��������������ɽ�ơ�\n"); 

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

	level = (int)me->query_skill("xumishan-zhang", 1);

	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 90)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 120)
		return notify_fail("�����������������ɽ�ơ�\n");

	me->receive_damage("qi", 80);
	me->add("neili", -110);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xumishan-zhang/" + action;
}
