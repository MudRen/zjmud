#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
	"ȴ��$n̤ǰһ������ʽбָ����ұۣ���Ҫʹ$P������ˡ�\n",
	"$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$P�͹����ػӳ���λ�����̩ɽ��" HIY "�����" NOR "��������\n",
	"$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ�����ġ�" HIC "��������" NOR "����ͼ��ʹ$P���С�\n",
	"$nͻȻһ������$P��$l����һ��ȴ�����������ţ�$P�����޴룬���Ʋ�������ͣ��������\n"
	"$n�������ܣ��ٽ������ʹ����" HIC "���両��" NOR "������$P��$l���뵲������С�\n",
	"$nͻȻʹ��������ɷ罣���ġ�" HIG "���ڤڤ" NOR "�������Ƿ�λȴ����ƫ���������$Pһ�ʣ���\nͼͻ��$P�Ĺ��ƣ�\n"
	"$nͦ��һ�����ǡ�" HIW "���Ƴ��" NOR "���ش�$P��$l����ͼ��$P�Ĺ��ƻ��⡣\n",
	"ֻ��$n���˷���������Ʈ�磬�����һʽ��" HIW "��������" NOR "���������޶�����׽���ص�ס��$P��\n������\n",
	"$n���˷�����ʹ����ɽ���С�" HIC "�������" NOR "����ɭɭ�����������ܣ��ܿ���$P������\n",
});

string *feiyue_msg = ({
"$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��֪����Ǻ�",
"$N����һ��ָ��$n���������$n���������ڣ��˵����������ף�����˼��",
"$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮����ʵ�����Ѳ�",
"$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����ʲô����",
"$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ��������ȵ�$n���ò���",
"$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������$n��$l",
"$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N��������ʵ",
"$N���ֺὣ����$n��$l���������������е�һ��������ȴ�����$n���Կ��彣������",
});

mapping *action = ({
([      "action" : "����$Nͦ����ϣ�$wһ����һ�з·�̩ɽ�����ġ�" HIC "������Ȫ" NOR "��ֱ��$n��$l",
	"force" : 10,
	"attack": 62,
	"dodge" : 45,
	"parry" : 45,
	"damage": 10,
	"lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$N������$n�ӳ���" CYN "Ȫ��ܽ��" NOR "������" MAG "�����ϸ�" NOR "������" HIG
		   "ʯ������" NOR "������" HIW "��������" NOR "������" HIY "���ף��" NOR "����\n"
		   "ɽ����",
	"force" : 10,
	"attack": 65,
	"dodge" : 50,
	"parry" : 45,
	"damage": 15,
	"lvl" : 7,
	"damage_type" : "����"
]),
([
	"action" : "$N������ת�������̳�ʮ�Ž�����Ȼ�ǻ�ɽ��" HIW "��Ůʮ�Ž�" NOR "�������������"
		   "ʮ�Ž�����һ�У��ַ�֮�죬\n"
		   "ֱ�Ƿ�����˼",
	"force" : 10,
	"attack": 60,
	"dodge" : 65,
	"parry" : 60,
	"damage": 20,
	"lvl" : 14,
	"damage_type" : "����"
]),
([      "action" : "$N���ƺ��������裬�������������������ɽ����Ϊһ������$n������ȥ",
	"force" : 20,
	"attack": 65,
	"dodge" : 65,
	"parry" : 60,
	"damage": 25,
	"lvl" : 21,
	"damage_type" : "����"
]),
([      "action" : "$N����ͻ������ɭ�ϣ�����ǧ�������۶�������ǹ��ꪣ���ɳǧ�������ɽ���ƻ���$n",
	"force" : 20,
	"attack": 70,
	"dodge" : 60,
	"parry" : 65,
	"damage": 30,
	"lvl" : 28,
	"damage_type" : "����"
]),
([      "action" : "ȴ��$N���潣�ߣ����һ�գ��ұ�һ�䣬����Ҳ��ԽתԽ�Ӻ�����������" HIY "̩ɽʮ��"
		   "��" NOR "��Ϊһ����\n"
		   "��$n",
	"force" : 30,
	"attack": 73,
	"dodge" : 70,
	"parry" : 65,
	"damage": 30,
	"lvl" : 35,
	"damage_type" : "����"
]),
([      "action" : "$N����ͻ�䣬ʹ����ɽ�ġ�" HIB "һ�������" NOR "��������$n��$l����֪������;��"
		   "ͻȻת�򣬴��$n\n"
		   "����֮��",
	"force" : 40,
	"attack": 75,
	"dodge" : 75,
	"parry" : 70,
	"damage": 40,
	"lvl" : 42,
	"damage_type" : "����"
]),
([      "action" : "$N����������һ�����ǡ�" CYN "������ɽ" NOR "��������$w����ն�䣬ֱ����$n��$l",
	"force" : 50,
	"attack": 72,
	"dodge" : 80,
	"parry" : 70,
	"damage": 50,
	"lvl" : 49,
	"damage_type" : "����"
]),
([      "action" : "$N����$wԽתԽ�죬ʹ�ľ�Ȼ�Ǻ�ɽ�ġ�" HIW "�ٱ�ǧ������ʮ��ʽ" NOR "������ʽ"
		   "�����ƾ���ӿ���Թ�\n"
		   "�߲��ɵ�ĿΪ֮ѣ",
	"force" : 60,
	"attack": 71,
	"dodge" : 80,
	"parry" : 70,
	"damage": 60,
	"lvl" : 56,
	"damage_type" : "����"
]),
([      "action" : "$N��Ц����������ׯ�ϣ�$w��ӣ����ڡ�" HIR "��Ħ��" NOR "��Ϊһʽ������ش���$n",
	"force" : 70,
	"attack": 80,
	"dodge" : 90,
	"parry" : 65,
	"damage": 70,
	"lvl" : 63,
	"damage_type" : "����"
]),
([      "action" : "$N����$w��ʹ��" CYN "̫����" NOR "�����⣬�������СС������ԲȦ�������޾�Դ"
		   "Դ�����ز���$n",
	"force" : 80,
	"attack": 77,
	"dodge" : 90,
	"parry" : 70,
	"damage": 80,
	"lvl" : 70,
	"damage_type" : "����"
]),
([      "action" : "$N�������أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n����" HIR "��Ħ��" NOR
		   "���Ľ����¶����",
	"force" : 90,
	"attack": 70,
	"dodge" : 75,
	"parry" : 70,
	"damage": 90,
	"lvl" : 77,
	"damage_type" : "����"
]),
([      "action" : "ȴ��$NͻȻ�鲽������ʹ�������䵱��" HIG "���ѵ�ˮ" NOR "����һ��",
	"force" : 110,
	"attack": 75,
	"dodge" : 90,
	"parry" : 75,
	"damage": 100,
	"lvl" : 84,
	"damage_type" : "����"
]),
([      "action" : "$N�˽���磬��������з���$n��$l�����Ա�$n���أ��������ǡ�" HIR "��ħ��" NOR
		   "���ġ�" HIR "����ʽ" NOR "��",
	"force" : 120,
	"attack": 80,
	"dodge" : 90,
	"parry" : 85,
	"damage": 110,
	"lvl" : 91,
	"damage_type" : "����"
]),
([      "action" : "$NͻȻ�˽����һ�ֹ���ġ�" HIY "�����罣��" NOR "������Ȼ��$n�����Ҵ�����",
	"force" : 150,
	"attack": 90,
	"dodge" : 70,
	"parry" : 95,
	"damage": 120,
	"lvl" : 98,
	"damage_type" : "����"
]),
([      "action" : "$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N��������ʵ",
	"force" : 180,
	"attack": 100,
	"dodge" : 70,
	"parry" : 105,
	"damage": 130,
	"lvl" : 105,
	"damage_type" : "����"
]),
([      "action" : "$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����ʲô����",
	"force" : 210,
	"attack": 110,
	"dodge" : 75,
	"parry" : 95,
	"damage": 140,
	"lvl" : 112,
	"damage_type" : "����"
]),
([      "action" : "$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��֪����Ǻ�",
	"force" : 230,
	"attack": 115,
	"dodge" : 90,
	"parry" : 95,
	"damage": 150,
	"lvl" : 119,
	"damage_type" : "����"
]),
([      "action" : "$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ��������ȵ�$n���ò���",
	"force" : 250,
	"attack": 120,
	"dodge" : 95,
	"parry" : 95,
	"damage": 160,
	"lvl" : 126,
	"damage_type" : "����"
]),
([      "action" : "$N���ֺὣ����$n��$l���������������е�һ����������Ȼ���$n���Կ��彣������",
	"force" : 270,
	"attack": 125,
	"dodge" : 85,
	"parry" : 95,
	"damage": 170,
	"lvl" : 133,
	"damage_type" : "����"
]),
([      "action" : "$N�ٽ���ӣ�Ѹ���ޱȵص���$n��$l��ȴ���˿�������������ʲô��ʽ",
	"force" : 300,
	"attack": 130,
	"dodge" : 115,
	"parry" : 80,
	"damage": 180,
	"lvl" : 140,
	"damage_type" : "����"
]),
([      "action" : "$N����һ��ָ��$n���������$n���������ڣ��˵����������ף�����˼��",
	"force" : 330,
	"attack": 140,
	"dodge" : 95,
	"parry" : 100,
	"damage": 190,
	"lvl" : 147,
	"damage_type" : "����"
]),
([      "action" : "$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������$n��$l",
	"force" : 350,
	"attack": 150,
	"dodge" : 110,
	"parry" : 100,
	"damage": 200,
	"lvl" : 154,
	"damage_type" : "����"
]),
([
	"action" : "$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮����ʵ�����Ѳ�",
	"force" : 380,
	"attack": 155,
	"dodge" : 115,
	"parry" : 105,
	"damage": 230,
	"lvl" : 180,
	"damage_type" : "����"
])
});

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
      int level;
	level = (int) me->query_skill("lonely-sword", 1);

	if( level > 350 )
		return ([
			"action": HIC+replace_string(replace_string(feiyue_msg[random(sizeof(feiyue_msg))], "$w", "$w"), "$w", "$w"HIC)+NOR,
			"dodge": 200+random(50),
			"parry": 200+random(50),
			"force": 200 + random(100),
	            "attack": 300,
			"damage": 100 + random(20),
			"damage_type": "����",
		]);


	return action[random(sizeof(action))];
}

int valid_learn(object me)
{
	object ob;

	if( !(ob = me->query_temp("weapon"))
	||   (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ�ѽ�������������\n");

	if (me->query("int") < 34)
		return notify_fail("������ʲ��㣬�޷������¾Ž��Ľ��⡣\n");

	if (me->query("character") == "�ĺ�����")
		return notify_fail("��һ����ɱ�����ˣ�û�������¾Ž��ĵ��������塣\n");

	if (me->query("character") == "���ռ�թ")
		return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û�������¾Ž���\n");

	if (me->query("character") == "��������")
		return notify_fail("�����а�����ʲô���¾Ž������߰���ģ�û�а�����ơ�\n");

	if (me->query_skill("sword", 1) < me->query_skill("lonely-sword", 1))
		return notify_fail("��Ļ��������������ޣ��޷���������Ķ��¾Ž���\n");

	return 1;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;
	int i;

	lvl = me->query_skill("sword-cognize", 1);
	i = random(lvl);

	if (me->query("family/family_name") == "��ɽ����" &&
	    i > 50 && random(2) == 0)
	{
		if (i < 120)
		{
			victim->receive_wound("qi", damage_bonus / 6);
			return HIR "ֻ��$N" HIR "������Ȼ����$n" HIR "����֪$N" HIR
			       "�ھ����£�����ֱ��$n" HIR "���ڣ�"NOR"\n";
		}
		if (i < 240)
		{
			victim->receive_wound("qi", damage_bonus / 4);
			return HIG "����$N" HIG "΢΢һЦ��ȫ�������ڽ��У���"
			       "��ԴԴ��������$n" HIG "��"NOR"\n";
		} else
		{
			victim->receive_wound("qi", damage_bonus / 2);
			return HIM "$N" HIM "Ĭ���ڹ���ͻȻ̧ͷ����һ�У�$n" HIM
			       "��ʱ�����Ĵ������ݺᣬ���޿ɱܣ�"NOR"\n";
		}
	}
}

/*
int practice_skill(object me)
{
	return notify_fail("���¾Ž�ֻ��ͨ�����ܾ�ʽ����������\n");
}
*/

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) || 
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 400)
		return notify_fail("����������������¾Ž���\n");

	if ((int)me->query("neili") < 400)
		return notify_fail("����������������¾Ž���\n");

	//message_vision(HIG "$N"HIG"ʹ�����¾Ž�֮���ܾ�ʽ����������" +weapon->name()+ HIG "���������̡�"NOR"\n",me);
	tell_object(me, HIG "��ʹ�����¾Ž�֮���ܾ�ʽ����������" + weapon->name() + HIG "���������̡�"NOR"\n");
	me->receive_damage("qi", 300);
	me->add("neili", -300);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"lonely-sword/" + action;
}

int difficult_level()
{
	return 400;
}
