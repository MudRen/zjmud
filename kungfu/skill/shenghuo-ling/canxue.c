#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define CANXUE "��" HIR "��Ѫ��" NOR "��"

string query_name() { return "��Ѫ��"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int damage, skill;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (userp(me) && ! me->query("can_perform/shenghuo-ling/canxue"))
		return notify_fail("�㻹����ʹ��" CANXUE "��һ������\n");

	if (! target) target = offensive_target(me);

	skill = me->query_skill("shenghuo-ling", 1);

	if (! (me->is_fighting()))
		return notify_fail(CANXUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮"
				   CANXUE "��\n");

	if (skill < 250)
		return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ����"
				   "��֮" CANXUE "��\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʹ��ʥ���֮"
				   CANXUE "��\n");

	if (me->query("max_neili") < 1500)
		return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮"
				   CANXUE "��\n");

	if (me->query("neili") < 300)
		return notify_fail("�����������������ʹ��ʥ���֮" CANXUE "��\n");

	if (me->query_skill_mapped("sword") != "shenghuo-ling")
		return notify_fail("��û�м���ʥ������޷�ʹ��" CANXUE "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "һ����Х������" + weapon->name() +
	      HIR "һת��������ʱ��ù����ޱȣ������벻���ķ�"
	      "λ����$n" HIR "��"NOR"\n";

	// ���ʥ�������߱��� max_hit����������˺���
	// ԭ���и���˺��ѿ�͸�����������Գ������ӹ�
	// ����Ч�ʷǳ���
	if (random(me->query_skill("shenghuo-ling", 1)) > target->query_skill("parry", 1) / 2)
	{
		msg += HIR "$n" HIR "��ȫ�޷���͸$N" HIR "������ʵ�����ɵ���"
		       "�����⣬��ʽһ�ͣ���ʱ�����ٳ���"NOR"\n";
		count = me->query_skill("shenghuo-ling", 1) / 10;
	} else
	{
		msg += HIY "$n" HIY "��$N" HIY "������ӿ���ĵ�һ��������"
		       "��С�Ľ��С�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -120);
	me->add_temp("apply/attack", count);

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;

		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(6));
	return 1;
}
