// bow.c

#include <ansi.h>

inherit ITEM;
inherit F_SSERVER;

void create()
{
	set_name("�̹�", ({ "short bow", "bow", "duan gong", "gong" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "һ�Ŷ̹����������Ϊ���£����в����׼ȷ�ȡ�\n");
		set("value", 20000);
		set("power", 100000);   // ��������
		set("accuracy", 120);   // ׼ȷ��120%
	}
	setup();
}

string long()
{
	string str;
	object arrow;
	str = ""+query("long");
	if(objectp(arrow=query_temp("inarrow")))
		str += "��׼�����Զ����䣺"+arrow->query("name")+"\n";
	else
		str += "��δ׼���Զ������֧��\n";
	str += ZJURL("cmds:inarrow")+ZJSIZE(22)+"׼����֧"NOR"\n";
	return str;
}

void init()
{
	if (this_player() == environment())
	add_action("do_shot", "shot");
	add_action("do_inarrow", "inarrow");
}

int do_inarrow(string arg)
{
	string item;
	object me;
	object *inv,ob;
	string msg;
	int i;

	me = this_player();
	if (me->query_temp("handing") != this_object())
		return notify_fail("����Ȱ�" + name() + "��(hand)�����в��С�\n");

	if (me->is_busy())
		return notify_fail("������æ���ء�\n");

	if (! arg)
	{
		inv = filter_array(all_inventory(me),(:$1->is_arrow():));
		if(!sizeof(inv))
			return notify_fail("������û�п��������������Ʒ��\n");

		msg = ZJOBLONG"��ѡ�����������������Ʒ��\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		for(i=0;i<sizeof(inv);i++)
		{
			msg += inv[i]->query("name")+":inarrow "+file_name(inv[i]);
			if(i<(sizeof(inv)-1)) msg += ZJSEP;
		}
		tell_object(me,msg+"\n");
		return 1;
	}

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û��������Ʒ��\n");

	if (! ob->is_arrow())
		return notify_fail("����Ʒ�޷������á�\n");

	if (ob->query_amount() < 1)
		return notify_fail("�����ϵ�" + ob->name() + "�������ˡ�\n");

	set_temp("inarrow",ob);

	return 1;
}
int do_shot(string arg)
{
	string target, item;
	object me, victim;
	object ob;
	object env;
	int amount;
	int my_exp, v_exp;
	int ap;
	string msg;

	me = this_player();
	if (me->query_temp("handing") != this_object())
		return notify_fail("����Ȱ�" + name() + "��(hand)�����в��С�\n");

	env = environment(me);
	if (! env || env->query("no_fight"))
		return notify_fail("���ﲻ��ս����\n");

	if (me->is_busy())
		return notify_fail("������æ���ء�\n");

	if (me->query("jing") < 80)
		return notify_fail("�����ھ��񲻹��ã��޷�ʹ��" + name() + "�������֡�\n");

	if( !me->is_fighting() )
		return notify_fail("��û����ս��������ʲô��\n");

	if (! arg)
	{
		if( !me->is_fighting() )
			return notify_fail("���빥��˭��\n");
		else if( !objectp(ob=query_temp("inarrow")) )
			return notify_fail("�㻹ûΪ����׼����֧��\n");
	}
	else if (sscanf(arg, "%s with %s", target, item) == 2)
	{
		if (! objectp(ob = present(item, me)))
			return notify_fail("������û�� " + item + " ������Ʒ���Է��䡣\n");
	}
	else
		return notify_fail("��Ҫ��ʲô�������֣�(shot <����> with <����>)\n");

	if (! ob->is_arrow())
		return notify_fail("�ⲻ�Ǽ������޷����䡣\n");

	if ((amount = ob->query_amount()) < 1)
		return notify_fail("�����ϵ�" + ob->name() + "�������ˡ�\n");

	if (target)
	{
		victim = present(target, env);
	}
	else
	{
		victim = offensive_target(me);
	}
	if(!victim||!objectp(present(victim, env)))
		return notify_fail("����û������ˡ�\n");

	if (! victim->is_character() || victim->query("not_living"))
		return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n");

	if (! me->is_fighting(victim))
		return notify_fail("��ֻ�����ս���еĶ��֡�\n");

	my_exp = me->query("combat_exp");
	v_exp = victim->query("combat_exp");

	if (my_exp < 10000)
		return notify_fail("��ʵս����̫ǳ����������" + name() + "������֡�\n");

	switch (random(3))
	{
	case 0:
		msg = "$Ņ��" + name() + "�����һ" + ob->query("base_unit") +
		      ob->name() + "����ಡ���һ������$n��\n";
		break;

	case 1:
		msg = "$N����һ�����һ" + ob->query("base_unit") +
		      ob->name() + "��ֱ��$n��ȥ��\n";
		break;

	default:
		msg = "ֻ����ಡ���һ���ƿ�����$N��׼$n���һ" + ob->query("base_unit") +
		      ob->name() + "��\n";
		break;
	}

	ap = my_exp * query("accuracy") / 100;
	if (userp(victim)) ap /= 2;

	if (v_exp / 2 + random(v_exp) > query("power") || ap < v_exp)
	{
		switch (random(3))
		{
		case 0:
			msg += "ȴ��$n����һ������$N��" + ob->name() + "���˿�ȥ��\n";
			break;
		case 1:
			msg += "ֻ��$n���Ų�æ������һŤ���㿪��$N��һ�С�\n";
			break;
		default:
			msg += "$n��������һ������$N��" + ob->name() + "���˸��ա�\n";
			break;
		}
	} else
	{
		msg += COMBAT_D->do_damage(me, victim, ob,
					   ob->query("weapon_prop/damage"), ob->query("wound_percent"),
					   HIR "ֻ��$p" HIR "һ�����ܲ���������$P"
					   HIR "��һ" + ob->name() + HIR "����ʱ��Ѫ�ɽ���"NOR"\n");
	}
	ob->add_amount(-1);
	me->start_busy(2);
	me->receive_damage("jing", 10);

	message_combatd(msg, me, victim);
	return 1;
}
