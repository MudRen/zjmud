// taohua-zhangfa.c �һ��Ʒ�
inherit SKILL;

mapping *action = ({
([      "action" : "$N������ָ����һ�գ�һʽ��������桹����ָ��Ȼңң����$n��$nֻ������"
		   "�ɼ���Ϯ���Լ��崦��Ѩ",
	"force"  : 40,
	"dodge"  : 20,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "�������"
]),
([      "action" : "$NͻȻ����Ծ���գ�һʽ���仨���项��˫�����£�����$n��ͷ��",
	"force"  : 60,
	"dodge"  : 25,
	"damage_type" : "����",
	"lvl" : 10,
	"skill_name" : "�仨����"
]),
([      "action" : "$N������ֲ�£ʳָ��ָ�����������һʽ��Ѱ��̽������ֱָ$n������",
	"force"  : 80,
	"dodge"  : 20,
	"damage_type" : "����",
	"lvl" : 20,
	"skill_name" : "Ѱ��̽��"
]),
([      "action" : "$NͻȻ������ˣ�����һʽ�������š���ƽ�����˫����$n��$l"
		   "��������",
	"force"  : 100,
	"dodge"  : 35,
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "������"
]),
([      "action" : "$Nʹһʽ������Ҷ����ȫ��ͻȻ������ת��˫�ƺ�ǰ�����͵�����$n"
		   "���ؿ�",
	"force"  : 110,
	"dodge"  : 30,
	"damage_type" : "����",
	"lvl" : 40,
	"skill_name" : "����Ҷ"
]),
([      "action" : "$Nǰ��һ�࣬һʽ����ݲ�������˫���Ƴ�һ������֮��Ϯ��$n��$1 ",
	"force"  : 130,
	"dodge"  : 35,
	"damage_type" : "����",
	"lvl" : 50,
	"skill_name" : "��ݲ���"
]),
([      "action" : "$N˫��ʳָ����ָѸ�ٺ���һ��һʽ���ݻ���Ҷ����һ��ǿ�ҵ���"
		   "��ӿ��$n��ȫ��",
	"force"  : 150,
	"parry"  : 25,
	"dodge"  : 20,
	"damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "�ݻ���Ҷ"
]),
([      "action" : "$Nʹһʽ����Ůɢ������˫���������Ȧ������һ������$n��$l�ȥ ",
	"force" : 170,
	"parry" : 25,
	"dodge" : 35,
	"damage_type" : "����",
	"lvl" : 70,
	"skill_name" : "��Ůɢ��"
]),
([      "action" : "$N��������ǰ��ʲ��ʩչ�����Ʋ���������˫����Ȼ�ֿ����������Ź�"
		   "����ٹ���$n",
	"force" : 190,
	"parry" : 25,
	"dodge" : 30,
	"damage_type" : "����",
	"lvl" : 80,
	"skill_name" : "�Ʋ�����"
]),
([      "action" : "$Nһʽ����Ӣ�ͷס���˫������ǰ��ת��Ȧ����������������$n��$nֻ"
		   "�������ƻ������Լ�������Ϊ�������۷���������֪��ܡ�",
	"force" : 210,
	"parry" : 30,
	"dodge" : 35,
	"damage_type" : "����",
	"lvl" : 90,
	"skill_name" : "��Ӣ�ͷ�"
])
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }  

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
	return notify_fail("���һ��Ʒ�������֡�\n");

    if ((int)me->query("max_neili") < 100)
	return notify_fail("�������̫�����޷����һ��Ʒ���\n");

    if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("taohua-zhangfa", 1))
	return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�����������һ��Ʒ���\n");

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
    level = (int)me->query_skill("taohua-zhangfa", 1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 40)
	return notify_fail("�������̫���ˡ�\n");

    if ((int)me->query("neili") < 20)
	return notify_fail("��������������һ��Ʒ���\n");

    me->receive_damage("qi", 30);
    me->add("neili", -5);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"taohua-zhangfa/" + action;
}
