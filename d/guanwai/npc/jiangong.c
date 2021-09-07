// jiangong �๤

#include <ansi.h>

inherit NPC;

mixed ask_mine();
mixed ask_transit();
int   do_mine(string arg);
int   working(object me);
int   halt_working(object me);

void create()
{
	set_name("�๤", ({ "jian gong", "jiangong" }));
	set("long", "����һ���๤���۹ⲻ����˸����֪���ڴ�ʲô�����⡣\n");
	set("gender", "����");
	set("age", 38);
	set("no_get", 1);
	set_skill("unarmed", 100);

	set_temp("apply/attack", 100);
	set_temp("apply/damage", 100);

	set("combat_exp", 500000);
	set("shen_type", 1);
	set("inquiry", ([
		"�ɿ�" : (: ask_mine :),
		"�˻�" : (: ask_transit :),
	]));
	setup();

	set("chat_chance", 1);
	set("chat_msg", ({
		"�๤�ȵ����죡����Ҹɣ�\n",
		"�๤һ����ӣ�����������̵ģ�����ҷ���ʵ�㡣\n",
		"�๤���������ܣ���֪���ڴ�ʲô���⡣ \n",
		"�๤�ݺݵĳ���һ���˼��£��������ô��ʯͷ���������ˣ����Ɀ����\n",
	}));
}

void init()
{
	add_action("do_mine", "move");
	add_action("do_mine", "mine");
}

mixed ask_mine()
{
	object me;
	object *obs;

	me = this_player();
	if (me->query_temp("job/move"))
		return "������ʯ�������û�У��ٺ����ҳ����㣡";

	if (me->query("combat_exp") < 1500)
		return "����㾭��Ҳ����ʯ���죿���һ��翴�㲻˳�۾Ͱ���ŵ��ˡ�";

	if (me->query("combat_exp") > 25000)
		return "������Ҳ����ʯͷ���������ˣ��һ��������˰ɣ�";

	if (me->query("qi") < 60)
		return "�ҿ�������������������������˰ɣ��ҿɲ����ֳ���������";

	if (me->query_str() < 25)
		return "��˵���ж��������Ҳ�������֣�";

	if (! interactive(me))
		return "...";

	obs = filter_array(all_inventory(environment()),
			   (: interactive($1) &&
			      $1 != $(me) &&
			      $1->query_temp("job/move") &&
			      query_ip_number($1) == query_ip_number($(me)) :));
	if (sizeof(obs) > 0)
		return "�����Ѿ���" + obs[0]->name() + "�ɻ��أ���Ъ�Űɡ�";

	me->set_temp("job/move", 1);
//	if(me->query("zjvip/level")&&me->query_temp("tuoguan/caishi"))
		tell_object(me,ZJFORCECMD("move"));
	tell_object(me,ZJEXIT"northwest:"RED"ֹͣ�ɿ�"NOR":halt\n");
	return "�ã����ȥɽ��"ZJURL("cmds:move")ZJSIZE(15)"��ʯ��"NOR"����(move)�����⹤�ʿɲ���Ŷ��";
}

int do_mine(string arg)
{
	object me;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ���أ����ż���\n");

	if (! me->query_temp("job/move"))
		return notify_fail("����û��Ϲæ��ɶ��\n");

	me->set_temp("job/step", 1);
	me->start_busy(bind((: call_other, __FILE__, "working" :), me),
		       bind((: call_other, __FILE__, "halt_working" :), me));
	tell_object(me, "�㿪ʼ������\n");
	return 1;
}

int working(object me)
{
	string msg;
	int finish;
	int b;

	if (! me->query_temp("job/step"))
		me->set_temp("job/step", 1);

	if (! living(me))
	{
		me->delete_temp("job/move");
		me->delete_temp("job/step");
		return 0;
	}

	finish = 0;
	switch (me->query_temp("job/step"))
	{
	case 1:
		me->receive_damage("qi", 1);
		msg = "$N�첽�ĳ�ɽ����ȥ��";
		break;
	case 2:
		me->receive_damage("qi", 1);
		msg = "$N�ߵ�ɽ����������������ʯ�ϵġ�";
		break;
	case 3:
		me->receive_damage("qi", 1);
		msg = "�����Ĺ���ɨ��$Nһ�ۣ��ƺ�û������һ�������ֵ����ˣ��Ƕ���ȥ�Ƕ��ᡣ";
		break;
	case 4:
		me->receive_damage("qi", 6);
		msg = "$N�ϵ����Ƶĵط���ѡ��һ���������Լ���ʯ�ϣ����ڼ�ͷ��";
		break;
	case 5:
	case 7:
	case 9:
		me->receive_damage("qi", 8);
		msg = "$N����ʯ�ϣ�һ��һ����ɽ�°���";
		break;
	case 6:
		me->receive_damage("qi", 9);
		msg = "$N���˿��������˵��ͷ��ʯ�ϣ�����ǰ����";
		break;
	case 8:
		me->receive_damage("qi", 10);
		msg = "$N���ü�ͷ��ʯ��Խ��Խ�أ�ֻ�û�һ�¼翸��";
		break;
	default:
		me->receive_damage("qi", 5);
		msg = "$N��ʯ�Ͽ���$n�����ʯ��װ�ϳ��ӣ��������˿�����";
		finish = 1;
		break;
	}
	msg += "\n";

	if (finish)
	{
		object ob;
		if (me->query_str() >= 30)
			msg += "$n����$N���ʯ�ϣ��ȵ�������������ô���ʯ��Ҳ�������ˣ�\n";
		else
			msg += "$n����$N���ʯ�ϣ������У��ɵò���������������Ĺ�Ǯ��\n";
		me->delete_temp("job/move");
		me->delete_temp("job/step");

		// ����ʯ������
		environment(me)->improve_product_amount("stone",15 + (me->query_str() - 30) * 4 + random(8));

		b = 7 + random(4);
		me->add("combat_exp", b);
		me->improve_potential((b + 2) / 3);
		me->improve_skill("unarmed", (b + 1) / 2);

		ob = new("/clone/money/coin");
		ob->set_amount(100 + (me->query_str() - 25) * 10);
		ob->move(me, 1);
	}

	message_vision(msg, me, this_object());
	if (finish)
	{
		if (b > 0)
		{
			tell_object(me, HIC "\n������" + chinese_number(b) + "�㾭���" + chinese_number((b + 2) / 3) + "��Ǳ�ܡ�"NOR"\n");
		}
		if( (int)me->query("qi") < 60 )
		{
			SKILL_D("force/recover")->exert(me, me);
		}
//		if(me->query("zjvip/level")&&me->query_temp("tuoguan/caishi"))
		if(!interactive(me)) return 0;
			tell_object(me,ZJFORCECMD("ask "+this_object()->query("id")+" about �ɿ�"));
		return 0;
	}

	me->add_temp("job/step", 1);
	return 1;
}

int halt_working(object me)
{
	if (me->query_temp("job/step") >= 4)
	{
		message_vision("$N�Ѽ�ͷ��ʯ��һ�ԣ��������ֵ����������ˣ��治���˸ɵĻ\n", me);
	} else
	{
		message_vision("$N̾�˿������������첻���ˣ�\n", me);
	}

	me->delete_temp("job/move");
	me->delete_temp("job/step");
	return 1;
}

mixed ask_transit()
{
	string startroom;
	int c;
	object ob;
	object me;
	int amount;

	if (! stringp(startroom = query("startroom")) ||
	    find_object(startroom) != environment())
		return "��...���е�ͷ��...";

	me = this_player();

	if (me->query("score") < 1000)
		return "������������Щǳ��Ҳ�ҽ����ʹ��";

	if (me->query("combat_exp") < 30000)
		return "һ�߶�ȥ�������˱���̫��ҿɲ���������Ѻ����";

	if (objectp(me->query_temp("job/gw_cart")))
		return "�ϴ������͵���������ô����ȥ�������£�";

	if ((amount = me->query("job/gw_stone")) > 0)
	{
		amount = (amount + 99) / 20;
		// ����(MUDʱ��)��������ﻹû���ʹ������
		message_sort("$N��Цһ������$n������" + me->name(1) +
			     "���ϴ����͵�ʯ��... �ߣ��㱾��"
			     "��΢������Ҳ����׷���ˣ�����"
			     "��һ��ʯ�����ܾ������װ׵Ķ���"
			     "����������" + chinese_number(amount) +
			     "��������˵����\n",
			     this_object(), me);
		return 1;
	}

	c = environment(me)->query_product_amount("stone");
	if (c < 800)
		return "���ڻ�û�ж���ʯ���أ���æ���ߣ���ȵȰɡ�";
	else
	if (c < 1200)
		message_vision("$N���˿�$n��������Ҳ�ã���Ȼ"
			       "���ڻ����࣬����Ҳ����ˡ���\n",
			       this_object(), me);
	else
	if (c < 2000)
		message_vision("$N���ͷ����$n�������ðɣ���"
			       "����һ���ˣ��ͷ��˰ɡ���\n",
			       this_object(), me);
	if (c < 10000)
		message_vision("$N����$n���к����������ã���"
			       "���㷢���أ��������ɣ���\n",
			       this_object(), me);
	else
	if (c < 30000)
		message_vision("$N��æ��������׼���ɣ�������"
			       "���кü����ˣ���\n",
			       this_object(), me);
	else
		message_vision("$N����$n����ϲ���������ã���"
			       "��������Ҫ���ˣ����������ã���\n",
			       this_object(), me);

	if (c > 3000) c = 3000;
	environment(me)->improve_product_amount("stone", -c);

	// ���ɽ�ͨ����
	ob = new("/clone/misc/cart");
	ob->set_temp("goods/name", "ʯ��");
	ob->set_temp("goods/id",   "stone");
	ob->set_temp("goods/unit", "��");
	ob->set_temp("goods/amount", c);
	message_sort("$Nߺ�������������ƹ�һ" + ob->query("unit") + ob->name() + "������ͷ��" + me->name() +
		     "��������������⳵�����͵���������ʯ��ȥ������ʯͷ����Ǯ������һ��Ҫ���������\n",
		     this_object(), me);
	tell_object(me, YEL + name() + "������һ" + ob->query("unit") + ob->name() + "��"NOR"\n");
	ob->move(environment(me));
	ob->set_owner(me);

	// ��¼����������Ϣ
	me->set("job/gw_stone", c);
	me->set_temp("job/gw_cart", ob);
	ob->set_temp("job/info", "gw_stone");
	ob->set_temp("job/owner", me);

	return 1;
}

int accept_object(object who, object ob)
{
	int amount;

	if (! ob->query("money_id"))
		return 0;

	if ((amount = who->query("job/gw_stone")) > 0)
	{
		amount = (amount + 99) / 20;
		if (ob->value() < amount * 100)
		{
			message_vision("$N���˿�$n�ݹ�����Ǯ�����"
				       "����������㣿һ�߶�ȥ����\n",
				       this_object(), who);
			return 0;
		}

		message_vision("$N���Ӻ���һ�����ӹ�" + ob->name() +
			       "�����������ˣ��Ͳ�׷�����ˡ���\n",
			       this_object(), who);
		who->delete("job/gw_stone");
	} else
	{
		message_vision("$Nü����Ц����" + ob->name() +
			       "���˹�����������ң�ȴ�����$n��\n",
			       this_object(), who);
	}

	destruct(ob);
	return -1;
}

