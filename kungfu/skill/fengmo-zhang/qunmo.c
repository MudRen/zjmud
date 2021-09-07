#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "Ⱥħ"ZJBR"����"; }
string *pfm_type() { return ({ "staff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int lvl;
	int i;
 
	if (userp(me) && ! me->query("can_perform/fengmo-zhang/qunmo"))
		return notify_fail("�㻹����ʹ�á�Ⱥħ���衹��һ�С�\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ⱥħ���衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʩչ��Ⱥħ���衹��\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ��Ⱥħ���衹��\n");

	if ((lvl = (int)me->query_skill("fengmo-zhang", 1)) < 120)
		return notify_fail("��ķ�ħ�ȷ��������ң��޷�ʹ�á�Ⱥħ���衹��\n");

	if (me->query_skill_mapped("staff") != "fengmo-zhang")
		return notify_fail("��û�м�����ħ�ȷ����޷�ʹ�á�Ⱥħ���衹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "ֻ��$N" HIR "����ɱ����ʢ������һ����������ǰ��"
		  "���緢��һ�㣬���е�" + weapon->name() +
	      HIR "����������Ӱ��һ�����$n" HIR "��"NOR"\n";

	if (lvl / 2 + random(lvl) > target->query_skill("parry") * 2 / 3)
	{
		msg += HIY "$n" HIY "��$N" HIY "������ƣ�����������"
		       "ս��һʱ��֪Ӧ����εֵ���Ψ���������ˡ�"NOR"\n";
		count = lvl / 6;
		me->add_temp("apply/attack", count);
	} else
		count = 0;

	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 3; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(2) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}

