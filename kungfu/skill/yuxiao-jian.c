// yuxiao-jian.c ���｣��

inherit SKILL;

mapping *action = ({
([      "action": "$N����������һ�С�Ӣ�������Ҷ��С���ƮȻ����$n��ǰ���漴����$w΢��"
		   "���⼲����$n��$l",
	"force" : 120,
	"attack": 41,
	"parry" : 40,
	"dodge" : 31,
	"damage": 10,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action": "$Nб��һ����ʹ��һʽ����Ů�鳤ֻ�޶̡����ӽ��������һ��һ�̵Ĺ�Ӱ"
		   "ֱ��$n��$l",
	"force" : 140,
	"attack": 52,
	"parry" : 41,
	"dodge" : 42,
	"damage": 12,
	"lvl"   : 10,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С���Ȼ��ȥ��˼�项��$w��Ȼ���������̻ص������У��漴ת����Ȼ"
		   "��ȥ��$n��ʱ�Ÿо�����һ�ɾ��������Լ���$l",
	"force" : 150,
	"attack": 58,
	"parry" : 45,
	"dodge" : 43,
	"damage": 20,
	"lvl"   : 20,
	"damage_type" : "����"
]),
([      "action": "$N˫�־ٽ����죬һ�С�����Ⱥ�������塹��$w���������ף����϶�����"
		   "$n��ͷ­��ȥ",
	"force" : 170,
	"attack": 61,
	"parry" : 48,
	"dodge" : 48,
	"damage": 25,
	"lvl"   : 40,
	"damage_type" : "����"
]),
([      "action": "$Nʩչ�������һЦ������������$w���΢΢һЦ��$nֻ����һ����ȴ��"
		   "һ����Ӱ�������ΰ�Ϯ���Լ���$l�����Լ�ȴû����$N��ʱ�����֣���",
	"force" : 190,
	"attack": 68,
	"parry" : 51,
	"dodge" : 50,
	"damage": 30,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([      "action": "$N���̤ʵ���ҽ���㣬һ�С�һ����ϳ�᡹��$w����һ�Ž�����Ʈ��"
		   "�����ر���$n��$l",
	"force" : 200,
	"attack": 71,
	"parry" : 55,
	"dodge" : 55,
	"damage": 35,
	"lvl"   : 80,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����Ū������项�������ḧ$w���漴�͵�һ����������ǰһ�ݣ�"
		   "ֻ��һ����˸�����Ľ�ӰѸ�ٴ���$n��$l",
	"force" : 230,
	"attack": 78,
	"parry" : 60,
	"dodge" : 62,
	"damage": 40,
	"lvl"   : 100,
	"damage_type" : "����"
]),
([      "action": "$N������ף���ɫ��Ȼ��һ�С�������Թ���˳�����$w�������Ʋ����ش���"
		   "$n��$l",
	"force" : 250,
	"attack": 81,
	"parry" : 64,
	"dodge" : 65,
	"damage": 70,
	"lvl"   : 110,
	"damage_type" : "����"
]),
([      "action": "$N�������棬һ�С��˽�������������������$wб���»�����$n΢����֣�����"
		   "�ɼ䣬ȴ��$N���е�$w�ѷ������ϣ�ֱ���Լ����ʺ�",
	"force" : 280,
	"attack": 84,
	"parry" : 68,
	"dodge" : 75,
	"damage": 69,
	"lvl"   : 120,
	"damage_type" : "����"
]),
([      "action": "$N��Ȼ��¶΢Ц��һ�С���������Ц���ա�������$wһ����������Ž�������$n"
	       "����������·",
	"force" : 300,
	"attack": 88,
	"parry" : 70,
	"dodge" : 78,
	"damage": 80,
	"lvl"   : 130,
	"damage_type" : "����"
]),
([      "action": "$N����ʳָ����$w��һ�С��������������项��$w����һ���������������ƣ�$n"
		  "ֻ���õ���ǰһ�ƣ�һ����͵ľ��������Լ�",
	"force" : 330,
	"attack": 91,
	"parry" : 72,
	"dodge" : 85,
	"damage": 88,
	"lvl"   : 140,
	"damage_type" : "����"
]),
([      "action": "$N����΢��һ�С�������������ϡ�������$w����������һ����������ĺ�����"
		  "ɲ�Ǽ��ɳ��ʯ��$n����һ�Ž���������£�������֧����",
	"force" : 350,
	"attack": 94,
	"parry" : 72,
	"dodge" : 85,
	"damage": 100,
	"lvl"   : 150,
	"damage_type" : "����"
]),
});


int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry");
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 900)
		return notify_fail("��������������޷�ѧϰ����������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷�ѧϰ����������\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ���������򲻹����޷�ѧϰ����������\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuxiao-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;

	level = (int) me->query_skill("yuxiao-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("����������������｣����\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("����������������｣����\n");

	me->receive_damage("qi", 45);
	me->add("neili", -66);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yuxiao-jian/" + action;
}
