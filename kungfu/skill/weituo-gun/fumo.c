// fumo.c Τ�з�ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "Τ��"ZJBR"��ħ"; }
string *pfm_type() { return ({ "club", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Τ�з�ħ��ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("weituo-gun", 1) < 135)
		return notify_fail("���Τ�ӹ�����Ϊ������Ŀǰ����ʹ��Τ�з�ħ��\n");

	if (me->query("neili") < 800)
		return notify_fail("�����������������ʹ��Τ�з�ħ��\n");

	if (me->query_skill_mapped("club") != "weituo-gun")
		return notify_fail("��û�м���Τ�ӹ���������ʹ��Τ�з�ħ��\n");

	if (me->query("shen") < 10000)
		return notify_fail("���������㣬�������Τ�з�ħ�ľ��衣\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "��ɫ��ͣ�����һ�ɴ���֮�⣬���е�" + weapon->name() +
	      HIY "������������Գ����Τ������\n������䣬����ס$n" + HIY "��"NOR"\n";

	if (target->is_bad())
	{
		ap = me->query("shen") / 1000;
		if (ap > 100) ap = (ap - 100) / 4 + 100;
		if (ap > 200) ap = (ap - 200) / 4 + 200;
		if (ap > 300) ap = (ap - 300) / 4 + 300;
		if (ap > 500) ap = 500;
		msg += HIR "$n" HIR "ƽ�������٣����˴���˾������в�����Ȼ��"NOR"\n";
	} else
		ap = 0;
	ap += me->query_skill("club"); 
	dp = target->query_skill("force");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + random(ap);
		me->add("neili", -300);
		me->start_busy(1);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
					   HIR "���ֻ��$p" HIR "һ���ҽУ���$P"
					   "һ���Ӵ���Ҫ��������һ�����̣����Ƕ�����Ѫ����"NOR"\n");

	} else
	{
		me->add("neili", -60);
		me->start_busy(2);
		msg += CYN "����$p" CYN "ǿ������û�б�$P"
		       CYN "���Ի�Ӳ�����ļ�ס��$P" CYN "��һ�У�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
