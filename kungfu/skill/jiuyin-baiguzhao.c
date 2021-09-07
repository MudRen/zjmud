#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$N��צ��Σ���צ������һ�С�������ǡ�ֱ����$n��$l",
    "force" : 250,
    "attack": 45,
    "dodge" : 10,
    "parry" : 18,
    "damage": 30,
    "lvl"   : 0,
    "skill_name" : "�������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N˫��������צ��צצ����$n������������������$n��$lץ��",
    "force" : 270,
    "attack": 50,
    "dodge" : 20,
    "parry" : 26,
    "damage": 45,
    "lvl"   : 40,
    "skill_name" : "��������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N˫��ʹ����ʮָ���ġ������в���$n��$l",
    "force" : 300,
    "attack": 60,
    "dodge" : 20,
    "parry" : 32,
    "damage": 45,
    "lvl"   : 70,
    "skill_name"  : "��������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N����Χ$nһת��ʹ�������޵�������$n��$l����ȫ������צӰ��",
    "force" : 340,
    "attack": 85,
    "dodge" : 30,
    "parry" : 55,
    "damage": 55,
    "lvl"   : 100,
    "skill_name" : "���޵���" ,
    "damage_type" : "ץ��"
]),
([  "action": "$Nʹһ�С������ơ���˫צ�ó�����צӰץ��$nȫ��",
    "force" : 370,
    "attack": 110,
    "dodge" : 40,
    "parry" : 68,
    "damage": 70,
    "lvl"   : 130,
    "skill_name" : "������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N����������һ�С�Ψ�Ҷ���˫צ������$n�������",
    "force" : 420,
    "attack": 140,
    "dodge" : 50,
    "parry" : 85,
    "damage": 90,
    "lvl"   : 160,
    "skill_name" : "Ψ�Ҷ���" ,
    "damage_type" : "ץ��"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_combine(string combo) { return combo == "cuixin-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������׹�צ������֡�\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("�������̫�����޷��������׹�צ��\n");

	if ((int)me->query_str() < 30)
		return notify_fail("�������������������޷��������׹�צ��\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ�̫��޷��������׹�צ��\n");

	if ((int)me->query_skill("claw", 1) < 60)
		return notify_fail("��Ļ���צ��̫��޷��������׹�צ��\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("jiuyin-baiguzhao", 1))
		return notify_fail("��Ļ���צ����򲻹����޷���������ľ����׹�צ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i - 1]["lvl"])
			return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("jiuyin-baiguzhao",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
	object obj;
	object *obs;
	int i, skill, damage;

	skill = me->query_skill("jiuyin-baiguzhao", 1);
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("������������������׹�צ��\n");

	if (skill < 200)
	{
		obs = filter_array(all_inventory(environment(me)),
				   (: (base_name($1) == CORPSE_OB &&
				       ! $1->query("been_cut/head") ||
				       base_name($1) == "/clone/misc/head") &&
				      ! $1->query_temp("clawed_by_jiuyin") :));
		if (sizeof(obs) < 1)
			return notify_fail("�������׹�ץ����ʬ�������õ�ͷ�ǹǡ�\n");

		me->add("neili", -450);
	}

	me->receive_damage("qi", 80);
	me->add("neili", -40);
	if (skill < 200)
	{
		message_vision(HIB "ֻ��$N" HIB "������Ȧ�¹���������ת��������"
			       "�߰˰㻨�������������һ�죬�۵�һ�죬�����ֱָ"
			       "����\nͷ�ǵ����š���������ָ" HIR "Ѫ����"
			       HIB "���Ὣ������"NOR"\n", me);

		if (base_name(obs[0]) == "/clone/misc/head")
			obs[0]->set("long", obs[0]->query("long") +
				    "�����Ȼ�����С��������һ̽���պÿ��Բ��롣\n");

		obs[0]->set_temp("clawed_by_jiuyin", 1);
		me->improve_skill("jiuyin-baiguzhao", 100 + skill * 5 + random(500));
	}

	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if (damage_bonus < 100) return 0;

	if (damage_bonus / 5 > victim->query_str())
	{
		victim->receive_wound("qi", (damage_bonus - 100) / 2);
		return HIR "�����������꡹һ�����죬�����ǹ������ѵ�������"NOR"\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"jiuyin-baiguzhao/" + action;
}
