// baibian-daxue.c
inherit SKILL;

mapping *action = ({
([      "action":"$Nһ�С�ָ�㽭ɽ��������$w������$n������Ѩ!",
	"force" : 60,
	"dodge" : 20,
	"damage" : 22,
	"lvl" : 0,
	"damage_type" : "����",
	"skill_name" : "ָ�㽭ɽ",
]),
([      "action":"$N��������һ�С�������������$w���������£���$n�׺�Ѩ��ȥ",
	"force" : 90,
	"dodge" : 15,
	"damage" : 28,
	"lvl" : 9,
	"damage_type": "����",
	"skill_name" : "��������",
]),
([      "action":"$N��ǰ����һ��������$wһ�Σ�����һ��ʹ������������������$n�ĵز�Ѩ",
	"force" : 120,
	"dodge" : 10,
	"damage" : 32,
	"lvl" : 19,
	"damage_type" : "����",
	"skill_name" : "��������",
]),
([      "action":"$N���е�$w���Ҽ��Σ����һ�ι�â��ʹ����ǧ���򻯡����ź�������������$n������Ѩ",
	"force" : 140,
	"dodge" : 8,
	"damage" : 38,
	"lvl" : 29,
	"damage_type": "����",
	"skill_name" : "ǧ����",
]),
([      "action":"$N����Ծ��һʽ��ǧ�߳����������������Ӱ��������ס$n",
	"force" : 160,
	"dodge" : 15,
	"damage" : 44,
	"lvl" : 39,
	"damage_type": "����",
	"skill_name" : "ǧ�߳���",
]),
([      "action":"$N�������У�$w�Ƴ������â���ӳ�����̨�۾�����һ�п�һ�еع���$n",
	"force" : 190,
	"dodge" : 12,
	"damage" : 49,
	"lvl" : 59,
	"damage_type": "����",
	"skill_name" : "��̨�۾�",
]),
([      "action":"$Nʹ��һ�С�������·��ͦ���й�ֱ����$w���Ĳ�������;��Ȼת�����ϱ���޷�",
	"force" : 230,
	"dodge" : 5,
	"damage" : 53,
	"lvl" : 79,
	"damage_type": "����",
	"skill_name" : "������·",
]),
([      "action":"$N�������е�$wб�̣�һ�С���ɵ�����������$n��ǰ̴�д�Ѩ",
	"force" : 250,
	"dodge" : 15,
	"damage" : 58,
	"lvl" : 99,
	"damage_type": "����",
	"skill_name" : "��ɵ���",
]),
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 150)
		return notify_fail("�������������û�а취���ٱ��Ѩ����\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ���򲻹���������ѧϰ�ٱ��Ѩ��!\n");

	if ((int)me->query_skill("staff", 1) < (int)me->query_skill("baibian-daxue", 1))
		return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������İٱ��Ѩ�ȷ���\n");

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
       level   = (int) me->query_skill("baibian-daxue",1);
       for(i = sizeof(action); i > 0; i--)
	       if(level > action[i-1]["lvl"])
		       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{       object ob;
	if( !(ob = me->query_temp("weapon")) ||
	    (string)ob->query("skill_type") != "staff" )
		return notify_fail("���������һ�����Ȳ���ѧϰ�ٱ��Ѩ����\n");

	if( (int)me->query("qi") < 50)
		return notify_fail("�����������û�а취��ϰ�ٱ��Ѩ����\n");

	if( (int)me->query("neili") < 40)
		return notify_fail("�������������û�а취��ϰ�ٱ��Ѩ����\n");

	me->receive_damage("qi", 32);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__ "baibian-daxue/" + action;
}

