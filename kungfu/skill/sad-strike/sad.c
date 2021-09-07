// sad.c ��Ȼ����

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "��Ȼ"ZJBR"����"; }
string *pfm_type() { return ({ "unarmed", }); }

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
		return notify_fail("����Ȼ���꡹ֻ����ս���жԶ���ʹ�á�\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����Ȼ���꡹ֻ�ܿ���ʹ�á�\n");
		
	if (me->query("static/marry") > 1)
		return notify_fail("��������Ѳ��������ﻹ�����Ե�������Ȼ����ĸо���\n");

	if (! me->query("couple/id"))
		return notify_fail("�����Ŷ�û�У�����Ȼʲô��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("sad-strike", 1) < 180)
		return notify_fail("�����Ȼ�����Ʋ���180�����޷�ʩչ����Ȼ���꡹��\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���Ч�ȼ�����300�����޷�ʩչ����Ȼ���꡹��\n");

	if (sizeof(me->query_skill_prepare()) &&
	    me->query_skill_prepared("unarmed") != "sad-strike")
		return notify_fail("������û��׼��ʹ����Ȼ�����ƣ��޷�ʩչ����Ȼ���꡹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIM "$N" HIM "һ����̾������ֹˮ����Ȼ���ˣ��ڲ���������"
	      "��ʹ����" HIR "����Ȼ���꡻" HIM "��"NOR"\n";

	ap = me->query_skill("unarmed") + me->query("con") * 10;
	dp = target->query_skill("parry") + target->query("dex") * 10;
	if (ap / 2 + random(ap) > dp)
	{
		count = ap / 12;
		msg += HIY "$n" HIY "��$P" HIY "��һ�б仯Ī�⣬�����"
		       "�������ɴ��һ��������������������"NOR"\n";
	} else
	{
		msg += HIC "$n" HIC "����С��$P" HIC
		       "�����У���Ų������С���мܡ�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add_temp("apply/attack", count);

	me->add("neili", -200);
	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 0 && ! target->is_busy())
			target->start_busy(1);

		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->start_busy(1 + random(6));
	me->add_temp("apply/attack", -count);

	return 1;
}

