// tuo.c
// �����ս���ַ���ʱ��ʩչ�ľ���ʤ��
// ��һ�С�

#include <ansi.h>
#include <combat.h>

#define TUO "��" HIM "�����ˮ" NOR "��"

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ˮ"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;
	int effqi, maxqi;
	string couple;
	object cob;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(TUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query("static/marry") > 1)
		return notify_fail("��������Ѳ��������ﻹ�����Ե�������Ȼ����ĸо���\n");

	if (! me->query("couple/id"))
		return notify_fail("�����Ŷ�û�У�����Ȼʲô��\n");

	if ((int)me->query_skill("force") < 250)
		return notify_fail("����ڹ���Ч�ȼ�����250����ʹ����" TUO "��\n");

	if ((int)me->query_skill("sad-strike", 1) < 180)
		return notify_fail("�����Ȼ�����Ʋ���180��������ʹ��" TUO "��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʹ��" TUO "��\n");

	if (me->query_skill_mapped("unarmed") != "sad-strike")
		return notify_fail("��û�м�����Ȼ�����ƣ��޷�ʹ��" TUO "��\n");

	if (! stringp(couple = me->query("couple/id")))
		return notify_fail("��û�����ӣ���᲻�����������ҵĸо���\n");

	if (! objectp(cob = find_player(couple)))
		return notify_fail("���Ų��ڰ���������˭����\n");

	if (time() - me->query_temp("last_perform/sad-strike/tuo") < 60)
		return notify_fail("��ո�ʩչ�������ˮ����������û����ô�����ˡ�\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	effqi = me->query("eff_qi");
	maxqi = me->query("max_qi");

	ap = me->query_skill("unarmed");
	dp = target->query_skill("dodge");
	me->start_busy(3);

	if (effqi < maxqi * 25 / 100)
	{
		msg = HIR "$N" HIR "���������ң���Ȼ��" + cob->name(1) +
		      HIR "����һ�ۣ������������ˣ����Լ����ء���\n"
		      "����ʧ�����ǣ�����һ�У�ǡ��ʹ������Ȼ��������"
		      "�ġ������ˮ����"NOR"\n";
		ap += ap * 50 / 100;
	} else
	{
		msg = HIM "ֻ��$N" HIM "û����ɵĻ��������ĳ�һ�ƣ�����"
		      "��Ȼ�������еġ������ˮ����"NOR"\n";
	}
	if (ap / 2 + random(ap) > dp)
	{ 
		damage = ap + random(ap / 2);
		me->add("neili", -300);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
					   HIR "ֻ��$n" HIR "һ���ƺߣ����ۡ���һ"
					   "������һ�����û���$p" HIR "��ͷ�� \n"
					   NOR);
		me->set_temp("last_perform/sad-strike/tuo", 1);
	} else
	{
		me->add("neili", -100);
		msg += HIC "����$p" HIC "С��Ӧ���������мܣ���������һ�С�\n"
		       NOR;
	}
	message_combatd(msg, me, target);
	return 1;
}
