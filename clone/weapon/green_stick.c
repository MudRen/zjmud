//green_stick.c

#include <weapon.h>
#include <ansi.h>

inherit STAFF;

string do_wield();
string do_unwield();

void create()
{
	set_name(HIG "������" NOR, ({ "lvyu zhang", "stick", "lvyu" }));
	set_weight(1500);
	if (clonep())
		destruct(this_object());
	else {
		set("long", @LONG
����һ����Ө���̵����������ؤ������������Ψһ���
LONG );
		set("unit", "��");
		set("value", 800000);
	       // set("icon", "05042");
		set("no_sell", 1);
		set("material", "bamboo");
		set("wield_msg", (: do_wield :));
		set("unwield_msg", (: do_unwield :));
		set("stable", 80);
	}
	init_staff(200);
	setup();
}

string do_wield()
{
	object me;
	me = this_player();

	return HIG "$N����һ������֪��ʱ�������Ѿ�����һ����Ө��͸�������"NOR"\n"; 
}

string do_unwield()
{
	object me;
	me = this_player();

	return HIG "$N΢΢һЦ����һ������������Ѳ�����Ӱ��"NOR"\n";
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int n;
	int my_exp, ob_exp;

	if (me->query_skill_mapped("staff") != "dagou-bang" ||
	    me->query_skill("dagou-bang", 1) < 100)
		// only increase damage
		return damage_bonus / 2;

	switch (random(8))
	{
	case 0:
		if (! victim->is_busy())
			victim->start_busy(me->query_skill("staff") / 10 + 2);
		return HIC "$N��ǰһ�������е�" NOR+HIG "������" NOR+HIC "�û�������ԲȦ��"
		       "�����������ǵذ�ѹ��$n��ֱ��\n"
		       "��$n��æ���ң�����ס�������ˡ�"NOR"\n";

	case 1:
		n = me->query_skill("staff");
		victim->receive_damage("qi", n, me);
		victim->receive_wound("qi", n, me);
		n = victim->query("eff_jing");
		n /= 2;
            if (n>=5000) n=5000;
		victim->receive_damage("jing", n, me);
		victim->receive_wound("jing", n/2, me);
		return random(2) ? HIG "$Nһ����Х�����е������Ȼ���һ����â����ৡ���ɨ"
				   HIG "��$n��"NOR"\n":
				   HIG "$NͻȻ�����ȵ������󱲣������ܣ������������Ⱥ���"
				   HIG "һ����$n��ʱ������ǰһ����"NOR"\n";
	}

	// double effect
	return damage_bonus;
}

void start_borrowing()
{
	remove_call_out("return_to_hong");
	call_out("return_to_hong", 7200 + random(600));
}

void return_to_hong()
{
	object me;

	me = environment();
	if (! objectp(me))
		return;

	while (objectp(environment(me)) && ! playerp(me))
		me = environment(me);
 
	if (playerp(me))
	{
		if (me->is_fighting())
		{
			call_out("return_to_hong", 1);
			return;
		}

		message_vision("��Ȼһ��ؤ��������˹���������$N��æ�к��������������"
			       "���������û������ȣ������ڲ�����ô����\n"
			       "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
			       "$N�������Ƚ���ؤ����Ӵ����ˡ�\n", me);
	} else
	{
		message("vision", "��Ȼһ��ؤ��������˹��������������ȣ�̾�˿�"
				  "����ҡҡͷ���ˡ�\n", me);
	}

	destruct(this_object());
}
