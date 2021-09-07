inherit SKILL;

mapping *action = ({
([      "action": "$N������̧��һ�в�ȭ�ģ۳����ڣݣ���׼$n��$l�ͻ���ȥ",
	"force" : 420,
	"attack": 30,
	"dodge" : 5,
	"parry" : 5,
	"damage": 140,
	"lvl"   : 0,
	"skill_name" : "��ȭ",
	"damage_type":  "����"
]),
([      "action": "$Nһ������ȭ�ģ۰׺�����ݣ�����������ת�ɹ��������������ɹ��֣���\n"
		  "��һ�����죬����$n$l",
	"force" : 480,
	"attack": 35,
	"dodge" : 10,
	"parry" : 50,
	"damage": 155,
	"lvl"   : 0,
	"skill_name" : "����ȭ",
	"damage_type":  "����"
]),
([      "action": "$N����һ�ݣ�ʩչС�����ֵ��ַ���˫�ֶ���$n$l���Ĺؽ�ֱֱץȥ",
	"force" : 220,
	"attack": 40,
	"dodge" : 15,
	"parry" : 15,
	"damage": 70,
	"lvl"   : 0,
	"skill_name" : "С������",
	"damage_type":  "ץ��"
]),
([      "action": "$N��ȭ��������ȭת�ۻ��ţ�һ�����ֵĴ���ȭͻȻ���������������������$n",
	"force" : 280,
	"attack": 60,
	"dodge" : 22,
	"parry" : 20,
	"damage": 90,
	"lvl"   : 30,
	"skill_name" : "���ִ���ȭ",
	"damage_type":  "����"
]),
([      "action": "ֻ��$N����������ʹ���˼�ȭ�еģ۰˼�����ʽ�ݣ�˫�ƶ���$n��$lƽƽ��ȥ",
	"force" : 300,
	"attack": 55,
	"dodge" : 40,
	"parry" : 40,
	"damage": 80,
	"lvl"   : 60,
	"skill_name" : "�˼�ȭ",
	"damage_type":  "����"
]),
([      "action": "$N���һ����������$n���һ����������$n���ֻ�ȥ�����ǰ����Ƶ���ʽ",
	"force" : 310,
	"attack": 65,
	"dodge" : 30,
	"parry" : 30,
	"damage": 95,
	"lvl"   : 80,
	"skill_name" : "������",
	"damage_type":  "����"
]),
([      "action": "$N�������ߣ����ֻ��أ�����һ����������Ƶģ��ο�̽צ�ݣ�Ѹ������$n$l",
	"force" : 320,
	"attack": 80,
	"dodge" : 45,
	"parry" : 45,
	"damage": 85,
	"lvl"   : 100,
	"skill_name" : "���������",
	"damage_type":  "����"
]),
([      "action": "ֻ��$N������ʽ�����䵱�ɵ�����ʹ���ܲ�͸�磬���в���$n��$l",
	"force" : 330,
	"attack": 75,
	"dodge" : 90,
	"parry" : 90,
	"damage": 70,
	"lvl"   : 120,
	"skill_name" : "�䵱����",
	"damage_type":  "����"
]),
([      "action": "$NͻȻ����һԾ����˫������צ״������$n��$l��Ȼץȥ����Ȼ��ӥצ������ʽ",
	"force" : 340,
	"attack": 105,
	"dodge" : 90,
	"parry" : 70,
	"damage": 105,
	"lvl"   : 140,
	"skill_name" : "ӥצ��",
	"damage_type":  "ץ��"
]),
([      "action": "ֻ��$N����һ����˫�ַ�����һ��̫��ȭ�����֣�ֱ��$n$l",
	"force" : 350,
	"attack": 90,
	"dodge" : 90,
	"parry" : 100,
	"damage": 90,
	"lvl"   : 160,
	"skill_name" : "̫��ȭ",
	"damage_type":  "����"
]),
([      "action": "$Nһ��ת����$n���������ֽ�$n���α�ס�͵ĳ�����ˤȥ����Ȼ���ɹŵ�ˤ����ʽ",
	"force" : 360,
	"attack": 105,
	"dodge" : 5,
	"parry" : 60,
	"damage": 105,
	"lvl"   : 180,
	"skill_name" : "ˤ��",
	"damage_type":  "ˤ��"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���ٻ���ȭ������֡�\n");

	if (me->query("max_neili") < 1500)
		return notify_fail("���������ΪԶԶ���㣬������ϰ�ٻ���ȭ��\n");

	if ((int)me->query_skill("force", 1) < 150)
		return notify_fail("����ڹ������ǳ���޷�ѧϰ�ٻ���ȭ��\n");

	if ((int)me->query_skill("unarmed", 1) < 200)
		return notify_fail("���ȭ�Ÿ������ޣ��޷����ٻ���ȭҪ�衣\n");

	if ((int)me->query_skill("cuff", 1) < 150)
		return notify_fail("���ȭ���������ޣ��޷����ٻ���ȭҪ�衣\n");

	if ((int)me->query_skill("hand", 1) < 150)
		return notify_fail("����ַ��������ޣ��޷����ٻ���ȭҪ�衣\n");

	if ((int)me->query_skill("claw", 1) < 150)
		return notify_fail("���צ���������ޣ��޷����ٻ���ȭҪ�衣\n");

	if ((int)me->query_skill("strike") < 150)
		return notify_fail("����Ʒ��������ޣ��޷����ٻ���ȭҪ�衣\n");

	if ((int)me->query_skill("unarmed", 1)/3 < (int)me->query_skill("baihua-quan", 1)/2)
		return notify_fail("���ȭ�Ÿ�������㣬�޷���������İٻ���ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baihua-quan", 1))
		return notify_fail("���ȭ����������㣬�޷���������İٻ���ȭ��\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("baihua-quan", 1))
		return notify_fail("����ַ���������㣬�޷���������İٻ���ȭ��\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("baihua-quan", 1))
		return notify_fail("���צ����������㣬�޷���������İٻ���ȭ��\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("baihua-quan", 1))
		return notify_fail("����Ʒ���������㣬�޷���������İٻ���ȭ��\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "cuff" || usage == "unarmed" || usage == "parry" || usage == "hand" || usage == "strike" || usage == "claw";
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
	level = (int)me->query_skill("baihua-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("����������������Ϣһ�������ɡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 50);
	me->add("neili", -60);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"baihua-quan/" + action;
}

