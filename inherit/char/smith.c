// smith.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_me();
int  do_stop(string arg);
int  do_gu(string arg);
int  do_dapi(string arg);
int  do_cuihuo(string arg);
int  do_repair(string arg);
void reward(object me);

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_gu", "gu");
	add_action("do_stop", "stop");
	add_action("do_dapi", "dapi");
	add_action("do_cuihuo", "cuihuo");
	add_action("do_repair", "repair");
	add_action("do_repair", "xiuli");
}

void setup()
{
	set("inquiry/����",    (: ask_me :));
	set("inquiry/����",   "����Ҫ��(repair)��ʲô��");
	::setup();
}

string ask_me()
{
	object me = this_player();

	if (me->is_busy())
		return "���Ȱ���ͷ�����¶�æ����˵�ɣ�";

	if (me->query("combat_exp") > 1500000)
		return "�����ϸ����δ�������˰ɣ�";

	if (me->query("qi") < 40)
		return "�㻹��Ъ����ɣ�Ҫ�ǳ��������ҿɳе�����";

	if (me->query_temp("smith/gu"))
		return "����"ZJURL("cmds:gu")+ZJSIZE(15)"���ġ�"NOR"���䣬����ô��ĥ��(gu)��";

	if (me->query_temp("smith/dapi"))
		return "����������"ZJURL("cmds:dapi")+ZJSIZE(15)"����"NOR"��û��(dapi)��";

	if (me->query_temp("smith/cuihuo"))
		return "�ɻ���ô��͵���������"ZJURL("cmds:cuihuo")+ZJSIZE(15)"�����"NOR"ȥ(cuihuo)��";

	me->set_temp("pending/auto_tie",1);
	switch(random(3))
	{
	case 0:
		me->set_temp("smith/gu", 1);
//		if(me->query("zjvip/level")&&me->query_temp("pending/auto_tie"))
			tell_object(me,ZJFORCECMD("gu"));
		return "�ã������"ZJURL("cmds:gu")+ZJSIZE(15)"���ġ�"NOR"һ�������(gu)��";

	case 1:
		me->set_temp("smith/dapi", 1);
//		if(me->query("zjvip/level")&&me->query_temp("pending/auto_tie"))
			tell_object(me,ZJFORCECMD("dapi"));
		return "�����ɣ������"ZJURL("cmds:dapi")+ZJSIZE(15)"����"NOR"һ������(dapi)��";

	case 2:
		me->set_temp("smith/cuihuo", 1);
//		if(me->query("zjvip/level")&&me->query_temp("pending/auto_tie"))
			tell_object(me,ZJFORCECMD("cuihuo"));
		return "ȥ���Ұ���Щ�ճ�¯��"ZJURL("cmds:cuihuo")+ZJSIZE(15)"���㡿"NOR"һ�»�(cuihuo)��";
	}
}

int do_gu(string arg)
{
	object me = this_player();
	int skill_exp;
	if (me->is_busy())
		return notify_fail("��������æ��\n");

	if (! me->query_temp("smith/gu"))
	{
		message_vision("$n��͵͵������ķ�������˼���硣������$N��$n��ȵ����������Ҹ�ʲô��\n",this_object(), me);
		return 1;
	}

	message_vision("$n����ķ��ƴ������������$N���˵��˵�ͷ��\n",this_object(), me);
	skill_exp=me->query_int()/10 + random(2);
	me->improve_skill("force",skill_exp);
	write(HIG"����<�ķ�>�ж�<����>��������\n[�����ڹ�] ���������� +"+skill_exp+""NOR"\n");
	call_out("reward",5,me);
	me->start_busy(5);
	return 1;
}

int do_dapi(string arg)
{
	object me = this_player();
	int skill_exp;
	if (me->is_busy())
		return notify_fail("��������æ��\n");

	if (! me->query_temp("smith/dapi"))
	{
		message_vision("$n���𼸿���������������˵ࡣ������$N��$n��ȵ������£��Ҹ�ʲô��\n",this_object(), me);
		return 1;
	}

	message_vision("$n���Ŵ��ӶԸճ�¯�Ļ��ȵ����������ô��ţ�$N���š���һ��������ȥ��Щ���⡣\n",this_object(), me);
	skill_exp=me->query_int()/10 + random(2);
	me->improve_skill("unarmed",skill_exp);
	write(HIG"����<����>�ж�<ȭ������>������\n[����ȭ��] ���������� +"+skill_exp+""NOR"\n");
	call_out("reward",5,me);
	me->start_busy(5);
	return 1;
}

int do_cuihuo(string arg)
{
	object me = this_player();
	int skill_exp;
	if (me->is_busy())
		return notify_fail("��������æ��\n");

	if (! me->query_temp("smith/cuihuo"))
	{
		message_vision("$n�ճ���һ������õ����ӣ�������$N��$n��ȵ������£�����Ҹ㻵�ˡ�\n",this_object(), me);
		return 1;
	}

	message_vision("$N����ǯ����һ��������ӣ������ˮ�أ����ꡱ��һ��������ð��\n",me);
	skill_exp=me->query_int()/10 + random(2);
	me->improve_skill("dodge",skill_exp);
	write(HIG"����<���>�ж�<��תŲ��>������\n[�����Ṧ] ���������� +"+skill_exp+""NOR"\n");
	call_out("reward",5,me);
	me->start_busy(5);

	return 1;
}

void reward(object me)
{
	object coin;
	int exp_add;
	me->delete_temp("smith/gu");
	me->delete_temp("smith/dapi");
	me->delete_temp("smith/cuihuo");

			     
      message_vision("$N��$n�������Ǹ���Ĺ�Ǯ��\n",this_object(), me);
	
	if (me->query("combat_exp") < 1500000)
	{
      	exp_add= 10 + random(11);
	coin = new("/clone/money/coin");
	coin->set_amount(exp_add*3/2);
	coin->move(me);
//      	command("give coin to " + me->query("id"));
		write(HIG"�����๤����ã� ͭ�壺+"+exp_add*3/2+"  ���飺+"+exp_add+"  ������+1\n"NOR);
		me->add("score", 1);//me->improve_potential(exp_add*2);
		me->add("combat_exp", exp_add);
	}
	me->receive_damage("qi", 25 + random(10));
	if(me->query_temp("pending/auto_tie"))
	{
		write(ZJEXIT"northwest:"RED"�����й�"NOR":stop\n");
		write(YEL"�й��У��Ժ��������������"NOR"\n");
		call_out("auto_ask",5,me);
	}
}

void auto_ask(object me)
{
	if(!me||!interactive(me)) return;
	if(me->is_busy()||me->query("qi") < 40)
		call_out("auto_ask",3,me);
	else if(present(me,environment(this_object())))
		tell_object(me,ZJFORCECMD("ask "+this_object()->query("id")+" about ����"));
}

int do_stop(string arg)
{
	if(this_player()->query_temp("pending/auto_tie"))
	{
		write(YEL"�����йܡ�����"NOR"\n");
		this_player()->delete_temp("pending/auto_tie");
	}
	return 1;
}

int do_repair(string arg)
{
	object me;
	object ob;
	mixed  msg;
	int consistence;
	int cost;
	mapping repair;

	if (! arg)
		return 0;

	me = this_player();
	if (! objectp(ob = present(arg, me)))
		return notify_fail("�����Ϻ���û������������\n");

	if (undefinedp(consistence = ob->query("consistence")))
		return notify_fail(ob->name() + "�ƺ�����Ҫ����������ɣ�\n");

	if (consistence >= 100)
		return notify_fail(ob->name() + "�����������������ʲô��\n");

	if (! undefinedp(msg = ob->query("no_repair")))
	{
		if (stringp(msg))
			write(name() + "�������ҿ������ˡ�\n");
		else
			write(name() + "����" + msg);
		return 1;
	}

	if (mapp(repair = me->query_temp("pending/repair")) && repair["item"] == ob)
	{
		if (me->is_busy())
			return notify_fail("��������æ���أ�\n");

		notify_fail("���ȴ�����Ǯ��˵��\n");
		if (MONEY_D->player_pay(me, repair["cost"]) != 1)
			return 0;

		message_vision("$n��" + ob->name() + "�ݸ���$N��ֻ��$N���𹤾ߣ�������������" + ob->name() + "�������ޡ�\n", this_object(), me);
		ob->set("consistence", 100);
		message_vision("$N���������ˣ������ְ�" + ob->name() + "��$n��$n���˿���������ͳ���һЩǮ�����ʡ�\n", this_object(), me);
		me->start_busy(1 + random(100 - consistence) / 10);
		me->delete_temp("pending/repair");
		return 1;
	}

	cost = ob->query("magic/power")+ob->query("point")+ob->level_now(1)*30;
	if(cost<80) cost = 80;
	cost *= 1000;
	cost = (100 - consistence)*cost/100;

	msg = "$n�ó�һ" + ob->query("unit") + ob->name() + "��$NƳ��һ�ۣ�������Ҫ�޺�����Ҫ" + MONEY_D->price_str(cost) + "���С���\n";
	message_vision(msg, this_object(), me);	
	tell_object(me, YEL "��"ZJSIZE(20)+ZJURL("cmds:repair"+arg)"ȷ��"NOR+YEL"�뻨��"+MONEY_D->price_str(cost)+"����"+ob->name()+"��"NOR"\n");
	me->set_temp("pending/repair/item", ob);
	me->set_temp("pending/repair/cost", cost);
	return 1;
}
