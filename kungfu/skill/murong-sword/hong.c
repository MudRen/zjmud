// hong.c �׺����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "�׺�"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���׺���ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ʩչ���׺���ա����б�������һ�ѽ���\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("��������������޷�ʩչ���׺���ա���\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���򲻹����޷�ʩչ���׺���ա���\n");

	if ((int)me->query_skill("murong-sword", 1) < 180)
		return notify_fail("���Ľ�ݽ����������ң��޷�ʹ�þ������׺���ա���\n");

	if (me->query_skill_mapped("sword") != "murong-sword")
		return notify_fail("��û�м���Ľ�ݽ������޷�ʹ�á��׺���ա���\n");

	msg = HIW "$N" HIW "����һת��ת�ۼ�Ծ����У��漴ѩ���Ľ���һ��һɨ������"
	      "���󣬼��پ���$n" HIW "��"NOR"\n";
	ap = me->query_skill("sword");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -250);
		me->start_busy(3);
		damage = ap + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 59,
					   HIR "$n" HIR "���μ��ˣ�Ȼ��$N" HIR "�˽�����"
					   "Ѹ���ޱȣ���������ңң��������ʱ��$n"
					   HIR "���ϴ̴���һ������Ĵ��ڡ�"NOR"\n");
	} else
	{
		me->add("neili", -100);
		me->start_busy(2);
		msg += WHT "$n" WHT "�������Ƶ����ͣ����������мܣ�����"
		       "���������ٵ���˫��һ̤һ��һԾ������Ӷ��ˡ�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
