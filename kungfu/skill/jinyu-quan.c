inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С� "+HIY+"������"+NOR+"����˫ȭһ��һ��, ��$n��ȥ",
	"force"  : 120,
	"dodge"  : 10,
	"damage" : 5,
	"lvl"    : 0,
	"skill_name" : HIY"������"NOR,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�"+RED+"�����Ͻ�"+NOR+"�����ó�һƬȭӰ��������磬����$n��ͷ��",
	"force"  : 140,
	"dodge"  : 20,
	"damage" : 10,
	"lvl"    : 20,
	"skill_name" : RED"�����Ͻ�"NOR,
	"damage_type" : "����"
]),
([      "action" : "$N��Ӱ����Ʈ������΢Ц��һ�С�"+HIC+"��������"+NOR+"������������$n��$l",
	"force"  : 150,
	"dodge"  : 10,
	"damage" : 10,
	"lvl"    : 40,
	"skill_name" : HIC"��������"NOR,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�"+HIM+"��������"+NOR+"����˫ȭһ�ϣ�$nֻ��������$N��ȭӰ",
	"force"  : 160,
	"dodge"  : 15,
	"damage" : 20,
	"lvl"    : 60,
	"skill_name" : HIM"��������"NOR,
	"damage_type" : "����"
]),
([      "action" : "$N�������ߣ�ȭ����磬��������$n������һ�С�"+HIG+"��������"+NOR+"��",
	"force"  : 170,
	"dodge"  : 15,
	"damage" : 15,
	"lvl"    : 80,
	"skill_name" : HIG"��������"NOR,
	"damage_type" : "����"
]),
([      "action" : "ֻ��$Nһ�������˲���Ѹ����ף�һ�С�"+YEL+"��ʯ�ɽ�"+NOR+"������$n��ǰ��",
	"force"  : 180,
	"dodge"  : 15,
	"damage" : 20,
	"lvl"    : 100,
	"skill_name" : YEL"��ʯ�ɽ�"NOR,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�"+MAG+"�ڿ����"+NOR+"��������$n���ƺ�$n��ȫ����ȭӰ����",
	"force"  : 210,
	"dodge"  : 15,
	"damage" : 25,
	"lvl"    : 120,
	"skill_name" : MAG"�ڿ����"NOR,
	"damage_type" : "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷�������ȭ��\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������̫�����޷�������ȭ��\n");

	if ((int)me->query_skill("cuff") < 20)
		return notify_fail("��Ļ���ȭ���ȼ�̫�ͣ��޷�������ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("jinyu-quan", 1))
		return notify_fail("��Ļ���ȭ�����ˮƽ���ޣ��޷���������Ľ���ȭ��\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "cuff" || usage == "parry";
}

int valid_combine(string combo)
{
	return combo == "wuluo-zhang";
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("jinyu-quan",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("�����������������ȭ��\n");

	me->receive_damage("qi", 35);
	me->add("neili", -21);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jinyu-quan/" + action;
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
