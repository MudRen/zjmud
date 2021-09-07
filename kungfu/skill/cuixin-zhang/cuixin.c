#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp;
	int damage, lvl;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("������ǿ��ֲ���ʹ�ö������ģ�\n");
 
	lvl = me->query_skill("cuixin-zhang", 1);

	if (lvl < 120)
		return notify_fail("��Ĵ����ƻ��������죡\n");

	if (me->query_skill("force") < 120)
		return notify_fail("����ڹ����̫�ͣ��޷�ʹ���������ġ�\n");

	if (me->query("neili") < 800)
		return notify_fail("��������������޷�ʹ���������ġ�\n");

	if (me->query_skill_mapped("strike") != "cuixin-zhang")
		return notify_fail("��û�м���������, ����ʹ�á��������ġ���\n");

	if (me->query_skill_prepared("strike") != "cuixin-zhang")
		return notify_fail("������û��׼��ʹ�ô����ƣ��޷�ʹ�á��������ġ���\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = BLU "$N" BLU "�������ƣ�����һ����Х��ɲ�Ǽ�˫�ƽ���һ��"
		  "���������ġ����������ھ�ֱ��$n" BLU "��"NOR"\n";

	ap = me->query_skill("strike") + lvl;
	dp = target->query_skill("parry");

	if (dp < 1) dp = 1;

	if ( ap / 2 + random(ap) > dp + random(dp) )
	{
	me->add("neili", -300);
	damage = lvl + random(lvl);
	target->affect_by("cuixin_zhang",
		([ "level" : me->query("jiali") + random(me->query("jiali")),
		"id"    : me->query("id"),
		"duration" : lvl / 50 + random(lvl / 20) ]));
	msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70, 
	       HIR "ֻ��$n" HIR "�ҽ�һ����ֻ��������"
	       "����Ŀ��������һ�����Ѫ������̱����"NOR"\n");

	me->start_busy(2);
	}
    else
	{
	msg += HIY "$p��$P������ӿ����æ����һԾ���𣬶㿪����������һ����"NOR"\n";
	me->add("neili", -300);
	me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

