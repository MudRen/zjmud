// /guanwai/famu.c

#include <ansi.h>

inherit ROOM;

int start_work(object me, object ob);
varargs int end_working(object me, object passive);
int working(object me);
int coagent(object me);
int halt_working(object me, object who, int silent);

void create()
{
	set("short", "��ľ��");
	set("long", @LONG
������¹���������µ�һƬɭ�֣�����������Ĳ����������ֱͦ�Σ�
�����Ϻõ�ľ�ģ�����������￳��(famu)ľ�ϣ�Ȼ���˵���ԭ����ٹ���
�ǽ�����լ������ش���ɽ���֣�ʱ�������͵�Ұ�޳�û��
LONG );
	set("exits", ([
		"east"  : __DIR__"famu",
	]));
	set("outdoors", "guanwai");
	setup();
}

void init()
{
	add_action("do_famu", "famu");
	if (find_call_out("call_beast") == -1)
		call_out("call_beast", random(60) + 20);
}

void call_beast()
{
	object ob;
	string beast;
	int n;

	remove_call_out("call_beast");

	if (sizeof(filter_array(all_inventory(), (: interactive :))) < 1)
		return;

	// Call out wovles when player is here
	call_out("call_beast", random(200) + 30);

	if (present("he xiong", this_object()) ||
	    present("ye lang", this_object()))
		return;

	switch (random(10))
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		n = 1 + random(4);
		beast = __DIR__"npc/wolf";
		break;
	case 8:
	case 9:
		n = 1;
		beast = __DIR__"npc/bear";
		break;
	}

	message("vision", "ɽ������ͻȻ����" + chinese_number(n) +
		beast->query("unit") + beast->name() +
		"\n", this_object());
	while (n--)
	{
		ob = new(beast);
		ob->move(this_object());
	}
}

int do_famu(string arg)
{
	object me;
	object ob;
	object old;
	object weapon;

	me = this_player();

	if (! arg || sscanf(arg, "with %s", arg) != 1)
		return notify_fail("��Ҫ��˭һ��ľ(famu with <sb>)��\n");

	ob = present(arg, this_object());
	if (! ob)
		return notify_fail("����û������˿��Ժ���һ��ľ��\n");

	if (me == ob)
		return notify_fail("���ǲ��Ǵ��Խ�ˮ...��Ҫ����\n");

	if (wizardp(me))
		return notify_fail("��δ��Ҳ̫�����˰ѣ�\n");

	if (! living(ob))
		return notify_fail("����ôҲ�õ��˼��ѹ�����˵�ɣ�\n");

	if (ob->query_temp("job/famu"))
	{
		if (! ob->is_busy())
			ob->delete_temp("job/famu");
		else
			return notify_fail("�˼��������ڷ�ľ�ء�\n");
	}

	if (me->query_temp("job/famu"))
	{
		if (! me->is_busy())
			me->delete_temp("job/famu");
		else
			return notify_fail("�����ڲ������ڷ�ľ�\n");
	}

	if (ob->is_fighting())
		return notify_fail("�˼��������ڴ�ܣ����й������㣿\n");

	if (me->is_fighting())
		return notify_fail("�㻹�Ǵ����˼���˵�ɡ�\n");

	if (ob->is_busy())
		return notify_fail("�˼�������æ��û�������㡣\n");

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɡ�\n");

	if (ob->query("qi") < 200)
		return notify_fail("�˼��������ӣ��������˰ɡ�\n");

	if (me->query("qi") < 200)
		return notify_fail("��������Ϣ����������������������˵�ɡ�\n");

	if (ob->query_str() < 30)
		return notify_fail("���˼��Ǹ�ģ���������ܸ������ػ���ˡ�\n");

	if (me->query_str() < 30)
		return notify_fail("��������������ɲ��������ػ\n");

	if (ob->query_temp("pending/job_coagent") == me)
	{
		ob->delete_temp("pending/job_coagent");
		return start_work(me, ob);
	}

	if (objectp(old = me->query_temp("pending/job_coagent")))
	{
		if (old == ob)
			return notify_fail("���Ѿ���������Ҫ���ˣ������˼һ�û�д�Ӧ��\n");

		tell_object(old, me->name() + "�ı������ⲻ�����һͬ��ľ�ˡ�\n");
		tell_object(me, "��ı������ⲻ���" + old->name() + "һͬ��ľ�ˡ�\n");
	}

	me->set_temp("pending/job_coagent", ob);
	message_vision("$N��$n������������ɣ�" + RANK_D->query_respect(ob) +
		       "������һͬ��ľ��Σ���\n", me, ob);
	tell_object(ob, YEL + me->name() + "������һͬ��ľ�������"
		    "Ը���һ���(famu with " + me->query("id") + ")�ɡ�"NOR"\n");
	return 1;
}

int start_work(object me, object ob)
{
	object weapon, hand;
	object swap;

	hand = me->query_temp("handing");
	if (! objectp(hand) || ! hand->is_saw())
	{
		swap = me;
		me = ob;
		ob = swap;
		hand = me->query_temp("handing");
	}

	if (! objectp(hand) || ! hand->is_saw())
		return notify_fail("������˭��û���þ⣬��ô��ľ��\n");

	if ((! objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "axe") &&
	    (! objectp(weapon = ob->query_temp("weapon")) || weapon->query("skill_type") != "axe"))
		return notify_fail("����û�и�ͷ�����ɲ��갡��\n");

	me->set_temp("job/famu", 1);
	me->set_temp("job/step", 1);
	me->set_temp("job/coagent", ob);
	ob->set_temp("job/famu", 1);
	ob->set_temp("job/step", 1);
	ob->set_temp("job/coagent", me);
	me->start_busy(bind((: call_other, __FILE__, "working" :), me),
		       bind((: call_other, __FILE__, "halt_working" :), me));
	ob->start_busy(bind((: call_other, __FILE__, "coagent" :), me),
		       bind((: call_other, __FILE__, "halt_working" :), me));
	tell_object(me, "���" + ob->name() + "��ʼ��ľ��\n");
	tell_object(ob, "���" + me->name() + "��ʼ��ľ��\n");
	return 1;
}

private varargs int end_working(object me, object passive)
{
	object coagent;

	if (! me->query_temp("job/famu"))
		return 0;

	coagent = me->query_temp("job/coagent");
	me->interrupt_me(me, 1);
	me->delete_temp("job");
	if (objectp(passive))
	{
		message_vision("$n�����ˣ�$NҲֻ�ø���ͣ��������\n",
			       me, passive);
	}
	if (coagent) end_working(coagent, me);
	return 0;
}

int working(object me)
{
	object ob;
	object coagent;
	object weapon;
	object wood;
	string msg;
	string gmsg;
	int finish;
	int b;

	if (! me->query_temp("job/step"))
		me->set_temp("job/step", 1);

	if (! objectp(coagent = me->query_temp("job/coagent")))
	{
		message_vision("��æ�������ˣ�$Nֻ��ͣ�ֲ����ˡ�\n", me);
		return end_working(me);
	}

	if (! living(me))
	{
		return end_working(me);
	}

	ob = me->query_temp("handing");
	if (! objectp(ob) || ! ob->is_saw())
	{
		message_vision("��û�ˣ�$Nͣ�ֲ����ˡ�\n", me);
		return end_working(me);
	}

	finish = 0;
	switch (me->query_temp("job/step"))
	{
	case 1:
		me->receive_damage("qi", 20);
		msg = "$N���ܿ�����ѡ����һ���Ϻõ�������";
		break;
	case 2:
		me->receive_damage("qi", 20);
		msg = "$N��$n�ߵ������ԣ�������һ�£�Ȼ����" + ob->name() +
		      "��ʼ�������⡣";
		break;
	case 3:
		me->receive_damage("qi", 30);
		msg = "��֨��֨�¡���ľм����������˲���ľм��";
		break;
	case 4:
		me->receive_damage("qi", 30);
		msg = "����֨��֨����$N��$n�������⡣";
		break;
	case 5:
		me->receive_damage("qi", 30);
		msg = "��֨��֨�¡������ϵ�ľм��Խ��Խ�࣬��ҲԽ��Խ�";
		break;
	case 6:
		me->receive_damage("qi", 30);
		msg = "����֨��֨����$N��$n�������⡣";
		break;
	case 7:
		me->receive_damage("qi", 30);
		msg = "��֨��֨�¡�����Ȼ����������һ����������Щҡ�Ρ�";
		break;
	case 8:
		if (objectp(weapon = me->query_temp("weapon")) &&
		    weapon->query("skill_type") == "axe")
		{
			msg = "$N�ڰ��֣���$n������������ȥ���ǡ������ѡ��Ŀ���";
			break;
		}
		if (objectp(weapon = coagent->query_temp("weapon")) &&
		    weapon->query("skill_type") == "axe")
		{
			msg = "$n�ڰ��֣���$N������������ȥ���ǡ������ѡ��Ŀ���";
			break;
		}
		
		message_vision("�⵽������ϣ�ȴû�ҵ���ͷ��$N��$n"
			       "�ɵ��۾���ֻ��ͣ�֡�\n", me, coagent);
		return end_working(me);
	default:
		msg = "������֨ѽ֨ѽ���ĵ���������$N��$n��æ������";
		finish = 1;
		break;
	}
	msg += "\n";

	// send message out
	gmsg = replace_string(msg, "$N", "��");
	gmsg = replace_string(gmsg, "$n", coagent->name());
	tell_object(me, gmsg);
	gmsg = replace_string(msg, "$n", "��");
	gmsg = replace_string(gmsg, "$N", me->name());
	tell_object(coagent, gmsg);

	if (finish)
	{
		me->delete_temp("job");
		coagent->delete_temp("job");
		coagent->interrupt_me(coagent, 1);

		wood = new("/d/guanwai/obj/largewood");
		wood->move(this_object());

		if (me->query_dex() / 2 + random(me->query_dex() / 3) < 12)
		{
			message_vision("������Ȼ���أ�$N���ǲ���һ������"
				       "����ž����һ�°�$Nѹ�˸�����ʵʵ��\n", me);
			me->unconcious();
		} else
		if (coagent->query_dex() / 2 + random(coagent->query_dex() / 3) < 12)
		{
			message_vision("������Ȼ���أ�$N���ǲ���һ������"
				       "����ž����һ�°�$Nѹ�˸�����ʵʵ��\n", coagent);
			coagent->unconcious();
		} else
		{
			message_vision("������Ȼ���أ�$N��$nĨ��Ĩͷ"
				       "�ϵĺ�������һЦ��\n", me, coagent);

			if (wood->move(me))
			{
				message_vision(HIC "$N" HIC "���ˡ���һ������$n" HIC
					       "�İ����°�" + wood->name() + HIC
					       "����������"NOR"\n", me, coagent);
			} else
			if (wood->move(coagent))
			{
				message_vision(HIC "$n" HIC "���ˡ���һ������$N" HIC
					       "�İ����°�" + wood->name() + HIC
					       "����������"NOR"\n", me, coagent);
			} else
			{
				message_vision("$N��$n��ȥ���˵�ľ�ϣ�������̫"
					       "�أ�ֻ���ȷ��ڵ��ϡ�\n",
					       me, coagent);
			}
		}

		if (me->query("combat_exp") >= 100000 &&
		    me->query("combat_exp") < 500000)
		{
			// bonus to me
			b = 15 + random(10);
			me->add("combat_exp", b);
			me->improve_potential((b + 2) / 3);
			me->improve_skill("force", (b + 3) / 4);
			tell_object(me, HIC "\nͨ����ζ����������ѧ������ֽ�һ���������" +
				    chinese_number(b) +
				    "�㾭���" +
				    chinese_number((b + 2) / 3) +
				    "��Ǳ�ܡ�"NOR"\n");
		}

		if (coagent->query("combat_exp") >= 100000 &&
		    coagent->query("combat_exp") < 500000)
		{
			// bonus to coagent
			b = 15 + random(10);
			coagent->add("combat_exp", b);
			coagent->improve_potential((b + 2) / 3);
			coagent->improve_skill("force", (b + 3) / 4);
			tell_object(coagent, HIC "\nͨ����ζ����������ѧ������ֽ�һ���������" +
				    chinese_number(b) +
				    "�㾭���" +
				    chinese_number((b + 2) / 3) +
				    "��Ǳ�ܡ�"NOR"\n");
		}

		return 0;
	} else
		me->add_temp("job/step", 1);

	return 1;
}

int coagent(object me)
{
	return 1;
}

int halt_working(object me, object who, int silent)
{
	if (! me->query_temp("job/famu"))
		return 1;

	if (! silent)
		message_vision("$N̾�˿����������������ˣ���"
			       "��������磡��\n", me);
	end_working(me);
	return 1;
}
