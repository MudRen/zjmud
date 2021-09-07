// beg.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string what, who;
	object ob, victim;
	int sp, dp;

	object where = environment(me);

	seteuid(getuid());

	if (me->query("family/family_name") != "ؤ��")
	  	return notify_fail("ֻ����ؤ�������֣�\n");

	if (environment(me)->query("no_beg") ||
	    environment(me)->query("no_fight"))
		return notify_fail("���ﲻ����л��������ַ��ĵط���\n");

	if (me->query_temp("begging"))
		return notify_fail("���Ѿ������˼������ˣ�\n");

	if (! arg)
		return notify_fail("ָ���ʽ��beg ����\n");

	victim = present(arg, environment(me));
	if (! victim || victim == me)
		return notify_fail("�������ֵĶ��������\n");

	if (! living(victim) || ! objectp(victim))
		return notify_fail("��Ҫ��˭���֣�\n");

	if (victim->query("family/family_name") == "ؤ��")
		return notify_fail("�㲻������ؤ���֣�\n");

	if (! wizardp(me) && wizardp(victim))
		return notify_fail("��Ҳ�������ʦ���֡�\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("һ�ߴ��һ��Ҫ���������ǻ����ˣ�\n");

	if (victim->is_fighting())
		return notify_fail(victim->name() + "���ڴ�ܣ�û�����㣡\n");

	if (! ob) ob = present("gold", victim);
	if (! ob) ob = present("silver", victim);
	if (! ob) ob = present("coin", victim);

	if (! ob)
		return notify_fail( victim->name() + "���Ͽ�����û��ʲ���������Ȥ�Ķ�����\n");

	if (ob->query("equipped") || ob->query("no_drop"))
		return notify_fail("�������˵�����һ�϶�������㡣\n");

	sp = (int)me->query_skill("begging");
	sp = sp * sp * sp / 10;

	if (sp < 1) sp = 1;
	dp = (int)victim->query("jing") + ob->value() / 5;

	tell_object(me, "��װ�������Ͱ͵����ӣ���������" + victim->name() + "�߹�ȥ�����˫�֣���Ҫ"
			+ ob->query("unit") + ob->name() +"...\n\n");
	tell_object(victim, me->name() + "�����Ͱ͵����������߹���������֣�˵����" + RANK_D->query_respect(victim) + "���кã�����"
			+ ob->query("unit") + ob->name() + "�� ...��\n\n");
	message("vision", "ֻ��" + me->name() + "װ�������Ͱ͵����ӣ���������"
		+ victim->name() + "�߹�ȥ��\n���˫�֣�˵����"
		+ RANK_D->query_respect(victim) + "�����кð� ...\n\n", environment(me), ({ me, victim}) );

	me->set_temp("begging", 1);
	call_out( "compelete_beg", 3, me, victim, ob, sp, dp);
	return 1;
}

private void compelete_beg(object me, object victim, object ob, int sp, int dp)
{
	int amount;
	int bcount;
	object ob1;
	object where;

	if (! objectp(me)) return;
	me->delete_temp("begging");

	where = environment(me);
	if (! objectp(ob) || ! living(me) || me->is_fighting())
		return;

	if (! victim || environment(victim) != environment(me))
	{
		tell_object(me, "̫��ϧ�ˣ���Ҫ���ֵ����Ѿ����ˡ�\n");
		return;
	}

	if (environment(ob) != victim)
	{
		tell_object(me, "̫��ϧ�ˣ��˼Һ����Ѿ�û��" + ob->name() + "�ˡ�\n");
		return;
	}

	if (living(victim) && (random(sp + dp) > dp))
	{
		if (! ob->query("money_id") || ! (amount = ob->query_amount()))
		{
			tell_object(me, "���������߰ɣ���һ������Ѿ�û�ж�����ˮ��ե�ˡ�\n");
			return;
		}

		bcount = amount / 5;
		if (! bcount) bcount = 1;
		ob->set_amount(amount - bcount);

		ob1=new("/clone/money/" + ob->query("money_id"));
		ob1->set_amount(bcount);
		ob1->move(me);

		tell_object(me, victim->name() + "��ͷ����һ�ᣬ�ֿ��˿��㣬ҡҡͷ��̾�˿�����������һ" +
				ob1->query("unit") + ob1->name() + "��\n");
		tell_object(victim, "�㿴��" +  me->name() +"�Ŀ�������̾�˿�����������һ" +
				ob1->query("unit") + ob1->name() + "��\n");

      		if (me->can_improve_skill("begging"))
	  		me->improve_skill("begging", random(me->query("int")));

      		if ((int)me->query("potential") < (int)me->query_potential_limit())
			me->add("potential", 1);

		me->add("combat_exp",1);
		if (! me->is_busy())
			me->start_busy(3 + random(4));
	} else
	{
		if (random(sp) > dp / 2)
		{
			message_vision(victim->name() + "�ݺ�"
				       "�ص���$Nһ�ۣ��ȵ�������"
				       "$N����һ������æŤͷ����"
				       "����߿��ˡ�\n", me);
			if (! me->is_busy())
				me->start_busy(3);
			return;
		}

		tell_object(me, victim->name() + "Ť��ͷȥ������������\n");
		tell_object(victim, "��Ť��ͷȥ����" + me->name() +
			    "������\n");
		message("vision", victim->name() + "Ť��ͷȥ����" +
			me->name() +  "������\n",
			environment(me), ({ me, victim }) );

		if (! me->is_busy())
			me->start_busy(3);
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ : beg <ĳ��> from <ĳ��>

HELP );
	return 1;
}
