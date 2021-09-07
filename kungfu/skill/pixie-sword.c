// pixie-sword.c
// modified by Venus Oct.1997
#include <ansi.h>
inherit SKILL;

mapping *action = ({
    ([  "name":    "Ⱥа����",
	"action":  "$Nʹһ�С�Ⱥа���ס�������$wȦ��ٿ�ش̳������ǵ�㣬����ֱ��$n��$l��ȥ",
	"dodge":   5,
	"damage":  0,
	"damage_type":  "����"
    ]),
    ([  "name":    "��ظ��Ŀ",
	"action":  "$Nһ�С���ظ��Ŀ����������ת��Χ��$n��Χ���̣������������$n��$l",
	"dodge":   0,
	"damage":  5,
	"damage_type":  "����"
    ]),
    ([  "name":    "��������",
	"action":  "$N�趯$w��һ�С���������Ю�������������$n��$l",
	"dodge":   10,
	"damage":  10,
	"damage_type":  "����"
    ]),
    ([  "name":    "���Ǹ���",
	"action":  "$N����$wһ����Х�����������Ǹ��¡�������˸������������裬�͵���һ��ͦ����ֱ��$n$l",
	"dodge":   5,
	"damage":  5,
	"damage_type":  "����"
    ]),
    ([  "name":    "���ഩ��",
	"action":  "$N����$w���Ⱪ����һ�С����ഩ������$n$l��ȥ",
	"dodge":   10,
	"damage":  10,
	"damage_type":  "����"
    ]),
    ([  "name":    "����Ū��",
	"action":  "$N����$w����һ���⻡��ֱָ$n$l��һ�С�����Ū�ѡ���������������ȥ",
	"dodge":   5,
	"damage":  15,
	"damage_type":  "����"
    ]),
});

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_neili") < 50)
	return notify_fail("�������������û�а취����а������\n");

    if ((int)me->query_skill("sword", 1) < (int)me->query_skill("pixie-sword", 1))
	return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������ı�а������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    object ob;

    if (! (ob = me->query_temp("weapon")) ||
       (string)ob->query("skill_type") != "sword")
	return notify_fail("���������һ�ѽ�������������\n");

    if ((int)me->query("qi") < 30)
       return notify_fail("�������̫���ˣ�û�а취��ϰ��а������\n");
	
    if ((int)me->query("neili") < 5)
       return notify_fail("�������������û�а취��ϰ��а������\n");

    me->receive_damage("qi", 25);
    me->add("neili", -2);
    return 1;
}
