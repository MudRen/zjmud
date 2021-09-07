// taiji-quan.c ̫��ȭ 
// ���Ӳ�ͬ���ܼ�����Ӧ��ѧϰ����ʹ����������, by ReyGod, in 12/17/1996
//      query_skill_name() and query_action()
// Updated by Doing

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action" : "$Nʹһ�С�"+RED+"��ȸβ"+NOR+"����˫�ֻ��˸���Ȧ������$n��$l",
	"force" : 20,
	"dodge" : 50,
	"parry" : 38,
	"skill_name" : RED"��ȸβ"NOR,
	"lvl" : 0,
	"damage_type" : "����"
]),
([	"action" : "$Nʹһ�С�"+GRN+"����"+NOR+"������������ӳ�������$n��$l",
	"force" : 25,
	"dodge" : 48,
	"parry" : 57,
	"skill_name" : GRN"����"NOR,
	"lvl" : 5,
	"damage_type" : "����"
]),
([	"action" : "$Nʹһ�С�"+YEL+"������ʽ"+NOR+"������$n��$l��ȥ",
	"force" : 25,
	"dodge" : 46,
	"parry" : 49,
	"skill_name" : YEL"������ʽ"NOR,
	"lvl" : 10,
	"damage_type" : "����"
]),
([	"action" : "$N˫�ֻ�����ʹһ�С�"+HIC+"�׺�����"+NOR+"�����ֻ�$n�����ź�$l",
	"force" : 25,
	"dodge" : 44,
	"parry" : 71,
	"skill_name" : HIC"�׺�����"NOR,
	"lvl" : 15,
	"damage_type" : "����"
]),
([	"action" : "$N����΢ת��ʹһ�С�"+HIW+"§ϥ�ֲ�"+NOR+"��������$n��$l",
	"force" : 25,
	"dodge" : 44,
	"parry" : 58,
	"skill_name" : HIW"§ϥ�ֲ�"NOR,
	"lvl" : 20,
	"damage_type" : "����"
]),
([	"action" : "$N�������������������ںϣ�һ�С�"+MAG+"�ֻ�����"+NOR+"������$n��$l��ȥ",
	"force" : 30,
	"dodge" : 48,
	"parry" : 62,
	"skill_name" : MAG"�ֻ�����"NOR,
	"lvl" : 25,
	"damage_type" : "����"
]),
([	"action" : "$N��ȭ�����´�����һ�С�"+RED+"��׿���"+NOR+"��������$n��$l",
	"force" : 30,
	"dodge" : 54,
	"parry" : 71,
	"skill_name" : RED"��׿���"NOR,
	"lvl" : 30,
	"damage_type" : "����"
]),
([	"action" : "$N���ǰ̤�벽������ʹһ�С�"+YEL+"������"+NOR+"����ָ������$n��$l��ȥ",
	"force" : 30,
	"dodge" : 76,
	"parry" : 65,
	"skill_name" : YEL"������"NOR,
	"lvl" : 35,
	"damage_type" : "����"
]),
([	"action" : "$N�С�"+GRN+"��ͨ��"+NOR+"�������һ������������ȭ��$n��$l��ȥ",
	"force" : 30,
	"dodge" : 79,
	"parry" : 76,
	"skill_name" : GRN"��ͨ��"NOR,
	"lvl" : 40,
	"damage_type" : "����"
]),
([	"action" : "$N��������ԣ�����ʹһ�С�"+HIC+"б��ʽ"+NOR+"��������$n��$l",
	"force" : 35,
	"dodge" : 82,
	"parry" : 52,
	"skill_name" : HIC"б��ʽ"NOR,
	"lvl" : 45,
	"damage_type" : "����"
]),
([	"action" : "$N�����鰴������ʹһ�С�"+YEL+"��������"+NOR+"������$n��$l��ȥ",
	"force" : 35,
	"dodge" : 70,
	"parry" : 82,
	"skill_name" : YEL"��������"NOR,
	"lvl" : 50,
	"damage_type" : "����"
]),
([	"action" : "$N˫����ȭ����ǰ��󻮻���һ�С�"+HIC+"˫����"+NOR+"������$n��$l",
	"force" : 35,
	"dodge" : 88,
	"parry" : 51,
	"skill_name" : HIC"˫����"NOR,
	"lvl" : 55,
	"damage_type" : "����"
]),
([	"action" : "$N�����黮������һ�ǡ�"+WHT+"ָ�ɴ�"+NOR+"������$n���ɲ�",
	"force" : 40,
	"dodge" : 86,
	"parry" : 71,
	"skill_name" : WHT"ָ�ɴ�"NOR,
	"lvl" : 60,
	"damage_type" : "����"
]),
([	"action" : "$Nʩ����"+MAG+"����ʽ"+NOR+"�������ֻ���$n��$l�����ֹ���$n���ɲ�",
	"force" : 40,
	"dodge" : 84,
	"parry" : 81,
	"skill_name" : MAG"����ʽ"NOR,
	"lvl" : 65,
	"damage_type" : "����"
]),
([	"action" : "$N�ɱ۴��֣�����������һ�С�"+RED+"����"+NOR+"��������$n��$l",
	"force" : 45,
	"dodge" : 82,
	"parry" : 87,
	"skill_name" : RED"����"NOR,
	"lvl" : 70,
	"damage_type" : "����"
]),
([	"action" : "$N������������ʹһ�С�"+YEL+"�𼦶���"+NOR+"������$n��$l��ȥ",
	"force" : 50,
	"dodge" : 90,
	"parry" : 51,
	"skill_name" : YEL"�𼦶���"NOR,
	"lvl" : 75,
	"damage_type" : "����"
]),
([	"action" : "$N�����ɹ����ƣ�˫���������ϣ��Ƴ�һ�С�"+HIC+"��̽��"+NOR+"��",
	"force" : 55,
	"dodge" : 68,
	"parry" : 90,
	"skill_name" : HIC"��̽��"NOR,
	"lvl" : 80,
	"damage_type" : "����"
]),
([	"action" : "$N����ʹһʽ�С�"+MAG+"��Ů����"+NOR+"����������$n��$l��ȥ",
	"force" : 60,
	"dodge" : 76,
	"parry" : 92,
	"skill_name" : MAG"��Ů����"NOR,
	"lvl" : 85,
	"damage_type" : "����"
]),
([	"action" : "$N���־���ǰƲ����ʹһ�С�"+HIG+"����Ʋ��"+NOR+"������$n��$l��ȥ",
	"force" : 65,
	"dodge" : 84,
	"parry" : 95,
	"skill_name" : HIG"����Ʋ��"NOR,
	"lvl" : 90,
	"damage_type" : "����"
]),
([	"action" : "$N�����鰴������ʹһ�С�"+HIB+"�������"+NOR+"������$n��$l��ȥ",
	"force" : 70,
	"dodge" : 42,
	"parry" : 99,
	"skill_name" : HIB"�������"NOR,
	"lvl" : 100,
	"damage_type" : "����"
]),
([	"action" : "$N�������ϻ���������ʹһ�С�"+RED+"��������"+NOR+"������$n��$l��ȥ",
	"force" : 75,
	"dodge" : 81,
	"parry" : 102,
	"skill_name" : RED"��������"NOR,
	"lvl" : 120,
	"damage_type" : "����"
]),
([	"action" : "$Nʹһ�С�"+YEL+"�Դ�"+NOR+"��������§��ϥ���������´���$n��$l",
	"force" : 80,
	"dodge" : 88,
	"parry" : 115,
	"skill_name" : YEL"�Դ�"NOR,
	"lvl" : 140,
	"damage_type" : "����"
]),
([	"action" : "$N˫���ȱ�����״����һ�С�"+MAG+"Ұ�����"+NOR+"������$n��$l�����Ŵ�ȥ",
	"force" : 85,
	"dodge" : 86,
	"parry" : 119,
	"skill_name" : MAG"Ұ�����"NOR,
	"lvl" : 160,
	"damage_type" : "����"
]),
([	"action" : "$N��������ǰ���£��ұ�΢����һ�С�"+HIC+"������ɽ"+NOR+"������$n��$l��ȥ",
	"force" : 90,
	"dodge" : 94,
	"parry" : 115,
	"skill_name" : HIC"������ɽ"NOR,
	"lvl" : 180,
	"damage_type" : "����"
]),
([	"action" : "$N˫������ǰ����ʮ��״��һʽ��"+HIY+"ʮ����"+NOR+"������$n��$l��ȥ",
	"force" : 95,
	"dodge" : 102,
	"parry" : 122,
	"skill_name" : HIY"ʮ����"NOR,
	"lvl" : 200,
	"damage_type" : "����"
]),
([	"action" : "$N���̤�鲽��˫�ֽ���ʮ��ȭ��һ�С�"+HIM+"��������"+NOR+"������$n��$l��ȥ",
	"force" : 100,
	"dodge" : 110,
	"parry" : 133,
	"skill_name" : HIM"��������"NOR,
	"lvl" : 210,
	"damage_type" : "����"
]),
([	"action" : "$N��������ڳ���ʹһ�С�"+HIG+"�����"+NOR+"������$n��$l�����Ŵ�ȥ",
	"force" : 115,
	"dodge" : 132,
	"parry" : 121,
	"skill_name" : HIG"�����"NOR,
	"lvl" : 220,
	"damage_type" : "����"
]),
([	"action" : "$N����Ϊ�ᣬһ�С�"+HIC+"ת�����"+NOR+"������$n������Ӱ֮��",
	"force" : 120,
	"dodge" : 154,
	"parry" : 145,
	"skill_name" : HIC"ת�����"NOR,
	"lvl" : 230,
	"damage_type" : "����"
]),
([	"action" : "$N˫����ȭ��ȭ�������һ�С�"+HIR+"�乭�仢"+NOR+"����ֱ��$n���Ѷ�ȥ",
	"force" : 115,
	"dodge" : 166,
	"parry" : 175,
	"skill_name" : HIR"�乭�仢"NOR,
	"lvl" : 240,
	"damage_type" : "����"
]),
([	"action" : "$N˫���Ƴ���һ�С�"+GRN+"����Ʊ�"+NOR+"����һ�ɾ���ֱ��$n",
	"force" : 120,
	"dodge" : 178,
	"parry" : 185,
	"skill_name" : GRN"����Ʊ�"NOR,
	"lvl" : 250,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "wudang-zhang" || combo == "paiyun-shou";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��̫��ȭ������֡�\n");

	if ((int)me->query_skill("force") < 180)
		return notify_fail("����ڹ���򲻹����޷�ѧ̫��ȭ��\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷���̫��ȭ��\n");

	if ((int)me->query_skill("unarmed", 1) < 100)
		return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ѧ̫��ȭ��\n");

	if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("taiji-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷����������̫��ȭ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action) - 1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("taiji-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 5, level / 5)];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;

	if ((int)me->query_skill("taiji-quan", 1) < 100 ||
	    ! living(me) || me->query_temp("weapon"))
		return;

	mp = ob->query_skill("count", 1);
	ap = ob->query_skill("force") + mp;
	dp = me->query_skill("parry", 1) / 2 +
	     me->query_skill("taiji-quan", 1);

	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(3))
		{
		case 0:
			result += (["msg" : HIC "$n" HIC "�溬΢Ц��˫�������������"
					    "һ��ԲȦ����Ȼ��$N" +
					    HIC "�Ĺ���ȫ��������"NOR"\n"]);
			break;

		case 1:
			result += (["msg" : HIC "$n" HIC "���Ҹ񵵣�ʹ��������ǧ����ַ���"
					    "����$N" HIC "�Ĺ��������Ρ�"NOR"\n"]);
			break;

		default:
			result += (["msg" : HIC "$n" HIC "������ȭ"
					    HIC "��������Ȼ������ȴ��$N"
					    HIC "�е�����ճ�ͣ������泩��"NOR"\n"]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(3))
		{
		case 0:
			result = HIY "$n" HIY "�溬΢Ц��˫�������������"
				 "һ��ԲȦ��Ȼ��$N" +
				 HIY "��Ҳ�������ֻ���ֱ�룬��Ϯ$n"
				 HIY "��"NOR"\n";
			break;

		case 1:
			result = HIY "$n" HIY "���Ҹ񵵣�ʹ��������ǧ����ַ���"
				 "����$N" HIY "����ȴ�Ǳ仯�޷�������ѭ����"NOR"\n";
			break;

		default:
			result = HIY "$n" HIY "������ȭ"
				 HIY "����������ȴ��$N"
				 HIY "�е�ճ�ͣ�����$N"
				 HIY "���̱仯���࣬�����п��ٽ���$n"
				 HIY "��"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

int query_effect_parry(object attacker, object me)
{
	int lvl;

	if (me->query_temp("weapon"))
		return 0;

	lvl = me->query_skill("taiji-quan", 1);
	if (lvl < 80)  return 0;
	if (lvl < 200) return 50;
	if (lvl < 280) return 80;
	if (lvl < 350) return 100;
	return 120;
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������̫��ȭ��\n");

	me->receive_damage("qi", 40);
	me->add("neili", -80);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"taiji-quan/" + action;
}
//�ȼ��������Ƿ�ѧ���µ���ʽ
string query_skill_up(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
	 {
		if(level == action[i]["lvl"])
		 {
		     return action[i]["skill_name"];
		 }
	 }
	  return "no";
}