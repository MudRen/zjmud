// huimou.c ��������
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "hand", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
  
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("shenlong-bashi", 1) < 150)
		return notify_fail("���������ʽ�ַ���������죬����ʹ�ù���������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʹ�ù���������\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�ù���������\n");

	if (me->query_skill_mapped("hand") != "shenlong-bashi")
		return notify_fail("��û�м���������ʽ�ַ�������ʹ�ù���������\n");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "����΢����������Ť�����㷴����$nС��"
	      HIG "ȥ��$n������ܣ�$N˳�Ʒ�������������§ס$n��ͷ"
	      HIG "�������ֶ�׼��$n�Ĵ����͵�һ�С�"NOR"\n";
	      
	me->start_busy(2 + random(2));

	if (random(me->query_skill("hand")) > target->query_skill("parry") / 2)
	{
		damage = (int)me->query_skill("force");
		damage = damage * 3 / 4 + random(damage);
		me->add("neili", -180);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
					   HIR "$p" HIR "��æ����ȥ����ȴû�ܵ�ס$P" 
					   HIR "�������������$P" HIR "���صĻ��У�"
					   "�۵�����һ����Ѫ��"NOR"\n");
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ��˦ͷ�ܿ���$P"
		       CYN "�Ľ�����"NOR"\n";
		me->add("neili", -70);
	}
	message_combatd(msg, me, target);

	return 1;
}
