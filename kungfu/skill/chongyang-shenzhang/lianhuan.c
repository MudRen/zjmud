// lianhuan.c ����

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "������"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	mapping p;
	int i;
	int af;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("ʩչ�������ơ�������֣�\n");

	if (! mapp(p = me->query_skill_prepare()) ||
	    p["strike"] != "chongyang-shenzhang")
		return notify_fail("�����׼����ʹ���������ƹ�������ʩչ�������ơ���\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("chongyang-shenzhang", 1) < 100)
		return notify_fail("����������ƻ������ң��޷�ʹ�á������ơ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "���һ����˫�������ĳ�������$n" HIY "��"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -80);
	af = member_array("strike", keys(p));

	for (i = 0; i < 4; i++)
	{
		if (! me->is_fighting(target))
			break;

		me->set_temp("action_flag", af);		
		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->start_busy(1 + random(4));
	return 1;
}
