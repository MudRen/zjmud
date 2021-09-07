// wulun.c ��������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "hammer", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
	int count;
 
	if (userp(me) && ! me->query("can_perform/riyue-lun/wulun"))
		return notify_fail("�㻹�������á��������ҡ���һ������\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���������ҡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "hammer")
		return notify_fail("��û�к��ʵı��������ʩչ���������ҡ���\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������޷�ʩչ���������ҡ���\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʩչ���������ҡ���\n");

	if ((int)me->query_skill("riyue-lun", 1) < 120)
		return notify_fail("��������ַ��������ң��޷�ʹ���������ң�\n");

	if (me->query_skill_mapped("hammer") != "riyue-lun")
		return notify_fail("��û�м��������ַ����޷�ʹ�á��������ҡ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (random(3))
	{
	case 0:
		msg = HIM "$N" HIM "��Ŀ��ȣ����е�" + weapon->name() +
		      HIM "ʹ�������������⣬��Ҳ�Ƶ�����ѹ��$n" HIM "��"NOR"\n";
		break;

	case 1:
		msg = HIM "$N" HIM "΢΢��Ц������һ���������е�" + weapon->name() +
		      HIM "��ת��ɣ�������âһ��ѹ��$n" HIM "��"NOR"\n";
		break;

	default:
		msg = HIM "$N" HIM "����������һ����ȣ������е�" + weapon->name() +
		      HIM "����������ȥ��Ʈ��������\nֻ����" + weapon->name() +
		      HIM "��Ҫ����գ�$P" HIM "����ǰȥһ����" + weapon->name() +
		      HIM "ȴ�ֱ���һ����λ����������$n" HIM "��"NOR"\n";
		break;
	}

	message_combatd(msg, me, target);
	me->add("neili", -100);

	count = me->query_skill("hammer") / 9;
	me->add_temp("apply/attack", count);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}

