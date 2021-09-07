// jinguan-yusuo ���������ʮ�ľ�

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
	"ȴ��$n˫����ת����ס������ʱ��$N������ȫȫ������\n",
	"����$n���μ��䣬�ھ��ŷ�����$N�Ĺ������������\n",
	"����$n����΢�࣬˫��ͬʱһ�����ѽ�$N������ж�����Ρ�\n",
});

string query_parry_msg(object weapon)
{
	return parry_msg[random(sizeof(parry_msg))];
}

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("taoism", 1) < 200)
		return notify_fail("��Ե�ѧ����ⲻ�����룬�޷�ѧϰ���������ʮ�ľ���\n");

	if ((int)me->query_skill("xiantian-gong", 1) < 180)
		return notify_fail("������칦��򲻹����޷�ѧϰ���������ʮ�ľ���\n");

	if ((int)me->query_skill("force", 1) < 180)
		return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ���������ʮ�ľ���\n");

	if ((int)me->query_skill("parry", 1) < 180)
		return notify_fail("��Ļ����мܻ�򲻹����޷�ѧϰ���������ʮ�ľ���\n");

	if ((int)me->query("max_neili") < 3000)
		return notify_fail("���������Ϊ���㣬�޷�ѧϰ���������ʮ�ľ���\n");

	if ((int)me->query_skill("taoism", 1) < (int)me->query_skill("jinguan-yusuo", 1) + 10)
		return notify_fail("��Ե�ѧ�ķ���������ޣ��޷���������Ľ��������ʮ�ľ���\n");

	if ((int)me->query_skill("xiantian-gong", 1) < (int)me->query_skill("jinguan-yusuo", 1))
		return notify_fail("������칦ˮƽ���ޣ��޷���������Ľ��������ʮ�ľ���\n");

	if ((int)me->query_skill("force", 1) < (int)me->query_skill("jinguan-yusuo", 1))
		return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷���������Ľ��������ʮ�ľ���\n");

	if ((int)me->query_skill("parry", 1) < (int)me->query_skill("jinguan-yusuo", 1))
		return notify_fail("��Ļ����м�ˮƽ���ޣ��޷���������Ľ��������ʮ�ľ���\n");

	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;

	if ((int) me->query_skill("jinguan-yusuo", 1) < 100 ||
	    ! living(me))
		return;

	mp = ob->query_skill("count", 1);
	ap = ob->query_skill("force", 1) + mp;
	dp = me->query_skill("jinguan-yusuo", 1);

	// ��Ϊ���ڿ�����ϰ�����Ա�֤����ж�еļ��ʵ�
	if (ap / 2 + random(ap) < dp * 2 / 3)
	{
		result = ([ "damage" : -damage ]);

		switch (random(3))
		{
		case 0:
			result += ([ "msg" : YEL "$n" YEL "�溬΢Ц��˫�ֻ�"
					     "Ȧ����ʱ��$N" YEL "������ȫȫ"
					     "������"NOR"\n" ]);
			break;
		case 1:
			result += ([ "msg" : YEL "$n" YEL "��������������"
					     "�����£���ƾ�ռ���һ����ǽ����$N"
					     YEL "�Ĺ���ȫȻ������⡣"NOR"\n" ]);
			break;

		default:
			result += ([ "msg" : YEL "ȴ��$n" YEL "�Ƴ���磬Ʈ"
					     "�����������赭д��$N" YEL "��"
					     "����ж֮�����Ρ�"NOR"\n" ]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(3))
		{
		case 0:
			result = HIY "$n" HIY "˫�ֻ�Ȧ����ͼ����$N" HIY "��"
				 "�������ɶ�Ȼ��ȴ��$N" HIY "���ֻ�ת���ٹ���"
				 "һ�С�"NOR"\n";
			break;

		case 1:
			result = HIY "$n" HIY "�����������������ھ��赲$N"
				 HIY "�Ĺ��ƣ���$N" HIY "��ı��У�����һ��"
				 "λ���롣"NOR"\n";
			break;

		default:
			result = HIY "$n" HIY "�Ƴ���磬ƮȻ��סȫ����$N"
				 HIY "��Ҳ����ֻ�������ھ������ƹ��롣"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

int practice_skill(object me)
{
	if (me->query_skill("jinguan-yusuo", 1) < 200)
		return notify_fail("��Խ��������ʮ�ľ����˽���ǳ�������������ж�����\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("����������������������ʮ�ľ���\n");

	me->receive_damage("qi", 50);
	me->add("neili", -85);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jinguan-yusuo/" + action;
}

