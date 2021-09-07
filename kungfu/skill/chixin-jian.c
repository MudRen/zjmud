// chixin-jian.c �����鳤��
// Made by deaner
// Modified by Venus Oct.1997

#include <ansi.h>

inherit SKILL;

mapping *action = ({
   (["skill_name" : "��Ͷ���չ����",
     "action" : "$Nʹһʽ"+HIC"����Ͷ���չ���ա�"NOR+"����¶΢Ц������$wһ��������"
		"����������$n��$l",
     "dodge"  : 10,
     "force"  : 50,
     "damage" : 10,
     "lvl"    : 0,
     "damage_type":  "����"]),
   (["skill_name" : "ͻ�����������",
     "action" : "$Nʹһʽ"+HIC"��ͻ�������������"NOR+"���������������ж��䣬����$w"
		"��һ�����벻���ķ�λбб����$n��$l",
     "dodge"  : 20,
     "force"  : 70,
     "damage" : 5,
     "lvl"    : 10,
     "damage_type":  "����"]),
   (["skill_name" : "����ĺĺƵ˼��",
     "action" : "$Nʹһʽ"+HIC"������ĺĺƵ˼�䡻"NOR+"���������ߣ����׸���Ƭ�̣���"
		"������$w��Ȼ���ϣ�����$n��$l",
     "dodge"  : 20,
     "force"  : 75,
     "damage" : 20,
     "lvl"    : 20,
     "damage_type":  "����"]),
   (["skill_name" : "ǧ��濾�ֻ�ǿ�",
     "action" : "$Nʹһʽ"+HIC"��ǧ��濾�ֻ�ǿա�"NOR+"������һ�Σ����Ӷ��ϣ�����$w"
		"����һ������׼$n��$l��������",
     "dodge"  : 40,
     "force"  : 90,
     "damage" : 25,
     "lvl"    : 30,
     "damage_type":  "����"]),
   (["skill_name" : "�������������",
     "action" : "$Nʹһʽ"+HIC"��������������须"NOR+"��һ����������$n����Ӱ���棬"
		"����$w���Ȼ��������$n��$l��ȥ",
     "dodge"  : 60,
     "force"  : 100,
     "damage" : 25,
     "lvl"    : 40,
     "damage_type":  "����"]),
   (["skill_name" : "ȴ���칫������",
     "action" : "$Nʹһʽ"+HIC"��ȴ���칫��������"NOR+"��һ����������$w����б����"
		"��ֱָ$n��$l",
     "dodge"  : 50,
     "force"  : 130,
     "damage" : 30,
     "lvl"    : 50,
     "damage_type":  "����"]),
   (["skill_name" : "�����޶���˼��",
     "action" : "$Nʹһʽ"+HIC"�������޶���˼�ࡻ"NOR+"��΢΢һ��ת������$wȴ����"
		"���´���������$n��$l",
     "dodge"  : 40,
     "force"  : 150,
     "damage" : 30,
     "lvl"    : 60,
     "damage_type":  "����"]),
   (["skill_name" : "�˺������޾���",
     "action" : "$Nʹһʽ"+HIC"���˺������޾��ڡ�"NOR+"����ɫ΢�䣬���ж�Ȼ���������"
		"�ȣ�����$w��ƥ��������$n��$l",
     "dodge"  : 30,
     "force"  : 180,
     "damage" : 40,
     "lvl"    : 70,
     "damage_type":  "����"]),
   (["skill_name" : "��Ȼ����������",
     "action" : "$Nʹһʽ"+HIC"����Ȼ���������桻"NOR+"���������ף�����̾�˿���������"
		"Ө����������������$w�й�ֱ����Ѹ���ޱȵ���$n��$l��ȥ",
     "dodge"  : 20,
     "force"  : 200,
     "damage" : 35,
     "lvl"    : 80,
     "damage_type":  "����"]),
   (["skill_name" : "Ը�˳��ÿ��ź�",
     "action" : "$Nʹһʽ"+HIC"��Ը�˳��ÿ��źޡ�"NOR+"�������Ծ������$w�ڰ�������£�"
		"����һ����ɫ��������$n��$l",
     "dodge"  : 30,
     "force"  : 220,
     "damage" : 45,
     "lvl"    : 90,
     "damage_type":  "����"]),
   (["skill_name" : "����δ���ɰ�ͷ",
     "action" : "$Nʹһʽ"+HIC"������δ���ɰ�ͷ��"NOR+"������ಽ������$w���ּ���������"
		"��ৡ���һ����$n��$l��ȥ",
     "dodge"  : 65,
     "force"  : 240,
     "damage" : 50,
     "lvl"    : 100,
     "damage_type":  "����"]),
   (["skill_name" : "����������ǰԵ",
     "action" : "$Nʹһʽ"+HIC"������������ǰԵ��"NOR+"����ؼ���һ�����ֳ�ǰ����������"
		"$w��Ϊ�⻡��$n��$l��ȥ",
     "dodge"  : 40,
     "force"  : 260,
     "damage" : 50,
     "lvl"    : 110,
     "damage_type":  "����"]),
   (["skill_name" : "���鲻�Ƽ��Ƹ�",
     "action" : "$Nʹһʽ"+HIC"�����鲻�Ƽ��Ƹ֡�"NOR+"������Ծ�𣬲�����Ӱ������ȴ�ִ�"
		"����д��£�˫������$w�����Ʊ��˵ش���$n��$l",
     "dodge"  : 60,
     "force"  : 280,
     "damage" : 65,
     "lvl"    : 120,
     "damage_type":  "����"]),
   (["skill_name" : "�����칫������",
     "action" : "$Nʹһʽ"+HIC"�������칫�����ۡ�"NOR+"������$w���͡���һ��б������գ�"
		"�漴���¡��ৡ����£�����һ�����֣���$n��$l��ȥ",
     "dodge"  : 45,
     "force"  : 300,
     "damage" : 60,
     "lvl"    : 130,
     "damage_type":  "����"]),
   (["skill_name" : "�ճ��˻�����ʱ",
     "action" : "$Nʹһʽ"+HIC"���ճ��˻�����ʱ��"NOR+"������΢̧������$w���·�����"
		"����һ�ɾ��練��$n��$l",
     "dodge"  : 50,
     "force"  : 310,
     "damage" : 70,
     "lvl"    : 140,
     "damage_type":  "����"]),
   (["skill_name" : "��������鳤��",
     "action" : "$N�㾡ȫ�����"+HIC"����������鳤����"NOR+"����ɫʮ�ּ�������������"
		"����������$w���費ͣ��ȫ�������������˵Ľ����У�$n���ɺ�Ȼ��ֻ��$N"
		"����΢�䣬�����������ѱ���$n��$l",
     "dodge"  : 70,
     "damage" : 80,
     "force"  : 320,
     "lvl"    : 150,
     "damage_type":  "����"])
});

int valid_enable(string usage){return usage=="sword" || usage=="parry";}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 900)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ���������򲻹����޷�ѧϰ�����鳤����\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("chixin-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ĳ����鳤����\n");

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
    level   = (int) me->query_skill("chixin-jian",1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
	return notify_fail("��ʹ�õ��������ԡ�\n");

    if( (int)me->query("qi") < 50)
	return notify_fail("�������Ŀǰû�а취��ϰ�����鳤����\n");

    if( (int)me->query("neili") < 60)
	return notify_fail("��������������޷���ϰ�����鳤����\n");
	
    me->receive_damage("qi", 40);
    me->add("neili", -55);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"chixin-jian/" + action;
}
