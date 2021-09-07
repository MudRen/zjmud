// douzhuan-xingyi ��ת����

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
	"ֻ�������ϡ�һ����$n�ñ�������һ�ܣ��ı���$N��һ���ķ���\n",
	"���Ǳ�$n�����б���������\n",
	"����$n����һ�࣬����ת�����еı��У���$N�о���������ʩ��\n",
});

string *unarmed_parry_msg = ({
	"���Ǳ�$p˫��һ�ƣ�$N�Ĺ��ƶ�ʱ���˷���\n",
	"$n����һת��$Nֻ���õ����е�����ȫ���������Լ���\n",
	"����$N�о�����޻���һ����˵�����Ĺ��졣\n",
});

string query_parry_msg(object weapon)
{
	if( weapon )
		return parry_msg[random(sizeof(parry_msg))];
	else
		return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
	//if ((int)me->query_skill("zihui-xinfa", 1) < 50)
	//	return notify_fail("����ϻ��ķ���򻹲���������ѧϰ��ת���ơ�\n");

	if ((int)me->query_skill("parry", 1) < 100)
		return notify_fail("��Ļ����мܼ������յĻ������������޷�ѧϰ��ת���ơ�\n");

	if ((int)me->query_skill("parry", 1) < (int)me->query_skill("douzhuan-xingyi", 1)) 
		return notify_fail("��Ļ����м�ˮƽ���ޣ��޷�ѧϰ������Ķ�ת���ơ�\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("��ת����ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;

	if ((int) me->query_skill("douzhuan-xingyi", 1) < 100 ||
	    ! living(me))
		return;

	mp = ob->query_skill("count", 1) + ob->query_skill("never-defeated", 1)/3;
	ap = ob->query_skill("force", 1) + mp;
	dp = me->query_skill("douzhuan-xingyi", 1);

	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage" : -damage ]);

		switch (random(3))
		{
		case 0:
			result += ([ "msg" : HIC "$n" HIC "ʹ������Ľ�ݵĶ��ž�������ת���ơ�����$N"
						HIC "�ľ�������������ȥ��"NOR"\n"+
						COMBAT_D->do_respond(me, ob, damage, 50, HIR "$Pֻ��һ�ɰ�����ӿ���������ɼ��Ļ����Լ���"NOR"\n")]);
			break;
		case 1:
			result += ([ "msg" : HIC "$n" HIC "ʹ������Ľ�ݵĶ��ž�������ת���ơ�����$N"
						HIC "�ľ�������������ȥ��"NOR"\n"+
						COMBAT_D->do_respond(me, ob, damage, 50, HIR "$Pֻ��һ�ɰ�����ӿ���������ɼ��Ļ����Լ���"NOR"\n")]);
			break;

		default:
			result += ([ "msg" : HIC "$N" HIC "һ���ۿ�������$n" HIC "��Ȼ��$n" HIC "����һ�ӣ�"
					     "��$N" HIC "�Ĺ���Ϥ��������ȥ��"NOR"\n"+
						COMBAT_D->do_respond(me, ob, damage, 50, HIR "$Pֻ��һ�ɰ���������������ʱһ����Ѫ��ӿ��"NOR"\n")]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(3))
		{
		case 0:
			result = HIY "$n" HIY "���κ�Ȼת����ͣ��Ȼ��$N"
				 HIY "���ѿ������а��˿������Ӱ�죬����ֱ�롣"NOR"\n";
			break;

		case 1:
			result = HIY "$n" HIY "����һ�У�$N"
				 HIY "��������׼��������Ȼ���ѣ���ʱ�仯��ʽ��"NOR"\n";
			break;

		default:
			result = HIY "$n" HIY "����һж��������$N"
				 HIY "��Ȼ��������������ǧ��ı仯��������Ų����$n"
				 HIY "�������̾ʹ���ա�"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

string perform_action_file(string action)
{
	return __DIR__"douzhuan-xingyi/" + action;
}

int diffcult_level() { return 300; }

