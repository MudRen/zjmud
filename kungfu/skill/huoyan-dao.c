// huoyan-dao.c ���浶

inherit SKILL;

mapping *action = ({
([      "action": "$Nʹ��һ�С���ľȡ�𡹣�����ת��˫����ǰƽƽ����$n",
	"skill_name" : "��ľȡ��",
	"force" : 90,
	"attack": 25,
	"dodge" : 15,
	"parry" : 25,
	"lvl"   : 0,
	"damage": 40,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�ף�ڻ��桹�������絶��бб����$n��$l",
	"skill_name" : "ף�ڻ���",
	"force" : 130,
	"attack": 47,
	"dodge" : 25,
	"parry" : 31,
	"lvl"   : 30,
	"damage": 55,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�����ޱߡ���˫��һ�ģ�һ�����������й���$n��$l",
	"skill_name" : "����ޱ�",
	"force" : 180,
	"attack": 61,
	"dodge" : 25,
	"parry" : 40,
	"lvl"   : 60,
	"damage": 65,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С������ֻء���˫�ֺ�ʮ����ͷ����$n",
	"skill_name" : "�����ֻ�",
	"force" : 240,
	"attack": 75,
	"dodge" : 20,
	"parry" : 47,
	"lvl"   : 90,
	"damage": 70,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�˫�����桹��˫��һ�������������湥��$n��$l",
	"skill_name" : "˫������",
	"force" : 300,
	"attack": 80,
	"dodge" : 30,
	"parry" : 56,
	"lvl"   : 120,
	"damage": 80,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С���ɽ�𺣡���˫������б�ģ���ʱ��ǧ������������˷�����$n",
	"skill_name" : "��ɽ��",
	"force" : 350,
	"attack": 91,
	"dodge" : 35,
	"parry" : 62,
	"lvl"   : 140,
	"damage": 85,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С��׷��ȡ�����ۻ��գ�����������ֱ��$n��$l",
	"skill_name" : "�׷���",
	"force" : 370,
	"attack": 102,
	"dodge" : 37,
	"parry" : 78,
	"lvl"   : 160,
	"damage": 90,
	"damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�������������˫��΢��������ǰ�죬һ���ھ�����ɽ�����㹥��$n",
	"skill_name" : "��������",
	"force" : 400,
	"attack": 110,
	"dodge" : 45,
	"parry" : 84,
	"lvl"   : 180,
	"damage": 109,
	"damage_type" : "����",
]),
});


int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "dashou-yin" ||
	       combo == "yujiamu-quan";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����浶������֡�\n");

	if ((int)me->query("max_neili") < 1200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��\n");

	if (me->query_skill("strike", 1) < me->query_skill("huoyan-dao", 1))
		return notify_fail("��Ļ����Ʒ�������ޣ��޷���������Ļ��浶����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("huoyan-dao",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����浶������֡�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������������������˻��浶��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������˻��浶��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -62);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huoyan-dao/" + action;
}
