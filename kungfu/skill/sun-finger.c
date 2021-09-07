// sun-finger.c һ��ָ book: һ��ָ��

inherit SKILL;

mapping *action = ({
([	"action": "$Nһʽ��"+HIR+"��������"+NOR+"����������ָ���籡������������ָ�������"
		   "��������$n��$l",
	"force" : 350,
	"attack": 90,
	"dodge" : 75,
	"parry" : 55,
	"damage": 60,
	"skill_name" : HIR"��������"NOR,
	"damage_type" : "����"
]),
([	"action": "$N����һת��һ���絽$n���$n��æת��$N���������Ծ�أ�"
		   "һʽ��"+YEL+"³������"+NOR+"��������ʳָ������ָ��$n��$l",
	"force" : 390,
	"attack": 75,
	"dodge" : 45,
	"parry" : 60,
	"damage": 78,
	"skill_name" : YEL"³������"NOR,
	"damage_type" : "����"
]),
([	"action": "$N����̤��һ���������������ʳָЮ���ۻ���������$n��$l��"
		   "��ʽ����̹��������һʽ��"+WHT+"������ѩ"+NOR+"��",
	"force" : 330,
	"attack": 69,
	"dodge" : 80,
	"parry" : 70,
	"damage": 66,
	"skill_name" : WHT"������ѩ"NOR,
	"damage_type" : "����"
]),
([	"action": "$N��ӰƮ��һʽ��"+CYN+"��������"+NOR+"�������϶��£���������繳����"
		   "��$n���Ҽ磬$n������ܣ�$N���ֳ��Ƶ���$n��$l",
	"force" : 380,
	"attack": 72,
	"dodge" : 50,
	"parry" : 55,
	"damage": 85,
	"skill_name" : CYN"��������"NOR,
	"damage_type" : "����"
]),
([	"action": "ֻ��$N���Ϻ���һ�죬����һ�գ�һʽ��"+HIY+"���ս���"+NOR+"��������ʳָ"
		   "бָ����$n��$l��ȥ",
	"force" : 370,
	"attack": 75,
	"dodge" : 65,
	"parry" : 60,
	"damage": 71,
	"skill_name" : HIY"���ս���"NOR,
	"damage_type" : "����"
]),
([	"action": "$N����б����ͻȻ�����Ϊָ���͵�һ���죬һʽ��"+HIM+"���ﳯ��"+NOR+"����"
		   "ʹ��һ��ָ��������$n��$l",
	"force" : 400,
	"attack": 64,
	"dodge" : 60,
	"parry" : 45,
	"damage": 85,
	"skill_name" : HIM"���ﳯ��"NOR,
	"damage_type" : "����"
]),
([	"action": "$N����һԾ������$n������ϥһ��������ʳָ����һʽ��"+HIR+"��"
		   "������"+NOR+"��������$n�ĺ���",
	"force" : 420,						  
	"attack": 60,
	"dodge" : 55,
	"parry" : 60,
	"damage": 95,
	"skill_name" : HIR"��������"NOR,
	"damage_type" : "����"
]),
([      "action": "$Nһ�����, һʽ��"+HIY+"������̩"+NOR+"�����þ�ȫ����$n��$l��ȥ",
	"force" : 440,
	"attack": 75,
	"dodge" : 45,
	"parry" : 45,
	"damage": 98,
	"skill_name" : HIY"������̩"NOR,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="haotian-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��һ��ָ������֡�\n");

	if (me->query("gender") != "����")
		return notify_fail("���������㣬�޷�ѧһ��ָ��\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷���һ��ָ��\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ѧһ��ָ��\n");

	if ((int)me->query_skill("finger", 1) < 100)
		return notify_fail("��Ļ���ָ����򲻹����޷�ѧһ��ָ��\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("tanzhi-shentong", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷����������һ��ָ��\n");

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
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�������������һ��ָ!\n");

	me->receive_damage("qi", 55);
	me->add("neili", -65);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"sun-finger/" + action;
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
