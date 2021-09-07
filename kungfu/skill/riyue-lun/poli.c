// poli.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�ƶ�"ZJBR"����"; }
string *pfm_type() { return ({ "hammer", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/riyue-lun/poli"))
		return notify_fail("�㻹�������á���������һ������\n");

	if (! target ) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "hammer")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("riyue-lun", 1) < 120)
		return notify_fail("��������ַ���������죬����ʹ�á���������\n");

	if ((string)me->query_skill_mapped("force") != "longxiang")
		return notify_fail("����뼤���������������ʩչ������������\n");
	
	if ((int)me->query_skill("force") < 180)
		return notify_fail("����ڹ���������޷�ʩչ����������\n");

	if (me->query("neili") < 400)
		return notify_fail("��������������޷�ʩչ����������\n");

	if (me->query_skill_mapped("hammer") != "riyue-lun")
		return notify_fail("��û�м��������ַ����޷�ʩչ����������\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�־�" + weapon->name() + HIY "��������$n" +
	      HIY "���£����˵���ȫȻ��$n" HIY "�������У�\n";

	ap = me->query_skill("force") + me->query_str() * 10;
	dp = target->query_skill("force") + target->query_str() * 10;

	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -300);
		damage = ap / 2 + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIR "$n" HIR "��$N" HIR "��ǿ���ޱȵ��ھ����"
					   "����ҡ�һţ��������У�������Ѫ��"NOR"\n");
		me->start_busy(2);

	} else
	{
		msg += HIC "ȴ��$p" HIC "�벻���⣬����һ���Ͷ����$P"
		       HIC "���׺�������"NOR"\n";
		me->add("neili", -150);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
