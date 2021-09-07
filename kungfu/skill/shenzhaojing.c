// ���վ��� shenzhaojing.c
// Editd By Vin On 26/4/2001

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("shenzhaojing", 1);
	return lvl * lvl * 15 * 16 / 100 / 200;
}

mapping *action = ({
([      "action" : "$NٿȻԾ��������һȭ����һȭ������Ӱ��ȥ�ƿ켫����$n���ؿڴ�ȥ",
	"dodge"  : 81,
	"force"  : 323,
	"attack" : 119,
	"parry"  : 94,
	"damage" : 68,
	"lvl"    : 0,
	"damage_type": "����" 
]), 
([      "action" : "$N˿��������ɫ������ƽ�죬�����������վ��񹦵ľ���������һ������$n",
	"dodge"  : 73,
	"force"  : 362,
	"attack" : 138,
	"parry"  : 51,
	"damage" : 73,
	"lvl"    : 200,
	"damage_type": "����"
]), 
([      "action" : "$N����΢΢һչ����Ȼ������$n��ǰ����Ȼ��˫����ʩ����$n���Ķ�ȥ",
	"dodge"  : 78,
	"force"  : 389,
	"attack" : 152,
	"parry"  : 53,
	"damage" : 87,
	"lvl"    : 220,
	"damage_type": "����"
]),
([      "action" : "$N�˺�һ����˫�ƻ��գ���ջ���һ��ԲȦ����ʱһ�����ȵ�����ֱӿ$n����",
	"dodge"  : 75,
	"force"  : 410,
	"attack" : 163,
	"parry"  : 67,
	"damage" : 93,
	"lvl"    : 250,
	"damage_type": "����"
]), 
});

int valid_force(string force)
{
	return 1;
}

int valid_enable(string usage)
{ 
	return usage == "force" || usage=="unarmed" || usage =="parry";
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" && me->query("shenzhaojing", 1) > 49)
		return notify_fail("���޸����ԣ�������������������������վ��񹦡�\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ������100��������ѧ���վ��񹦡�\n");

	if ((int)me->query_skill("unarmed", 1) < 100)
		return notify_fail("��Ļ���ȭ�Ż����100��������ѧ���վ��񹦡�\n");

	if ((int)me->query("max_neili", 1) < 1000)
		return notify_fail("���������Ϊ����1000�㣬����ѧ���վ��񹦡�\n");

	if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
		return notify_fail("��Ļ����ڹ�ˮƽ���������Զ������������վ��񹦡�\n");

	if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���������Զ������������վ��񹦡�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("shenzhaojing", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 50, level)];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;

	lvl = me->query_skill("shenzhaojing", 1);

	if (damage_bonus < 160 || lvl < 180) return 0;

	// ���վ��������еļ���������˺���ʹ������
	// ����max_hit �������书���Ǿ��޽��еģ�����
	// �����ֵļ����Լ��˺�ֵ�ּ������˺��������
	// ���书��������
	if (damage_bonus / 6 > victim->query_con() && random(3) == 0)
	{
		victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
		victim->affect_by("shenzhao",
			       ([ "level" : me->query("jiali") + random(me->query("jiali")),
				  "id"    : me->query("id"),
				  "duration" : lvl / 150 + random(lvl / 10) ]));
		return HIR "$n" HIR "һ���Һ���ȫ��������������"
		       "�����߹ǡ��۹ǡ��ȹ�ͬʱ���ۡ�"NOR"\n";
	}
}

int practice_skill(object me)
{
	int lvl;
	lvl = me->query_skill("shenzhaojing", 1);
	
	if (me->query_temp("shenzhaojing/parctice"))
		return notify_fail("��������ϰ���վ���ȴ���������᲻�������������ǵõ�һ������ϰ��\n");
		
	if (lvl < 40)
		return notify_fail("������վ�����ʶ̫ǳ��ֻ����ѧ(learn)�������������ȡ�\n");
	
	if (lvl > 180)
		return notify_fail("��������վ��񹦸����ޱȣ�����ͨ���򵥵���ϰ�����������ȡ�\n");
	
	if ((int)me->query("neili") < 200 + (20 * lvl) / 6)
		return notify_fail("�����ڵ�����̫���ˣ��޷���ϰ���վ��񹦡�\n");
		
	if (me->query("potential") - me->query("learned_points") >= 10)
	{
		me->improve_skill("shenzhaojing", me->query("con") * 4 + 20);
		me->set_temp("shenzhaojing/parctice",1);
		me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), 2);
		me->add("neili", - (20 * lvl) / 6); 
		me->add("potential", -10);
		return 1;
	}
	else 
		return notify_fail("������û��Ǳ����������վ����ˡ�\n");
	
	return notify_fail("���վ���ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
	return 500;
}

string perform_action_file(string action)
{
	return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
	return __DIR__"shenzhaojing/exert/" + action;
}

void remove_effect(object me)
{
	if (me->query_temp("shenzhaojing/parctice"))
	{
		me->delete_temp("shenzhaojing/parctice");
	}
}
