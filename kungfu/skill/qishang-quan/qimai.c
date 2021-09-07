// qimai.c ��������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int count;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���������ˡ�ֻ����ս���жԶ���ʹ�á�\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������ˡ�ֻ�ܿ���ʹ�á�\n");
		
	if (me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ���������޷�ʩչ���������ˡ���\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query("qi") < 800)
		return notify_fail("����������ڲ�����\n");

	if ((int)me->query_skill("qishang-quan", 1) < 150)
		return notify_fail("�������ȭ��򲻹����޷�ʹ�á��������ˡ���\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���Ϊ�������޷�ʹ�á��������ˡ���\n");

	if (me->query_skill_prepared("cuff") != "qishang-quan")
		return notify_fail("������û��׼��ʹ������ȭ���޷�ʹ�á��������ˡ���\n");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�������������������ľ��Ƹ���ʫ�����ˣ�"
	      "�ܾ���ɲ�Ǽ䣬����һ����������ȭ��"NOR"\n";
	ap = me->query_skill("cuff") + me->query("con") * 10;
	dp = target->query_skill("force") + target->query("con") * 6;
	if (ap / 2 + random(ap) > dp)
	{
		count = ap / 9;
		msg += HIR "$n" HIR "���$P" HIR "���Ѹ����ȭ������ȫ"
		       "û�ж�������أ����飬�飬�顱�ؿ�Ӳ������ȭ��"NOR"\n";
	} else
	{
		msg += HIC "$n" HIC "������ȫ�������⼸������$P" HIC
		       "�Ĺ��ơ�"NOR"\n";
		count = 0;
	}

	message_vision(msg, me, target);
	me->add_temp("apply/attack", count);

	me->add("neili", -300);
	me->add("qi", -100);   
			       
	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(5) < 2 && ! target->is_busy())
			target->start_busy(1);

		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->start_busy(1 + random(5));
	me->add_temp("apply/attack", -count);

	return 1;
}
