// dashou-yin.c ���ڴ���ӡ

inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ��һ�С���������ӡ����˫�ƺ�ʮ��ֱֱײ��$n��ǰ��",
	"skill_name" : "��������ӡ",
	"force" : 120,
	"attack": 25,
	"dodge" : 10,
	"lvl" : 0,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ƹ���ӡ��������Ծ��˫���繴��ץ��$n��$l",
	"skill_name" : "���ƹ���ӡ",
	"force" : 170,
	"attack": 30,
	"dodge" : 15,
	"lvl" : 25,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�׼���ĸӡ����������ָ��ֱȡ$n��$l",
	"skill_name" : "׼���ĸӡ",
	"force" : 220,
	"attack": 35,
	"dodge" : 5,
	"lvl" : 50,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С���������ӡ����ŭ��һ����һ�Ƶ�ͷ����$n��$l",
	"skill_name" : "��������ӡ",
	"force" : 250,
	"attack": 40,
	"dodge" : 25,
	"lvl" : 80,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�ҩʦ�����ӡ�����ͳ���ǰ�����������㹥��$n",
	"skill_name" : "ҩʦ�����ӡ",
	"force" : 280,
	"attack": 45,
	"dodge" : 15,
	"lvl" : 100,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����½��ӡ������������˫������ɨ��$n��$l",
	"skill_name" : "���½��ӡ",
	"force" : 320,
	"attack": 50,
	"dodge" : 15,
	"lvl" : 120,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ֽ��ӡ���������Ծ��˫��ǰ�������ץ��$n����"
		   "��",
	"skill_name" : "���ֽ��ӡ",
	"force" : 340,
	"attack": 55,
	"dodge" : 20,
	"lvl" : 140,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С������ǻ�ӡ������ʱ��������������г���������Ӱ��"
		   "��$n��$l",
	"skill_name" : "�����ǻ�ӡ",
	"force" : 360,
	"attack": 65,
	"dodge" : 25,
	"lvl" : 160,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo=="yujiamu-quan" ||
	       combo=="huoyan-dao";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����ڴ���ӡ������֡�\n");

	if ((int)me->query("max_neili") < 350)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("lamaism", 1) < 20)
		return notify_fail("��������ķ���֪ʶ�˽�̫�٣��޷�������ڴ���ӡ��\n");

	if ((int)me->query_skill("lamaism", 1) < (int)me->query_skill("dashou-yin",1) &&
	    (int)me->query_skill("lamaism", 1) < 200)
		return notify_fail("���������ķ�֪ʶ��֪ʶ���ޣ����Խ�һ���������ӡ��\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("dashou-yin",1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷�������������ڴ���ӡ��\n");

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
		  level   = (int) me->query_skill("dashou-yin",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ڴ���ӡ��������֡�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("����������������������ڴ���ӡ��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("����������������������ڴ���ӡ��\n");

	me->receive_damage("qi", 50);
	me->add("neili", -61);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dashou-yin/" + action;
}
