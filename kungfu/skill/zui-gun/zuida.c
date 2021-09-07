// zuida.c ������� �������

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

string query_name() { return "����"ZJBR"���"; }

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int count, count1, cnt, skill;
	
	if (! me->is_fighting())
		return notify_fail("���������ֻ����ս����ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_temp("zg_zuida"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ������ڹ������ˣ�û�и��������ʹ�ð������\n");

	if ((int)me->query_str() < 25)
		return notify_fail("�����ڵı���������Ŀǰ����ʹ�ô˾�����\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

	if ((int)me->query_skill("club") < 100)
		return notify_fail("��Ĺ�����Ϊ����������ʹ�ô��������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("����������㣡\n");

	msg = HIY "$N" HIY "ʹ����������ľ�����������򡹣���"
	      "����Ȼ����, ����Ȼ�ӿ죡"NOR"\n";
	
   	message_combatd(msg, me, target);
	skill = me->query_skill("zui-gun",1);
	cnt =(int)( (int)me->query_condition("drunk") / 3);
	count = me->query("str") * random(cnt + 2);
	count1 = me->query("dex") * random(cnt + 2);

	me->add_temp("str", count);
	me->add_temp("dex", count1);
	me->set_temp("zg_zuida", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",
			   me, count, count1 :), skill / 3);

	me->add("neili", -150);
   	return 1;
}

void remove_effect(object me, int amount, int amount1)
{
	if ((int)me->query_temp("zg_zuida"))
	{
		me->add_temp("str", -amount);
		me->add_temp("dex", -amount1);
		me->delete_temp("zg_zuida");
		tell_object(me, "��İ�������˹���ϣ��������ջص��\n");
	}
}
