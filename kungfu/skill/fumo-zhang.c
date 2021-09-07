inherit SKILL;

mapping *action = ({
([      "action":"$N�ݲ���ǰ������$w���¶��ϣ������ޱȵ���$n��С����ȥ",
	"force" : 180,
	"attack": 24,
	"dodge" : -10,
	"parry" : 10,
	"damage": 15,
	"lvl"   : 0,
	"damage_type":"����"
]),
([      "action":"$N�첽���������ƽ��$w�����������ȶˣ�����$n���ؿ�",
	"force" : 200,
	"attack": 36,
	"dodge" : -10,
	"parry" : 19,
	"damage": 25,
	"lvl"   : 30,
	"damage_type":"����"
]),
([      "action":"$N�߾�$w��ȫ��Ծ������$w����$nͷ���������Ȼ������ȥ",
	"force" : 230,
	"attack": 42,
	"dodge" : -5,
	"parry" : 25,
	"damage": 25,
	"lvl"   : 60,
	"damage_type":"����"
]),
([      "action":"$N˫�ֳ������֣���׼$n�͵�һ������ͬƽ�ع���һ������",
	"force" : 270,
	"attack": 51,
	"dodge" : -5,
	"parry" : 30,
	"damage": 35,
	"lvl"   : 80,
	"damage_type":"����"
]),
([      "action":"$N���$w���ȶ˻���������ԲȦ�����ͳ��أ���$n��������",
	"force" : 320,
	"attack": 64,
	"dodge" : -15,
	"parry" : 40,
	"damage": 30,
	"lvl"   : 100,
	"damage_type":"����"
]),
([      "action":"$Nȫ�������$w�̵غ�ɣ�����������Ӱ����Ӱ��$n��������",
	"force" : 350,
	"attack": 68,
	"dodge" : 5,
	"parry" : 42,
	"damage": 35,
	"lvl"   : 120,
	"damage_type":"����"
]),
([      "action":"$N˫�ֺ�ʮ������һ�ݳ�$w��ֻ��$w������ɳ���������$nײȥ",
	"force" : 380,
	"attack": 70,
	"dodge" : -5,
	"parry" : 52,
	"damage": 40,
	"lvl"   : 140,
	"damage_type":"����"
]),
([      "action":"$N���һ��������$w�������������Ծ����ֱ��$n���ؿڴ���",
	"force" : 410,
	"attack": 72,
	"dodge" : -5,
	"parry" : 60,
	"damage": 45,
	"lvl"   : 160,
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 300)
		return notify_fail("��������������޷�ѧϰ��ʮ��·��ħ�ȡ�\n");

	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ����̫ǳ���޷�ѧϰ��ʮ��·��ħ�ȡ�\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("fumo-zhang", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������Ķ�ʮ��·��ħ�ȡ�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("fumo-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("���������������ʮ��·��ħ�ȡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("���������������ʮ��·��ħ�ȡ�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -68);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"fumo-zhang/" + action;
}

