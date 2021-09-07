#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (playerp(me) && ! me->query("can_perform/chanhun-suo/duo"))
		return notify_fail("�㻹����ʹ�ö�ꡣ\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹���ʹ���˾�����ꡣ\n");

	if (me->query_skill("chanhun-suo", 1) < 80)
		return notify_fail("��Ĳ���������̫ǳ��ʹ���˾�����ꡣ\n");

	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʹ�ö�ꡣ\n");

	if (me->query_skill_mapped("whip") != "chanhun-suo")
		return notify_fail("��û�м�������������ʹ�������ꡣ\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�����һЦ������" + weapon->name() +
	      HIY "���ñ�ֱ������$n" HIY "���󣬿��Ǵ�����;ȴ��ͣ�ͣ�ת��$n"
	      HIY "�ؿڻ�ȥ��"NOR"\n";

	ap = me->query_skill("whip") + me->query_skill("force");
	dp = target->query_skill("force") + target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 3 + random(ap / 3);
		me->add("neili", -100);
		me->start_busy(2);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
					   HIR "���$n" HIR "һ���ҽУ�δ�ܿ���$N"
					   HIR "����ͼ������һ��Ӳ�����ؿڣ���Ѫ��"
					   "����Ƥ��������"NOR"\n");
		message_combatd(msg, me, target);
		if (ap > 400) ap = 400;
		dp += target->query_skill("martial-cognize", 1) * 2;
		if (! target->is_busy() &&
		    weapon->query("material") == "white silk" &&
		    ap / 2 + random(ap) > dp)
		{
			message_vision(HIW "$N" HIW "һ�������е�" + weapon->name() +
				       HIW "��ಡ��Ĵ��˳���������Ȼ����$n"
				       HIW "��\n$n" HIW "���һ������æ�˺���ȥ��һ�С�"NOR"\n",
				       me, target);
		}
	} else
	{
		me->add("neili", -100);
		me->start_busy(3);
		msg += CYN "����$p" CYN "����һԾ���𣬶�ܿ���"
		       CYN "$P" CYN "�Ĺ�����"NOR"\n";
		message_combatd(msg, me, target);
	}

	return 1;
}
