// sanshen.c ���������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����������塹ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ��������㣡\n");

	if ((int)me->query_skill("blade") < 50 ||
	    me->query_skill_mapped("blade") != "fanliangyi-dao")
		return notify_fail("��ġ������ǵ������������ң��޷�ʹ�á���������塹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ����ɽ�ɾ�������������塹����"
	      "��ͻȻ����쳣�鶯Ʈ����"NOR"\n";
	message_combatd(msg, me);

	for (i = 0; i < 3; i++)
	{
		if (! me->is_fighting(target))
			break;

		COMBAT_D->do_attack(me, target, weapon);
	}

	me->add("neili", -100);
	me->start_busy(1 + random(3));

	return 1;
}
