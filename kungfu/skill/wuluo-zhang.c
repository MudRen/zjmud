//����������
inherit SKILL;

mapping *action = ({
([      "action": "$Nһ�������һ�С�"+BLU+"���б��"+NOR+"��ֱϮ$n��$l�����ް��ۼ�",
	"force" : 30,
	"dodge" : 30,
	"lvl"   : 0,
	"skill_name" : BLU"���б��"NOR,
	"damage_type": "����"
]),
([      "action": "$Nת������������һ�С�"+HIB+"��������"+NOR+"���������㣬���ƻ���$n������",
	"force" : 50,
	"dodge" : 40,
	"damage": 5,
	"lvl"   : 10,
	"skill_name" : HIB"��������"NOR,
	"damage_type": "����"
]),
([      "action": "$N�鲽����һ�С�"+MAG+"��Ҷ����"+NOR+"��������һת������$n",
	"force" : 60,
	"dodge" : 45,
	"damage": 10,
	"lvl"   : 20,
	"skill_name" : MAG"��Ҷ����"NOR,
	"damage_type": "����"
]),
([      "action": "$Nһ�С�"+RED+"��·δ��"+NOR+"����˫�ƻ���������Ӱ����ƮƮ������$n",    
	"force" : 70,
	"dodge" : 55,
	"damage": 15,
	"lvl"   : 34,
	"skill_name" : RED"��·δ��"NOR,
	"damage_type": "����"
]),
([      "action": "$Nһ�С�"+HIC+"�������"+NOR+"����������ָ΢΢�ſ�������$n������",
	"force" : 90,
	"dodge" : 70,
	"damage": 20,
	"lvl"   : 45,
	"skill_name" : HIC"�������"NOR,
	"damage_type": "����"
]),
([      "action": "$Nת���ͷ������һЦ��ʹ��һ�С�"+YEL+"��ң����"+NOR+"����һ���ĳ����·�ʳ����˼��̻�",  
	"force" : 110,
	"dodge" : 75,
	"damage": 25,
	"lvl"   : 59,
	"skill_name" : YEL"��ң����"NOR,
	"damage_type": "����"
]),
([      "action": "$N����Ʈ����һ�С�"+HIG+"��������"+NOR+"����˫�������������$n",
	"force" : 120,
	"dodge" : 80,
	"damage": 30,
	"lvl"   : 80,
	"skill_name" : HIG"��������"NOR,
	"damage_type": "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����������Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 20)
		return notify_fail("����ڹ���򲻹����޷�ѧ���������ơ�\n");

	if ((int)me->query("max_neili") < 100)
		return notify_fail("���������Ϊ̫�����޷������������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wuluo-zhang", 1))
		return notify_fail("��Ļ����Ʒ�������ޣ��޷�������������������ơ�\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
	return combo == "jinyu-quan";
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("wuluo-zhang", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˣ����������������ơ�\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("�������̫���ˣ����������������ơ�\n");

	me->receive_damage("qi", 40);
	me->add("neili", -13);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wuluo-zhang/" + action;
}
string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}
//�ȼ��������Ƿ�ѧ���µ���ʽ
string query_skill_up(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
	 {
		if(level == action[i]["lvl"])
		 {
		     return action[i]["skill_name"];
		 }
	 }
	  return "no";
}

