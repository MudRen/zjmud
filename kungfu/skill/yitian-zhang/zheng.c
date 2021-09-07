#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "˭��"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int count;
	int lvl;
	int i;

	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/yitian-zhang/zheng"))
		return notify_fail("�����ڻ�����ʹ�á�˭�����桹��һ�У�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("��˭�����桹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á�˭�����桹��\n");

	if ((lvl = (int)me->query_skill("yitian-zhang", 1)) < 125)
		return notify_fail("������������Ʋ�����죬����ʹ�á�˭�����桹��\n");

	if ((int)me->query("neili", 1) < 500)
		return notify_fail("����������̫��������ʹ�á�˭�����桹��\n");

	if (me->query_skill_prepared("strike") != "yitian-zhang")
		return notify_fail("������û��׼��ʹ�����������ƣ�����ʹ�á�˭�����桹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "������ͨ�������������ƶ�ʮ����һ���ǳɣ�˫��Я������ɽ����֮������$n" HIY "��"NOR"\n";
	me->add("neili", -150);

	if (random(me->query_skill("force") + me->query_skill("strike")) >
	    target->query_skill("force"))
	{
		msg += HIR "$n" HIR "��ʱ���ú���������ȫȻ����"
		       "���������ƣ�ֻ��ƴ���˶��ֵ���"NOR"\n";
		count = lvl / 5;
		me->add_temp("apply/attack", count);
	} else
	{
		msg += HIC "$n" HIC "����һ����������ֵ�������������"
		       "�ھ��κ���֮�У����ҵ�����ȴ�ǲ�����"NOR"\n";
		count = 0;
	}
	message_combatd(msg, me, target);

	for (i = 0; i < 4; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, 0, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(6));
	return 1;
}
