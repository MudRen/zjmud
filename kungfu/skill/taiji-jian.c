// taiji-jian.c ̫����
// cleansword 2/15/96
// Marz 5/21/96
// Updated by Doing

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N�鲽������һ�С����ѵ�ˮ��������$w���������һ��������$n��$l",
	"force" : 25,
	"dodge" : 20,
	"parry" : 25,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action": "$N��ǰ����һ�������ֽ���������$wʹ��һʽ��ָ���롹ֱ��$n��$l",
	"force" : 30,
	"dodge" : 25,
	"parry" : 30,
	"lvl"   : 6,
	"damage_type" : "����"
]),
([      "action": "$N��������һ�죬���ֽ���������$wʹ��һʽ������ǡ�����$n��$l",
	"force" : 30,
	"dodge" : 35,
	"parry" : 35,
	"lvl"   : 12,
	"damage_type" : "����"
]),
([      "action": "$N˫ϥ�³�������$wʹ��һʽ��̽��ʽ�������¶��ϼ���$n��$l",
	"force" : 35,
	"dodge" : 35,
	"parry" : 40,
	"lvl"   : 15,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С������Ӳ�����$w���϶��»���һ���󻡣�ƽƽ����$n��$l��ȥ",
	"force" : 35,
	"dodge" : 45,
	"parry" : 45,
	"lvl"   : 18,
	"damage_type" : "����"
]),
([      "action": "$N���������һš��һ�С�������β��������$w������$n��$l��ȥ",
	"force" : 35,
	"dodge" : 45,
	"parry" : 55,
	"lvl"   : 21,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����ɨ����һ�С�����ɨ��������ƽָ��һ���ǳɺ�ɨ$n��$l",
	"force" : 40,
	"dodge" : 60,
	"parry" : 55,
	"lvl"   : 24,
	"damage_type" : "����"
]),
([      "action": "$N������ϥ������$wбָ��һ�С�����Ͷ�֡�����$n��$l",
	"force" : 40,
	"dodge" : 55,
	"parry" : 60,
	"lvl"   : 27,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�������ˮ����$w���¶��ϻ���һ���󻡣�ƽƽ�ػ���$n��$l",
	"force" : 45,
	"dodge" : 65,
	"parry" : 65,
	"lvl"   : 30,
	"damage_type" : "����"
]),
([      "action": "$Nʹ�����������¡���$w��������ԲȦ������ֱ�������಻�ϻ���$n��$l",
	"force" : 45,
	"dodge" : 70,
	"parry" : 70,
	"lvl"   : 35,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����Ҷ����$w����ػ�������Բ����Ѹ�ٵ���$n��$l��ȥ",
	"force" : 50,
	"dodge" : 75,
	"parry" : 80,
	"lvl"   : 40,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����ͷ����$w����һ������ҸߵĴ󻡣�бб��ն��$n��$l",
	"force" : 50,
	"dodge" : 75,
	"parry" : 80,
	"lvl"   : 45,
	"damage_type" : "����"
]),
([      "action": "$Nʹ����ʨ��ҡͷ����$w�������󻮳�һ�����֣���$nȦ������",
	"force" : 55,
	"dodge" : 85,
	"parry" : 80,
	"lvl"   : 50,
	"damage_type" : "����"
]),
([      "action": "$N���̤ʵ���ҽ���㣬һ�С�����ָ·��������$w����һ�Ž���������$n��$l",
	"force" : 55,
	"dodge" : 95,
	"parry" : 80,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([      "action": "$N����Ծ��һ�С�Ұ����������$w�ڰ���л�ΪһȦ��â������$n��$l",
	"force" : 60,
	"attack": 3,
	"dodge" : 95,
	"parry" : 90,
	"lvl"   : 80,
	"damage_type" : "����"
]),
([      "action": "$N����ǰ���󹭣�һ�С�����ʽ��������$wֱ��$n��$l",
	"force" : 65,
	"attack": 5,
	"dodge" : 100,
	"parry" : 100,
	"lvl"   : 100,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�С���ǡ�����������һ�죬���ֽ���������$wƽƽ����$n��$l��ȥ",
	"force" : 70,
	"attack": 7,
	"dodge" : 100,
	"parry" : 105,
	"damage": 1,
	"lvl"   : 110,
	"damage_type" : "����"
]),
([      "action": "$N������ϣ�һ�С���Գ�׹���������$wбб����$n��$l��ȥ",
	"force" : 75,
	"attack": 10,
	"dodge" : 110,
	"parry" : 120,
	"damage": 2,
	"lvl"   : 120,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�ӭ�絧������$w���������һ�ӣ�$nȴ����һ�ɾ���ӭ��Ϯ����",
	"force" : 80,
	"attack": 12,
	"dodge" : 105,
	"parry" : 115,
	"damage": 4,
	"lvl"   : 130,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�˳ˮ���ۡ���$w���϶��»���һ���󻡣�ƽƽ����$n��$l��ȥ��",
	"force" : 85,
	"attack": 15,
	"dodge" : 115,
	"parry" : 125,
	"damage": 5,
	"lvl"   : 140,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С����Ǹ��¡���$w����$n��$l",
	"force" : 90,
	"attack": 18,
	"dodge" : 135,
	"parry" : 125,
	"damage": 8,
	"lvl"   : 150,
	"damage_type" : "����"
]),
([      "action": "$NͻȻ�̶���������һ�С��������¡���$w���¶��ϵ���$n��$l��ȥ",
	"force" : 95,
	"attack": 20,
	"dodge" : 125,
	"parry" : 125,
	"damage": 12,
	"lvl"   : 160,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����ʽ����$w���¶������컮��һ���󻡣�ƽƽ����$n��$l��ȥ",
	"force" : 100,
	"attack": 22,
	"dodge" : 135,
	"parry" : 145,
	"damage": 17,
	"lvl"   : 170,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С��Ʒ��붴����$w���϶��»���һ���󻡣�ƽƽ����$n��$l��ȥ",
	"force" : 105,
	"attack": 25,
	"dodge" : 140,
	"parry" : 165,
	"damage": 20,
	"lvl"   : 180,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�����չ�᡹������Ծ������$w����$n��$l",
	"force" : 110,
	"attack": 28,
	"dodge" : 145,
	"parry" : 155,
	"damage": 22,
	"lvl"   : 190,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С����ֽ�����$w����һƬ���̣�ƽƽ����$n��$l��ȥ",
	"force" : 115,
	"attack": 28,
	"dodge" : 155,
	"parry" : 175,
	"damage": 25,
	"lvl"   : 200,
	"damage_type" : "����"
]),
([      "action": "$N��������棬������ǰһ�ˣ�һ�С������пա���$w��$n��$l��ȥ",
	"force" : 120,
	"attack": 29,
	"dodge" : 165,
	"parry" : 180,
	"damage": 31,
	"lvl"   : 210,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С���ɨ÷����������Ծ�ڰ�գ�����$wɨ��$n��$l",
	"force" : 125,
	"attack": 32,
	"dodge" : 175,
	"parry" : 185,
	"damage": 33,
	"lvl"   : 220,
	"damage_type" : "����"
]),
([      "action": "$Nһ�С�ȴ���齣�������Ծ����أ�$w�س飬���ֹ���$n��$l",
	"force" : 130,
	"attack": 35,
	"dodge" : 185,
	"parry" : 200,
	"damage": 34,
	"lvl"   : 230,
	"damage_type" : "����"
]),
([      "action": "$N���Ȱ�����ף�һ�С�����Ʊա���������ָ��ת������$n��$l",
	"force" : 135,
	"attack": 38,
	"dodge" : 185,
	"parry" : 220,
	"damage": 37,
	"lvl"   : 240,
	"damage_type" : "����"
]),
([  "action" : "$N����š���������鱧��һ�С�����հ�ա���$w�й�ֱ��������$n��$l",
	"force" : 150,
	"attack": 40,
	"dodge" : 220,
	"parry" : 220,
	"damage": 40,
	"lvl" : 250,
	"damage_type" : "����"
]),
});

string *taiji_msg = ({
"$N����������һʽ���ֻ����ҡ������鸧�����ֳ������ֻ�������㽣������$n����ʵ����",
"$NĿ��Զ�����·ɣ���̾һ������������$w�������������������ƾ��Ƕϣ����������콣Ӱ",
"����$N�������¿��ϡ�����������ʵ�ѵ���̫�������ľ���",
"$N����$w��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ���",
"$N���������Ҫ֮���������˳�������ս��ǿ��$w�������ھ�������ǿ",
"̫�������������������̫��ȭ������ʵ�ǽ����Ƿ��켫�Ľ�����$N����һ���˿������಻������������",
"$N��������������ﳤ����������$n������$P$wһ��������һ�ƽ�������",
"$N����$n��ʽ������������֮�ơ���ׯ��֮�Σ��������ն���������������������˸����",
"$N�����ٻ������ǽ���������֮�٣�ʵ������",
"$N����$w������ǰ��������һ���Σ�һ��ɭɭ������ֱ����$n��ͻȻ֮�䣬$N�������֣�����һ����$n��$l��ȥ",
"$N����ͻ�䣬���������������Լ����������ʹ����������������������������⵴������������",
"$N����Ѹ�ݣ����ǽ���������֮�٣�ʵ������",
"$N$w����һ�д�����Լ�֮�ۣ�����֮�޷棬���������ᴫ�ڵ�̫���������⡹�ľ�������",
"$N��Ȼ�����У����ж�δ��ʹ�ϣ���ȻȦת�����������˳�һ�㣬����ӿ��$n",
"$N��ʽ����Ʈ��֮���������й��ӻ�񣬽��ϵ������ƺ�ֻ���ӵ�һ���ɣ������ȴ�������Դ�����ز�¶",
"�������������$N����$w���˳�ȥ����������ƽ�̣������������",
"$N˫��ע��$n������$w���������߰��ԣ��ν�һ���й�ͦ�������ƻ���������ʵ��������ϳ�̫��֮�������ܱٽ����",
"$N����û����ʽ��������ȫ�ǡ����ڽ��ȡ����಻����֮�⣬һ˿˿����$n",
"$N������Ȧ��һ�㺮�Ǵ���$n",
"����$N������$w������������ֻ��˸���Բ������$n",
"$N����һ�ӣ�$w��������б����������һ�������ƿ�������֤�������Ѵﷴ�ӹ���ľ���",
"$N$w�ڿ��л��ɴ�Ȧ�����ֽ�������������Ҳ��������΢��",
"$N����̤�ϣ��������֣�һ�С��������¡���һ������ʵʵ�������ֽ����У������Ϲ�â��˸�������͵ķ�����΢����",
"$N���ӻ�����ת�����ֳֽ������������𣬽��������ǰ������������ԣ�˫�۳ɻ�������$w�������Ȼ��������",
"$Nһ���̵�����������������������죬������ǿ",
"$N�������Ž���������$w��ס�Ķ���������$n�����ߴ�ҪѨ�����⼱��������������δ�",
"$N���ֽ���б����$w�����������Բ������������ֱ��$n$l",
"$N����һ���˿�������$w�������಻������������",
"$N����$wʹ����Ӧ�֣��켫���������о��棬�����鶯����ò��⣬ͻȻ���󷭽���ֱ��$n��$l�̵�",
"$N$w�ݳ���˳��$n��·���£��Լ�֮�ۣ�����֮�޷棬ʵ�ѵ���̫�������ľ���",
"$N����Ԧ����ǧ���򻯣������޾���ÿһ�ж�����ƽ����ʵ�������Դ�����ز�¶",
"$N��$w����һ����ԲȦ��ÿһ�о����Ի��δ̳����Ի����ջ�",
"$N����Ԧ�������ڽ��ȣ����಻�������п��������̣������࣬ʵ��ǧ���򻯣������޾�",
"$N������Х�������ݺ�仯������޷���$w����������ʹ֮����������������ɵ�",
"$N���о��ް�����ң������˽���$wÿ��һ�У����Ʒų�һ��ϸ˿��Ҫȥ��ס$n",
"$N�������У���˵����ȥȥֻ��һ�У�Ȼ����һ��ȴ����Ӧ������",
"$N�������¿��ϡ�������������̫���������Ҫ֮���������˳���������һ���˿������಻��",
"$N����$w������ǰ��������һ���Ρ�$nֻ��һ��ɭɭ������ֱ�ƹ���",
"$N������������������$w��ס������ͻȻƽ�̣����⼱��������������δ���$P��һ����������$n�����ߴ�ҪѨ",
"$N����δ��ʹ�ϣ���ȻȦת��ͻȻ֮�䣬$n��ǰ�����˼�����ɫ��Ȧ����ȦСȦ����ȦбȦ����˸����",
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 1500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("taiji-quan", 1) < 100)
		return notify_fail("���̫��ȭ���̫ǳ��\n");
	if ( me->query_skill("taiji-jian", 1) > me->query_skill("taiji-quan", 1)+30 )
		return notify_fail("ѧϰ̫��������̫��ȭΪ������\n");
	if ( me->query_skill("taiji-jian", 1) > me->query_skill("taiji-shengong", 1)+30 )
		return notify_fail("ѧϰ̫��������̫����Ϊ������\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ����������̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("taiji-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������̫��������\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	string str;
	level = (int) me->query_skill("taiji-jian", 1);

	if( me->query_temp("tjj/sanhuan") ) {
		switch(me->query_temp("tjj/sanhuan")){
			case 3: str = HIG"$N"HIG"ʹ�����������¡�����ʽһ�䣬���ָ����ѣ������н������������������һ��Բ����$w"HIG"��$n��������"NOR; break;
			case 2: str = HIG"Ȼ��$N"HIG"�ƽ�һ�����������У��������У�ͬ��һ�����Żӳ�����������������һ��ͣ�ٵĺۼ�"NOR; break;
			case 1: str = HIG"������ӣ�$N"HIG"���е�$w"HIG"��һ�λӳ�����$n$l���������������������������������ͬ�����ϵ�������֮��"NOR; break;
			default: str = HIG"$Nʹ�����������¡�����ʽһ�䣬���ָ����ѣ������н������������������һ��Բ����$w"HIG"��$n��������"NOR; break;
		}
		if( me->query_temp("tjj/sanhuan") > 0 )
			me->add_temp("tjj/sanhuan", -1);
		return ([
			"action":str,
			"dodge": random(30),
			"parry": random(30),
			"force": 350 + random(250),
			"damage": 140 + random(130),
			"damage_type": "����",
		]);
	}

	if( level > 350 )
		return ([
			"action": WHT+replace_string(replace_string(taiji_msg[random(sizeof(taiji_msg))], "$w", "$w"), "$w", "$w"WHT)+NOR,
			"dodge": random(30),
			"parry": random(30),
			"force": 350 + random(250),
			"damage": 140 + random(130),
			"damage_type": "����",
		]);

	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];

}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;
	object m_weapon;

	if ((int) me->query_skill("taiji-jian", 1) < 100 ||
	    ! (m_weapon = me->query_temp("weapon")) ||
          m_weapon->query("skill_type") != "sword"||
	    ! living(me) )
		return;

	mp = ob->query_skill("count", 1);
	ap = ob->query_skill("force") + mp;
	dp = me->query_skill("parry", 1) / 2 +
	     me->query_skill("taiji-jian", 1);

	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(3))
		{
		case 0:
			result += (["msg" : HIC "$n" HIC "һ�����е�" + m_weapon->name() +
					    HIC "��������һ��ԲȦ����Ȼ��$N" +
					    HIC "�Ĺ���ȫȻ��ա�"NOR"\n"]);
			break;

		case 1:
			result += (["msg" : HIC "$n" HIC "����" + m_weapon->name() +
					    HIC "��������ָ��$N" HIC "�����е�������"NOR"\n"]);
			break;

		default:
			result += (["msg" : HIC "$n" HIC "�ζ����е�" + m_weapon->name() +
					    HIC "����ס�ı�ý��ƣ���$N"
					    HIC "��ȫ�޷���׽��������"NOR"\n"]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(2))
		{
		case 0:
			result = HIY "$n" HIY "һ�����е�" + m_weapon->name() +
				 HIY "��������һ��ԲȦ��$N"
				 HIY "��Ҳ������������ֱ�룬��Ϯ$n"
				 HIY "��"NOR"\n";
			break;

		case 1:
			result = HIY "$n" HIY "����" + m_weapon->name() + "������"
				 HIY "��ָ��$N" HIY "�����е�����������$N"
				 HIY "����һ�䣬�������̲���Ϊ������"NOR"\n";
			break;

		default:
			result = HIY "$n" HIY "�ζ����е�" + m_weapon->name() +
				 HIY "����ס�ı�ý��ƣ�Ȼ��$N"
				 HIY "������񣬾���������˿������$n"
				 HIY "���Ի�\n"  NOR;
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 100)
		return notify_fail("�������������̫��������\n");

	if ((int)me->query("neili") < 120)
		return notify_fail("�������������̫��������\n");

	me->receive_damage("qi", 50);
	me->add("neili", -100);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"taiji-jian/" + action;
}
