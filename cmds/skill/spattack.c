// spattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping weapon_name = ([
	"sword" : "��",
	"blade" : "��",
	"staff" : "��",
	"whip"  : "��",
	"club"  : "��",
]);

void do_remote_fight(object me, object couple, object target, int n);
void do_here_fight(object me, object couple, object target, int n);

int main(object me, string arg)
{
	int same_place;
	string couple_id;
	string couple_name;
	object couple;
	object target;

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ��ս����\n");

	if (! arg)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	} else
		target = present(arg, environment(me));

	if (! target || ! me->is_fighting(target))
		return notify_fail("����һ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! stringp(couple_id = me->query("couple/id")))
		return notify_fail("�㻹û�а��£�ʹʲô����һ����\n");

	couple_name = me->query("couple/name");

	if (! objectp(couple = find_player(couple_id)))
		return notify_fail(couple_name + "������������ϣ��޷�������������\n");

	if (couple->is_ghost())
		return notify_fail(couple_name + "�����ǹ��һ�����޷���Խ��������������\n");

	if (! living(couple))
		return notify_fail("������������޷���" + couple_name + "��ͨ��\n");

	if (target == couple)
		return notify_fail("���в�����\n");

	same_place = (environment(couple) == environment(me));

	if (! same_place)
		do_remote_fight(me, couple, target, me->query("sex/" + couple->name(1)));
	else
		do_here_fight(me, couple, target, me->query("sex/" + couple->name(1)));
	return 1;
}

void do_remote_fight(object me, object couple, object target, int n)
{
	object weapon;
	string chinese_type;
	int need, cost;
	int enhance, count;
	string msg;

	if (n > 500) n = 500;
	need = 300 - n / 2;
	cost = 300 - n / 3;

	if (me->query("jingli") < need)
	{
		write("����ͼ����İ��½��������ϵĹ�ͨ������һʱ���þ������ã�������ϵ��\n");
		return;
	}

	if (couple->query("jingli") < need)
	{
		write("������ԼԼ�ĸо�������µ����������Ƿǳ�΢�������Ѳ�׽����\n");
		return;
	}

	if (me->is_busy())
	{
		write("( ����һ��������û����ɣ�����ʩչ����һ����)\n");
		return;
	}

	if (random(2))
		tell_object(me, HIM "������ĬĬ������" + couple->name(1) +
			    HIM "�����֣������е������������"
			    "�������͸���޾�����գ���������������"NOR"\n");
	else
		tell_object(me, HIM "��������翵���գ���·𿴵�" + couple->name(1) +
			    HIM "�����������ϵĹ�����޾���������"NOR"\n");

	if (random(2))
		tell_object(couple, HIM "���ƺ��о���" + me->name(1) +
			    HIM "�������������������֣�����֮"
			    "������������Ϭ����ĬĬ��Ϊ" +
			    gender_pronoun(me->query("gender")) +
			    "ף����ȥ�ɣ��ҵİ��ˣ�"NOR"\n");
	else
		tell_object(couple, HIM "ڤڤ��е���" + me->name(1) +
			    HIM "����ĺ�������һɲ�ǣ�������������"
			    "ȫȻ��ͨ����������ε�����ע����Է���������" +
			    gender_pronoun(me->query("gender")) + "��"NOR"\n");

	me->add("jingli", -cost);
	couple->add("jingli", -cost);
	weapon = me->query_temp("weapon");
	if (weapon && (chinese_type = weapon_name[weapon->query("skill_type")]))
	{
		if (me->query("gender") == "Ů��")
			msg = HIG "$N" HIG "��" + chinese_type +
			      "������������ݺ���ȣ�Ʈ����������е�" +
			      weapon->name() + HIG "��������ҹ�꣬����$n"
			      HIG "��"NOR"\n";
		else
			msg = HIC "$N��" + chinese_type + "��������Ȼ��$n" HIC "�����������" +
			      weapon->name() + HIC "�������磬������" +
			      chinese_type + "Ӱ����$p" HIC "���ڵ��С�"NOR"\n";
	} else
	{
		if (me->query("gender") == "Ů��")
			msg = HIG "$N" HIG "����ǳЦ��ƮȻ������������"
			      "���ף�����������Ṳ̊��쳾������Ͷ��֮��û���κ�������"NOR"\n";
		else
			msg = HIC "$N" HIC "������Х��һ��ɱ����Ȼ������"
			      "�ص�ʱɫ�䣬$N" HIC "Ю�������֮�ƣ�ѹ��$n"
			      HIC "��"NOR"\n";
	}

	message_combatd(msg, me, target);
	enhance = ((int)couple->query_skill("force") + n / 10) / 5;
	count = 1 + random(3 + n / 100);
	if (count > 3)
		count = 3;
	me->add_temp("apply/attack", enhance);
	while (count--)
	{
		if (! me->is_fighting(target))
			break;

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
	}
	me->add_temp("apply/attack", -enhance);
	me->start_busy(3);
	return;
}

void do_here_fight(object me, object couple, object target, int n)
{
	int need, cost;
	int enhance1, enhance2, count;
	string msg;

	if (n > 500) n = 500;
	need = 300 - n / 2;
	cost = 300 - n / 3;

	if (me->is_busy())
	{
		write("( ����һ��������û����ɣ�����ʩչ����һ����)\n");
		return;
	}

	if (couple->is_busy())
	{
		write("��İ���������æ���޷��������л���һ����\n");
		return;
	}

	if (! couple->is_fighting(target))
		couple->fight_ob(target);

	message_combatd(HIY "$N" HIY "��$n" HIY "��������һ����������"
			"Ȼ��ͨ�����ɵĻ���һЦ��ֻ����������һ����ʱ\n"
			"�Ѿ���" + target->name() + "�������У�"NOR"\n",
			me, couple);

	enhance1 = ((int)couple->query_skill("force") + n / 10) / 5;
	enhance2 = ((int)me->query_skill("force") + n / 10) / 5;
	count = 2 + random(5 + n / 50);
	if (count > 6)
		count = 6;
	me->add_temp("apply/attack", enhance1);
	couple->add_temp("apply/attack", enhance2);
	while (count--)
	{
		if (me->is_fighting(target) && (count % 2) == 0)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
		else
		if (couple->is_fighting(target))
			COMBAT_D->do_attack(couple, target, couple->query_temp("weapon"), 0);
		else
			break;
	}

	me->start_busy(2);
	couple->start_busy(2);
	me->add_temp("apply/attack", -enhance1);
	couple->add_temp("apply/attack", -enhance2);
	return;
}

int help (object me)
{
	write(@HELP
ָ���ʽ��spattack [<ʩ�ö���>]

��������ˣ��Ϳ���ʹ�û���һ�������ִ���������ڹ����Ķ��֣�
��ʹ��İ��²��������ߣ�Ҳ����������������ңԶ��ʱ�ո�����
֧�֣���Ȼ����Ҫ�ķѾ����������������ϵĴ���Խ�࣬�ķѵľ�
����Խ�١������İ��¾��������ߣ������һ��ʩչ����������
�֣�����Ҫ�ķѾ����������������������������ϵĴ����ڰ��µ�
�ڹ��ȼ���ء�
HELP );
	return 1;
}
