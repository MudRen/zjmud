// leiting.c ������һ����

#include <ansi.h>
#include <combat.h>

#define LEITING "��" HIY "����һ��" NOR "��"

inherit F_SSERVER;

string query_name() { return "����"ZJBR"һ��"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(LEITING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("force") < 250)
		return notify_fail("����ڹ���򲻹���ʹ����" LEITING "��\n");

	if ((int)me->query_skill("dragon-strike", 1) < 170)
		return notify_fail("��Ľ���ʮ���Ʋ�������������ʹ��" LEITING "��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʹ��" LEITING "��\n");

	if (me->query_skill_mapped("strike") != "dragon-strike")
		return notify_fail("��û�м�������ʮ���ƣ��޷�ʹ��" LEITING "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "Ĭ���ڹ���ʩչ��" LEITING HIC "��ȫ����ת��������"
	      "Խ��Խ�죬��\n����һ�����磬��Ȼ�䣬$N" HIC "�Ѿ�������"
	      "�÷�����" HIC "$n��"NOR"\n";  

	ap = me->query_skill("strike") + me->query("str") * 10;
	dp = target->query_skill("dodge") + target->query("dex") * 10;
	me->start_busy(3);
	if (ap / 2 + random(ap) > dp)
	{ 
		damage = ap + random(ap / 2);
		me->add("neili", -400);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
					   HIR "$p" HIR "ֻ��һ������Ӱ�ж�Ȼ�ֳ�$P"
					   HIR "��˫�ƣ�������������ܣ������ػ��У�\n��"
					   "���������ڲ��ݣ�������Ѫ��������������"NOR"\n");
	} else
	{
		msg += HIG "����$p" HIG "������$P" HIG "����ͼ��û"
		       "���ܵ��Ի�������һ�ߡ�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}

