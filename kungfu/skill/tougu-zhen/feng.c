#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "͸��"ZJBR"��ɱ"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int damage;
	int lvl;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("͸���롸��ɱ��ֻ����ս����ʹ�á�\n");

	if ((int)me->query_skill("tougu-zhen", 1) < 100)
		return notify_fail("���͸���뻹������죬�޷�ʩչ����ɱ��������\n");

	if ((int)me->query_skill("force") < 160)
		return notify_fail("���ڹ���򲻹�������ʩչ����ɱ��������\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("��������������޷�ʩչ����ɱ����������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ����ɱ����������\n");

	if (me->query_skill_mapped("finger") != "tougu-zhen") 
		return notify_fail("��û�м���͸���룬�޷�ʹ�á���ɱ��������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$Nʹ��͸���롸��ɱ����������ָ���裬�ó����캮�ǣ�Я��������֮��ֱ��$n����ҪѨ��"NOR"\n";

	lvl = me->query_skill("tougu-zhen", 1);
	ap = me->query_skill("finger") + me->query_skill("force");
	dp = target->query_skill("parry") + me->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 3 + random(ap / 4);
		target->affect_by("tougu_zhen",
			       ([ "level" : me->query("jiali") + random(me->query("jiali")),
				  "id"    : me->query("id"),
				  "duration" : lvl / 50 + random(lvl / 20) ]));
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
	      HIR "���ֻ��$nһ���Һ������������ţ�͸���뼫��֮�����ģ�ȫ��̱�飬��Ѫ���磡"NOR"\n");

		me->add("neili", -250);
		me->start_busy(1);
	} else
	{
		msg += CYN "����$n��æ��������������㿪����һ����"NOR"\n";
		me->start_busy(3);
		me->add("neili", -50);
	}
	message_combatd(msg, me, target);

	return 1;
}

