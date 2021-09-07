#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(HIW "����" NOR, ({ "yin zhen" , "yin", "zhen" }) );
	set_weight(200);

	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "ö");
		set("long", HIW "����һö���糤�����룬ϸ�����ͣ���Ϊҽ��"
			    "��Ѩ����֮�á����������������ҽ�߶�Ϊ����\n"
			    "��ҽ�����������ڹ���������������������"
			    "(zhenjiu)���ˡ�"NOR"\n");
		set("value", 0);   
		set("icon","05080");	   
		set("yingdu", 50);
		set("base_unit", "ö");
		set("base_weight", 10);
		set("base_value", 0);
		set("material","crimsonsteel");
	}
	set_amount(1);
	init_throwing(30);
	setup();
}

void init()
{
	add_action("do_heal", "zhenjiu");
}

int do_heal(string arg)
{
	object me, ob;
	int damage, heals, i;
	int exp, pot;
	int flag;
	string msg, s;
	write( L_ICON("05080")); 
	me = this_player();
	if (me->query_skill("zhenjiu-shu", 1) < 1 )
		return notify_fail("���������ûѧ��ȥɱ�˰���\n");

	if (this_object() != me->query_temp("handing"))
		return notify_fail("�����������������������ġ�\n");

	if (! arg || ! objectp(ob = present(arg, environment(me))))
		return notify_fail("�����˭ʩ���������\n");

	if (! ob->is_character() || ob->query("not_living")) 
		return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n"); 

	if (! living(ob))
		return notify_fail("�㻹�ǵ�������֮�������ưɡ�\n");

	if (ob->query("no_zhenjiu"))
		return notify_fail("�˼Ҳ��������ĺ��⡣\n");

	flag = 0;

	if (! playerp(ob))
	{
		if (me->query_skill("zhenjiu-shu", 1) < 60)
		{
			message_vision( HIY "$N" HIY "�����$n" HIY "���ˣ���$n"
					HIY "����$N" HIY "�ǲ�ͣ������˫�֣�����"
					"¶�����µ���ɫ��"NOR"\n" + CYN "$n" CYN
					"������üͷ����$N" CYN "˵�������ǵ�����"
					"�������˰ɡ�\n", me, ob);
			return 1;
		}
	} else
	{
		if (ob != me && playerp(ob))
		{
			if (! is_sub(me->query("id"), ob->query("env/can_accept")))
			{
				// user refuse to accept
				return notify_fail("�˼����ڲ��������ĺ��⡣\n");
			}
			flag = 1;
		}
	}

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (me->is_fighting() || ob->is_fighting())
		return notify_fail("ս���л������ˣ�����������\n");

	if (ob->is_killing(me->query("id")))
		return notify_fail("�˼Ҳ�������������ġ�\n");

	if (ob->query_skill("force") >= 150)
		return notify_fail("�˼��ڹ���񣬲�ָ�����������ˡ�\n");

	if ((ob->query("max_qi") * 5 / 100 > ob->query("eff_qi")))
		return notify_fail("���ڴ������˹��أ�ʩ�����̫Σ���ˣ�\n");   

	if (ob->query("max_qi") == ob->query("eff_qi"))
	{
		if(me != ob)
			return notify_fail("���˲�û�����ˣ�\n");
		else
			message_vision(HIW "$N" HIW "�������Լ��������飬������Լ�"
				       "�������ˮƽ��"NOR"\n", me);
	}

	if (me->query("neili") < 80)
		return notify_fail("����������㣬�޷�ʹ�������Ϊ�����ˣ�\n");

	if (me->query("jing") < 50)
		return notify_fail("��ľ����㣬�޷����о�����\n");

	if (time() - ob->query_temp("last/zhenjiu") < 60)
		return flag = 1;

	ob->set_temp("last/zhenjiu", time());

	me->add("neili", -50);
	me->add("jing", -30);
	me->start_busy(1 + random(1));
	me->improve_skill("zhenjiu-shu", 5 + random(30));
	tell_object(me, HIC "��ʵ����������ġ������������ˣ�"NOR"\n");

	if (me == ob) s = "$N";
		 else s = "$n";

	msg = HIW "$N" HIW "�������룬С���������" + s + HIW "��Ѩ����ȥ��"NOR"\n";

	if (random(120) > (int)me->query_skill("zhenjiu-shu", 1))
	{
		damage = 1 + random(ob->query("max_qi") / 2);		
		i = ob->query("max_qi") * 10 / damage;

		if (i > 100)
			msg += CYN "����$N" CYN "������ƫ��û����Ѩ����" + s +
			       CYN "����¶��һ˿�ѹ������顣" NOR;
		else
		{
			if (i > 40)
				msg += RED "����$N" RED "�������ͣ���Ȼ�̳���"
				"Ѫ�����������еĴ�ɣ�" NOR;
			else
				msg += RED "$N" RED "������ȥ�ŷ��̴ִ���Ѩ����"
				+ s + RED "���ۡ��������һ����Ѫ��" NOR;
		}

		ob->receive_wound("qi", damage);		
		damage = i;
	} else
	{
		msg += HIW "$N" HIW "������׼ȷ����Ĵ���Ѩ������������Ļ���ת"
		       "����" + s + HIW "�����ĳ���һ��������ɫ�ÿ����ˡ�"NOR"\n";

		damage = -1;

		if (me != ob && me->query("combat_exp") < 200000 &&
		    ! flag)
		{
			exp = 10 + random(30);
			pot = 5 + random(10);

			me->add("combat_exp", exp);
			me->add("potential", pot);
			if (me->query("potential") > me->query_potential_limit())
				me->set("potential", me->query_potential_limit());

			tell_object(me, HIC "������" + chinese_number(exp) +
				"�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�"NOR"\n");
		}

		heals = me->query_skill("zhenjiu-shu", 1) + random(me->query_skill("zhenjiu-shu", 1));

		if ((ob->query("eff_qi") + heals) > ob->query("max_qi"))
			ob->set("eff_qi", ob->query("max_qi"));
		else
			ob->add("eff_qi", heals / 3);
	}

	msg += "\n";
	
	if (me == ob)
		message_vision(msg, me);
	else
		message_vision(msg, me, ob);

	if (damage > 0)
	{
		if (ob->query("qi") < 0)
		{
			ob->set("eff_qi", 1);
			ob->set("qi", 1);

			if (playerp(ob))
			{
				if (me == ob)
					message_vision(HIR "���հ���$N" HIR "��һ����Լ���"
						       "����"NOR"\n", me);
				else
					message_vision(HIR "���հ���$N" HIR "��һ���$n" HIR
						       "������\n", me,ob);
			}
		} else
		{
			if (me != ob)
			{
				if (random(damage) < 40)
				{
					message_vision(HIR "$N" HIR "ʹ�á����ۡ���в�ֹ��"
						       "ŭ������Ȼ���¶��֣�����ɱ���Ұ���"NOR"\n", ob);

					ob->kill_ob(me);
					me->fight_ob(ob);
				} else
				{
					message_vision(HIR "$N" HIR "���ۡ��Ĵ��һ������"
						       "���ص�����ʹ�����´����ǧ���ĵ�"
						       "��\n",ob);
				}
			}
		}
	}

	return 1;
}
