inherit SKILL;

string  *msg = ({
"$N����ƽƽ�̳�һ�������ƺ��ޱ仯��ȴ�к��֮����$nֻ��һ�ɴ�����$w����ֱ������",
"$N���Ծ������$w�𣬽�������֮����������һ������$n�������ڽ���֮��",
"$N��̾һ�������ֺ���һ��������ָ��$n������ƽ�����̺����б仯������ʤ����",
"$NѸ������һ�����˽�֮�죬������˼��$n����֮��һȾ����Ȼ�޷��ֱ潣·��ȥ",
"$N��$w˳�̣�������������������޲��ǽ��������ţ����淵�ӹ��棬�Ѳ����κ�����",
"$N���׳�Х������Ʊ�ã�����$w����������$n���������$n���������κ���֮��", 
"$N��������$w��������ɽ������ͺ�һ�����������ǽ�Ӱ������ǧ����������$n����ζ�",
"$N����ʮ�ལ��һʱѸ�������ǻ��գ�һʱ���سٻ��������޼���Ѱ��ƽ�������ַ�˼����", 
"$N����$w������磬�޿ɵ��棬$n�����и����������纣��һ�㣬һ��һ������ӿ�������Ӳ���",
"$N����$w��ǰ����������������������֪���ƽ��ϣ�����ȴ�纣��һ����ӿ����$nϮȥ",
"$NԶԶ�ӳ�һ����$n�����������֮ǿ������һ�裬һ�ɴ�����ͷ����",
"$N����һ����������$wЮ��������ƽƽ�����Ļ���$n������Խ��Խ�죬����ͬ����֮��һ��",
"$Nһ����$w��Ȼ����������һ�㰵��ɫ��â������ŭ��һ�ߣ���$n��ȥ",
});

string  *super_msg = ({
"$N���ֻӳ�һ����ȥ�Ƽ���ȴ�������š�¡¡���ķ���֮�����Ѿ��ﵽ���������ܵ����߾���",
"$N����$w�����֣��������ָ��$n��$p������������ӭ�������ԭ��$N�����޽�ʤ�н��ľ���",
"$Ņ��һ��������ɺ�����ȴ��˿����Ϣ���ž��Լ����ѿ�����֮��",
"$Nһ���̵������𵭵�������������Ϣ������ȴ�Ǽ�ǿ",
"$Nÿ��һ��������Χ������Ӧ�ϣ���ʽ�������������������֮������֮����",
"$N���о��ް�㲨�����������˽�������ÿ��һ������ӿ��һ������������Ҫȥ��û����",
"$NͻȻ֮������ȫ�ޣ�ֻ�Ǽ�ƽ����һ�̣�ȴ�Ѿ����ڽ�ǰ����ʽԽ��ƽƽ����ȴ��Խ��",
"$N������磬��������ʽ������Ͷ��֮���ھ���񣬽�����Ȼ��豹����������ʤ",
});


mapping *action = ({
([      "action": "$N���е�$w����������󽭶�ȥ���Ʋ��ɵ�",
	"force" : 250,
	"attack": 70,
	"dodge" : 30,
	"damage": 13,
	"parry" : 70,
	"lvl"   : 0,
	"damage_type": "����"
]),
([      "action": "$N̤��һ��������$w���һ����������$n��$l",
	"force" : 310,
	"attack": 80,
	"dodge" : 33,
	"parry" : 79,
	"damage": 24,
	"lvl"   : 40,
	"damage_type": "����"
]),
([      "action": "$N����$wһ����һ���̳�������$n��$l��û�а�㻨��",
	"force" : 330,
	"attack": 90,
	"dodge" : 41,
	"parry" : 85,
	"damage": 35,
	"lvl"   : 80,
	"damage_type": "����"
]),
([      "action": "$N����$w΢΢��������Ȼ�̳���һ����������$n��$l",
	"force" : 360,
	"attack": 95,
	"dodge" : 45,
	"parry" : 92,
	"damage": 39,
	"lvl"   : 120,
	"damage_type": "����"
]),
([      "action": "$N���$w����Ȼ��ɨ$n���������",
	"force" : 380,
	"attack": 97,
	"dodge" : 47,
	"parry" : 99,
	"damage": 48,
	"lvl"   : 160,
	"damage_type": "����"
]),
([      "action": "$N���е�$w�������̣��д���һ�������ӹ�$nȫ��",
	"force" : 400,
	"attack": 100,
	"dodge" : 50,
	"parry" : 100,
	"damage": 50,
	"lvl"   : 200,
	"damage_type": "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻵����޷�ѧϰ����������\n");

	if (me->query("max_neili") < 2000)
		return notify_fail("�������̫��޷�ѧϰ����������\n");

	if (me->query_str() < 45)
		return notify_fail("����������̫��޷�ѧϰ����������\n");

	if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
		return notify_fail("����ڹ����ӻ��������޷��������������������\n");

	if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("xuantie-jian", 1);


	if( level > 250 )
		return ([
			"action": CYN+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"CYN)+NOR,
			"dodge": random(30),
			"parry": random(30),
			"force": 350 + random(250),
			"damage": 140 + random(130),
			"damage_type": "����",
		]);


	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) || 
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 80)
		return notify_fail("�����������������������\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�����������������������\n");

	me->receive_damage("qi", 65);
	me->add("neili", -70);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuantie-jian/" + action;
}
