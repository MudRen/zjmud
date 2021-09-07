// jingsng.c ���ȭ ������ͨ

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

string query_name() { return "����"ZJBR"���"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int d_count, count, qi, maxqi, skill;

	if ((int)me->query_temp("jingang"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ͨ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ��������ͨ����\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ����������ʹ�ô�����ͨ��\n");

	if ((int)me->query_skill("cuff") < 150)
		return notify_fail("���ȭ���������ң��޷�ʹ�ô�����ͨ��\n");

	if (me->query_skill_mapped("cuff") != "jingang-quan") 
		return notify_fail("��û�м������ȭ���޷�ʹ�ô�����ͨ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ������ȭ�ľ�����������ͨ����������Ȼ���ӣ�"NOR"\n";
	
	qi = me->query("qi");
	maxqi = me->query("max_qi");
	skill = (int) (me->query_skill("jingang-quan", 1) / 3);
	count = skill / 2;
	d_count = (int)me->query_dex() / 2;

	if (qi > (maxqi * 0.4))
	{	
		message_combatd(msg, me, target);
		
		me->add_temp("str", count * 2);
		me->add_temp("dex", -d_count);
		me->set_temp("jingang", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);

		me->add("neili", -150);
	} else
	{
		msg = HIR "$N" HIR "ƴ����������ʹ���˴���ȭ����"
		      "������, ȫ�����һ����, ����$n" HIR "ͬ���ھ���"NOR"\n";
		message_combatd(msg, me, target);
		me->add_temp("str", count * 10);
		me->set_temp("jingang", 1);

		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 10, 0 :), 2);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
		me->set("neili",0);
		me->add("max_neili", -10);

		msg = HIR "$N" HIR "�þ������һ������, ���һ����Ѫ, һͷ�Ե��ڵأ�"NOR"\n";
		message_combatd(msg, me, target);
		me->unconcious();
	}
	return 1;
}

void remove_effect(object me, int aamount, int damount)
{
	if ((int)me->query_temp("jingang"))
	{
		me->add_temp("str", -aamount);
		me->add_temp("dex", damount);
		me->delete_temp("jingang");
		tell_object(me, "��Ĵ�����ͨ������ϣ��������ջص��\n");
	}
}
