// crattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

void hate_attack(object me, object target);
void shout_message(string msg);

int main(object me, string arg)
{
	object target;
	int craze;
	string msg;
	int attack;
	int damage;

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ��ս����\n");

	if (me->is_busy())
		return notify_fail("( ����һ��������û����ɣ�����ʩ�÷�ŭһ����)\n");

	if (! arg)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	} else
		target = present(arg, environment(me));

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ŭһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! living(target))
		return notify_fail("�˼Ҷ��Ѿ���������ˣ��㻹�õ�����ô������ô��\n");

	if ((craze = me->query_craze()) < 500)
		return notify_fail("��������ƽ���ͣ�̸����ʲô��ŭ��\n");

	if (craze < 1000)
		return notify_fail("�����ڻ�������ŭ���޷�ʩչ��ŭ��ɱ������\n");

	if (me->query("qi") * 100 / me->query("max_qi") < 50)
		return notify_fail("����������̫�������޷�ʩչ��ŭ��ɱ������\n");

	if (me->query("qi") < 200)
		return notify_fail("��������Ϣ����ǿ������ʩչ���ҵķ�ŭ��ɱ������\n");

	me->receive_damage("qi", random(me->query("max_qi") / 4));

	if (me->is_most_craze())
	{
		int second;

		if (me->is_hating(target->query("id")))
		{
			hate_attack(me, target);
			return 1;
		}

		if (me->query("gender") == "Ů��")
			msg = HIR "$N" HIR "�����������У������ɨ��$n" HIR "�������������˸���ս��ֻ��$P������"
			      "������" + RANK_D->query_rude(target) + "����ȥ���ɣ���"NOR"\n";
		else
			msg = HIR "$N" HIR "�������ף������񣬶�$n" HIR "��ȵ�����" + RANK_D->query_rude(target) +
			      "���㻹���������������"NOR"\n";
		message_combatd(msg, me, target);

		// first attack
		attack = craze / 50;
		damage = craze / 20;
		if (attack > me->query_skill("force") + 10)
			attack = me->query_skill("force") + 10;
		if (damage > me->query_str() * 8)
			damage = me->query_str() * 8;
		me->add_temp("apply/attack", attack);
		me->add_temp("apply/damage", damage);
		me->add_temp("apply/unarmed_damage", damage);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
		msg = HIR "$N" HIR "һ�й������������ݣ��漴������������һ�У�"NOR"\n";
		if (! me->is_fighting(target) && living(target))
		{
			msg += HIY "$n" HIY "��$N" HIY "����������ȫȻ�����Լ��Ѿ��������գ����ɴ��һ������æ�ֵ���"NOR"\n";
		}
		message_combatd(msg, me, target);

		// second attack
		second = me->query("str");
		attack += second;
		damage += second;
		me->add_temp("apply/attack", second);
		me->add_temp("apply/damage", second);
		me->add_temp("apply/unarmed_damage", second);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
		me->add_temp("apply/attack", -attack);
		me->add_temp("apply/damage", -damage);
		me->add_temp("apply/unarmed_damage", -damage);
		me->cost_craze(craze / 4 + random(craze / 2));
		me->start_busy(2);
		return 1;
	}

	if (me->query("gender") == "Ů��")
		msg = HIR "$N" HIR "һ��������ңָ$n" HIR "�ȵ�����" +
		      RANK_D->query_rude(target) + "�����У���"NOR"\n";
	else
		msg = HIR "$N" HIR "һ�������ͬ�����������$n" HIR
		      HIR "���ȵ�����" + RANK_D->query_rude(target) +
		      "���㻹�������������"NOR"\n";

	message_combatd(msg, me, target);
	attack = craze / 60;
	damage = craze / 30;
	if (attack > me->query_skill("force") + 10)
		attack = me->query_skill("force") + 10;
	if (damage > me->query_str() * 8)
		damage = me->query_str() * 8;

	me->add_temp("apply/attack", attack);
	me->add_temp("apply/damage", damage);
	me->add_temp("apply/uanrmed_damage", damage);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	me->add_temp("apply/attack", -attack);
	me->add_temp("apply/damage", -damage);
	me->add_temp("apply/uanrmed_damage", -damage);
	me->cost_craze(craze / 4 + random(craze / 2));
	me->start_busy(1);
	return 1;
}

void hate_attack(object me, object target)
{
	int craze;
	int attack;
	int damage;

	craze = me->query_craze();
	attack = craze / 40;
	damage = craze / 18;
	if (attack > me->query_skill("force") + 10)
		attack = me->query_skill("force") + 10;
	if (damage > me->query_str() * 8)
		damage = me->query_str() * 8;

	if (random(2))
		shout_message(me->name(1) + "��" + target->name() + HIR "�����ȵ���" +
			      RANK_D->query_rude(target) + "������" +
			      RANK_D->query_self(me) + "Ҫ��ѪծѪ�������У�");
	else
		shout_message(me->name(1) + "��" + target->name() + HIR "ŭ�ȵ���" +
			      RANK_D->query_rude(target) + "���Թ�ɱ�˳�����" +
			      "�����Ҿ�Ҫ��Ĺ��������ɣ�");

	me->want_kill(target);
	me->kill_ob(target);
	me->add_temp("apply/attack", attack);
	me->add_temp("apply/damage", damage);
	me->add_temp("apply/unarmed_damage", damage);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е���" + target->name() +
		       "�����ٿ�����һ�У�"NOR"\n", me);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е���" + RANK_D->query_rude(target) +
		      "�����ٿ�����һ�У�"NOR"\n", me);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е����ã����ٽ�����һ�У�"NOR"\n", me);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е������ߣ����ٽ�����һ�У�"NOR"\n", me);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е�����������⵱�д���һ�У�"NOR"\n", me);
	damage += me->query("str");
	attack += me->query("str");
	me->add_temp("apply/attack", me->query("str"));
	me->add_temp("apply/damage", me->query("str"));
	me->add_temp("apply/unarmed_damage", me->query("str"));
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

	message_combatd(HIR "\n$N" HIR "�е�����û�꣬�������һ�У�����"NOR"\n", me);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	me->add_temp("apply/attack", -attack);
	me->add_temp("apply/damage", -damage);
	me->add_temp("apply/unarmed_damage", -damage);

	if (target->query("qi") >= 0 &&
	    target->query("jing") >= 0)
	{
		if (random(2))
			shout_message(target->name(1) + "�ǺǴ�Ц������λ" +
				      RANK_D->query_respect(me) + "��������������������������ҺΣ�");
		else
			shout_message(target->name(1) + "������Ц�������" +
				      "���ƺ��װ�����ϧ����̫�Ҳ�գ�Ҳ�գ�������");

		tell_object(me, HIR "��Ŀ�����ѣ�����ȼ�������ŭ��˿��û�м�����"NOR"\n");
	} else
	{
		if (random(2))
			shout_message(target->name(1) + "�ҽе����ҵ��죡");
		else
			shout_message(target->name(1) + "�������ţ��찡����Ӧ���úÿ죡");

		me->cost_craze(craze);
		me->craze_defeated(target->query("id"));
		tell_object(me, HIC "�㳤��һ����������ƽ������ࡣ"NOR"\n");
	}
	me->start_busy(2);
}

void shout_message(string msg)
{
	message("channel:chat", HIR "������" HIW "ѩ" HIR "�ޡ�" + msg + ""NOR"\n",all_interactive());
}

int help (object me)
{
	write(@HELP
ָ���ʽ��crattack <����>

����㴦�ڷ�ŭ״̬���Ϳ��������Լ��ķ�ŭ��ַ����Լ���������
�������ڽ��ֵĶ��ֳ��صĴ������Ȼ�㻹��ʹ�ø��ͻ���ɱ������
���书�����յ����õ�Ч�������ŭ���ﵽ�˶����ʱ����������
��ͬ���졣

����㱻�˴��λ���ɱ������������ɱ������˽���Ϊ�����޵Ķ�
�󣬵����ŭ�ﵽ������ʱ�򣬾Ϳ��Զ������޵Ķ���ʩչ��������
ɱ������ֻ�ܶ�һ�����޵Ķ�������һ�Ρ�

HELP );
	return 1;
}
