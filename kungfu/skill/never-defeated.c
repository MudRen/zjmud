// never-defeated.c ������

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
	"$n�ƿ�������ǡ�ö����$N�Ĺ�����\n",
	"$n��Ȼ������ֱָ$N���������Ƶ�$Nֻ�ܻ��ء�\n",
	"$n�������ܣ���$N��ʵ��ȫ�������\n",
	"$n����һ�����ԣ��ƺ����⣬ȴ�պö��$N��һ����\n",
});

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("never-defeated", 1);
	return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *action_default = ({
([      "action" : "$N���ƺ��������裬�ƽ������Ƶ�����׽��������$n������ȥ",
	"force" : 410,
	"attack": 150,
	"dodge" : 70,
	"parry" : 120,
	"damage": 225,
	"damage_type":  "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ�������۶�������ɨ$n",
	"force" : 410,
	"attack": 160,
	"dodge" : 85,
	"parry" : 110,
	"damage": 210,
	"damage_type":  "����"
]),
([      "action":"$N�������е�$w������$n�ҿ����ң�û�а���·�",
	"force" : 430,
	"attack": 170,
	"dodge" : 70,
	"parry" : 130,
	"damage": 205,
	"damage_type":  "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n��Χ",
	"force" : 425,
	"attack": 160,
	"dodge" : 65,
	"parry" : 125,
	"damage": 190,
	"damage_type":  "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
	"force" : 530,
	"attack": 176,
	"dodge" : 75,
	"parry" : 115,
	"damage": 200,
	"damage_type":  "����"
]),
([      "action":"$N��̾һ������$w���ֵݳ������Լ�Ҳ��֪��Ҳ��������",
	"force" : 440,
	"attack": 170,
	"dodge" : 80,
	"parry" : 125,
	"damage": 210,
	"damage_type":  "����"
]),
([      "action":"$N��ɫ���أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n",
	"force" : 410,
	"attack": 160,
	"dodge" : 95,
	"parry" : 120,
	"damage": 220,
	"damage_type":  "����"
]),
([      "action":"$N����$w�������籩�꣬���������з���$n��$l�����Ա�$n����",
	"force" : 420,
	"attack": 150,
	"dodge" : 95,
	"parry" : 135,
	"damage": 200,
	"damage_type":  "����"
]),
([      "action":"$NͻȻ���������е�$w��Ȼ��$n�����Ҵ�����",
	"force" : 410,
	"attack": 165,
	"dodge" : 85,
	"parry" : 125,
	"damage": 235,
	"damage_type":  "����"
]),
([      "action":"$N��$w����һ�ڣ�$n�����Լ���$wײ�����������֮����ʵ�����Ѳ�",
	"force" : 430,
	"attack": 180,
	"dodge" : 75,
	"parry" : 110,
	"damage": 225,
	"damage_type":  "����"
]),
([      "action":"$N���е�$w�����ƣ�ȴ�ƻ򵶷����ּ��ӹ���֮�⣬��$nѣĿ",
	"force" : 420,
	"attack": 175,
	"dodge" : 85,
	"parry" : 130,
	"damage": 220,
	"damage_type":  "����"
]),
});

mapping *action_whip = ({
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
	"force" : 430,
	"attack": 180,
	"dodge" : 75,
	"parry" : 115,
	"damage": 225,
	"damage_type": "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ�������۶�����$w�������һ���ɨ$n",
	"force" : 410,
	"attack": 160,
	"dodge" : 85,
	"parry" : 125,
	"damage": 210,
	"damage_type": "����"
]),
([      "action":"$N�������е�$w����������һ�����$n�ҿ����ң�û�а���·�",
	"force" : 440,
	"attack": 175,
	"dodge" : 80,
	"parry" : 125,
	"damage": 205,
	"damage_type": "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n���Ű�Χ",
	"force" : 425,
	"attack": 160,
	"dodge" : 65,
	"parry" : 125,
	"damage": 190,
	"damage_type": "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
	"force" : 510,
	"attack": 180,
	"dodge" : 70,
	"parry" : 120,
	"damage": 200,
	"damage_type": "����"
]),
});

string *usage_skills = ({ "sword", "blade", "dagger",
			  "staff", "hammer", "club", "whip",  
			  "dodge", "parry", "force", "throwing" });

int valid_enable(string usage)
{
	return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
	return combo == "never-defeated";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
	switch (weapon ? weapon->query("skill_type") : "default")
	{
	case "whip":
		return action_whip[random(sizeof(action_whip))];
	default:
		return action_default[random(sizeof(action_default))];
	}
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
	int level;
	int i;

	if ((int)me->query("combat_exp") < 3000000 && !me->query("relife/zhuanshi") )
		return notify_fail("����ò��������֮����"
				   "ƾ�Լ���ս������һʱ��������ᡣ\n");

	if ((int)me->query_skill("martial-cognize", 1) < 50)
		return notify_fail("����ò����񹦹�����£���"
				   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

	if (me->query("character") != "������")
		return notify_fail("��ѧ�˰��죬���ֲ����񹦹Źֵ�"
				   "�������ϳ��������޷���ᡣ");

	if (me->query("int") < 22 && me->query_int() < 52)
		return notify_fail("����ò����񹦹�����£���"
				   "���Լ�������������⡣\n");

	if (me->query("gender") == "����" &&
	    (int)me->query_skill("never-defeated", 1) > 239)
		return notify_fail("���޸����ԣ���������������������Ĳ����񹦡�\n");

	level = me->query_skill("never-defeated", 1);

	if ((int)me->query_skill("martial-cognize", 1) < 300 &&
	    (int)me->query_skill("martial-cognize", 1) < level && !me->query("relife/zhuanshi"))
		return notify_fail("������Լ�����ѧ�������ޣ�������������Ĳ����񹦡�\n");

	if (me->query_skill("force", 1) < level)
		return notify_fail("��Ի����ڹ�����⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("parry", 1) < level)
		return notify_fail("��Ի����мܵ���⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("dodge", 1) < level)
		return notify_fail("��Ի����Ṧ����⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("sword", 1) < level)
		return notify_fail("��Ի�����������⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("blade", 1) < level)
		return notify_fail("��Ի�����������⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("whip", 1) < level)
		return notify_fail("��Ի����޷�����⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	if (me->query_skill("throwing", 1) < level)
		return notify_fail("��Ի�����������⻹�������޷�����"
				   "��������Ĳ����񹦡�\n");

	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;
	int i;
	object weapon;

	lvl = me->query_skill("sword-cognize", 1);
	i = random(lvl);
	
	if (objectp(weapon = me->query_temp("weapon")) &&
	    (string)weapon->query("skill_type") == "sword" &&
	    me->query("family/family_name") == "��ɽ����" &&
	    i > 60 && random(2) == 0)
	{
		if (i < 120)
		{
			victim->receive_wound("qi", damage_bonus / 6);
			return HIC "ֻ��$N" HIC "������Ȼ����$n" HIC "����֪$N" HIC
			       "�ھ����£�����ֱ��$n" HIC "���ڣ�"NOR"\n";
		}
		if (i < 180)
		{
			victim->receive_wound("qi", damage_bonus / 4);
			return HIG "����$N" HIG "΢΢һЦ��ȫ��������" NOR + 
			       weapon->name() + HIG "�У�����ԴԴ��������$n" 
			       HIG "��"NOR"\n";
		}
		if (i < 240)
		{
			victim->receive_wound("qi", damage_bonus / 3);
			return HIW "����$N" HIW "�����������ת����" NOR + 
			       weapon->name() + HIW"��ɲ�Ǽ�����������"
			       "�����͵ؾ���$n" HIW "��"NOR"\n";
		}
		else
		{
			victim->receive_wound("qi", damage_bonus / 2);
			return HIM "$N" HIM "Ĭ���ھ���" NOR + weapon->name() +
			       HIM "�Ϲ���һ�У���ʱ��ֻ�������������粨�˰�"
			       "��ӿ����ɱ��$n" HIM "��"NOR"\n";
		}
	}
}

int practice_skill(object me)
{
	return notify_fail("�����񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
	return 500;
}

string perform_action_file(string action)
{
	return __DIR__"never-defeated/perform/" + action;
}

string exert_function_file(string action)
{
	return __DIR__"never-defeated/exert/" + action;
}


