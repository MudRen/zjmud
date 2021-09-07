#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "�ٻ�"ZJBR"����"; }

int perform(object me, object target)
{
	string msg;
	int count;
	int lvl;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�ٻ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_skill_prepared("unarmed") != "baihua-quan" &&
	    me->query_skill_prepared("cuff") != "baihua-quan" &&
	    me->query_skill_prepared("strike") != "baihua-quan" &&
	    me->query_skill_prepared("claw") != "baihua-quan" &&
	    me->query_skill_prepared("hand") != "baihua-quan")
		return notify_fail("������û��׼��ʹ�ðٻ���ȭ���޷�ʩչ�ٻ����ң�\n");
 
	if (me->query_temp("weapon"))
		return notify_fail("�ٻ��������ǿ��ֲ���ʩչ��\n");

	if (me->query("neili") < 300)
		return notify_fail("��������������޷�ʩչ�ٻ����ҡ�\n");

	if ((lvl = me->query_skill("baihua-quan", 1)) < 160)
		return notify_fail("��İٻ���ȭ���������죡\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "ֻ��$Nʹ���ٻ���ȭ�ľ���ٻ����ң��������м���ӥצ�������ֲ�ȭ���������ơ���\n"
		  "��ȥ�ǰ����ƣ��ջ�ʱ����̫��ȭ������ӳ£����޹��ɣ�ֻ��$n�ۻ����ҡ�"NOR"\n";
	i = 5;
	if (lvl / 2 + random(lvl) > (int)target->query_skill("parry", 1))
	{
		msg += HIW "$nֻ�е�ͷ��Ŀѣ��ֻ��$N���ơ���צ����ȭ����ָ����ǵص����Լ�������λϮ����\n"
			   "ֻһ˲�䣬ȫ���Ѷ�����ʮ���˺ۣ�"NOR+HIR"��Ѫ"NOR+HIW"��к��ֹ��"NOR"\n";
		count = me->query_skill("baihua-quan", 1) / 6;
		me->add_temp("apply/attack", count);
		me->add("neili", -300);
		target->start_busy(4);
	} else
	{
		msg += HIY "$nֻ��$N��ȭ�籼����ȭ�ͷ׵ݳ�����æ����������ǿ�ֵ���"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);

	while (i--)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}
