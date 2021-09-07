// taixuan.c ̫����

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "̫����"; }
string *pfm_type() { return ({ "unarmed", }); }

int query_cd() { return 5; }

int perform(object me, object target)
{
	string msg;
	int count;
	int lvl;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��̫������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("ʩչ��̫������������֣�\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������޷�ʩչ��̫��������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ��̫��������\n");

	if ((lvl = (int)me->query_skill("taixuan-gong", 1)) < 120)
		return notify_fail("���̫���񹦻������ң��޷�ʹ��̫������\n");

	if (me->query_skill_mapped("unarmed") != "taixuan-gong")
		return notify_fail("��û�м���̫����, ����ʹ�á�̫��������\n");

	if (sizeof(me->query_skill_prepare()) &&
	    me->query_skill_prepared("unarmed") != "taixuan-gong")
		return notify_fail("������û��׼��ʹ��̫�������޷�ʩչ��̫��������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "һ�����ȣ���������ǰ����˫������ʵʵ�Ĺ���$n" HIY "��"NOR"\n";

	if ( random(lvl) > target->query_skill("dodge",1) / 4)
	{
		msg += HIR "$n" HIR "����$N" HIR "����������������"
		       "��һ����һʱ���벻�ø���ζ�����"NOR"\n";
		count = lvl;
		target->add_temp("apply/parry", -count);
		target->add_temp("apply/dodge", -count);
		target->set_temp("taixuaned", 1);
	}

 
	message_combatd(msg, me, target);
	me->add("neili", -120);

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;

		if (random(3) == 1 && ! target->is_busy())
			target->start_busy(1);

		COMBAT_D->do_attack(me, target, 0, 0);
	}


	//me->add_temp("apply/unarmed_damage", -lvl/3); 

      if (target->query_temp("taixuaned")) {
	target->add_temp("apply/parry", count);
	target->add_temp("apply/dodge", count);
      target->delete("taixuaned");
      }

	me->start_busy(1);
	return 1;
}
