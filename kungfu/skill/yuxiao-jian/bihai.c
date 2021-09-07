#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�̺�"ZJBR"����"; }

int perform(object me, object target)
{
	string msg;
	int ap, dp, lvl;
	int jing, skill;
	object ob;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail(HIW "�̺�����������" NOR
				   "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(ob = me->query_temp("handing")) || ! ob->valid_as_xiao())
	{
		// ����û���������쿴����
		if (! objectp(ob = me->query_temp("weapon")) ||
		    ! ob->valid_as_xiao())
		{
			// ����ı���Ҳ������Ϊ��ʹ��
			return notify_fail("������û���������޷�ʹ��������У�\n");
		}
	}

	skill = me->query_skill("yuxiao-jian", 1);

	if (skill < 150)
		return notify_fail("������｣���ȼ�����, ����ʹ��"
				   HIW "�̺�����������" NOR "��\n");

	if (me->query("neili") < 300)
		return notify_fail("��������������޷�����"
				   HIW "�̺�����������" NOR "��\n");

        if (target->query("qi")>target->query("max_jing")*3 && !userp(target))
	      return notify_fail("�Է���Ѫ��ӯ��" HIW "�̺�����������" NOR "�޷�Ӱ�졣\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	ap = me->query_skill("yuxiao-jian", 1) / 2 +
	     me->query_skill("force") + me->query_skill("chuixiao-jifa");
	dp = target->query_skill("force") * 2;

	lvl = (int) me->query_skill("yuxiao-jian", 1) / 5 + 1;
	if (lvl > 40) lvl = (lvl - 40) / 3 + 40;

	jing = (int) target->query("max_jing");
	if (jing>10000) jing = (int) me->query("max_jing");

	msg = HIC "$N" HIC "�ְ�" + ob->name() + HIC "����̤���Է�λ�����" NOR
	      HIW "��" HIC "�̺�����������" HIW "��" NOR
	      HIC "............"NOR"\n";
	msg += HIW "\nֻ���������٣�����񣬷��˼�������������"
		   "���Ʈ��һ��������͵Ķ���������"NOR"\n";

	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "$n" HIR "��ͷһ�������ϲ��Խ���¶��΢Ц��"NOR"\n";
		target->receive_damage("jing", jing / 5, me);
		target->receive_wound("jing", jing / 5, me);
		message_combatd(msg, me, target);
	} else
	{
		msg += HIY "$n" HIY "����������һ��������������Ӧ��ԣ�磡"NOR"\n";
		message_vision(msg, me, target);
	}

	msg = HIW "�Ƕ���������Ʈ����������ת������һ��Ů��һ��"
		  "��̾Ϣ��һ���������һ����������´��\n"
		  "�����л���"NOR"\n";

	if (ap / 4 + random(ap) > dp)
	{
		msg+= HIR "$nֻ��ȫ����Ѫ���ڣ���ֻ�������㵸���Ҷ�һ����"NOR"\n";
		target->receive_damage("jing", jing / 3, me);
		target->receive_wound("jing", jing / 3, me);
		message_combatd(msg, me, target);
	} else
	{
		msg += HIY "$n" HIY "����������һ��������������Ӧ��ԣ�磡"NOR"\n";
		message_vision(msg, me, target);
	}

	msg = HIW  "��������������󺣺��������޲���Զ����ˮ�����ƽ����������죬��������ӿ��������\n"
		   "ɽ������ˮ����Ծ�����������Ϸ�ХŸ�ɣ��ټ���ˮ�����֣�ȺħŪ����������ɽƮ��������\n"
		   "�Ⱥ���У��������֮���¡�"NOR"\n";

	if (ap / 4 + random(ap / 2) > dp)
	{
		msg+= HIR "$n" HIR "ֻ����ͷ���ȣ�������"NOR"\n";
		target->receive_damage("jing", jing / 2, me);
		target->receive_wound("jing", jing / 2, me);
		message_combatd(msg, me, target);
	} else
	{
		msg += HIY "$n" HIY "����������һ��������������Ӧ��ԣ�磡"NOR"\n";
		message_vision(msg, me, target);
	}

	msg = HIW "����������ϸ�������������ţ����糱�˺�ˮƽ��"
		  "��������ȴ���ǰ����ļ���"NOR"\n";

	if (ap / 5 + random(ap / 4) > dp)
	{
		msg+= HIR "$n" HIR "��ʱ���ݾ�������Ҳ�޷�����"NOR"\n";
		target->receive_damage("jing", jing / 2, me);
		target->receive_wound("jing", jing / 2, me);
		me->start_busy(1 + random(2));
		me->add("neili", -200);
		message_combatd(msg, me, target);
		return 1;
	} else
	{
		msg+= HIY "$n" HIY "����������һ��������������Ӧ��ԣ�磡"NOR"\n";
		me->start_busy(2 + random(3));
		me->add("neili", -200);
		message_vision(msg, me, target);
		return 1;
	}

	message_combatd(msg, me, target);

	return 1;
}
