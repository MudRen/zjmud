// shenlong-bashi ������ʽ
inherit SKILL;

mapping *action = ({
([	"action": "$Nʹһ�С���Ӱ��б������������һĨ����$n��$l��ȥ",
	"force" : 100,
	"parry" : 10,
	"damage": 20,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name" : "��Ӱ��б"
]),
([	"action": "$N������ȣ�˫��ʹһ�С��嶡��ɽ��������$n��$l",
	"force" : 150,
	"attack": 5,
	"parry" : 30,
	"damage": 30,
	"lvl"   : 60,
	"damage_type" : "����",
	"skill_name" : "�嶡��ɽ"
]),
([	"action": "$N˳��ʹһ�С����в��ȡ����Ƽ�ת�����ƻ��棬����ֱ��$n",
	"force" : 200,
	"attack": 15,
	"dodge" : 80,
	"parry" : 20,
	"damage": 40,
	"lvl"   : 80,
	"damage_type": "����",
	"skill_name" : "���в���"
]),
([	"action": "$N�˺󼸲���ͻȻ����һ�ƣ�һ�С�������β�����ޱȹ���ػ���$n",
	"force" : 250,
	"attack": 21,
	"dodge" : 80,
	"parry" : 20,
	"damage": 50,
	"lvl"   : 100,
	"damage_type": "����",
	"skill_name" : "������β"
]),
([	"action": "$Nʹһʽ�������ơ���ȫ�������ת��˫��һǰһ���͵�����$n���ؿ�",
	"force" : 300,
	"attack": 32,
	"dodge" : 10,
	"parry" : 52,
	"damage": 50,
	"lvl"   : 30,
	"lvl"   : 140,
	"damage_type" : "����",
	"skill_name" : "������"
]),
([	"action": "$N����ʹ����Ǭ��������������֧�أ�˫�ȷ�������$n",
	"force" : 350,
	"attack": 35,
	"dodge" : 60,
	"parry" : 32,
	"damage": 60,
	"lvl"   : 160,
	"damage_type": "����",
	"skill_name" : "Ǭ������"
]),
([	"action": "$N���һ����ʹ����ͬ���ھ���������һ�а�����$n",
	"force" : 380,
	"attack": 45,
	"dodge" : 45,
	"parry" : 30,
	"damage": 60,
	"lvl"   : 180,
	"damage_type": "����",
	"skill_name" : "ͬ���ھ�"
]),
([	"action": "$N����һ�����������ǳ���״����Ȼ���Ǹ��°�ֱײ��$n",
	"force" : 400,
	"attack": 52,
	"dodge" : 80,
	"parry" : 15,
	"damage": 70,
	"lvl"   : 200,
	"damage_type": "����",
	"skill_name" : "���Ǹ���"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) { return combo == "huagu-mianzhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������ʽ������֡�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹����޷�ѧ������ʽ.\n");

	if ((int)me->query("max_neili") < 750)
		return notify_fail("�������̫�����޷���������ʽ��\n");

	if ((int)me->query_skill("hand", 1) < 80)
		return notify_fail("��Ļ����ַ���򲻹����޷�ѧϰ������ʽ��\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("shenlong-bashi", 1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷�ѧϰ�������������ʽ��\n");

	return 1;
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
		return notify_fail("�������������������ʽ��\n");

	me->receive_damage("qi", 61);
	me->add("neili", -62);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shenlong-bashi/" + action;
}
