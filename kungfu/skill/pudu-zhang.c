// pudu-zhang.c �ն��ȷ�
// modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action":"$Nʹһ�С���ţת�ǡ�������$w���¶��ϣ������ޱȵ���$n��С����ȥ��",
	"force" : 180,
	"attack": 24,
	"dodge" : -10,
	"parry" : 10,
	"damage": 15,
	"lvl"   : 0,
	"skill_name" : "��ţת��",
	"damage_type":"����"
]),
([      "action":"$N�첽�����һ�С�Ұ��׷�硹������ƽ��$w�����������ȶˣ�����$n���ؿڡ�",
	"force" : 200,
	"attack": 36,
	"dodge" : -10,
	"parry" : 19,
	"damage": 25,
	"lvl"   : 30,
	"skill_name" : "Ұ��׷��",
	"damage_type":"����"
]),
([      "action":"$N�߾�$w��һ�С��ͻ���������ȫ��Ծ������$w§ͷ�Ƕ�����$n��ȥ��",
	"force" : 230,
	"attack": 42,
	"dodge" : -5,
	"parry" : 25,
	"damage": 25,
	"lvl"   : 60,
	"skill_name" : "�ͻ�����",
	"damage_type":"����"
]),
([      "action":"$Nһ�С�ʨ��ҡͷ����˫�ֳ������֣���׼$n�͵�һ������ͬƽ�ع���һ�����硣",
	"force" : 270,
	"attack": 51,
	"dodge" : -5,
	"parry" : 30,
	"damage": 35,
	"lvl"   : 80,
	"skill_name" : "ʨ��ҡͷ",
	"damage_type":"����"
]),
([      "action":"$N���$w��һ�С�������β�����ȶ˻���������ԲȦ�����ͳ��أ���$n�������С�",
	"force" : 320,
	"attack": 64,
	"dodge" : -15,
	"parry" : 40,
	"damage": 30,
	"lvl"   : 100,
	"skill_name" : "������β",
	"damage_type":"����"
]),
([      "action":"$Nȫ�������$w�̵غ�ɣ�ͻ��һ�С�������������Ӱ��$n��������",
	"force" : 350,
	"attack": 68,
	"dodge" : 5,
	"parry" : 42,
	"damage": 35,
	"lvl"   : 120,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([      "action":"$N˫�ֺ�ʮ������һ�С���ɮ�в�����$w������ɳ���������$nײȥ��",
	"force" : 380,
	"attack": 70,
	"dodge" : -5,
	"parry" : 52,
	"damage": 40,
	"lvl"   : 140,
	"skill_name" : "��ɮ�в�",
	"damage_type":"����"
]),
([      "action":"$Nһ�С��Ⱥ��նɡ���$w�������������Ծ����ֱ��$n���ؿڴ��롣",
	"force" : 410,
	"attack": 72,
	"dodge" : -5,
	"parry" : 60,
	"damage": 45,
	"lvl"   : 160,
	"skill_name" : "�Ⱥ��ն�",
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 300)
		return notify_fail("��������������޷�ѧϰ�ն��ȷ���\n");

	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ����̫ǳ���޷�ѧϰ�ն��ȷ���\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("pudu-zhang", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷�����������ն��ȷ���\n");

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
	level = (int) me->query_skill("pudu-zhang",1);
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
		return notify_fail("��������������ն��ȷ���\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������ն��ȷ���\n");

	me->receive_damage("qi", 65);
	me->add("neili", -68);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"pudu-zhang/" + action;
}
